#pragma once

#include <vector>
#include "Start.h"
#include "minesweeper.h"

class Scene;
enum SceneType {MAIN = 0, MINESWEEPER = 1, AGAIN};

class Game {
	sf::RenderWindow* window;
	sf::Event event;
	sf::VideoMode video;
	std::vector<Scene*> scenes;
	SceneType currScene;

	void initVar();
	void initWin();
	void initScenes();

public:

	Game();
	~Game();
	void play();
	void pollEvents();
	void change_scene(SceneType newScene);
	const bool running() const;
};