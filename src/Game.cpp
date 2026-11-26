
#include "Game.h"
#include "Tile.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  
}

Game::~Game()
{
    
}

bool Game::init()
{
    gamestate = MENU;
    board = std::make_shared<Board>(window);
    board->init();   
    font = std::make_unique<sf::Font>();
    font->openFromFile("../Data/Fonts/OpenSans-Bold.ttf");
    HostText = std::make_unique<sf::Text>(*font);
    HostText->setFont(*font);
    HostText->setString("Host Game");
    HostText->setFillColor(sf::Color::White);
    HostText->setCharacterSize(50);
    HostText->setPosition({ 900,100 });

    JoinText = std::make_unique<sf::Text>(*font);
    JoinText->setFont(*font);
    JoinText->setString("Join Game");
    JoinText->setFillColor(sf::Color::White);
    JoinText->setCharacterSize(50);
    JoinText->setPosition({ 900,200 });
    return true;
}

void Game::update(float dt)
{

}

void Game::render()
{
    board->render();  
    if (gamestate == MENU)
    {
        window.draw(*HostText);
        window.draw(*JoinText);
    }
}

void Game::mouseButtonPressed(const sf::Event::MouseButtonPressed* event)
{
    board->mouseButtonPressed(event);
    if (gamestate == MENU)
    {
        if (HostText->getGlobalBounds().contains(sf::Vector2f(event->position)))
        {
            gamestate = PLAYING;
            std::cout << "Creating server." << std::endl;
            server = std::make_unique<Server>();
            server->init();
            server->run();
        }
        else if (JoinText->getGlobalBounds().contains(sf::Vector2f(event->position)))
        {
            gamestate = PLAYING;
            std::cout << "attemting to connect." << std::endl;
            client = std::make_unique<Client>();
            client->connect();
            client->run();
        }
    }
}

void Game::mouseButtonReleased(const sf::Event::MouseButtonReleased* event)
{
    board->mouseButtonReleased(event);    
}

void Game::keyPressed(const sf::Event::KeyPressed* event)
{

}

void Game::keyReleased(const sf::Event::KeyReleased* event)
{

}

void Game::mouseMoved(const sf::Event::MouseMoved* event)
{
    board->mouseMoved(event);
}




