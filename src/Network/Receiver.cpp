#include "Network/Receiver.hh"
#include "Network/Server.hh"

Receiver::Receiver(packetStack &packetStack, std:: mutex &mutex, std::mutex &signalMutex, std::condition_variable &packetsWaiting) : _packetStack(packetStack), _mutex(mutex), _signalMutex(signalMutex), _packetsWaiting(packetsWaiting)
{
}

Receiver::~Receiver()
{
	if (_quit == false)
	{
		close();
	}
}

void Receiver::insertPacket(std::shared_ptr<Packet> pk)
{
	std::lock_guard<std::mutex> lock(_signalMutex);

	_packetStack.push_front(pk);
	_packetsWaiting.notify_one();
}

void Receiver::close()
{
	_quit = true;
	_thread->join();
}