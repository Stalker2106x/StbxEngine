#ifndef HUD_HH_
#define HUD_HH_

#include <SFML/Graphics.hpp>
#include <vector>

class HUDIndicator
{

public:
	HUDIndicator();
	~HUDIndicator();

private:
	sf::Text _value;
};

class HUDPanel
{
public:
	HUDPanel();
	~HUDPanel();

private:
	sf::Sprite _background;
};

class HUD
{
public:
	HUD();
	~HUD();

	void toggle();
	void addPanel();
	void addIndicator();

private:
	bool _active;
	std::vector<HUDPanel> _panels;
	std::vector<HUDIndicator> _indicators;
};

#endif /* !DRAWABLE_HH_ */