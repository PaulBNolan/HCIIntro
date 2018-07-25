/// <summary>
/// @Author: Paul Nolan
/// @Version 2.0
/// </summary>

#ifndef CREDITS
#define CREDITS

#include "Game.h"
#include "CreditsLoader.h"
#include "yaml-cpp\yaml.h"

enum class CreditsState { Names, Titles };
enum class MovementState { Movement, Rotation };

class Credits
{
public:
	Credits(Game& t_game, sf::Font t_font, sf::RenderWindow& t_window);
	~Credits();

	void update(sf::Time t_deltaTime, sf::RenderWindow& t_window, GameState& m_gameState);
	void render(sf::RenderWindow& t_window);
	//This function moves the title text
	void movementTitles();
	//These functions move and rotate the name text
	void movementsNames();
	void rotateNames();
	//This function prepares the next piece of text
	void setNextValues();
private:
	Game& m_game;
	//This struct is used to load in the names and job titles from the Yaml file onto the below std vectors

	sf::Texture m_texture;
	sf::Sprite m_creditsBackground;
	TextData m_credits;

	sf::Font m_font;
	std::vector<sf::Text> m_names;
	std::vector<sf::Text> m_titles;
	//These values are used to position and rotate the name text
	sf::Vector2f m_namePosition;
	sf::Vector2f m_nameRelativePosition;
	sf::Vector2f m_nameRotatedPosition;

	sf::Vector2f m_titlePosition;

	sf::Vector2f m_targetPosition;
	//These values are used to move the pieces of text and translate them onto the screen when rotating
	sf::Vector2f m_velocity;
	sf::Vector2f m_transformation;

	//These values are used to rotate the name text
	double m_currentAngleDegrees;
	double m_currentAngleRadians;
	double m_degreeIncrement;
	double m_radianIncrement;

	//These ints are used to designate which piece of text is being used and which directions they will move in
	int m_no;
	int m_loop;
	int m_sizeNames;
	int m_sizeTitles;

	AnimationState m_animationState;
	CreditsState m_creditState;
	MovementState m_movementState;

	sf::Time m_pauseTimer;
};

#endif