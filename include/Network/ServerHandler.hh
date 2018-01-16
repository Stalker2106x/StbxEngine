#ifndef SERVERHANDLER_HH_
#define SERVERHANDLER_HH_

#include "Network/Handler.hh"
#include "Network/networkdefs.h"

namespace stb {

	class Server; //Forward
	class ServerReceiver; //Forward

	class ServerHandler : public Handler
	{
	public:
		ServerHandler(clientArray &clients, packetStack &packetStack, std::mutex &mutex, std::mutex &signalMutex, std::condition_variable &packetsWaiting, std::condition_variable &clientsReady, ServerReceiver &receiver);
		~ServerHandler();

		virtual void processLoop();

		//Functors
		void broadcastMessage(std::shared_ptr<Packet> packet);
		void kickPlayer(std::shared_ptr<Packet> packet);

	private:
		ServerReceiver &_receiver; //Hook on receiver to manage clients
		std::condition_variable &_clientsReady;
		clientArray &_clients;
	};

}

#endif /* !SERVERHANDLER_HH_ */