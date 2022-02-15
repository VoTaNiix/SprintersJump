#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
/* TODO
    -Background Image --> Gravity -> jump  --> Platforms w/ collision
*/



int main()
{
    RenderWindow window(sf::VideoMode(1280 , 720), "Splinters-Jump");

    Texture characterImage;
    Texture bgImage;

    Sprite bgSprite;
    Sprite characterSprite;

    bgSprite.setTexture(bgImage);
    characterSprite.setTexture(characterImage);

    if (!characterImage.loadFromFile("./Textures/Character1nb.png")) {
        std::cout << "Could not load character texture";
        return 0;
    }
    //else if (!bgImage.loadFromFile("./Textures/background.png")) {
    //    std::cout << "Could not load background texture";
    //    return 0;
    //}

    while (window.isOpen())
    {
        // closes the Window on Click close Button
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // Key input Movement
        float changeX = 0;
        float changeY = 0;
        if (sf::Keyboard::isKeyPressed(Keyboard::A) && characterSprite.getPosition().x >= 0) {
            changeX = -0.3;
        }
        else if (sf::Keyboard::isKeyPressed(Keyboard::D) && characterSprite.getPosition().x + characterSprite.getLocalBounds().width <= window.getSize().x) {
            changeX = 0.3;
        }
        else {
            changeX = 0;
        } if (sf::Keyboard::isKeyPressed(Keyboard::W) && characterSprite.getPosition().y >= 0) {
                changeY = -0.4;
            }
        else if (sf::Keyboard::isKeyPressed(Keyboard::S) && characterSprite.getPosition().y + characterSprite.getLocalBounds().width <= window.getSize().y) {
                changeY = 0.4;
            }
        else {
                changeY = 0;
            }


        window.clear();
        window.draw(characterSprite);
        characterSprite.move(changeX, changeY);
        window.display();
    }

    return 0;
}