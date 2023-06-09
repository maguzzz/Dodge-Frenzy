#include<iostream>
#include <fstream>
#include "SFML/Graphics.hpp"

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
	bool newScore = false;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Dodge Frenzy");
	window.setFramerateLimit(60);

	//Adding Font
	sf::Font pixelFont;
	pixelFont.loadFromFile("Fonts/DePixelHalbfett.ttf");

	//Score Text
	sf::Text Score;
	Score.setFont(pixelFont);
	Score.setString("Score: \n" + to_string(ScoreNum));
	Score.setFillColor(sf::Color::White);
	Score.setPosition(20, 20);
	Score.setScale(.6, .6);

	//High Score
	sf::Text HighScore;
	HighScore.setFont(pixelFont);
	HighScore.setString("High Score:\n" + to_string(HighScoreNum));
	HighScore.setFillColor(sf::Color::White);
	HighScore.setPosition(1110, 20);
	HighScore.setScale(.6, .6);

	//New High Score
	sf::Text newHighScoreText;
	newHighScoreText.setFont(pixelFont);
	newHighScoreText.setFillColor(sf::Color::White);
	newHighScoreText.setPosition(430, 300);
	newHighScoreText.setScale(1, 1);

	//Death Screen
	sf::Text deathText;
	deathText.setFont(pixelFont);
	deathText.setString("You are Dead");
	deathText.setFillColor(sf::Color::White);
	deathText.setPosition(350, 200);
	deathText.setScale(2, 2);

	//Options to exit Game
	sf::Text options;
	options.setFont(pixelFont);
	options.setString("[ESC] to exit      [R] to restart");
	options.setFillColor(sf::Color::White);
	options.setPosition(350, 550);
	options.setScale(1, 1);

	//Declearing a Rectangle called rec
	sf::RectangleShape rect;
	sf::Vector2f rectanglePosition(620, 360);
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

			//Square movement
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) playerPosition.y -= playerSpeed;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) playerPosition.x -= playerSpeed;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) playerPosition.y += playerSpeed;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) playerPosition.x += playerSpeed;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

			if (playerStatus == false && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				window.close();
				main();
			}
			rect.setPosition(rectanglePosition);
		}

		//Checking if player is Alive and adding Points
		if (playerStatus == true) {
			player.setFillColor(sf::Color::Green);
			ScoreNum = ScoreNum + 1;

			Score.setString("Score: \n" + to_string(ScoreNum));
			HighScore.setString("High Score:\n" + to_string(HighScoreNum));

			ifstream infile("score.txt"); // Opening file
			getline(infile, tempScore); // Reading file

			HighScoreNum = stoi(tempScore);

			//Increasing High Score if its lower then the current score and Checking for new Highscore
			if (ScoreNum >= HighScoreNum) {
				HighScoreNum = ScoreNum;
				newScore = true;
			}
		}
		else {
			player.setFillColor(sf::Color::Red);
			playerSpeed = 0;


			newHighScoreText.setString("New High Score " + to_string(HighScoreNum));
			ofstream outfile("score.txt"); // Opening file
			outfile << HighScoreNum ; // Writeing score in file
			outfile.close(); // Closeing file

		}

		EnemyVelocityX += ScoreNum / EnemyVelocityX / (4000 + (rand() % 8001));
		EnemyVelocityY += ScoreNum / EnemyVelocityY / (4000 + (rand() % 8001));

		// Calculating Hitbox by Moveing Origin point of Cube
		if (!(playerPosition.y + 50 <= rectanglePosition.y || playerPosition.y >= rectanglePosition.y + 100 /* Horizontal */ || playerPosition.x + 50 <= rectanglePosition.x || playerPosition.x >= rectanglePosition.x + 100)) playerStatus = false;


		//Bound Check Cube								-100 Is Padding
		if (rectanglePosition.x < 0 || rectanglePosition.x > 1280 - 100)EnemyVelocityX *= -1;
		if (rectanglePosition.y < 0 || rectanglePosition.y > 720 - 100)EnemyVelocityY *= -1;

		//Bound Check Cube                                    -50 Is Padding
		if (playerPosition.x < 0 || playerPosition.x > 1280 - 50 || playerPosition.y < 0 || playerPosition.y > 720 - 50) playerStatus = false;

		//physics
		rectanglePosition.x += EnemyVelocityX;
		rectanglePosition.y += EnemyVelocityY;

		rect.setPosition(rectanglePosition);
		player.setPosition(playerPosition);

		//Render
		window.clear();
		if (playerStatus == true) {
			window.draw(player);
			window.draw(rect);
			window.draw(Score);
			window.draw(HighScore);
		}
		else {
			if(newScore == true) window.draw(newHighScoreText);
			window.draw(deathText);
			window.draw(options);
		}
		window.display();
	}
	return 0;
}
