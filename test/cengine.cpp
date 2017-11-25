#include "cengine.hh"
#include "../include/Resolver.hh"
#include "imgui/imgui.h"

sEngine::sEngine()
{
	//Initialize paths
	stb::Resolver<sf::Font>::addLocation("./Data/font/");
	stb::Resolver<sf::Texture>::addLocation("./Data/texture/");
	stb::Resolver<stb::GUIScreen>::addLocation("./Data/screen/");
	//init engine
	init();
}

bool sEngine::update(const sf::Event &e)
{
	return (true);
}

void sEngine::draw(sf::RenderWindow &win)
{
	//ImGui
	ImGui::Begin("Frame");
	ImGui::Button("OVERBUTTON");
	ImGui::End();
}
