#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"



class Game{

private:
	float selectMenuPosY;
	int contSelect, contBackgroundMenu, contBackgroundInGame, contNave;
	int stateRight, stateLeft, stateUp, stateDown;

	sf::RenderWindow* window;
	sf::Event event;
	sf::VideoMode videoMode;
	sf::Clock clock1;
	sf::Clock clock2;
	sf::Font font;
	sf::Text textMenu1;
	sf::Text textMenu2;
	sf::Text textMenu3;
	sf::Text textMenu4;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Texture backgroundSelectTexture;
	sf::Sprite backgroundSelectSprite;
	sf::Texture backgroundInGameTexture;
	sf::Sprite backgroundInGameSprite;
	sf::Texture naveTexture;
	sf::Sprite naveSprite;

	void initiVariables();
	void initiWindow();
	void initiMenu();
	void initiInGame();
	

public:
	// Accessors
	const bool running() const;
	// Constructors and Destructors
	Game();
	virtual ~Game();

	// Functions

	void queueEventsInGame();
	void updateBackgroundInGame();
	void updateNaveInGame();
	void updatePosNaveInGame();
	void updateInGame();
	void renderInGame();
	void queueEventsMenu();
	void updateBackgroundMenu();
	void updateMenuSelect();
	void updateMenu();
	void renderMenu();


};

