/// <summary>
/// @Author: Paul Nolan
/// @Version 2.0
/// </summary>

#include "AuthorScreen.h"
AuthorScreen::AuthorScreen(Game & t_game, sf::Font t_font ,sf::RenderWindow& t_window):
	m_game{t_game},
	m_font{t_font},
	m_animationState{AnimationState:: Appear}	
{
	//This is used to produce random results
	srand(time(NULL));
	//Entry state is set
	m_entryState = EntryState::FirstWord;

	m_textSize = 80;
	m_enterVelocity = sf::Vector2f(0, 5);
	//The name string
	m_authorNamesMessage = "PAUL NOLAN";
	//Setting the sizes for the std vectors
	m_authorArray.resize(m_authorNamesMessage.getSize());
    m_fallTime.resize(m_authorNamesMessage.getSize());
	m_fallIndicator.resize(m_authorNamesMessage.getSize());
	m_onscreenIndicator.resize(m_authorNamesMessage.getSize());
	m_arrayLocations.resize(m_authorNamesMessage.getSize());

	//A temporary value used to determine the target location and the arrays rough location
	sf::Text temp;
	temp.setString(m_authorNamesMessage);
	temp.setCharacterSize((unsigned int)m_textSize);
	temp.setFont(m_font);

	m_targetLocation.y = t_window.getSize().y / 2 - temp.getGlobalBounds().height;

	m_arrayLocation = sf::Vector2f((float)-temp.getGlobalBounds().width / 2.0f + (float)t_window.getSize().x / 2.0f, -m_textSize * 1.5f);
	m_wordLength = 0;
	//The set up of the std veector values
	for (int index = 0; index < (int)m_authorNamesMessage.getSize(); index++)
	{ 
		m_authorArray[index].setString(m_authorNamesMessage[index]);
		m_authorArray[index].setCharacterSize((unsigned int)m_textSize);
		m_authorArray[index].setFont(m_font);
		m_authorArray[index].setColor(sf::Color::Black);

		m_wordLength += (int)m_authorArray[index].getGlobalBounds().width;

		m_authorArray[index].setPosition(m_arrayLocation.x + m_wordLength, m_arrayLocation.y);

		m_fallTime[index] = (rand() % 300 + 1) / 100;
		m_fallIndicator[index] = false;
		m_onscreenIndicator[index] = true;
	}
	//The set up of the made by text
	m_madeByText.setString("Made By");
	m_madeByText.setFont(m_font);
	m_madeByText.setColor(sf::Color::Black);
	m_madeByText.setCharacterSize((unsigned int)m_textSize);
	m_madeByLocation = sf::Vector2f((float)-m_madeByText.getGlobalBounds().width / 2 + (float)t_window.getSize().x / 2, (float)-m_textSize * 1.5f);
	m_madeByText.setPosition(m_madeByLocation);

	m_secondaryLocation.y = m_targetLocation.y + m_madeByText.getGlobalBounds().height * 3;
	//Setup of the degree values to be used during collision
	m_degreeIncrement = 180.0 / 36;
	m_currentAngle = 0;
	m_targetAngle = 20;
	//The set up of the exit velocity for 
	m_nameExitVelocity.y = m_enterVelocity.y * 3;

	if (m_texture.loadFromFile("ASSETS\\IMAGES\\AuthorScreen.jpg"))
	{

	}
	m_authorScreen.setTexture(m_texture);
	m_authorScreen.setPosition(0, 0); 
	m_authorScreen.setScale(1.25, 1.7);
}

AuthorScreen::~AuthorScreen()
{
}



