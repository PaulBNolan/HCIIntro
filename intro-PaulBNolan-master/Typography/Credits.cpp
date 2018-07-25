/// <summary>
/// @Author: Paul Nolan
/// @Version 2.0
/// </summary>
#include "Credits.h"


Credits::Credits(Game& t_game, sf::Font t_font, sf::RenderWindow& t_window) :
	m_game(t_game),
	m_font(t_font)
{
	//The names and job titles are loaded in from the yaml file
	if (CreditsLoader::load(m_credits))
	{

	}

	m_transformation = sf::Vector2f((float)t_window.getSize().x / 2, (float)t_window.getSize().y / 2);
	//The sizes of the text vectors are set to be equal to the lists loaded in
	m_names.resize(m_credits.m_name.size());
	m_titles.resize(m_credits.m_title.size());
	
	m_sizeNames = m_names.size();
	m_sizeTitles = m_titles.size();

	//The below for loops are used to set thee strings of the vectors
	int i = 0;
	for (auto &name : m_credits.m_name)
	{
		m_names[i].setString(name.m_name);
		i++;
	}

	i = 0;
	for (auto &title : m_credits.m_title)
	{
		m_titles[i].setString(title.m_title);
		i++;
	}

	m_velocity = sf::Vector2f(7, 7);

	m_loop = 0;
	m_no = 0;
	setNextValues();
	m_animationState = AnimationState::Appear;
	m_movementState = MovementState::Movement;
	m_degreeIncrement = 3;

	m_radianIncrement = 3 * (1.0 / 180) * PI;

	if (m_texture.loadFromFile("ASSETS\\IMAGES\\Credits.jpg"))
	{

	}
	m_creditsBackground.setTexture(m_texture);
	m_creditsBackground.setPosition(0, 0);
	m_creditsBackground.setScale(4.3, 3);
}


Credits::~Credits()
{
}

void Credits::update(sf::Time t_deltaTime, sf::RenderWindow& t_window, GameState& m_gameState)
{
	if (m_animationState == AnimationState::Appear)
	{
		if (m_creditState == CreditsState::Names)
		{
			if (m_movementState == MovementState::Movement)
			{
				if (m_namePosition != m_targetPosition)
				{
					movementsNames();
					//This situation is used to stop and set the position of the text once is has roughly reached its target location
					if ((m_no - m_loop == 0 && m_namePosition.y > m_targetPosition.y) 
						|| (m_no - m_loop == 1 && m_namePosition.x < m_targetPosition.x)
						|| (m_no - m_loop == 2 && m_namePosition.y < m_targetPosition.y)
						|| (m_no - m_loop == 3 && m_namePosition.x > m_targetPosition.x))

					{
						m_namePosition = m_targetPosition;
						m_names[m_no].setPosition(m_namePosition);
						m_movementState = MovementState::Rotation;
					}
				}
			}
			//This if situation is used to rotate the name text
			if (m_movementState == MovementState::Rotation)
			{
				if (m_currentAngleDegrees == 0)
				{
					m_creditState = CreditsState::Titles;
				}

				else if (m_currentAngleDegrees != 0)
				{
					rotateNames();
				}
			}
		}
		if (m_creditState == CreditsState::Titles)
		{
			if (m_titlePosition.x != m_namePosition.x)
			{
				movementTitles();
			}
			else
			{
				m_animationState = AnimationState::None;
			}
		}
	}
	if (m_animationState == AnimationState::None)
	{
		//This determines the amount of time the text remains still
		m_pauseTimer += t_deltaTime;
		//The below multiplication is used to compensate for the lack of resets inbetween use of this state
		if (m_pauseTimer.asSeconds() > 3 * (m_no + 1))
		{
			m_animationState = AnimationState::Disappear;
		}
	}
	if (m_animationState == AnimationState::Disappear)
	{
		//The below two if situtions carry out a similar process to the entry animation but in a different order
		if (m_movementState == MovementState::Rotation)
		{
			//This situation specifies which pieces of text are rotated and which ones are not
			if (((m_no - m_loop == 0) && m_currentAngleDegrees != 90) || (m_no - m_loop == 1 && m_currentAngleDegrees != 180) || (m_no - m_loop == 2 && m_currentAngleDegrees != 270))
			{
				rotateNames();
			}
			else
			{
				m_movementState = MovementState::Movement;
			}
		}

		if(m_movementState == MovementState::Movement)
		{
			movementsNames();
		}

		movementTitles();
		//This if situation checks if any of the text is on the screen. If not it begins preparing the next pair of words
		if ((m_namePosition.x + m_names[m_no].getGlobalBounds().width < 0 || m_namePosition.x > m_transformation.x * 2 || m_namePosition.y + m_names[m_no].getGlobalBounds().height < 0 || m_namePosition.y > m_transformation.y * 2)
			&& 
			(m_titlePosition.x + m_titles[m_no].getGlobalBounds().width < 0 || m_titlePosition.x > m_transformation.x * 2))
		{
			//This changes the text displayed
			m_no++;
	
			if (m_no >= m_sizeNames || m_no >= m_sizeTitles)
			{
				m_gameState = GameState::Exit;
			}
			//When four names have been used this situation is used to keep the code less complicated by preveting the need to add in extra conditions 
			//to if situations
			if (m_no - m_loop == 4)
			{
				m_loop += 4;
			}

				setNextValues();
			
		}
	}
}

