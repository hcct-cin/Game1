#include "Game.h"
#include <iostream>


// initializing general variables
void Game::initiVariables() {
	this->window = nullptr;
	this->selectMenuPosY = 364;
	this->contBackgroundMenu = 1;
	this->contSelect = 1;
	this->contBackgroundInGame = 1;
	this->contNave = 1;
	this->stateRight = 0;
	this->stateLeft = 0;
	this->stateUp = 0;
	this->stateDown = 0;

}

// initializing window stuffs
void Game::initiWindow() {

	this->videoMode.height = 690;
	this->videoMode.width = 582;

	this->window = new sf::RenderWindow(this->videoMode, "Space Invaders", sf::Style::Close);

}

 // initializing Menu stuffs
void Game::initiMenu() {

	// initialize background Menu
	if (!this->backgroundTexture.loadFromFile("backgroundMenu1.png")) {
		std::cout << "Error opening backgroundMenu1 Texture" << std::endl;
	}

	// initialize select menu variables
	this->backgroundSprite.setTexture(this->backgroundTexture);

	if (!this->backgroundSelectTexture.loadFromFile("backgroundMenuSelect1.png")) {
		std::cout << "Error opening backgroundMenuSelect Texture" << std::endl;
	}

	this->backgroundSelectSprite.setTexture(this->backgroundSelectTexture);

	this->backgroundSelectSprite.setPosition(260, selectMenuPosY);

	// Loading font menu and setting Text menu stuffs 
	// - Space Betão
	this->font.loadFromFile("FontePixel.ttf");
	this->textMenu1.setFont(this->font);
	this->textMenu1.setString("Space\nBetão");
	this->textMenu1.setPosition(215,21);
	this->textMenu1.setCharacterSize(40);
	this->textMenu1.setFillColor(sf::Color(204,172,0));
	// - Jogar
	this->textMenu2.setFont(this->font);
	this->textMenu2.setString("Jogar");
	this->textMenu2.setPosition(425,424);
	this->textMenu2.setCharacterSize(23);
	this->textMenu2.setFillColor(sf::Color(204, 172, 0));
	// - Controles
	this->textMenu3.setFont(this->font);
	this->textMenu3.setString("Controles");
	this->textMenu3.setPosition(425,524);
	this->textMenu3.setCharacterSize(23);
	this->textMenu3.setFillColor(sf::Color(204, 172, 0));
	// - Creditos
	this->textMenu4.setFont(this->font);
	this->textMenu4.setString("Creditos");
	this->textMenu4.setPosition(425,624);
	this->textMenu4.setCharacterSize(23);
	this->textMenu4.setFillColor(sf::Color(204, 172, 0));

}

void Game::initiInGame() {
	if (!this->backgroundInGameTexture.loadFromFile("backgroundInGame1.png")) {
		std::cout << "Error opening backgroundInGame texture" << std::endl;
	}

	this->backgroundInGameSprite.setTexture(this->backgroundInGameTexture);

	if (!this->naveTexture.loadFromFile("naveInGame1.png")) {
		std::cout << "Error opening backgroundInGame texture" << std::endl;
	}
	this->naveSprite.setTexture(this->naveTexture);

	this->naveSprite.setPosition(290,380);
	this->naveSprite.setScale(0.5,0.5);
}

 // Queue Events of Menu and event handler
void Game::queueEventsMenu(){
	
	while (this->window->pollEvent(this->event)){

		switch (this->event.type){
			
			// Closing window
			case sf::Event::Closed:
				this->window->close();
				break;
		
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					this->window->close();
				}
			// Moving selectMenuSprite Down
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					if (this->selectMenuPosY < 564){
						this->selectMenuPosY = this->selectMenuPosY + 100;
					}
					else if (this->selectMenuPosY == 564) {
						this->selectMenuPosY = 364;
					}

					this->backgroundSelectSprite.setPosition(260,selectMenuPosY);
				}
			// Moving selectMenuSprite Up
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					if (this->selectMenuPosY > 364) {
						this->selectMenuPosY = this->selectMenuPosY - 100;
					}
					else if (this->selectMenuPosY == 364) {
						this->selectMenuPosY = 564;
					}

					this->backgroundSelectSprite.setPosition(260, selectMenuPosY);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
					if (this->selectMenuPosY == 364) {
						while (this->running()) {
							this->updateInGame();
							this->renderInGame();
						}

					}
				}
				break;
		
		}

		 

	}

}

