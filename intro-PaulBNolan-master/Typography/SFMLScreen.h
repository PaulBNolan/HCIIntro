/// <summary>
/// @Author: Paul Nolan
/// @Version 2.0
/// </summary>

#ifndef SFML_SCREEN
#define SFML_SCREEN

#include <SFML\Graphics.hpp>
#include "Game.h"

class Game;
class SFMLScreen
{
public:
	SFMLScreen(Game & t_game, sf::Font t_font, sf::RenderWindow& t_window);
	~SFMLScreen();
	void update(sf::Time t_deltaTime, sf::RenderWindow& t_window, GameState& m_gameState);
	//Functions used to rotate the sprite and text
	void rotateText();
	void rotateLogo();

	void render(sf::RenderWindow& t_window);

private:
	AnimationState m_animationState;
	Game& m_game;

	sf::Texture m_logotexture;
	sf::Sprite m_SFMLLogo;

	sf::Text m_SFMLLicence;
	sf::Font m_font;
	//The color used and its transparency value
	float m_transparency = 15;
	float m_transparencyIncrement = 2;
	sf::Color m_grey{ 255,255,255,(sf::Uint8)m_transparency };

	//The relative and rotated locations for the text and sprite
	sf::Vector2f m_textRelativeLocation;
	sf::Vector2f m_textRotatedLocation;
	sf::Vector2f m_spriteRelativeLocation;
	sf::Vector2f m_spriteRotatedLocation;
	//The transformation used to translate the above on screen
	sf::Vector2f m_transformation;

	//The values used to rotate the text/sprite and their locations
	float m_currentAngleDegrees;
	float m_currentAngleRadians;
	//The increments used to alter the above
	float m_incrementDegrees;
	float m_incrementRadians;
	// value used to determine the size of the text
	float m_scale;
	float m_scaleIncrement;

	sf::Time m_cumulativeTime; // timer for screen
	sf::Time m_pauseTimer;
};
#endif