void Credits::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_creditsBackground);
	t_window.draw(m_names[m_no]);
	t_window.draw(m_titles[m_no]);
}

//The below two functions are used to move the text in general
void Credits::movementTitles()
{
	//These situations are used to move and them stop and set the position of the title text once it has reached its target location
	if (m_no - m_loop == 0 || m_no - m_loop == 2)
	{
		m_titlePosition.x += m_velocity.x;

		if (m_titlePosition.x > m_namePosition.x && m_animationState == AnimationState::Appear)
		{
			m_titlePosition.x = m_namePosition.x;
		}
	}

	else if (m_no - m_loop == 1 || m_no - m_loop == 3)
	{
		m_titlePosition.x -= m_velocity.x;

		if (m_titlePosition.x < m_namePosition.x && m_animationState == AnimationState::Appear)
		{
			m_titlePosition.x = m_namePosition.x;
		}
	}
	m_titles[m_no].setPosition(m_titlePosition);
}

void Credits::movementsNames()
{
	//The below two situations are used to movee the text in a certain direction based on its position in the text list 
	//and the current state of the animation
	if (m_animationState == AnimationState::Appear)
	{
	    if (m_no - m_loop == 0)
		{
			m_namePosition.y += m_velocity.y;
		}

		else if (m_no - m_loop == 1)
		{
			m_namePosition.x -= m_velocity.x;
		}
		else if (m_no - m_loop == 2)
		{
			m_namePosition.y -= m_velocity.y;
		}
		else if (m_no - m_loop == 3)
		{
			m_namePosition.x += m_velocity.x;
		}
	}

	if (m_animationState == AnimationState::Disappear)
	{

	    if (m_no - m_loop == 0)
		{
			m_namePosition.x += m_velocity.x;
		}

		else if (m_no - m_loop == 1)
		{
			m_namePosition.y += m_velocity.y;
		}
		else if (m_no - m_loop == 2)
		{
			m_namePosition.x -= m_velocity.x;
		}
		else if (m_no - m_loop == 3)
		{
			m_namePosition.y -= m_velocity.y;
		}
	}
	m_names[m_no].setPosition(m_namePosition);
}
//This function is used to rotate the name text
void Credits::rotateNames()
{
	m_currentAngleDegrees += m_degreeIncrement;

	m_currentAngleRadians -= m_radianIncrement;
	
	//This code is used to rotate the positions of the text
	double radians = m_currentAngleRadians;
	double m_1A = cos(radians);
	double m_1B = -sin(radians);
	double m_2A = sin(radians);
	double m_2B = cos(radians);

	m_nameRotatedPosition.x = m_1A * m_nameRelativePosition.x + m_2A * m_nameRelativePosition.y;
	m_nameRotatedPosition.y = m_1B * m_nameRelativePosition.x + m_2B * m_nameRelativePosition.y;
	m_namePosition = sf::Vector2f(m_nameRotatedPosition.x + m_transformation.x, m_nameRotatedPosition.y + m_transformation.y);
	m_names[m_no].setPosition(m_namePosition);

	//This ensures that the text is rotated correctly enough to be viewed upon stopping
	if (m_animationState == AnimationState::Appear)
	{
		if (m_currentAngleDegrees >= 360)
		{
			m_currentAngleDegrees = 0;
		}
	}
	//These situations are used to rotate the text in the direction there leaving the screen
	if (m_animationState == AnimationState::Disappear)
	{
		if (m_no - m_loop == 0 && m_currentAngleDegrees > 90)
		{
			m_currentAngleDegrees = 90;
		}

		else if (m_no - m_loop == 1 && m_currentAngleDegrees > 180)
		{
			m_currentAngleDegrees = 180;
		}
		else if (m_no - m_loop == 2 && m_currentAngleDegrees > 270)
		{
			m_currentAngleDegrees = 270;
		}
	}
	m_names[m_no].setRotation((float)m_currentAngleDegrees);
}
//This function is used to set up the next pair of words use
void Credits::setNextValues()
{
	//The text font is set and its relative position is found
	m_names[m_no].setFont(m_font);
	m_titles[m_no].setFont(m_font);

	m_nameRelativePosition = sf::Vector2f(-m_names[m_no].getGlobalBounds().width / 2, -m_names[m_no].getGlobalBounds().width / 2);

	//These situations are used to find the current texts position, their target position and the angle they are rotated by
	if (m_no - m_loop == 0)
	{
		m_namePosition.x = m_nameRelativePosition.x + m_transformation.x;
		m_namePosition.y = -m_names[m_no].getGlobalBounds().height;

		m_targetPosition = sf::Vector2f(m_namePosition.x, m_namePosition.y + m_transformation.y);

		m_titlePosition = sf::Vector2f(-m_titles[m_no].getGlobalBounds().width, m_transformation.y + m_titles[m_no].getGlobalBounds().height);

		m_currentAngleRadians = 0;
	}
	else if (m_no - m_loop == 1)
	{
		m_namePosition.x = m_names[m_no].getGlobalBounds().height + m_transformation.x * 2;
		m_namePosition.y = -m_names[m_no].getGlobalBounds().width + m_transformation.y;

		m_targetPosition = sf::Vector2f(m_namePosition.x - m_transformation.x, m_namePosition.y);

		m_currentAngleDegrees = 90;
		m_currentAngleRadians = 270 * (1.0 / 180) * PI;

		m_titlePosition = sf::Vector2f(m_titles[m_no].getGlobalBounds().width + m_transformation.x * 2, m_transformation.y + m_titles[m_no].getGlobalBounds().height);
	}
	else if (m_no - m_loop == 2)
	{
		m_namePosition.x = m_transformation.x + m_names[m_no].getGlobalBounds().width/2;
		m_namePosition.y = m_names[m_no].getGlobalBounds().height + m_transformation.y * 2;

		m_targetPosition = sf::Vector2f(m_namePosition.x, m_namePosition.y - m_transformation.y);

		m_currentAngleDegrees = 180;
		m_currentAngleRadians = 180 * (1.0 / 180) * PI;

		m_titlePosition = sf::Vector2f(-m_titles[m_no].getGlobalBounds().width, m_transformation.y + m_titles[m_no].getGlobalBounds().height);
	}
	else if (m_no - m_loop == 3)
	{
		m_namePosition.x = -m_names[m_no].getGlobalBounds().height;
		m_namePosition.y = -m_names[m_no].getGlobalBounds().width + m_transformation.y;

		m_targetPosition = sf::Vector2f(m_namePosition.x, m_namePosition.y + m_transformation.y);

		m_currentAngleDegrees = 270;
		m_currentAngleRadians = 90 * (1.0 / 180) * PI;
		

		m_titlePosition = sf::Vector2f(m_titles[m_no].getGlobalBounds().width + m_transformation.x * 2, m_transformation.y + m_titles[m_no].getGlobalBounds().height);
	}

	m_names[m_no].setRotation((float)m_currentAngleDegrees);
	m_names[m_no].setPosition(m_namePosition);
	m_titles[m_no].setPosition(m_titlePosition);

	m_animationState = AnimationState::Appear;
	m_creditState = CreditsState::Names;
}