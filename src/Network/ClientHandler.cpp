#include "Network/ClientHandler.hh"

ClientHandler::ClientHandler(sf::TcpSocket &socket, packetStack &packetStack, std::mutex &mutex, std::mutex &signalMutex, std::condition_variable &packetsWaiting) : Handler(packetStack, mutex, signalMutex, packetsWaiting), _socket(socket)
{
	_functors = {
		{Packet::Code::Client::Ready, &ClientHandler::togglePlayerReady},
		{Packet::Code::Describe::Player, &ClientHandler::getPlayer},
		{Packet::Code::Client::Drop, &ClientHandler::dropPlayer},
		{Packet::Code::Client::Message, &ClientHandler::getMessage},
		{Packet::Code::Server::Full, &ClientHandler::disconnect},
		{Packet::Code::Server::Start, &ClientHandler::startGame}
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