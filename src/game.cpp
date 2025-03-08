#include "game.h"

void Game::initVar() {
	currScene = MAIN;
}

void Game::initWin() {
	this->video.height = 400;
	this->video.width = 400;
	this->window = new sf::RenderWindow(this->video, "minesweeper", sf::Style::Titlebar | sf::Style::Close);
}

void Game::initScenes() {
	scenes.push_back(new Start(window, video, *this));
	scenes.push_back(new Minesweeper(window, video, *this));
}

Game::Game() {
	initVar();
	initWin();
	initScenes();
}

Game::~Game() {
	for (int i = 0; i < scenes.size(); ++i) {
		delete[] scenes[i];
	}
	scenes.erase(scenes.begin(), scenes.end());
	delete window;
}

void Game::play() {
	while (running()) {
		scenes[currScene]->update();
		pollEvents();
		scenes[currScene]->render();
	}
	exit(3);
}

void Game::change_scene(SceneType newScene) {
	currScene = newScene;
}

void Game::pollEvents() {
	while (this->window->pollEvent(event)) {
		scenes[currScene]->handle_event(event);
	}
}

const bool Game::running() const {
	return this->window->isOpen();
}
