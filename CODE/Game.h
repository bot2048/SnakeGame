#pragma once
#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/window.hpp>
#include<iostream>
#include<ctime>
#include<vector>
#include<sstream>
#include<fstream>
class Game
{
private:

	//Variables
	int size;
	int screen;
	bool endgame;
	int food_x;
	int food_y;
	int snake_size;
	int dir;
	sf::Clock clock;
	float timer;
	float delay;
	int snake_x[100];
	int snake_y[100];
	int highscore;
	int yourscore;

	//WIndow
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videomode;

	//Mouse Positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Pricate Functions
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();

public:
	//constructors destructors
	Game();
	virtual ~Game();

	//accessors

	const bool running() const;
	const bool getEndGame()  const;

	//resources
	sf::Font font;

	//text
	sf::Text start_text;
	sf::Text start_text_2;
	sf::Text temp;
	sf::Text score;
	sf::Text game_over;
	sf::Text yourScore_text;
	sf::Text highscore_text;

	//textures and sprite
	sf::Texture t1;
	sf::Sprite sprite1;
	sf::Texture t2;
	sf::Sprite sprite2;
	sf::Texture t3;
	sf::Sprite sprite3;

	//sound
	sf::Sound s1;
	sf::SoundBuffer sb1;
	sf::Sound s2;
	sf::SoundBuffer sb2;


	//functions
	void pollEvents();
	void updateMousePositions();
	void move();
	void getDir();
	void update();
	void renderScreen1();
	void renderScreen2();
	void render();
};

