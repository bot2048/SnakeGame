#include "Game.h"

void Game::initVariables() // initialise variables
{

	this->window = nullptr; // initialise window pointer to null
	this->screen = 1; 
	this->endgame = false;
	this->size = 32; // size of single square(building block) used
	this->food_x = 10; // initial position of food
	this->food_y = 10;
	this->snake_size = 4; // initial size of snake
	this->snake_x[0] = 4; // initial position of snake
	this->snake_x[1] = 3;
	this->snake_x[2] = 2;
	this->snake_x[3] = 1;
	this->snake_y[0] = 0;
	this->snake_y[1] = 0;
	this->snake_y[2] = 0;
	this->snake_y[3] = 0;
	this->dir = 1;  // initial direction of snake
	this->timer = 0; 
	this->delay = 0.1; //set speed
	this->yourscore = -1;// checks for game over condition


	// intialises high score by reading from file
	std::ifstream readFile;
	readFile.open("resources/highscore.txt");
	if (readFile.is_open())
	{
		while (!readFile.eof())
		{
			readFile >> highscore;
		}
	}

	readFile.close();


}

void Game::initWindow() 
{
	//sets dimension of game window
	this->videomode.height = 20*size;
	this->videomode.width = 30*size;
	this->window = new sf::RenderWindow(this->videomode, "SnakeGame");
	this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
	//imports font style from files
	this->font.loadFromFile("resources/Fonts/bruh2.ttf");
}

void Game::initText()
{
	//initialises all the text
	this->start_text.setFont(this->font);
	this->start_text.setCharacterSize(40);
	this->start_text.setFillColor(sf::Color::White);
	this->start_text.setString("Play");
	this->start_text.setPosition(440,300);

	this->start_text_2.setFont(this->font);
	this->start_text_2.setCharacterSize(40);
	this->start_text_2.setFillColor(sf::Color::White);
	this->start_text_2.setString("Exit");
	this->start_text_2.setPosition(440, 500);
	
	this->score.setFont(this->font);
	this->score.setCharacterSize(30);
	this->score.setFillColor(sf::Color::White);
	this->score.setPosition(5, 5);


	this->game_over.setFont(this->font);
	this->game_over.setCharacterSize(130);
	this->game_over.setFillColor(sf::Color::Red);
	this->game_over.setString("GameÍOver");
	this->game_over.setPosition(105, 15);

	this->yourScore_text.setFont(this->font);
	this->yourScore_text.setCharacterSize(40);
	this->yourScore_text.setFillColor(sf::Color::White);
	this->yourScore_text.setPosition(115, 200);

	this->highscore_text.setFont(this->font);
	this->highscore_text.setFillColor(sf::Color::White);
	this->highscore_text.setCharacterSize(40);
	this->highscore_text.setPosition(615, 200);


	this->t1.loadFromFile("resources/images/white.png");
	this->sprite1.setTexture(this->t1);

	this->t2.loadFromFile("resources/images/green.png");
	this->sprite2.setTexture(this->t2);

	this->t3.loadFromFile("resources/images/red.png");
	this->sprite3.setTexture(this->t3);


	this->sb1.loadFromFile("resources/audio/ra.wav");
	this->s1.setBuffer(this->sb1);

	this->sb2.loadFromFile("resources/audio/go.wav");
	this->s2.setBuffer(this->sb2);
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endgame;
}


void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}



void Game::updateMousePositions()
{
	//updates mouse position rel to windows
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
	//std::cout << this->mousePosView.x << "\t" << this->mousePosView.y <<"\n";

	if (this->screen == 1)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->start_text.getGlobalBounds().contains(this->mousePosView))
			{
				this->screen = 2;
			}
			else if (this->start_text_2.getGlobalBounds().contains(this->mousePosView))
			{
				this->window->close();
			}
		}
	}
}
void Game::move()
{
	for (int i = this->snake_size;i > 0;--i)
	{
		this->snake_x[i] = this->snake_x[i - 1];
		this->snake_y[i] = this->snake_y[i - 1];
	}
	if (this->dir == 2) this->snake_y[0] += 1;
	else if (this->dir == -1) this->snake_x[0] -= 1;
	else if (this->dir == 1) this->snake_x[0] += 1;
	else if (this->dir == -2) this->snake_y[0] -= 1;

	if ((this->snake_x[0] == this->food_x) && (this->snake_y[0] == this->food_y))
	{
		this->s1.play();
		this->snake_size++;
		this->food_x = rand() % 30; 
		this->food_y = rand() % 20;
	}

	for (int i = 1;i < snake_size;i++)
	{
		if (  (  this->snake_x[0] == this->snake_x[i] && this->snake_y[0] == this->snake_y[i]  )  ||  this->snake_x[0]<0||this->snake_x[0]>=30 || this->snake_y[0]<0 || this->snake_y[0]>=20)  
		{
			this->s2.play();
			this->yourscore = this->snake_size - 4;
			this->screen = 1;
			this->food_x = 10;
			this->food_y = 10;
			this->snake_x[0] = 3;
			this->snake_x[1] = 3;
			this->snake_x[2] = 2;
			this->snake_x[3] = 0;
			this->snake_y[0] = 0;
			this->snake_y[1] = 0;
			this->snake_y[2] = 0;
			this->snake_y[3] = 0;
			this->dir = 1;
			if (this->snake_size - 4 > this->highscore)
			{
				std::ofstream writeFile("resources/highscore.txt");
				if (writeFile.is_open())
				{
					this->highscore = this->snake_size - 4;
				}
				writeFile << this->highscore;
				writeFile.close();
			}

			this->snake_size = 4;
			break;
		}
	}
}

void Game::getDir()
{
	float time = this->clock.getElapsedTime().asSeconds();
	this->clock.restart();
	this->timer += time;
	if (this->dir == 1 || this->dir == -1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)|| sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dir = -2;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dir = 2;

	}

	else if (this->dir == 2 || this->dir == -2) 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dir = -1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dir = 1;
	}
	if (this->timer > this->delay)
	{
		this->timer = 0;
		move();
	}
	std::stringstream ss;
	ss << "Points: " << (this->snake_size-4);
	this->score.setString(ss.str());
}

void Game::update()
{

	this->pollEvents();
	if(this->screen==1)
		this->updateMousePositions();
	else if(this->screen == 2)
		this->getDir();
}

void Game::renderScreen1()
{
	this->window->clear();
	this->window->draw(this->start_text);
	this->window->draw(this->start_text_2);
	if (this->yourscore>=0)
	{
		
		this->window->draw(this->game_over);
		std::stringstream s1;
		s1 << "Points: " << this->yourscore;
		std::stringstream s2;
		s2 << "Highscore: " << this->highscore;
		this->yourScore_text.setString(s1.str());
		this->highscore_text.setString(s2.str());
		this->window->draw(this->yourScore_text);
		this->window->draw(this->highscore_text);
	}

	this->window->display();
}

void Game::renderScreen2()
{
	this->window->clear();
			this->sprite1.setPosition(0, 0);
			this->window->draw(this->sprite1);
		
	this->sprite2.setPosition(this->food_x * size, this->food_y * size);
	this->window->draw(this->sprite2);
	for (int i = 0;i < this->snake_size;i++)
	{
		this->sprite3.setPosition(snake_x[i] * size, snake_y[i] * size);
		this->window->draw(this->sprite3);
	}
	this->window->draw(this->score);
	this->window->display();
}

void Game::render()
{
	if (this->screen == 1)
		renderScreen1();
	if (this->screen == 2)
		renderScreen2();
}
