#include "Network/ServerHandler.hh"
#include "Network/ServerReceiver.hh"
#include "Network/Server.hh"

ServerHandler::ServerHandler(clientArray &clients, packetStack &packetStack, std::mutex &mutex, std::mutex &signalMutex, std::condition_variable &packetsWaiting, std::condition_variable &clientsReady, ServerReceiver &receiver) : Handler(packetStack, mutex, signalMutex, packetsWaiting), _clients(clients), _clientsReady(clientsReady), _receiver(receiver)
{
	_functors = {
		{ Packet::Code::Client::Ready, &ServerHandler::setClientReady },
		{ Packet::Code::Client::Message, &ServerHandler::broadcastMessage },
		{ Packet::Code::Client::Drop, &ServerHandler::kickPlayer }
	};
}

ServerHandler::~ServerHandler()
{

}

void ServerHandler::processLoop()
{
	std::shared_ptr<Packet> packet;

	while (!_quit)
	{
		std::unique_lock<std::mutex> lock(_signalMutex);
		while (_packetStack.empty() && !_quit)
		{
			_packetsWaiting.wait(lock);
		}
		for (int8_t i = 0; i < _clients.size(); i++)
		{
			if (_clients[i].second.autoHandle == false) //Client handled manually
				continue;
			packet = extractPacket(_clients[i].second.id);
			if (packet == nullptr) //No packet
				continue;
			packetFunctor f = _functors[packet->code];

			(this->*f)(packet);
		}
	}
}

void ServerHandler::broadcastMessage(std::shared_ptr<Packet> packet)
{
	std::string msg = packet->getData<std::string>();

	Packet::broadcast(_clients, Packet::Code::Client::Message, -1, packet->clientId, msg);
}

void ServerHandler::kickPlayer(std::shared_ptr<Packet> packet)
{
	clientNode &client = Server::getClient(packet->clientId);
	int8_t droppedClientId = packet->getData<int8_t>();
	clientNode &droppedClient = Server::getClient(droppedClientId);

	if (client.second.host == true)
	{
		Packet::broadcast(_clients, Packet::Code::Client::Drop, -1, droppedClient.second.id);
		_receiver.dropClient(droppedClient);
	}
}