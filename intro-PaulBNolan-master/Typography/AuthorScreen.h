/// <summary>
/// @Author: Paul Nolan
/// @Version 2.0
/// </summary>

#ifndef AUTHOR_SCREEN
#define AUTHOR_SCREEN
#include <SFML\Graphics.hpp>
#include "Game.h"
#include <stdio.h>  
#include <stdlib.h> 
#include <time.h>
#define PI           3.14159265358979323846;
class Game;
//This enum is used to structure the appear phase
enum class EntryState { FirstWord, SecondWord, Collsion };


class AuthorScreen
{
public:	
	AuthorScreen(Game& t_game, sf::Font t_font, sf::RenderWindow& t_window);
	~AuthorScreen();
	void update(sf::Time t_deltaTime,sf::RenderWindow& t_window, GameState& m_gameState);
	void render(sf::RenderWindow& t_window);

private:
	Game& m_game; // refrence to game object used to set game state
	sf::Font m_font; // font loaded by game

	sf::Texture m_texture;
	sf::Sprite m_authorScreen;

	//String used to quickly set up text that will be converted into a string array
	sf::String m_authorNamesMessage;
	//The text used to say Made By
	sf::Text m_madeByText;
	//The velocites by which the text enter and leave the screen
	sf::Vector2f m_enterVelocity;
	sf::Vector2f m_nameExitVelocity;
	sf::Vector2f m_madeByExitVelocity;

	//The loction of the basic piece of text
	sf::Vector2f m_madeByLocation;
	//The location used for the letter array for the first part of the animation
	sf::Vector2f m_arrayLocation;

	//The initial landing position for both pieces of text
	sf::Vector2f m_targetLocation;
	//The second landing location for the name text
	sf::Vector2f m_secondaryLocation;
	//STD Vectors which are associated with the name text
	//These are used due to their similarity to arrays and being able to change size easily
	std::vector<sf::Text> m_authorArray;
	std::vector<double> m_fallTime;
	std::vector<bool> m_fallIndicator;
	std::vector<bool> m_onscreenIndicator;
	std::vector<sf::Vector2f> m_arrayLocations;

	//This determines which direction the letters rotate in when paused
	int m_direction;
	//The below values are used to rotate the made by text and to determine its exit velocity
	double m_currentAngle;
	double m_targetAngle;
	double m_degreeIncrement;
	double m_pi = PI;

	float m_textSize;
	//This is used to find the exit velocity for the made by text
	int m_exitMultiplyer = 8;
	//This value is used to determine the x position of the letters for the name text
	int m_wordLength;
	//int pauseTimer;
	EntryState m_entryState;

	sf::Time m_cumulativeTime; // timer for screen
	//These timers are used to determine how long the puase state lasts for and when the letters start to move off screen.
	sf::Time m_pauseTimer;
	sf::Time m_dropTimer;
	AnimationState m_animationState; // which mode are we dong in/out/none

};

#endif // AUTHOR_SCREEN
