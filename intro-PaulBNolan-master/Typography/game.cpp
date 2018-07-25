/// <summary>
/// @mainpage: Typography
/// @Author: Paul Nolan
/// @Version 2.0
/// 
/// Project Summary:A program to display five different animations for the
/// author screen, smfl license, producer screen, splash screen and credits
/// Dates and Time of sessions: 
/// 02/12/17 6:00 6hr Splash Screen
/// 9/12/17 4:00 5hr Author and Sfml screens
/// 10/12/17 1:00 4hr Producer screen
/// 11/12/17 12:00 6hr Credits and bringing the code to college standards
/// Total
/// 15hr
/// </summary>

#include "Game.h"
#include <iostream>


/// <summary>
/// constructor for game setup window and initial state
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800, 800, 32 }, "SFML Game" },
	m_exitGame{false} //when true game will exit,

{
	loadFont(); // load font 


	//The below situations create the objects for each animation
	m_AuthorScreen = new AuthorScreen{ *this,m_font, m_window};
	m_SplashScreen = new SplashScreen{m_window};
	m_SFMLScreen = new SFMLScreen{ *this,m_font, m_window };
	m_producerScreen = new ProducerScreen{ *this, m_font, m_window };
	m_credits = new Credits{ *this, m_font, m_window };
}

/// <summary>
/// destructor for game class
/// </summary>
Game::~Game()
{
	if (m_AuthorScreen != nullptr) // never delete nothing
	{
		delete(m_AuthorScreen);
	}
}

/// <summary>
/// main method for game executes the main game loop
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render();
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if ( sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
			//This is used to change the state of the splash screen while it is paused
			if (sf::Keyboard::isKeyPressed)
			{
				m_SplashScreen->changeState();
			}
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	switch (m_currentGameState)
	{
	case GameState::None:		
		break;
	case GameState::Author:
		m_AuthorScreen->update(t_deltaTime, m_window, m_currentGameState);
		break;
	case GameState::Exit:
		m_window.close();
		break;
	case GameState::Licence:
		m_SFMLScreen->update(t_deltaTime, m_window, m_currentGameState);
		break;
	case GameState::Producer:
		m_producerScreen->update(t_deltaTime, m_window, m_currentGameState);
		break;
	case GameState::Splash:
		m_SplashScreen->update(t_deltaTime, m_window, m_currentGameState);
		break;
	case GameState::Credits:
		m_credits->update(t_deltaTime, m_window, m_currentGameState);
	default:
		break;
	}
}

//This functions helps to render each animation via accessing their respective classes render function
void Game::render()
{
	m_window.clear();
	switch (m_currentGameState)
	{
	case GameState::None:
		break;
	case GameState::Author:
		m_AuthorScreen->render(m_window);
		break;
	case GameState::Licence:
		m_SFMLScreen->render(m_window);
		break;
	case GameState::Producer:
		m_producerScreen->render(m_window);
		break;
	case GameState::Splash:
		m_SplashScreen->render(m_window);
		break;
	case GameState::Credits:
		m_credits->render(m_window);
	default:
		break;
	}
	m_window.display();
}

/// <summary>
/// load the font
/// </summary>
void Game::loadFont()
{
	if (!m_font.loadFromFile("ASSETS//FONTS//AuthorScreenFont.ttf"))
	{
		std::cout << "Font failed to load" << std::endl;
	}
}
