#ifndef HANDLER_HH_
#define HANDLER_HH_

#include <map>
#include <mutex>
#include <thread>
#include <functional>
#include <iostream>
#include "Packet.hh"
#include "networkdefs.h"

#define DEFAULT_TIMEOUT (sf::seconds(30))

namespace stb {

	class Handler
	{
	public:
		Handler(packetStack &packetStack, std::mutex &mutex, std::mutex &signalMutex, std::condition_variable &packetsWaiting);
		~Handler();

		void addHandle(std::pair<int, packetFunctor> &functor);

		void start();
		void stop();

		virtual void processLoop() = 0;

		//Grab packets
		std::shared_ptr<Packet> extractPacket(int8_t id, int16_t code, sf::Time retryDelay, sf::Time timeOut);
		std::shared_ptr<Packet> extractPacket(int8_t id = -1, int16_t code = -1);

	protected:
		bool _quit;
		packetFunctorMap _functors;
		packetStack &_packetStack;
		std::condition_variable &_packetsWaiting;
		std::mutex &_mutex, &_signalMutex;
		std::shared_ptr<std::thread> _thread;
	};
}

#endif /* !HANDLER_HH_ */