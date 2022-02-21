#include "stdafx.h"
#include "Platforms.h"

void Platforms::Platform(sf::Texture& texture_sheet, sf::IntRect texture_rect, bool damaging)
{
	this->sprite.setTexture(texture_sheet);
	this->sprite.setTextureRect(texture_rect);
}

const sf::FloatRect Platforms::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Platforms::update()
{
}

void Platforms::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
