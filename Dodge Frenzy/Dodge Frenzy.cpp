#include <iostream>
#include "SFML/Graphics.hpp"

using namespace std;


int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Dodge Frenzy");
    window.setFramerateLimit(60);


    //Declearing a Rectangle called rec
    sf::RectangleShape rect;
    //A vector with 2 floats vertical and horizontal alignment. It has its on var to change it later
    sf::Vector2f rectanglePosition(620,360);
    rect.setPosition(rectanglePosition);
    //Setting the size for the Rectangle
    rect.setSize(sf::Vector2f(100,100));

    float xVelocity = 3;
    float yVelocity = 3;

    while (window.isOpen())
    {
        //Checking if event happends
        sf::Event eventCheck;
        //Pointer to Event Returning True or False
        while (window.pollEvent(eventCheck))
        {
            //Checking if  the event is a Close butten press and closeing the Window
            if (eventCheck.type == sf::Event::Closed) window.close();

            //If Escape is Pressed window will be closed 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

        }
        //Bound Check                                           -100 Is Padding
        if (rectanglePosition.x < 0 || rectanglePosition.x > 1280 - 100) xVelocity *= -1;
        if (rectanglePosition.y < 0 || rectanglePosition.y > 720 - 100) yVelocity *= -1;


        //physics
        rectanglePosition.x += xVelocity;
        rectanglePosition.y += yVelocity;
        rect.setPosition(rectanglePosition);


        //Render
        window.clear();
        window.draw(rect);
        window.display();

    }
    return 0;
}
