#include <iostream>
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;


int main()
{
    Window window(VideoMode(1280, 720), "Dodge Frenzy");
    window.setFramerateLimit(60);


    while (window.isOpen())
    {
        //Checking if event happends
        Event event;
        while (window.pollEvent(event))
        {

        }
    }
}
