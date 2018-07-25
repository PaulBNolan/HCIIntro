/// <summary>
/// @Author: Paul Nolan
/// @Version 2.0
/// </summary>

#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include "MyEnums.h"  // gameState, animationState
//The headers for each of the animations
#include "AuthorScreen.h"
#include "SplashScreen.h"
#include "SFMLScreen.h"
#include "ProducerScreen.h"
#include "Credits.h"


class AuthorScreen;
class SplashScreen;
class SFMLScreen;
class ProducerScreen;
class Credits;

class Game
{
public:
	Game();
	~Game();
	
	void run();
	//This sets the inital animation
	GameState m_currentGameState{ GameState::Author }; 
													  
private:
	
	void processEvents();
	//The basic functions that set up the basic framework of the program
	void update(sf::Time t_deltaTime);
	void render();	
	//This loads the font used by the program
	void loadFont();	

	//The programs window which will be passed into the other classes for rendering
	sf::RenderWindow m_window; 
	//The font the program uses
	sf::Font m_font; 
	//Pointer objects representing each of the animations
	AuthorScreen *m_AuthorScreen; 
	SplashScreen *m_SplashScreen;
	SFMLScreen *m_SFMLScreen;
	ProducerScreen *m_producerScreen;
	Credits *m_credits;

	bool m_exitGame; // control exiting game
	int m_animationSpeed{ 10 }; // speed for every screen 1 -10
								// 1 quickest real time
								// 5 slow will notice animation
								// 10 slowest can see every aspect of animation
};

#endif // !GAME

