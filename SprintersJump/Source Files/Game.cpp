#include "Game.h"
#include "Player.h"
#include "stdafx.h"

void Game::initWindow()
{
	this->window.create(sf::VideoMode(1280, 720), "SplintersJump", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(60);
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

Game::Game() 
{
	this->initWindow();
	this->initPlayer();
}

Game::~Game()
{
	delete this->player;
}

void Game::update()
{
	// Polling window events
	while (this->window.pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->window.close();
		else if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
			this->window.close();
	}
	this->updatePlayer();
	this->updateCollision();
}

void Game::updatePlayer()
{
	// this->player->updateMovement();
	this->player->update();
}

void Game::updateCollision()
{
	//Collision Bottom
	if (this->player->getGlobalBounds().top + this->player->getGlobalBounds().height > this->window.getSize().y)
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getGlobalBounds().left, 
			this->window.getSize().y - this->player->getGlobalBounds().height
		);

	}
}

void Game::render()
{
	this->window.clear();
	//stuff that renders in game
	this->renderPlayer();


	this->window.display();
}



const sf::RenderWindow& Game::getWindow() const
{
	return this->window;
}