/// <summary>
/// @Author: Paul Nolan
/// @Version 2.0
/// </summary>

#include "ProducerScreen.h"

//The values assocated with each text are found and set up
ProducerScreen::ProducerScreen(Game& t_game, sf::Font t_font, sf::RenderWindow& t_window) :
	m_game(t_game),
	m_font(t_font)
{
	m_nameText.setFont(m_font);
	m_nameText.setCharacterSize(40);
	m_nameText.setString("Pete");
	m_nameCurrentLocation = sf::Vector2f(-m_nameText.getGlobalBounds().width, (float)t_window.getSize().y);
	m_nameText.setPosition(m_nameCurrentLocation);

	m_producedByText.setFont(m_font);
	m_producedByText.setCharacterSize(40);
	m_producedByText.setString("Produced By");
	m_producedByCurrentLocation = sf::Vector2f((float)t_window.getSize().x, -m_producedByText.getGlobalBounds().height);
	m_producedByText.setPosition(m_producedByCurrentLocation);

	m_nameTargetLocation = sf::Vector2f((float)t_window.getSize().x / 2 - m_nameText.getGlobalBounds().width / 2,(float)t_window.getSize().y / 2);
	m_producedByTargetLocation = sf::Vector2f(t_window.getSize().x / 2 - m_producedByText.getGlobalBounds().width / 2, t_window.getSize().y / 2 - m_producedByText.getGlobalBounds().height);

	m_angleName = atan((m_nameTargetLocation.y - m_nameCurrentLocation.y) / (m_nameTargetLocation.x - m_nameCurrentLocation.x));
	m_nameVelocityXComponent = 8.45;
	m_nameVelocityYComponent = 17.2;
	m_nameVelocity = sf::Vector2f((float)cos(m_angleName) * (float)m_nameVelocityXComponent, (float)sin(m_angleName) * (float)m_nameVelocityYComponent);

	m_angleProducedBy = atan((m_producedByTargetLocation.y - m_producedByCurrentLocation.y) / (m_producedByTargetLocation.x - m_producedByCurrentLocation.x));
	m_producedByVelocityXComponent = 9.7;
	m_producedByVelocityYComponent = 18.7;
	m_producedByVelocity = sf::Vector2f((float)-cos(m_angleProducedBy) * (float)m_producedByVelocityXComponent, (float)-sin(m_angleProducedBy) * (float)m_producedByVelocityYComponent);

	m_animationState = AnimationState::Appear;
	m_transistionState = TransistionState::FirstWord;

	m_acceleration = sf::Vector2f(0, 9.8f);


	if (m_texture.loadFromFile("ASSETS\\IMAGES\\Producer.jpg"))
	{

	}
	m_producerScreen.setPosition(0, 0);
	m_producerScreen.setTexture(m_texture);
	m_producerScreen.setScale(2.8, 5);
}


ProducerScreen::~ProducerScreen()
{
}

void ProducerScreen::update(sf::Time t_deltaTime, sf::RenderWindow& t_window, GameState& m_gameState)
{
	if (m_animationState == AnimationState::Appear)
	{
		//The first word appears on screen. Once it reaches its intended destination the second word starts moving
		if (m_transistionState == TransistionState::FirstWord)
		{
			if (m_producedByVelocity.y > 0)
			{
				m_producedByCurrentLocation += m_producedByVelocity;
				//This is done to take into account the number of frames persecond
				m_producedByVelocity.y -= m_acceleration.y * t_deltaTime.asSeconds();
			}
			m_producedByText.setPosition(m_producedByCurrentLocation);
			if (m_producedByVelocity.y < 0)
			{
				m_transistionState = TransistionState::SecondWord;
			}
		}
		//The seecond word moves to its target location. Once this is done the pause state starts
		if (m_transistionState == TransistionState::SecondWord)
		{
			if (m_nameVelocity.y < 0)
			{
				m_nameCurrentLocation += m_nameVelocity;
				m_nameVelocity.y += m_acceleration.y * t_deltaTime.asSeconds();
			}
			m_nameText.setPosition(m_nameCurrentLocation);

			if (m_nameVelocity.y > 0)
			{
				m_animationState = AnimationState::None;
			}
		}
	}
	if (m_animationState == AnimationState::None)
	{
		m_pauseTimer += t_deltaTime;
		if (m_pauseTimer.asSeconds() > 3)
		{
			m_animationState = AnimationState::Disappear;
		}
		//The values for the velocities are switched so that they will now go along each others paths.
		sf::Vector2f temp = m_nameVelocity;
		m_nameVelocity = m_producedByVelocity;
		m_producedByVelocity = temp;
	}
	//Both pieces of text start leaving the screen now on each others paths
	if (m_animationState == AnimationState::Disappear)
	{
		m_producedByCurrentLocation -= m_producedByVelocity;
		m_nameCurrentLocation -= m_nameVelocity;

		m_producedByVelocity.y -= m_acceleration.y * t_deltaTime.asSeconds();
		m_nameVelocity.y += m_acceleration.y * t_deltaTime.asSeconds();

		m_producedByText.setPosition(m_producedByCurrentLocation);
		m_nameText.setPosition(m_nameCurrentLocation);

		if (m_producedByCurrentLocation.y > t_window.getSize().y && m_nameCurrentLocation.y < 0)
		{
			m_gameState = GameState::Splash;
		}
	}
}

void ProducerScreen::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_producerScreen);
	t_window.draw(m_producedByText);
	t_window.draw(m_nameText);
}