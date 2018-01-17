#ifndef SERVERHANDLER_HH_
#define SERVERHANDLER_HH_

#include "Network/Handler.hh"
#include "Network/networkdefs.h"

namespace stb {

	class Server; //Forward
	class ServerReceiver; //Forward

	class ServerHandler : public Handler<Server>
	{
	public:
		ServerHandler(clientArray &clients, packetStack &packetStack, std::mutex &mutex, std::mutex &signalMutex, std::condition_variable &packetsWaiting, std::condition_variable &clientsReady, Server &server);
		~ServerHandler();

		virtual void processLoop();
		
	private:
		Server &_server; //Hook on server to manage functors
		std::condition_variable &_clientsReady;
		clientArray &_clients;
	};

}

#endif /* !SERVERHANDLER_HH_ */