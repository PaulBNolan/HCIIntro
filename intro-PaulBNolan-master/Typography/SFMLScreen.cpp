/// <summary>
/// @Author: Paul Nolan
/// @Version 2.0
/// </summary>

#include "SFMLScreen.h"

SFMLScreen::SFMLScreen(Game & t_game, sf::Font t_font, sf::RenderWindow& t_window) :
	m_game(t_game),
	m_font(t_font),
	m_animationState(AnimationState::Appear)
{
	//Set up of the scale and its increment
	m_scale = 1.0;
	m_scaleIncrement = (float)0.005;
	//The set up of the transformation
	m_transformation = sf::Vector2f((float)t_window.getSize().x/2, (float)t_window.getSize().y/2);

	//Below the sprite and text are set up along with their relative and rotated locations

	if (m_logotexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{

	}
	m_SFMLLogo.setTexture(m_logotexture);


	m_spriteRelativeLocation = sf::Vector2f(-m_SFMLLogo.getGlobalBounds().width / 2, -m_SFMLLogo.getGlobalBounds().height / 2);
	

	m_SFMLLicence.setFont(m_font);
	m_SFMLLicence.setColor(m_grey);
	m_SFMLLicence.setCharacterSize(80);
	m_SFMLLicence.setString("SFML License");

	m_textRelativeLocation = sf::Vector2f(-m_SFMLLicence.getGlobalBounds().width / 2, -m_SFMLLicence.getGlobalBounds().height/2);

	m_textRotatedLocation = m_textRelativeLocation;
	m_spriteRotatedLocation = m_spriteRelativeLocation;
	//The setup of the degree and radian values
	m_currentAngleDegrees = 360;
	m_currentAngleRadians = 0;
	//The set up of the increments
    m_incrementDegrees = 3.0;
	m_incrementRadians = (float)(1.0 / 180) * m_incrementDegrees * (float)PI;
}


SFMLScreen::~SFMLScreen()
{
}

void SFMLScreen::update(sf::Time t_deltaTime, sf::RenderWindow& t_window, GameState& m_gameState)
{
	m_cumulativeTime += t_deltaTime;
	if (m_cumulativeTime.asMilliseconds() > 0 && m_animationState == AnimationState::Appear)
	{
		//The degree and radian values are altered
		m_currentAngleRadians -= m_incrementRadians;
		m_currentAngleDegrees += m_incrementDegrees;
		//The transperancry value is increased
		m_transparency += m_transparencyIncrement;
		if (m_transparency > 255)
		{
			m_transparency = 255;
		}
		m_grey = sf::Color(100, 100, 100, (sf::Uint8)m_transparency);
		//The scale value is decreased and applied
		m_scale -= m_scaleIncrement;
		m_SFMLLicence.setScale(sf::Vector2f(m_scale,m_scale));
		//The sprite and text are rotates
		rotateLogo();
		rotateText();

		if (m_scale <= 0.4)
		{
			m_animationState = AnimationState::None;
			m_SFMLLicence.setRotation(0);
		}
	}
	if (m_cumulativeTime.asMilliseconds() > 0 && m_animationState == AnimationState::None)
	{
		m_pauseTimer += t_deltaTime;

		if (m_pauseTimer.asSeconds() > 5.0)
		{
			m_animationState = AnimationState::Disappear;
		}
	}
	if (m_cumulativeTime.asMilliseconds() > 0 && m_animationState == AnimationState::Disappear)
	{
		m_currentAngleRadians -= m_incrementRadians;
		m_currentAngleDegrees += m_incrementDegrees;

		m_scale -= m_scaleIncrement;
		m_SFMLLicence.setScale(sf::Vector2f(m_scale, m_scale));
		//The transperancy value is decreased and applied
		m_transparency -= m_transparencyIncrement;
		m_grey = sf::Color(100, 100, 100, (sf::Uint8)m_transparency);
		m_SFMLLicence.setRotation(0);


		rotateLogo();
		rotateText();
		//The game state is changed to producer
		if (m_scale <= 0.0)
		{
			m_gameState = GameState::Producer;
		}
	}
}
void SFMLScreen::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_SFMLLogo);
	t_window.draw(m_SFMLLicence);
}
//The logo and its location are rotated in this function
void SFMLScreen::rotateLogo()
{
	//A set of values representing a matrix are set up and used to find the rotated location
	double radians = m_currentAngleRadians;
	double m_1A = cos(radians);
	double m_1B = -sin(radians);
	double m_2A = sin(radians);
	double m_2B = cos(radians);

	m_spriteRotatedLocation.x = m_1A * m_spriteRelativeLocation.x + m_2A * m_spriteRelativeLocation.y;
	m_spriteRotatedLocation.y = m_1B * m_spriteRelativeLocation.x + m_2B * m_spriteRelativeLocation.y;
	//The logo is rotated
	m_SFMLLogo.setRotation(m_currentAngleDegrees);

	m_SFMLLogo.setPosition(m_spriteRotatedLocation + m_transformation);
}

void SFMLScreen::rotateText()
{
	double radians = m_currentAngleRadians;
	double m_1A = cos(radians);
	double m_1B = -sin(radians);
	double m_2A = sin(radians);
	double m_2B = cos(radians);

	m_textRotatedLocation.x = m_1A * m_textRelativeLocation.x + m_2A * m_textRelativeLocation.y;
	m_textRotatedLocation.y = m_1B * m_textRelativeLocation.x + m_2B * m_textRelativeLocation.y;
	//The relative location is found again in order to take the scale change into account
	//The below line is used to ensure the location us found
	m_SFMLLicence.setRotation(0);
	m_textRelativeLocation = sf::Vector2f(-m_SFMLLicence.getGlobalBounds().width / 2, -m_SFMLLicence.getGlobalBounds().height / 2);
	m_SFMLLicence.setPosition(m_textRotatedLocation + m_transformation);
	m_SFMLLicence.setColor(m_grey);
	m_SFMLLicence.setRotation(m_currentAngleDegrees);
}