/// <summary>
/// @Author: Paul Nolan
/// @Version 2.0
/// </summary>

#ifndef PRODUCER_SCREEN
#define PRODUCER_SCREEN

#include <SFML\Graphics.hpp>
#include "Game.h"

enum class TransistionState { FirstWord, SecondWord};

class ProducerScreen
{
public:
	ProducerScreen(Game& t_game, sf::Font t_font, sf::RenderWindow& t_window);
	~ProducerScreen();
	void update(sf::Time t_deltaTime, sf::RenderWindow& t_window, GameState& m_gameState);
	void render(sf::RenderWindow& t_window);

private:
	Game& m_game;

	sf::Font m_font;
	sf::Text m_producedByText;
	sf::Text m_nameText;

	sf::Texture m_texture;
	sf::Sprite m_producerScreen;

	//These are the launch angles for the two pieces of text
	double m_angleProducedBy;
	double m_angleName;
	//These values are used to ensure the text arrive at the target location
	double m_producedByVelocityXComponent;
	double m_producedByVelocityYComponent;
	double m_nameVelocityXComponent;
	double m_nameVelocityYComponent;

	//The target locations foor the text
	sf::Vector2f  m_producedByTargetLocation;
	sf::Vector2f  m_nameTargetLocation;
	//The current locations for the text
	sf::Vector2f  m_producedByCurrentLocation;
	sf::Vector2f  m_nameCurrentLocation;
	//The velocities for the text
	sf::Vector2f  m_producedByVelocity;
	sf::Vector2f  m_nameVelocity;
	//The acceleration for the text
	sf::Vector2f m_acceleration;
	//The animation and transistion states for the text
	AnimationState m_animationState;
	TransistionState m_transistionState;

	sf::Time m_pauseTimer;
};

#endif