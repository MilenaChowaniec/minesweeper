#include "Minesweeper.h"

void Minesweeper::initVar() {

	background.r = background.g = background.b = 100;
	background.a = 255;

	clickedOnce = false;
	bombsShowed = false;
	exposed_tiles = 0;

	bombs = 80;

	tiles_number = BOARDSIZE * ONE_CELL - bombs;

	x_points_r = 16;
	x_points_t = 46;
	x_time = 45;
	exposed_tiles = 0;
	stillPlaying = true;

	clock.restart();
}

void Minesweeper::initBombs(int x_c, int y_c) {

	int tmp = 0;

	//ustawienie bomb na planszy
	while (true) {
		int x = rand() % BOARDSIZE;
		int y = rand() % BOARDSIZE;
		if (board[x][y].value != NO_BOMB_UNDERNEATH || (x == x_c && y == y_c)) continue;
		if (abs(x_c - x) <= 1 && abs(y_c - y) <= 1) continue;
		else {
			board[x][y].value = BOMB_UNDERNEATH;
			++tmp;
		}
		if (tmp == bombs) break;
	}


	//ustawienie numerow na planszy
	for (int i = 0;i < BOARDSIZE; ++i) {
		for (int j = 0; j < BOARDSIZE; ++j) {
			if (board[i][j].value == BOMB_UNDERNEATH) continue;

			int bombsAmount = 0;

			for (int k = i - 1; k <= i + 1; ++k) {
				for (int l = j - 1; l <= j + 1; ++l) {
					if (k < 0 || l < 0 || k >= BOARDSIZE || l >= BOARDSIZE) continue;
					if (board[k][l].value == BOMB_UNDERNEATH) ++bombsAmount;

					
				}
			}

			if (bombsAmount == 0) board[i][j].value = EMPTY;
			else board[i][j].value = bombsAmount;
		}
	}
}

void Minesweeper::initFonts() {
	bold.loadFromFile("fonts/minesweeperBold.ttf");
	regular.loadFromFile("fonts/minesweeper.ttf");
}

void Minesweeper::initRect() {
	newgame.square.setPosition(80, 280);
	newgame.square.setFillColor(sf::Color(119, 119, 119, 220));
	newgame.square.setSize(sf::Vector2f(230, 60));
}

void Minesweeper::initText() {
	score.points.setFont(regular);
	score.points.setString("jes");
	score.points.setCharacterSize(14);
	score.points.setPosition(x_points_t, 20);
	score.points.setFillColor(sf::Color::White);

	score.time.setFont(regular);
	score.time.setCharacterSize(14);
	score.time.setString("jos");
	score.time.setPosition(x_time, 40);
	score.time.setFillColor(sf::Color::White);

	newgame.text.setFont(bold);
	newgame.text.setString("new game");
	newgame.text.setCharacterSize(38);
	newgame.text.setPosition(100, 280);
	newgame.text.setFillColor(sf::Color::White);
}

void Minesweeper::initScore() {
	score.square.setSize(sf::Vector2f(100, 70));
	score.square.setPosition(16, 10);
	score.square.setFillColor(sf::Color(100, 100, 100, 210));
	score.bonds = score.square.getGlobalBounds();
}

void Minesweeper::initTextures() {
	tile.unknown.loadFromFile("images/tiles/TileUnknown.png");
	tile.exploded.loadFromFile("images/tiles/TileExploded.png");
	tile.empty.loadFromFile("images/tiles/TileEmpty.png");
	tile.bomb.loadFromFile("images/tiles/TileMine.png");
	tile.flag.loadFromFile("images/tiles/TileFlag.png");


	for (int i = 0; i < 8; ++i) {
		tile.numbers[i].loadFromFile("images/tiles/numbers/Tile" + std::to_string(i + 1) + ".png");
	}
}

Minesweeper::Minesweeper(sf::RenderWindow* win, sf::VideoMode vid, Game& g) : window(win), video(vid), game(g) {
	cursor.loadFromSystem(sf::Cursor::Arrow);
	this->window->setMouseCursor(cursor);

	initVar();
	initBoard();
	initRect();
	initFonts();
	initText();
	initScore();
	initTextures();
}

void Minesweeper::move_square_with_points() {
	score.bonds = score.square.getGlobalBounds();

	if (score.bonds.contains(cursorPos.x, cursorPos.y)) {

		if (x_points_r == 16) x_points_r = 280;
		else x_points_r = 16;

		if (x_points_t == 46) x_points_t = 308;
		else x_points_t = 46;

		if (x_time == 45) x_time = 307;
		else x_time = 45;
		
		score.time.setPosition(x_time, 40);
		score.square.setPosition(x_points_r, 10);
		score.points.setPosition(x_points_t, 20);
	}
}

void Minesweeper::unveil_bombs(int x, int y) {

	for (int i = 0; i < BOARDSIZE; ++i) {
		for (int j = 0; j < BOARDSIZE;++j) {
			if (x == i && y == j) {
				board[i][j].value = BOMB_PRESSED;
				board[i][j].state = OPEN;
				continue;
			}
			if (board[i][j].value == BOMB_UNDERNEATH) {
				board[i][j].value = BOMB_NO_PRESSED;
				board[i][j].state = OPEN;
			}
		}
	}

	bombsShowed = true;

}