void Game::queueEventsInGame() {

	while (this->window->pollEvent(this->event)) {

		switch (this->event.type) {
			// Closing window
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
					while (this->running()) {
						this->updateMenu();
						this->renderMenu();
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
					this->window->close();
				}
				break;
		}

		if (this->event.type == sf::Event::KeyPressed){
			if (this->event.key.code == sf::Keyboard::Escape) {
				this->window->close();
			}
			if (this->event.key.code == sf::Keyboard::Right) {
				this->stateRight = 1;
			}
			if (this->event.key.code == sf::Keyboard::Left) {
				this->stateLeft = 1;
			}
			if (this->event.key.code == sf::Keyboard::Up) {
				this->stateUp = 1;
			}
			if (this->event.key.code == sf::Keyboard::Down) {
				this->stateDown = 1;
			}

		}
		else if(this->event.type == sf::Event::KeyReleased) {
			if (this->event.key.code == sf::Keyboard::Right) {
				this->stateRight = 0;
			}
			if (this->event.key.code == sf::Keyboard::Left) {
				this->stateLeft = 0;
			}
			if (this->event.key.code == sf::Keyboard::Up) {
				this->stateUp = 0;
			}
			if (this->event.key.code == sf::Keyboard::Down) {
				this->stateDown = 0;
			}
		}
		

	}

}

void Game::updateBackgroundMenu(){

	if (clock2.getElapsedTime().asSeconds() > 0.1f) {
		if (this->contBackgroundMenu < 6) {
			this->contBackgroundMenu = contBackgroundMenu + 1;
			clock2.restart();
		}
	}
	
	switch (this->contBackgroundMenu){
		case 1: 
			if (!this->backgroundTexture.loadFromFile("backgroundMenu1.png")) {
				std::cout << "Error opening backgroundMenu1 Texture" << std::endl;
			}
			break;
		case 2:
			if (!this->backgroundTexture.loadFromFile("backgroundMenu2.png")) {
				std::cout << "Error opening backgroundMenu1 Texture" << std::endl;
			}
			break;
		case 3:
			if (!this->backgroundTexture.loadFromFile("backgroundMenu3.png")) {
				std::cout << "Error opening backgroundMenu1 Texture" << std::endl;
			}
			break;
		case 4:
			if (!this->backgroundTexture.loadFromFile("backgroundMenu4.png")) {
				std::cout << "Error opening backgroundMenu1 Texture" << std::endl;
			}
			break;
		case 5:
			if (!this->backgroundTexture.loadFromFile("backgroundMenu5.png")) {
				std::cout << "Error opening backgroundMenu1 Texture" << std::endl;
			}
				break;
		case 6:
			if (!this->backgroundTexture.loadFromFile("backgroundMenu6.png")) {
				std::cout << "Error opening backgroundMenu1 Texture" << std::endl;
			}
			break;
	}
	
	if(contBackgroundMenu == 6) {
		this->contBackgroundMenu = 1;
	}
}

void Game::updateBackgroundInGame() {
	if (clock1.getElapsedTime().asSeconds() > 0.3f) {
		if (this->contBackgroundInGame < 4) {
			this->contBackgroundInGame = contBackgroundInGame + 1;
			clock1.restart();
		}
	}

	switch (this->contBackgroundInGame) {
	case 1:
		if (!this->backgroundInGameTexture.loadFromFile("backgroundInGame1.png")) {
			std::cout << "Error opening backgroundMenu1 Texture" << std::endl;
		}
		break;
	case 2:
		if (!this->backgroundInGameTexture.loadFromFile("backgroundInGame2.png")) {
			std::cout << "Error opening backgroundMenu1 Texture" << std::endl;
		}
		break;
	case 3:
		if (!this->backgroundInGameTexture.loadFromFile("backgroundInGame3.png")) {
			std::cout << "Error opening backgroundMenu1 Texture" << std::endl;
		}
		break;
	case 4:
		if (!this->backgroundInGameTexture.loadFromFile("backgroundInGame4.png")) {
			std::cout << "Error opening backgroundMenu1 Texture" << std::endl;
		}
		break;

	}

	if (contBackgroundInGame == 4) {
		this->contBackgroundInGame = 1;
	}

}

