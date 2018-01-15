#ifndef SERVERRECEIVER_HH_
#define SERVERRECEIVER_HH_

#include "Receiver.hh"
#include "ServerHandler.hh"
#include "networkdefs.h"

class ServerReceiver : public Receiver
{
public:
	ServerReceiver(packetStack &packetStack, std::mutex &mutex, std::mutex &signalMutex, clientArray &clientList, std::condition_variable &packetsWaiting);
	~ServerReceiver();

	void dropClient(clientNode &client, bool kick = false);
	void bindClient(sf::Socket &socket);

	virtual void receiveLoop();
	void start();
	virtual void close();

private:
	std::shared_ptr<sf::SocketSelector> _selector;
	clientArray &_clients;
};

#endif /* !SERVERRECEIVER_HH_ */