#ifndef RECEIVER_HH_
#define RECEIVER_HH_

#include <thread>
#include <mutex>
#include <deque>
#include <iostream>
#include "Packet.hh"
#include "Handler.hh"

class Receiver
{
public:
	Receiver(packetStack &packetStack, std::mutex &mutex, std::mutex &signalMutex, std::condition_variable &packetsWaiting);
	~Receiver();

	void insertPacket(std::shared_ptr<Packet> pk);
	
	virtual void receiveLoop() = 0;
	virtual void close();

protected:
	std::condition_variable &_packetsWaiting;
	std::mutex &_mutex, &_signalMutex;
	bool _quit;
	std::shared_ptr<std::thread> _thread;
	packetStack &_packetStack;
};

#endif /* !RECEIVER_HH_ */