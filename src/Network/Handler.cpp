#include "Network/Handler.hh"

Handler::Handler(packetStack &packetStack, std::mutex &mutex, std::mutex &signalMutex, std::condition_variable &packetsWaiting) : _packetStack(packetStack), _mutex(mutex), _signalMutex(signalMutex), _packetsWaiting(packetsWaiting)
{
	_quit = false;
}

Handler::~Handler()
{
	if (_thread != nullptr) //Dirty exit
		stop();
}

void Handler::start()
{
	_thread = std::make_shared<std::thread>(&Handler::processLoop, this);
}

void Handler::stop()
{
	{
		std::unique_lock<std::mutex> lock(_signalMutex);

		_quit = true;
		_packetsWaiting.notify_one();
	}
	_thread->join();
	_thread = nullptr;
}

std::shared_ptr<Packet> Handler::extractPacket(int8_t id, int16_t code, sf::Time retryDelay, sf::Time timeOut)
{
	sf::Clock clock;
	std::shared_ptr<Packet> packet = nullptr;

	for (sf::Clock clock; clock.getElapsedTime() < timeOut;)
	{
		if ((packet = extractPacket(id, code)) != nullptr)
		{
			return (packet);
		}
		sf::sleep(retryDelay);
	}
	return (nullptr);
}

std::shared_ptr<Packet> Handler::extractPacket(int8_t id, int16_t code)
{
	_mutex.lock();
	for (size_t i = 0; i < _packetStack.size(); i++)
	{
		if ((id != -1 && _packetStack[i]->clientId == id)		//Search by client ID
			|| (code != -1 && _packetStack[i]->code == code)	//Search by code
			|| (code == -1 && id == -1))						//Any
		{
			std::shared_ptr<Packet> packet = _packetStack[i];
			_packetStack.erase(_packetStack.begin() + i);
			_mutex.unlock();
			return(packet);
		}
	}
	_mutex.unlock();
	return (nullptr);
}