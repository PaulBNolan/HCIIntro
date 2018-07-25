/// <summary>
/// @Author: Paul Nolan
/// @Version 2.0
/// </summary>
#include "SplashScreen.h"

SplashScreen::SplashScreen(sf::RenderWindow& t_window)
{
	//Setting the angle values for the entry animation
	m_startAngle = 270;
	m_targetAngle = 360;
	m_currentAngleDegrees = m_startAngle;
	m_transistionAngle = m_targetAngle - m_startAngle;
	//This is done to make sure the transistion angle is a positive
	if (m_transistionAngle < 0)
	{
		m_transistionAngle = -m_transistionAngle;
	}
	//The number of required frames is set
	m_transistionTime = 60;
	//The degree increment is found
	m_incrementDegrees = m_transistionAngle / m_transistionTime;

	//The radian value is set and its increment is found
	m_currentAngleRadians = 0;
	m_incrementRadians = (float)(PI * (1.0/180)) * m_transistionAngle / m_transistionTime;

	//The sprites texture and scale is set
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\SplashScreen.jpg"))
	{
		std::cout << "Texture Load Failed" << std::endl;
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(0.42f, 0.70f);
	//The relative location and transformation is found using the width and height of the window use
	m_relativeLocation = sf::Vector2f(-(float)(t_window.getSize().y), 0);
	m_transformation = sf::Vector2f(0, (float)(t_window.getSize().x));

	//Initial state set
	m_splashState = AnimationState::Appear;
}


SplashScreen::~SplashScreen()
{
}

void SplashScreen::update(sf::Time t_deltaTime, sf::RenderWindow& t_window, GameState& m_gameState)
{
	if (m_splashState == AnimationState::Appear)
	{
		//The increments are applied
		m_currentAngleDegrees += m_incrementDegrees;
		m_currentAngleRadians -= m_incrementRadians;
		//The sprite is rotated
		m_sprite.setRotation(m_currentAngleDegrees);
		//The sprites location is rotated
		calculateRotation();
		//When the current angle matches the entered target angle the state will change causing the animation to end
		if (m_currentAngleDegrees == m_targetAngle)
		{
			m_splashState = AnimationState::None;
		}
		//These if situations are used in cases where the degrees go above 360 or below 0
		if (m_currentAngleDegrees < 0)
		{
			m_currentAngleDegrees = 360;
		}
		else if (m_currentAngleDegrees > 360)
		{
			m_currentAngleDegrees = 0;
		}
	}
	//In this state no movement occurs but the values are prepared for the exit animation
	else if (m_splashState == AnimationState::None)
	{
		m_textureLocation = sf::Vector2f(m_imageRelativeLocation.x, m_imageRelativeLocation.y + m_transformation.y);
		m_relativeLocation = m_textureLocation - m_transformation;

		m_startAngle = 0;
		m_targetAngle = 90;
		m_currentAngleDegrees = 0;
		m_currentAngleRadians = 0;
		m_transformation = sf::Vector2f((float)(t_window.getSize().x), (float)(t_window.getSize().y));
	}
	//This state is very similar to the appear state with one key difference
	if (m_splashState == AnimationState::Disappear)
	{
		m_currentAngleDegrees += m_incrementDegrees;
		m_currentAngleRadians -= m_incrementRadians;

		m_sprite.setRotation(m_currentAngleDegrees);
		calculateRotation();
		//This situation causes the games state to change to the final stage of the program.
		if (m_currentAngleDegrees > m_targetAngle)
		{
			m_gameState = GameState::Credits;
		}
	}

}

void SplashScreen::calculateRotation()
{
	double radians = m_currentAngleRadians;
	m_1A = cos(radians);
	m_1B = -sin(radians);
	m_2A = sin(radians);
	m_2B = cos(radians);

	m_imageRelativeLocation.x = m_1A * m_relativeLocation.x + m_2A * m_relativeLocation.y;
	m_imageRelativeLocation.y = m_1B * m_relativeLocation.x + m_2B * m_relativeLocation.y;
	m_textureLocation = sf::Vector2f(m_imageRelativeLocation.x + m_transformation.x, m_imageRelativeLocation.y + m_transformation.y);
	m_sprite.setPosition(m_textureLocation);
}

void SplashScreen::changeState()
{
	if (m_splashState == AnimationState::None)
	{
		m_splashState = AnimationState::Disappear;
	}
}
void SplashScreen::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_sprite);
}
