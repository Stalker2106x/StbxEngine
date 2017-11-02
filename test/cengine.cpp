#include "cengine.hh"
#include "../include/Resolver.hh"

sEngine::sEngine()
{
	//Initialize paths
	stb::Resolver<sf::Font>::addLocation("./Data/font/");
	stb::Resolver<sf::Texture>::addLocation("./Data/texture/");
	stb::Resolver<stb::GUIScreen>::addLocation("./Data/screen/");
	//Change none to any screen
	gui->changeScreen("main");
	//Add Draggable Panel
	stb::GUIPanel *panel = gui->addDraggablePanel("windowz", sf::Vector2i(400, 200), sf::Color(64, 64, 64), sf::Color(110, 110, 110));
	//Add FPS Indicator inside
	panel->addElement(new stb::GUIIndicator<int>("Indicator :", _framerate));
}

bool sEngine::update(const sf::Event &e)
{
	return (true);
}

void sEngine::draw()
{

}
