#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Scene {
public:
	virtual void render() = 0;
	virtual void update() = 0;
	virtual void handle_event(sf::Event& event) = 0;
};