void Game::updateMenuSelect() {

	if (clock1.getElapsedTime().asSeconds() > 0.1f) {
		if (this->contSelect<4) {
			this->contSelect = contSelect + 1;
			clock1.restart();
		}
	}

	switch (this->contSelect) {
	case 1:
		if (!this->backgroundSelectTexture.loadFromFile("backgroundMenuSelect1.png")) {
			std::cout << "Error opening backgroundMenu1 Texture" << std::endl;
			
		}
		break;
	case 2:
		if (!this->backgroundSelectTexture.loadFromFile("backgroundMenuSelect2.png")) {
			std::cout << "Error opening backgroundMenu1 Texture" << std::endl;
		}
		break;
	case 3:
		if (!this->backgroundSelectTexture.loadFromFile("backgroundMenuSelect3.png")) {
			std::cout << "Error opening backgroundMenu1 Texture" << std::endl;
		}
		break;
	case 4:
		if (!this->backgroundSelectTexture.loadFromFile("backgroundMenuSelect4.png")) {
			std::cout << "Error opening backgroundMenu1 Texture" << std::endl;
		}
		break;
	}

	if(this->contSelect == 4) {
		this->contSelect = 1;
	}
}

void Game::updateNaveInGame() {


	if (clock2.getElapsedTime().asSeconds() > 0.1f) {
		if (this->contNave < 6) {
			this->contNave = contNave + 1;
			clock2.restart();
		}
	}

	switch (this->contNave) {
	case 1:
		if (!this->naveTexture.loadFromFile("naveInGame1.png")) {
			std::cout << "Error opening backgroundMenu1 Texture" << std::endl;
		}
		break;
	case 2:
		if (!this->naveTexture.loadFromFile("naveInGame2.png")) {
			std::cout << "Error opening backgroundMenu1 Texture" << std::endl;
		}
		break;
	case 3:
		if (!this->naveTexture.loadFromFile("naveInGame3.png")) {
			std::cout << "Error opening backgroundMenu1 Texture" << std::endl;
		}
		break;
	case 4:
		if (!this->naveTexture.loadFromFile("naveInGame4.png")) {
			std::cout << "Error opening backgroundMenu1 Texture" << std::endl;
		}
		break;
	case 5:
		if (!this->naveTexture.loadFromFile("naveInGame5.png")) {
			std::cout << "Error opening backgroundMenu1 Texture" << std::endl;
		}
		break;
	case 6:
		if (!this->naveTexture.loadFromFile("naveInGame6.png")) {
			std::cout << "Error opening backgroundMenu1 Texture" << std::endl;
		}
		break;

	}

	if (this->contNave == 6) {
		this->contNave = 1;
	}
}

void Game::updatePosNaveInGame() {

	if (this->stateUp) {
		if (this->naveSprite.getPosition().y > -20) {
			this->naveSprite.move(0, -10);
		}
	}
	if (this->stateDown) {
		if (this->naveSprite.getPosition().y < 570) {
			this->naveSprite.move(0, 10);
		}
	}
	if (this->stateRight == 1) {
		if (this->naveSprite.getPosition().x < 450) {
			this->naveSprite.move(10, 0);
		}
	}
	if (this->stateLeft == 1) {
		if (this->naveSprite.getPosition().x > -30) {
			this->naveSprite.move(-10, 0);
		}
	}

}

void Game::updateMenu() {
	this->updateBackgroundMenu();
	this->updateMenuSelect();
	this->queueEventsMenu();
}

void Game::updateInGame() {
	this->updateBackgroundInGame();
	this->updateNaveInGame();
	this->updatePosNaveInGame();
	this->queueEventsInGame();
}


// Rendering sprites and clearing trashs sprites 
void Game::renderMenu() {

	this->window->clear(sf::Color::White);
	this->window->draw(backgroundSprite);
	this->window->draw(textMenu1);
	this->window->draw(textMenu2);
	this->window->draw(textMenu3);
	this->window->draw(textMenu4);
	this->window->draw(backgroundSelectSprite);
	this->window->display();
}

void Game::renderInGame() {
	this->window->clear(sf::Color::White);
	this->window->draw(backgroundInGameSprite);
	this->window->draw(naveSprite);
	this->window->display();

}

// Accessors
const bool Game::running() const {
	return this->window->isOpen();
}


// Constructor and Destructor
Game::Game(){
	this->initiVariables();
	this->initiWindow();
	this->initiMenu();
	this->initiInGame();
}

Game::~Game(){
	delete this->window;
}
