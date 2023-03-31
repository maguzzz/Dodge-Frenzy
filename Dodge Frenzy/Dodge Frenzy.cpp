#include <iostream>
#include "SFML/Graphics.hpp"

using namespace std;

int main()
{
	//Enemy
	float EnemyVelocityX = 4;
	float EnemyVelocityY = 4;

	//Player
	float playerSpeed = 6;
	//Score
	int ScoreNum = 000000000;
	int HighScoreNum = 000000000;


	sf::RenderWindow window(sf::VideoMode(1280, 720), "Dodge Frenzy");
	window.setFramerateLimit(60);

	//Adding Font
	sf::Font pixelFont;
	pixelFont.loadFromFile("C:\\Users\\Markus\\Documents\\DePixelHalbfett.ttf");

	//Adding Score Text
	sf::Text Score;
	Score.setFont(pixelFont);
	Score.setString("Score: \n000000000");
	Score.setFillColor(sf::Color::White);
	Score.setPosition(20, 20);
	Score.setScale(.6, .6);

	//Adding High Score
	sf::Text HighScore;
	HighScore.setFont(pixelFont);
	HighScore.setString("High Score:\n000000000");
	HighScore.setFillColor(sf::Color::White);
	HighScore.setPosition(1110,20);
	HighScore.setScale(.6, .6);

	//Declearing a Rectangle called rec
	sf::RectangleShape rect;
	//A vector with 2 floats vertical and horizontal alignment. It has its on var to change it later
	sf::Vector2f rectanglePosition(620, 360);
	//Setting the size for the Rectangle
	rect.setSize(sf::Vector2f(100, 100));
	rect.setPosition(rectanglePosition);


	//Player
	sf::RectangleShape player;
	sf::Vector2f playerPosition(520, 260);
	player.setSize(sf::Vector2f(50, 50));
	player.setPosition(playerPosition);


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

			//Squar movement
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				playerPosition.y -= playerSpeed;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				playerPosition.x -= playerSpeed;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				playerPosition.y += playerSpeed;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				playerPosition.x += playerSpeed;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
				ScoreNum = ScoreNum + 10;
				cout << "ScoreNumber +1" << endl;
				cout << ScoreNum << endl;
			}
			rect.setPosition(rectanglePosition);
		}

		// Calculating Hitbox by Moveing Origin point of Cube
		if (playerPosition.y + 50 <= rectanglePosition.y || playerPosition.y >= rectanglePosition.y + 100 /* Horizontal */||  playerPosition.x + 50 <= rectanglePosition.x || playerPosition.x >= rectanglePosition.x + 100) {
			//cout << "Alive" << endl;
			player.setFillColor(sf::Color::Green);
		}

		else {
			//cout << "Dead" << endl;
			player.setFillColor(sf::Color::Red);
		}

		//player.setFillColor(sf::Color::Green);




		//Bound Check Cube                                    -100 Is Padding
		if (rectanglePosition.x < 0 || rectanglePosition.x > 1280 - 100) EnemyVelocityX *= -1;
		if (rectanglePosition.y < 0 || rectanglePosition.y > 720 - 100) EnemyVelocityY *= -1;

		//Checking Position for Debugging
		//cout << "Rectangle | " << rectanglePosition.y << " " << rectanglePosition.x << endl;
		//cout << "Player    | " << playerPosition.y << " " << playerPosition.x << endl;

		//physics
		rectanglePosition.x += EnemyVelocityX;
		rectanglePosition.y += EnemyVelocityY;
		rect.setPosition(rectanglePosition);
		player.setPosition(playerPosition);

		//Render
		window.clear();
		window.draw(rect);
		window.draw(player);
		window.draw(Score);
		window.draw(HighScore);
		window.display();

	}
	return 0;
}
