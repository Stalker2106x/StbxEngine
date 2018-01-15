#include "cengine.hh"
#include "../include/Resolver.hh"
#include "../include/Profile.hh"
#include <TGUI/TGUI.hpp>

//
//Client
//

sClient::sClient() : stb::Client(stb::VersionInfo(0,1,0), true)
{

}

sClient::~sClient()
{

}

void sClient::receiveServerInfo(stb::Packet &serverInfo)
{

}

void sClient::receivePlayer(stb::Packet &playerData)
{

}

void sClient::onServerFull()
{

}

void sClient::onServerTimeout()
{

}

void sClient::onVersionMismatch()
{

}

void sClient::onNetworkError()
{

}

//
//Server
//

sServer::sServer() : stb::Server(stb::VersionInfo(0, 1, 0), stb::VersionInfo(0, 1, 0), "Test server", 27420, 5)
{

}

sServer::~sServer()
{

}

void sServer::loop()
{

}

void sServer::setClientData(stb::Packet &data)
{

}

void sServer::sendServerData(stb::clientNode &client)
{

}

void sServer::onClientTimeout()
{

}

void sServer::onNetworkError()
{

}

void sServer::onBindError()
{

}

//
// ENGINE
//

sEngine::sEngine()
{
	//Initialize paths
	stb::SFResolver<sf::Font>::addLocation("./Data/font/");
	stb::SFResolver<sf::Texture>::addLocation("./Data/texture/");

	stb::PathResolver<stb::RTexture>::addLocation("./Data/texture/");
	stb::PathResolver<stb::RSound>::addLocation("./Data/sound/");
	//init engine
	init();
	//BEGIN GAME INIT
	Engine::profile = &stb::Profile("Stabax", "Yebamod0");
	_client.connectServer("localhost"); //Test
}

bool sEngine::update(const sf::Event &e)
{
	return (true);
}

void sEngine::draw(sf::RenderWindow &win)
{
}
