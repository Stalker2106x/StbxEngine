#ifndef SERVERHANDLER_HH_
#define SERVERHANDLER_HH_

#include "Handler.hh"
#include "ServerGame.hh"
#include "serverdefs.h"

class Server; //Forward
class ServerReceiver; //Forward

class ServerHandler : public Handler
{
public:
	//Generic Handler typedef
	typedef void (ServerHandler::*packetFunctor)(std::shared_ptr<Packet>);
	typedef std::map<int16_t, packetFunctor> packetFunctorMap;

	ServerHandler(clientArray &clients, packetStack &packetStack, std::mutex &mutex, std::mutex &signalMutex, std::condition_variable &packetsWaiting, std::condition_variable &clientsReady, ServerReceiver &receiver);
	~ServerHandler();

	virtual void processLoop();

	//Functors
	void broadcastMessage(std::shared_ptr<Packet> packet);
	void setClientReady(std::shared_ptr<Packet> packet);
	void kickPlayer(std::shared_ptr<Packet> packet);

private:
	ServerReceiver &_receiver; //Hook on receiver to manage clients
	std::condition_variable &_clientsReady;
	clientArray &_clients;
	packetFunctorMap _functors;
};

#endif /* !SERVERHANDLER_HH_ */