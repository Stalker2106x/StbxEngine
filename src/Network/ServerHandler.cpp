#include "Network/ServerHandler.hh"
#include "Network/ServerReceiver.hh"
#include "Network/Server.hh"

using namespace stb;

ServerHandler::ServerHandler(clientArray &clients, packetStack &packetStack, std::mutex &mutex, std::mutex &signalMutex, std::condition_variable &packetsWaiting, std::condition_variable &clientsReady, Server &server) : Handler(packetStack, mutex, signalMutex, packetsWaiting), _clients(clients), _clientsReady(clientsReady), _server(server)
{
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
			packetFunctor<Server> f = _functors[packet->code];

			f(packet);
		}
	}
}