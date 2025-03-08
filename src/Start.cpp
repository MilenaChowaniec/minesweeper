#include "Start.h"

void Start::initFonts() {
	bold.loadFromFile("fonts/minesweeperBold.ttf");
	regular.loadFromFile("fonts/minesweeper.ttf");
}

void Start::initText() {
	minesweeper.text.setFont(bold);
	minesweeper.text.setCharacterSize(50);
	minesweeper.text.setPosition(48, 50);
	minesweeper.text.setString("minesweeper");

	start.text.setFont(regular);
	start.text.setString("start");
	start.text.setCharacterSize(40);
	start.text.setPosition(156, 165);
}

Start::Start(sf::RenderWindow* win, sf::VideoMode vid, Game& g) : window(win), video(vid), game(g){
	initText();
	initFonts();
}

void Start::display_menu() {
	cursor.loadFromSystem(sf::Cursor::Arrow);
	this->window->draw(minesweeper.text);

	if (start.text.getGlobalBounds().contains(cursorPos.x, cursorPos.y)) {
		start.text.setFillColor(sf::Color(159, 159, 159));
		cursor.loadFromSystem(sf::Cursor::Hand);
	}
	else start.text.setFillColor(sf::Color::White);

	this->window->draw(start.text);
	this->window->setMouseCursor(cursor);
}

void Start::handle_mouse_pressed(sf::Event& event) {
	if (event.mouseButton.button == sf::Mouse::Left && start.text.getGlobalBounds().contains(cursorPos.x, cursorPos.y)) {
		game.change_scene(MINESWEEPER);
	}
}

void Start::handle_event(sf::Event& event) {
	switch (event.type) {
		case sf::Event::Closed: {
			std::cout << "closed";
			this->window->close();
			break;
		}
		case sf::Event::KeyPressed: {
			if (event.key.code == sf::Keyboard::Escape) this->window->close();
			break;
		}
		case sf::Event::MouseButtonPressed: {
			handle_mouse_pressed(event);
			break;
		}
	}
}

void Start::update() {
	cursorPos = sf::Mouse::getPosition(*window);
}

void Start::render() {
	this->window->clear(sf::Color(100, 100, 100));

	display_menu();

	this->window->display();
}
