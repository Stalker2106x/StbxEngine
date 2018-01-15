#ifndef SERVER_HH_
#define SERVER_HH_

#include <vector>
#include <string>
#include <thread>
#include <iostream>
#include <SFML/Network.hpp>
#include <Engine.hpp>
#include "ServerGame.hh"
#include "ServerReceiver.hh"
#include "ServerHandler.hh"

class Server
{
public:
	Server(const std::string &name, const int port, const int slots);
	~Server();

	static clientNode &getClient(int8_t clientId);
	void sendClientsInfo(clientNode &client);
	void handshake(clientNode &client);
	uint8_t reserveSlot();
	void listenLoop();
	void run();
	void shutdown();

private:
	static clientArray _clients;
	std::shared_ptr<std::thread> _thisThread, _listenThread;
	std::condition_variable _packetsWaiting, _clientsReady;
	std::mutex _mutex, _signalMutex;
	bool _quit;
	std::string _name;
	uint8_t _slots;
	int _port;
	ServerReceiver _receiver;
	ServerHandler _handler;
	packetStack _packetStack;
	sf::TcpListener _listener;
};

#endif /* !SERVER_HH_ */