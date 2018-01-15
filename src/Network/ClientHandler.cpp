#include "Network/ClientHandler.hh"

ClientHandler::ClientHandler(sf::TcpSocket &socket, packetStack &packetStack, std::mutex &mutex, std::mutex &signalMutex, std::condition_variable &packetsWaiting) : Handler(packetStack, mutex, signalMutex, packetsWaiting), _socket(socket)
{
	_functors = {
		{Packet::Client::Ready, &ClientHandler::togglePlayerReady},
		{Packet::Describe::Player, &ClientHandler::getPlayer},
		{Packet::Client::Drop, &ClientHandler::dropPlayer},
		{Packet::Client::Message, &ClientHandler::getMessage},
		{Packet::Server::Full, &ClientHandler::disconnect},
		{Packet::Server::Start, &ClientHandler::startGame}
	};
}

ClientHandler::~ClientHandler()
{

}

void ClientHandler::processLoop()
{
	std::shared_ptr<Packet> packet;

	while (!_quit)
	{
		std::unique_lock<std::mutex> lock(_signalMutex);
		while (_packetStack.empty() && !_quit)
		{
			_packetsWaiting.wait(lock);
		}
		packet = extractPacket();
		if (packet == nullptr)
			continue;
		packetFunctor f = _functors[packet->code];

		(this->*f)(packet);
	}
}