#pragma once

#include <SFML/Graphics.hpp>

class cScene
{
	virtual void init (sf::RenderWindow& _window) = 0;
	virtual void unInit () = 0;
};