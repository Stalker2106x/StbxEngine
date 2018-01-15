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
	tgui::Button::Ptr sbutton = tgui::Button::create("Host");
	sbutton->setPosition("20%", "0%");
	sbutton->connect("Pressed", [&] {
		_server = std::make_shared<sServer>(); //Test server
	});
	gui->add(sbutton);
	tgui::Button::Ptr cbutton = tgui::Button::create("Connect");
	cbutton->connect("Pressed", [=] {
		static bool connected = false;
		if (!connected)
		{
			_client.connectServer("localhost"); //Test client
			cbutton->setText("Disconnect");
			connected = true;
		}
		else
		{
			_client.disconnect();
			cbutton->setText("Connect");
			connected = false;
		}
	});
	gui->add(cbutton);
	_tooltip = tgui::Panel::create();
	_tooltip->setSize(150, 150);
	_tooltip->getRenderer()->setBackgroundColor(tgui::Color::Blue);
	_tooltip->hide();
	gui->add(_tooltip);
	_cell = std::make_shared<sf::CircleShape>();
	_cell->setFillColor(sf::Color::Green);
	_cell->setRadius(20);
	_cell->setPosition(_winWidth.getValue() / 2, _winHeight.getValue() / 2);
}

bool sEngine::update(const sf::Event &e)
{
	static bool out = true;

	if (_cell->getGlobalBounds().contains(_mouse))
	{
		if (out == true)
		{
			_tooltip->show();
			out = false;
		}
		_tooltip->setPosition(_mouse);
	}
	else if (!_cell->getGlobalBounds().contains(_mouse) && out == false)
	{
		_tooltip->hide();
		out = true;
	}
	return (true);
}

void sEngine::draw(sf::RenderWindow &win)
{
	win.draw(*_cell);
}
