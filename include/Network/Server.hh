#ifndef SERVER_HH_
#define SERVER_HH_

#include <vector>
#include <string>
#include <thread>
#include <iostream>
#include <SFML/Network.hpp>
#include <Engine.hpp>
#include "ServerReceiver.hh"
#include "ServerHandler.hh"

namespace stb {

	class Server
	{
	public:
		Server(const VersionInfo &version, const VersionInfo &supportedVersion, const std::string &name, const int port, const int slots);
		~Server();

		static clientNode &getClient(int8_t clientId);
		bool isVersionSupported(const VersionInfo &version);

		void sendClientsInfo(clientNode &client);
		void handshake(clientNode &client);
		uint8_t reserveSlot();
		void listenLoop();
		void run();
		void shutdown();

		//Overload feature
		virtual void loop() = 0;
		virtual void setClientData(stb::Packet &data) = 0;
		virtual void sendServerData(clientNode &client) = 0;

		//Error handling
		virtual void onClientTimeout() = 0;
		virtual void onNetworkError() = 0;
		virtual void onBindError() = 0;

	protected:
		static clientArray _clients;
		VersionInfo _version, _supportedVersion;
		std::shared_ptr<std::thread> _thisThread, _listenThread;
		std::condition_variable _packetsWaiting, _clientsReady;
		std::mutex _mutex, _signalMutex;
		bool _quit;
		std::string _name;
		uint8_t _slots;
		int _port;
		ServerReceiver _receiver;
		ServerHandler _handler;
		packetStack _packetStack;
		sf::TcpListener _listener;
	};

}

#endif /* !SERVER_HH_ */