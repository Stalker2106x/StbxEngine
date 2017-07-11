#ifndef CENGINE_HH_
#define CENGINE_HH_

#include "../include/Engine.hpp"
#include "../include/Menu.hh"

class sEngine : public Engine
{
public:
	sEngine();

	~sEngine() {};

	bool update(sf::Event &e);
	void draw();

private:
	Menu _mainMenu;
};

#endif /* !CENGINE_HH_ */