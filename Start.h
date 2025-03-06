#pragma once

#include <iostream>
#include "scene.h"
#include "game.h"

class Scene;
class Game;

class Start : public Scene {
	sf::RenderWindow* window;
	sf::VideoMode video;
	sf::Font regular, bold;
	sf::Cursor cursor;
	sf::Vector2i cursorPos;

	struct SquareText {
		sf::FloatRect bonds;
		sf::Text text;
	};
	SquareText minesweeper, start;

	Game& game;
;
	void initFonts();
	void initText();
public:
	Start(sf::RenderWindow* win, sf::VideoMode vid, Game& g);
	
	void display_menu();
	void handle_mouse_pressed(sf::Event& event);
	void handle_mouse_moved(sf::Event& event);
	void handle_event(sf::Event& event);
	void update();
	void render();
};
