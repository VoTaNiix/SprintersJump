#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
/* TODO
    -Background Image --> Gravity -> jump  --> Platforms w/ collision
        Done               Kind of done
    */

float x = 0;
float y = 0;
float velocityX = 0;
float velocityY = 0;
float accelerationX = 0;
float accelerationY = 0;

float gravity = 2;

void updateMovement() {

    if (y < 600)                  //If you are above ground
        velocityY += gravity;    //Add gravity
    else if (y > 600)             //If you are below ground
        y = 600;                 //That's not supposed to happen, put him back up

    velocityX = velocityX+accelerationX;
    velocityY += accelerationY;

    x += velocityX;
    y += velocityY;

    // stop movement doesn't work properly jet
    if (velocityX > 0 && Keyboard::isKeyPressed(Keyboard::A)) {
        velocityX = 0;
    }
    else if (velocityX < 0 && Keyboard::isKeyPressed(Keyboard::D)) {
        velocityX = 0;
    }
}



int main()
{
    RenderWindow window(sf::VideoMode(1280 , 720), "Splinters-Jump");
    window.setFramerateLimit(60);

    Sprite characterSprite;
    Sprite bgSprite;
    Texture characterImage;
    Texture bgImage;

   // characterSprite.setPosition(0,600);


    if (!characterImage.loadFromFile("./Textures/Character1nb.png")) {
        std::cout << "Could not load character texture";
        return 0;
    }
    else if (!bgImage.loadFromFile("./Textures/background.png")) {
        std::cout << "Could not load character texture";
        return 0;
    }
    bgSprite.setTexture(bgImage);
    characterSprite.setTexture(characterImage);

    while (window.isOpen())
    {
        // closes the Window on Click close Button
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) { // Jump velocity
                velocityY = -20;
            }
        }
        //initialize permanent movement into x direction
        if (Keyboard::isKeyPressed(Keyboard::A))
            velocityX = -5;
        else if (Keyboard::isKeyPressed(Keyboard::D))
            velocityX = 5;

        if (characterSprite.getPosition().x < 0) {
            velocityX = 0;
        }
        else if (characterSprite.getPosition().x == 1260) {
                x = 0;
                y = 600;
        }

        //gets called ever frame
        updateMovement();
        characterSprite.setPosition(x, y);

        //if (characterSprite.getPosition().x <= 0) {
        //    velocityX = 0;
        //}
        //else if (characterSprite.getPosition().x == 1260) {
        //    characterSprite.setPosition(0, 600);
        //}



        // Key input Movement
        /*int changeX = 0;
        int changeY = 0;*/
  /*      if (sf::Keyboard::isKeyPressed(Keyboard::A) && characterSprite.getPosition().x >= 0) {
            velocityX = -5;
        }
        else if (sf::Keyboard::isKeyPressed(Keyboard::D) && characterSprite.getPosition().x + characterSprite.getLocalBounds().width <= window.getSize().x) {
            velocityX = 5;
        }
        else {
            velocityX = 0;
        } if (sf::Keyboard::isKeyPressed(Keyboard::W) && characterSprite.getPosition().y >= 0) {
                velocityX = -5;
            }
        else if (sf::Keyboard::isKeyPressed(Keyboard::S) && characterSprite.getPosition().y + characterSprite.getLocalBounds().width <= window.getSize().y) {
                velocityY = 5;
            }
        else {
                velocityY = 0;
            }*/


        window.clear();
        window.draw(bgSprite);
        window.draw(characterSprite);
       // characterSprite.move(changeX, changeY);
        window.display();
    }

    return 0;
}