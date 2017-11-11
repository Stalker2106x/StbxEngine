#ifndef CENGINE_HH_
#define CENGINE_HH_

#include "../include/Engine.hpp"
#include "../include/GUIContainer.hh"
#include "../include/GUIScreen.hh"
#include "../include/defs.h"

class sEngine : public stb::Engine
{
public:
	sEngine();

	~sEngine() {};

	bool update(const sf::Event &e);
	void draw(sf::RenderWindow &win);

private:
};

#endif /* !CENGINE_HH_ */