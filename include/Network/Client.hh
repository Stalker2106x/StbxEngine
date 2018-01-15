#ifndef CLIENT_HH_
#define CLIENT_HH_

#include <iostream>
#include <thread>
#include <mutex>
#include <SFML/Network.hpp>
#include "Packet.hh"
#include "ClientHandler.hh"
#include "ClientReceiver.hh"

namespace stb {

	class Client
	{
	public:
		Client(const VersionInfo &version, bool self);
		~Client();

		void disconnect(bool unexpected = false);

		sf::TcpSocket &getSocket();

		void receiveClientList();
		void handshake();
		bool connectServer(std::string ip);

		//Overload features
		virtual void receiveServerInfo(Packet &serverInfo) = 0;
		virtual void receivePlayer(Packet &playerData) = 0;

		//Error handling
		virtual void onServerFull() = 0;
		virtual void onServerTimeout() = 0;
		virtual void onVersionMismatch() = 0;
		virtual void onNetworkError() = 0;

	protected:
		bool _selfServer;
		VersionInfo _version;
		std::condition_variable _packetsWaiting;
		std::mutex _mutex, _signalMutex;
		ClientHandler _handler;
		ClientReceiver _receiver;
		packetStack _packetStack;
		int8_t _id;
		std::shared_ptr<sf::TcpSocket> _socket;
	};

}

#endif /* !CLIENT_HH_ */