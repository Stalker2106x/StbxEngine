#ifndef CLIENTHANDLER_HH_
#define CLIENTHANDLER_HH_

#include "Network/Handler.hh"

namespace stb {

	class Client; //Forward

	class ClientHandler : public Handler<Client>
	{
	public:
		ClientHandler(sf::TcpSocket &socket, packetStack &packetStack, std::mutex &mutex, std::mutex &signalMutex, std::condition_variable &packetsWaiting, Client &client);
		~ClientHandler();

		virtual void processLoop();

	private:
		Client &_client; //Hook on server to manage functors
		sf::TcpSocket &_socket; //Hook on socket
	};

}

#endif /* !CLIENTHANDLER_HH_ */