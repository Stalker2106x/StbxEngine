#ifndef CLIENTHANDLER_HH_
#define CLIENTHANDLER_HH_

#include "Handler.hh"

namespace stb {

	class ClientHandler : public Handler
	{
	public:
		ClientHandler(sf::TcpSocket &socket, packetStack &packetStack, std::mutex &mutex, std::mutex &signalMutex, std::condition_variable &packetsWaiting);
		~ClientHandler();

		virtual void processLoop();


	private:
		sf::TcpSocket &_socket;//Hook on socket
		packetFunctorMap _functors;
	};

}

#endif /* !CLIENTHANDLER_HH_ */