void Minesweeper::open_empty_tiles(int x, int y) { //x i y sa juz puste

	if (x < 0 || y < 0 || x > BOARDSIZE || y > BOARDSIZE || board[x][y].state == OPEN || (board[x][y].value != EMPTY && board[x][y].value < 0)) return;

	board[x][y].state = OPEN;
	++exposed_tiles;

	if (board[x][y].value > 0) return;

	open_empty_tiles(x - 1, y);
	open_empty_tiles(x + 1, y);
	open_empty_tiles(x, y + 1);
	open_empty_tiles(x, y - 1);
}

void Minesweeper::initBoard() {
	int bombs = 0;
	for (int i = 0;i < BOARDSIZE; ++i) {
		for (int j = 0; j < BOARDSIZE; ++j) {
			board[i][j].value = NO_BOMB_UNDERNEATH;
			board[i][j].state = CLOSED;
		}
	}

}

void Minesweeper::click(int x, int y, int button) {
	x /= 20;
	y /= 20;

	if (clickedOnce == false) {
		initBombs(x, y);
		clickedOnce = true;
	}

	if (button == LEFT) {
		//na JUZ NACISNIETA bombe lub plytke z FLAGA nie mozna dzialac
		if (board[x][y].value == BOMB_PRESSED || board[x][y].state == FLAGGED || board[x][y].state == OPEN) return;
		else if (board[x][y].value == BOMB_UNDERNEATH) unveil_bombs(x, y); //kiedy nacisniemy na tile z UKRYTA BOMBA
		else if (board[x][y].value == EMPTY) open_empty_tiles(x, y);
		else {
			board[x][y].state = OPEN;
			++exposed_tiles;
		}
	}
	else {
		if (board[x][y].state == OPEN) return;
		if (board[x][y].state == FLAGGED) board[x][y].state = CLOSED;
		else board[x][y].state = FLAGGED;
	}
	
}

void Minesweeper::display_score() {
	this->window->draw(score.square);

	score.points.setString(std::to_string(exposed_tiles) + "/" + std::to_string(tiles_number));
	this->window->draw(score.points);

	//ustawienie czasu 
	if (stillPlaying) {
		time = clock.getElapsedTime();
		float elapsedTime = time.asSeconds();
		std::ostringstream string;
		string << std::fixed << std::setprecision(2) << elapsedTime << std::endl;
		score.time.setString(string.str());
	}

	this->window->draw(score.time);
}

void Minesweeper::display_game() {
	cursor.loadFromSystem(sf::Cursor::Arrow);

	for (int i = 0; i < BOARDSIZE; ++i) {
		for (int j = 0; j < BOARDSIZE;++j) {

			sprite.setPosition(i * ONE_CELL, j * ONE_CELL);
			Element& el = board[i][j];

			//przypadki dla ZAMKNIETYCH 
			if (el.state == CLOSED) sprite.setTexture(tile.unknown);
			else if (el.state == FLAGGED) sprite.setTexture(tile.flag);
			else {
				//przypadki dla OTWARTYCH
				if (el.value > 0) sprite.setTexture(tile.numbers[el.value - 1]);
				else if (el.value == EMPTY) sprite.setTexture(tile.empty);
				else if (el.value == BOMB_PRESSED) sprite.setTexture(tile.exploded);
				else if (el.value == BOMB_NO_PRESSED) sprite.setTexture(tile.bomb);
			}
			
			this->window->draw(sprite);
		}
	}
	this->window->setMouseCursor(cursor);
	display_score();
	if (stillPlaying == false) {
		end_game();
	}
}

void Minesweeper::end_game() {
	if (stillPlaying == false) {
		this->window->draw(newgame.square);

		if (newgame.square.getGlobalBounds().contains(cursorPos.x, cursorPos.y)) {
			newgame.text.setFillColor(sf::Color(159, 159, 159));
			cursor.loadFromSystem(sf::Cursor::Hand);
		}
		else newgame.text.setFillColor(sf::Color::White);

		this->window->draw(newgame.text);
		this->window->setMouseCursor(cursor);
	}
}

void Minesweeper::new_game() {
	initBoard();
	stillPlaying = true;
	clickedOnce = false;
	bombsShowed = false;
	exposed_tiles = 0;
	clock.restart();
}

void Minesweeper::render() {
	this->window->clear(background);

	display_game();

	this->window->display();

}

void Minesweeper::update() {
	cursorPos = sf::Mouse::getPosition(*window);
}

void Minesweeper::handle_mouse_moved(sf::Event& event){
	if (score.bonds.contains(cursorPos.x, cursorPos.y)) move_square_with_points();
}

void Minesweeper::handle_event(sf::Event& event) {

	switch (event.type) {
	case sf::Event::Closed: {
		this->window->close();
		break;
	}
	case sf::Event::KeyPressed: {
		if (event.key.code == sf::Keyboard::Escape) game.change_scene(MAIN);
		break;
	}
	case sf::Event::MouseButtonPressed: {

		if (event.mouseButton.button == sf::Mouse::Left && stillPlaying) click(cursorPos.x, cursorPos.y, LEFT);
		else if (event.mouseButton.button == sf::Mouse::Right && stillPlaying) click(cursorPos.x, cursorPos.y, RIGHT);
		else if (newgame.square.getGlobalBounds().contains(cursorPos.x, cursorPos.y)) new_game();
		if (bombsShowed || exposed_tiles == tiles_number) stillPlaying = false;

		break;
	}
	case sf::Event::MouseMoved: {
		handle_mouse_moved(event);
		break;
	}
	}
	
}
