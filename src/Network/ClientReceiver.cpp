#include "Network/ClientReceiver.hh"

using namespace stb;

ClientReceiver::ClientReceiver(packetStack &packetStack, std::mutex &mutex, std::mutex &signalMutex, std::condition_variable &packetsWaiting) : Receiver(packetStack, mutex, signalMutex, packetsWaiting)
{
}

ClientReceiver::~ClientReceiver()
{

}

void ClientReceiver::receiveLoop()
{
	std::shared_ptr<sf::Packet> data;
	sf::Socket::Status status;

	while (!_quit)
	{
		data = std::make_shared<sf::Packet>();
		status = _socket->receive(*data);
		if (status == sf::Socket::Disconnected)
		{
			//DBWEngine::getInstance<DBWEngine>()->abortClient("Lost connection to host");
			return;
		}
		else if (status == sf::Socket::Done)
		{
			std::shared_ptr<Packet> packet = std::make_shared<Packet>(data, false);
			insertPacket(packet);
		}
	}
	//DBWEngine::getInstance<DBWEngine>()->abortClient();
}

void ClientReceiver::start(std::shared_ptr<sf::TcpSocket> socket)
{
	_quit = false;
	_socket = socket;
	_socket->setBlocking(false);
	_thread = std::make_shared<std::thread>(&ClientReceiver::receiveLoop, this);
}