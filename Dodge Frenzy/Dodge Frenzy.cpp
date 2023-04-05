#include<iostream>
#include <fstream>
#include "SFML/Graphics.hpp"
#include <windows.h>

using namespace std;

int main()
{
	//Enemy
	float EnemyVelocityX = 4;
	float EnemyVelocityY = 4;

	//Player
	int playerSpeed = 6;
	bool playerStatus = true;
	//Score
	int ScoreNum = 0;
	int HighScoreNum = 0;
	string tempScore;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Dodge Frenzy");
	window.setFramerateLimit(60);

	//Adding Font
	sf::Font pixelFont;
	pixelFont.loadFromFile("Fonts/DePixelHalbfett.ttf");

	//Adding Score Text
	sf::Text Score;
	Score.setFont(pixelFont);
	Score.setString("Score: \n" + to_string(ScoreNum));
	Score.setFillColor(sf::Color::White);
	Score.setPosition(20, 20);
	Score.setScale(.6, .6);

	//Adding High Score
	sf::Text HighScore;
	HighScore.setFont(pixelFont);
	HighScore.setString("High Score:\n" + to_string(HighScoreNum));
	HighScore.setFillColor(sf::Color::White);
	HighScore.setPosition(1110, 20);
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) playerPosition.y -= playerSpeed;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) playerPosition.x -= playerSpeed;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) playerPosition.y += playerSpeed;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) playerPosition.x += playerSpeed;

			rect.setPosition(rectanglePosition);
		}

		//Checking if player is Alive and adding Points
		if (playerStatus == true) {
			player.setFillColor(sf::Color::Green);
			ScoreNum = ScoreNum + 1;

			Score.setString("Score: \n" + to_string(ScoreNum));
			HighScore.setString("High Score:\n" + to_string(HighScoreNum));

			ifstream infile("score.txt"); // Datei zum Lesen öffnen
			getline(infile, tempScore); // Eingabe aus der Datei lesen

			HighScoreNum = stoi(tempScore);

			//Increasing High Score if its lower then the current score
			if (ScoreNum >= HighScoreNum) HighScoreNum = ScoreNum + 1;
		}
		else {
			player.setFillColor(sf::Color::Red);
			playerSpeed = 0;

			ofstream outfile("score.txt"); // Datei zum Schreiben öffnen
			outfile << HighScoreNum - 1; // Eingabe in die Datei schreiben
			outfile.close(); // Datei schließen
		}

		
		EnemyVelocityX += ScoreNum / EnemyVelocityX / ( 4000 + (rand() % 5001));
		EnemyVelocityY += ScoreNum / EnemyVelocityY / (4000 + (rand() % 5001));

		// Calculating Hitbox by Moveing Origin point of Cube
		if (!(playerPosition.y + 50 <= rectanglePosition.y || playerPosition.y >= rectanglePosition.y + 100 /* Horizontal */ || playerPosition.x + 50 <= rectanglePosition.x || playerPosition.x >= rectanglePosition.x + 100)) playerStatus = false;


		//Bound Check Cube								-100 Is Padding
		if (rectanglePosition.x < 0 || rectanglePosition.x > 1280 - 100){
			EnemyVelocityX *= -1;
		}
		if (rectanglePosition.y < 0 || rectanglePosition.y > 720 - 100) {
			EnemyVelocityY *= -1;	
		}



		cout << EnemyVelocityX << " X" << endl;
		cout << EnemyVelocityY << " Y" << endl;

		//Bound Check Cube                                    -50 Is Padding
		if (playerPosition.x < 0 || playerPosition.x > 1280 - 50 || playerPosition.y < 0 || playerPosition.y > 720 - 50) playerStatus = false;

		//physics
		rectanglePosition.x += EnemyVelocityX;
		rectanglePosition.y += EnemyVelocityY;

		rect.setPosition(rectanglePosition);
		player.setPosition(playerPosition);

		//Render
		window.clear();
		window.draw(player);
		window.draw(rect);
		window.draw(Score);
		window.draw(HighScore);
		window.display();
	}
	return 0;
}
