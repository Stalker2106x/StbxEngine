#ifndef CLIENT_HH_
#define CLIENT_HH_

#include <iostream>
#include <thread>
#include <mutex>
#include <SFML/Network.hpp>
#include "Packet.hh"
#include "ClientHandler.hh"
#include "ClientReceiver.hh"

class Client
{
public:
	Client(bool self);
	~Client();
	
	void disconnect(bool unexpected = false);

	sf::TcpSocket &getSocket();

	void receiveServerInfo();
	void handshake();
	bool connectServer(std::string ip);

protected:
	bool _selfServer;
	std::condition_variable _packetsWaiting;
	std::mutex _mutex, _signalMutex;
	ClientGame _game;
	ClientHandler _handler;
	ClientReceiver _receiver;
	packetStack _packetStack;
	int8_t _id;
	std::shared_ptr<sf::TcpSocket> _socket;
};

#endif /* !CLIENT_HH_ */