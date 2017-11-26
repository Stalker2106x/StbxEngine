#include "cengine.hh"
#include "../include/Resolver.hh"
#include <TGUI/TGUI.hpp>

sEngine::sEngine()
{
	//Initialize paths
	stb::Resolver<sf::Font>::addLocation("./Data/font/");
	stb::Resolver<sf::Texture>::addLocation("./Data/texture/");
	stb::Resolver<stb::GUIScreen>::addLocation("./Data/screen/");
	//init engine
	init();
	auto picture = tgui::Picture::create("./Data/texture/background.png");
	picture->setSize({ "100%", "100%" });
	gui->add(picture);
}

bool sEngine::update(const sf::Event &e)
{
	return (true);
}

void sEngine::draw(sf::RenderWindow &win)
{
}
