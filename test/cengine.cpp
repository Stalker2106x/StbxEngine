#include "cengine.hh"

sEngine::sEngine()
{
	gui->changeScreen("nestest");
	stb::GUIPanel *panel = gui->addDraggablePanel("windowz", sf::Vector2i(400, 200), sf::Color(64, 64, 64), sf::Color(110, 110, 110));
	panel->addElement(new stb::GUIIndicator<int>("Indicator :", _framerate));
}

bool sEngine::update(const sf::Event &e)
{
	return (true);
}

void sEngine::draw()
{

}
