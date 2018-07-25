/// <summary>
/// @Author: Paul Nolan
/// @Version 2.0
/// </summary>

#ifndef SPLASH_SCREEN
#define SPLASH_SCREEN


#include <SFML\Graphics.hpp>
#include "MyEnums.h"
#include "Game.h"
#include <string.h>
#include <iostream>
#include <math.h>
#define PI           3.14159265358979323846
class SplashScreen
{
public:
	SplashScreen(sf::RenderWindow& t_window);
	~SplashScreen();
	void update(sf::Time t_deltaTime, sf::RenderWindow& t_window, GameState& m_gameState);
	void render(sf::RenderWindow& t_window);
	//This function is used to rotate the position of the sprite
	void calculateRotation();
	//This function is used to start the exit animation of the sprite
	void changeState();
private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	AnimationState m_splashState;
	//This is used to find the sprites initial position during both animations
	sf::Vector2f m_relativeLocation;
	//This is used to find the sprites position after the previous value has been rotated
	sf::Vector2f m_imageRelativeLocation;
	//This vector is used to find by the sprites intended position on the screen
	sf::Vector2f m_transformation;
	//This value is used to set the current position of the texture
	sf::Vector2f m_textureLocation;
	//This value is used to determine the total angle the sprite and its position will be rotated by
	float m_transistionAngle;
	//This is used to determine the angle the sprite starts rotated at
	float m_startAngle;
	float m_currentAngleDegrees;
	float m_currentAngleRadians;
	float m_targetAngle;

	//These increments are used to rotate the sprite and its location respecitvely
	//Seperate values are used due to one being added and the other being subtracted from their respective values
	float m_incrementDegrees;
	float m_incrementRadians;

	//This value is used to determine the number of loops the animations will take
	float m_transistionTime;

	//These values are used to create a pseudo matrix that is used to rotate the sprites location
	float m_1A;
	float m_1B;
	float m_2A;
	float m_2B;
};

#endif