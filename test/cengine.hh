#ifndef CENGINE_HH_
#define CENGINE_HH_

#include "../include/Engine.hpp"
#include "../include/Network/Packet.hh"
#include "../include/Network/Server.hh"
#include "../include/Network/Client.hh"
#include "../include/Network/networkdefs.h"
#include "../include/defs.h"

class sServer : public stb::Server
{
public:
	sServer();
	~sServer();

	//Overload feature
	virtual void loop();
	virtual void setClientData(stb::Packet &data);
	virtual void sendServerData(stb::clientNode &client);

	//Error handling
	virtual void onClientTimeout();
	virtual void onNetworkError();
	virtual void onBindError();

private:
};

class sClient : public stb::Client
{
public:
	sClient();
	~sClient();

	//Overload features
	virtual void receiveServerInfo(stb::Packet &serverInfo);
	virtual void receivePlayer(stb::Packet &playerData);

	//Error handling
	virtual void onServerFull();
	virtual void onServerTimeout();
	virtual void onVersionMismatch();
	virtual void onNetworkError();

private:
};

class sEngine : public stb::Engine
{
public:
	sEngine();

	~sEngine() {};

	bool update(const sf::Event &e);
	void draw(sf::RenderWindow &win);

private:
	sServer _server;
	sClient _client;
};

#endif /* !CENGINE_HH_ */