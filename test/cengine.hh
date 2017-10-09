#ifndef CENGINE_HH_
#define CENGINE_HH_

#include "../include/Engine.hpp"
#include "../include/GUIScreen.hh"

class sEngine : public stb::Engine
{
public:
	sEngine();

	~sEngine() {};

	bool update(const sf::Event &e);
	void draw();

private:
	stb::GUIScreen _mainMenu;
};

#endif /* !CENGINE_HH_ */