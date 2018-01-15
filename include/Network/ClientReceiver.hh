#ifndef CLIENTRECEIVER_HH_
#define CLIENTRECEIVER_HH_

#include "Receiver.hh"

class ClientReceiver : public Receiver
{
public:
	ClientReceiver(packetStack &packetStack, std::mutex &mutex, std::mutex &signalMutex, std::condition_variable &packetsWaiting);
	~ClientReceiver();

	virtual void receiveLoop();
	void start(std::shared_ptr<sf::TcpSocket> socket);

private:
	std::shared_ptr<sf::TcpSocket> _socket;
};

#endif /* !CLIENTRECEIVER_HH_ */