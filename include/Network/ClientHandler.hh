#ifndef CLIENTHANDLER_HH_
#define CLIENTHANDLER_HH_

#include "Handler.hh"

class ClientHandler : public Handler
{
public:
	//Generic Handler typedef
	typedef void (ClientHandler::*packetFunctor)(std::shared_ptr<Packet>);
	typedef std::map<int16_t, packetFunctor> packetFunctorMap;

	ClientHandler(ClientGame &game, sf::TcpSocket &socket, packetStack &packetStack, std::mutex &mutex, std::mutex &signalMutex, std::condition_variable &packetsWaiting);
	~ClientHandler();

	virtual void processLoop();

	//Functors
	void getPlayer(std::shared_ptr<Packet> packet);
	void dropPlayer(std::shared_ptr<Packet> packet);
	void getMessage(std::shared_ptr<Packet> packet);
	void togglePlayerReady(std::shared_ptr<Packet> packet);
	void startGame(std::shared_ptr<Packet> packet);
	void disconnect(std::shared_ptr<Packet> packet);

private:
	sf::TcpSocket &_socket;//Hook on socket
	ClientGame &_game; //Hook on game
	packetFunctorMap _functors;
};

#endif /* !CLIENTHANDLER_HH_ */