#include "stdafx.h"
#include "Player.h"



Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
	this->initPhysics();
}

Player::~Player()
{

}

void Player::updateMovement()
{
	this->animState = IDLE;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) // Move player left
	{
		this->animState = MOVING_LEFT;
		this->move(-1.f, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) // Move player right
	{
		this->animState = MOVING_RIGHT;
		this->move(1.f, 0.f);
	}


	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) // Move player up
	//{
	//	this->sprite.move(0.f, -1.f);
	//}
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) // Move player down
	//{
	//	this->sprite.move(0.f, 1.f);
	//}
}



void Player::updatePhysics()
{
	//Gravity
	this->velocity.y += 1.0 * this->gravity;

	//Limit Gravity
	if (std::abs(this->velocity.x) > this->gravityMax)
	{
		this->velocity.y = this->gravityMax * ((this->velocity.y < 0.f) ? -1.f : 1.f);
	}

	//Deceleration
	this->velocity *= this->airResistance;

	//Limit Deceleration
	if (std::abs(this->velocity.x) < this->velocityMin)
		this->velocity.x = 0.f;
	if (std::abs(this->velocity.y) < this->velocityMin)
		this->velocity.y = 0.f;
	this->sprite.move(this->velocity.x, this->velocity.y);

}

void Player::move(const float dir_x, const float dir_y)
{
	//Acceleration
	this->velocity.x += dir_x * this->acceleration;


	//Limit velocity
	if (std::abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
	}
}

void Player::initPhysics()
{
	this->velocityMax = 10.f;
	this->velocityMin = 1.f;
	this->acceleration = 1.5f;
	this->airResistance = 0.93f;
	this->velocity.x = 0.f;
	this->gravity = 4.f;
	this->gravityMax = 10.f;
}

void Player::update() 
{
	this->updateMovement();
	this->updateAnimations();
	this->updatePhysics();
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}


void Player::updateAnimations()
{
	if (this->animState == IDLE)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f)
		{
			this->currentFrame.top = 0;
			this->currentFrame.left += 32.f;
			if (this->currentFrame.left >= 256.f)
				this->currentFrame.left = 0;
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == MOVING_RIGHT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f)
		{
			this->currentFrame.top = 128.f;
			this->currentFrame.left += 32.f;
			if (this->currentFrame.left >= 360.f)
				this->currentFrame.left = 0;
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else
		this->animationTimer.restart();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(258, 6, 32, 55);

	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(2.5f, 2.5f);
}

void Player::initAnimations()
{
	this->animationTimer.restart();
}

void Player::initVariables()
{	
	this->animState = IDLE;
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("./Textures/vampire-removebg.png"))
	{
		std::cout << "player Texture could not be loaded" << "\n";
	}
}