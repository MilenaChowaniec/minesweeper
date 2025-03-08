#pragma once
#include "scene.h"
#include "game.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

enum sizes { ONE_CELL = 20, BOARDSIZE = 20 };

enum values { NO_BOMB_UNDERNEATH = -2, BOMB_UNDERNEATH = -1, EMPTY = 0, BOMB_PRESSED = -3, BOMB_NO_PRESSED = -4 };

enum states { OPEN, CLOSED, FLAGGED };

enum game_state { WIN, LOST };

enum mouse_click { LEFT = 1, RIGHT = 2 };

class Game;

class Minesweeper : public Scene {
	sf::RenderWindow* window;
	sf::VideoMode video;
	sf::Color background;
	sf::Sprite sprite;
	sf::Vector2i cursorPos;
	sf::Cursor cursor;
	sf::Clock clock;
	sf::Time time;
	sf::Font bold, regular;

	struct Score {
		sf::Text time;
		sf::Text points;
		sf::RectangleShape square;
		sf::FloatRect bonds;
	};
	Score score;

	struct TextSquare {
		sf::Text text;
		sf::RectangleShape square;
	};
	TextSquare newgame;

	struct Tiles {
		sf::Texture unknown;
		sf::Texture exploded;
		sf::Texture empty;
		sf::Texture bomb;
		sf::Texture numbers[8];
		sf::Texture flag;
	};
	Tiles tile;

	struct Element {
		int state; //open or not
		int value; //co znajduje sie na tile, bomba pod spodem, czy nie czy klikniete czy nie itp
	};
	Element board[BOARDSIZE][BOARDSIZE];

	Game& game;

	game_state game_state;

	bool clickedOnce;
	bool bombsShowed;
	bool done;
	bool stillPlaying;

	int exposed_tiles;
	int tiles_number;
	int bombs;

	int x_points_r;
	int x_points_t;
	int x_time;

	void initVar();
	void initFonts();
	void initRect();
	void initText();
	void initScore();
	void initTextures();
	void initBombs(int x_c, int y_c);
	
public:

	Minesweeper(sf::RenderWindow* win, sf::VideoMode vid, Game& g);

	void move_square_with_points();
	void unveil_bombs(int x, int y);
	void open_empty_tiles(int x_s, int y_s);
	void initBoard();
	void click(int x, int y, int button);
	void display_score();
	void display_game();
	void end_game();
	void new_game();

	void handle_mouse_moved(sf::Event& event);
	void handle_event(sf::Event& event);
	void render();
	void update();
};