void AuthorScreen::update(sf::Time t_deltaTime, sf::RenderWindow& t_window, GameState& m_gameState)
{
	m_cumulativeTime += t_deltaTime;
	if (m_cumulativeTime.asMilliseconds() > 0 && m_animationState == AnimationState::Appear)
	{		
		//The movements of the array of letters
		if (m_entryState == EntryState::FirstWord)
		{
			m_arrayLocation += m_enterVelocity;
			m_wordLength = 0;
			for (int index = 0; index < (int)m_authorNamesMessage.getSize(); index++)
			{
				m_wordLength += (int)m_authorArray[index].getGlobalBounds().width;

				m_authorArray[index].setPosition(m_arrayLocation.x + m_wordLength, m_arrayLocation.y);
			}
			//This if situation ends this stage of the enter animation
			if (m_arrayLocation.y >= m_targetLocation.y)
			{
				m_entryState = EntryState::SecondWord;
			}
		}
		//The movement of the made by text
		if (m_entryState == EntryState::SecondWord)
		{
			m_madeByLocation += m_enterVelocity + m_enterVelocity;

			m_madeByText.setPosition(m_madeByLocation);
			if (m_madeByLocation.y >= m_targetLocation.y - m_textSize)
			{
				m_entryState = EntryState::Collsion;
			}
		}
		//This is where the colliion between text occurs
		if(m_entryState == EntryState::Collsion)
		{
			//The extra movement of the made by text
			if (m_madeByLocation.y < m_targetLocation.y)
			{
				m_madeByLocation.y += m_enterVelocity.y * 2;
				m_madeByText.setPosition(m_madeByLocation);
			}
			//This if situation rotates the made by text
			if (m_madeByLocation.y >= m_targetLocation.y)
			{
				if (m_currentAngle != m_targetAngle)
				{
					m_currentAngle += m_degreeIncrement;
					m_madeByText.setRotation((float)m_currentAngle);
				}
			}

			//The movement of the array of letters
			m_arrayLocation.y += m_enterVelocity.y * 2;
			m_wordLength = 0;
			for (int index = 0; index < (int)m_authorNamesMessage.getSize(); index++)
			{
				if (m_arrayLocation.y < m_secondaryLocation.y)
				{
					m_wordLength += (int)m_authorArray[index].getGlobalBounds().width;

					m_authorArray[index].setPosition(m_arrayLocation.x + m_wordLength, m_arrayLocation.y);
				}
			}
			//The switch to the pause state
			if (m_arrayLocation.y >= m_secondaryLocation.y)
			{
				m_animationState = AnimationState::None;
			}
		}
	}
	//This is the pause state
	if (m_cumulativeTime.asMilliseconds() > 0 && m_animationState == AnimationState::None)
	{
		//The exit velocity for the made by text iis calculated
		m_madeByExitVelocity.x =(float) cos(m_targetAngle * (m_pi/ 180.0)) * m_exitMultiplyer;
		m_madeByExitVelocity.y = (float)sin(m_targetAngle * (m_pi/180.0)) * m_exitMultiplyer;

		m_wordLength = 0;
		//This for loop is used to rotate the letters of the name text and to find their location for an array
		for (int index = 0; index < (int)m_authorNamesMessage.getSize(); index++)
		{
			m_direction = rand() % 2 + 1;
			m_wordLength += (int)m_authorArray[index].getGlobalBounds().width;
			if (m_direction == 1)
			{
				m_authorArray[index].rotate((float)m_degreeIncrement/20);
			}
			else if (m_direction == 2)
			{
				m_authorArray[index].rotate((float)-m_degreeIncrement/20);
			}
			m_arrayLocations[index] = sf::Vector2f(m_arrayLocation.x + m_wordLength, m_arrayLocation.y);
		}
		//This is the timer
		m_pauseTimer += t_deltaTime;
		if (m_pauseTimer.asSeconds() >= 3)
		{
			m_animationState = AnimationState::Disappear;
		}
	}

	if (m_cumulativeTime.asMilliseconds() > 0 && m_animationState == AnimationState::Disappear)
	{
		//The movement of the made by text during the disappear state
		m_madeByLocation += m_madeByExitVelocity;
		m_madeByText.setPosition(m_madeByLocation);

		m_dropTimer += t_deltaTime;
		//This for loop is used for the movement of the name text, when it starts moving and to determine which of its letters are still on screen
		for (int index = 0; index < (int)m_authorNamesMessage.getSize(); index++)
		{
			if (m_dropTimer.asSeconds() > m_fallTime[index])
			{
				m_fallIndicator[index] = true;
			}
			if (m_fallIndicator[index] == true)
			{
				m_arrayLocations[index] += m_nameExitVelocity;
				m_authorArray[index].setPosition(m_arrayLocations[index]);
			}

			if (m_arrayLocations[index].y > t_window.getSize().y)
			{
				m_onscreenIndicator[index] = false;
			}
		}
		//This for loop is used to determine is any of the name letters are still on screen and if they it causes the game state to change
		for (int index = 0; index < (int)m_authorNamesMessage.getSize(); index++)
		{
			if (m_onscreenIndicator[index] == true)
			{
				break;
			}
			if (index == m_authorNamesMessage.getSize() - 1 && m_onscreenIndicator[index] == false)
			{
	
				m_gameState = GameState::Licence;
			}
		}
	}

}
//The rendering function for this class
void AuthorScreen::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_authorScreen);
	for (int index = 0; index < (int)m_authorNamesMessage.getSize(); index++)
	{
		t_window.draw(m_authorArray[index]);
	}
	t_window.draw(m_madeByText);
}

