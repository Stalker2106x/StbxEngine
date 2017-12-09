#include "cengine.hh"
#include "../include/Resolver.hh"
#include <TGUI/TGUI.hpp>

sEngine::sEngine()
{
	//Initialize paths
	stb::SFResolver<sf::Font>::addLocation("./Data/font/");
	stb::SFResolver<sf::Texture>::addLocation("./Data/texture/");

	stb::PathResolver<stb::RTexture>::addLocation("./Data/texture/");
	stb::PathResolver<stb::RSound>::addLocation("./Data/sound/");
	//init engine
	init();
	/*
	auto picture = tgui::Picture::create("./Data/texture/background.png");
	picture->setSize("10%", "10%");
	picture->moveToBack();
	gui->add(picture);*/
}

bool sEngine::update(const sf::Event &e)
{
	return (true);
}

void sEngine::draw(sf::RenderWindow &win)
{
}
