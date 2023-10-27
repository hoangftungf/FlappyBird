#include "game.h"
#include "lib.h"
#include <iostream>

void game::takeInput()
{
    while(SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            userInput.Type = input::QUIT;
            quit = true;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN || (event.type == SDL_KEYDOWN && 
		(event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_UP) && event.key.repeat == 0) )
        {
            userInput.Type = input::PLAY;
        }
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE && event.key.repeat == 0)
		{
			userInput.Type = input::PAUSE;
		}
    }
}

game::game()
{
    initGraphic();
    pipe.init();
    land.init();
    sound.init();
}

game::~game()
{
    shiba.Free();
    pipe.Free();
    land.Free();
    sound.Free();
    free();
    releaseGraphic();
}

void game::releaseGraphic()
{
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    SDL_DestroyRenderer( gRenderer );
    gRenderer = NULL;
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

bool game::initGraphic()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow( "Chim bay", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

void game::display()
{
    SDL_RenderPresent(gRenderer);
    SDL_RenderClear(gRenderer);
}

void game::renderScoreSmall()
{
	string s = to_string(score);
	signed char len = s.length();
	LTexture image;

	for (signed char i = len - 1; i >= 0; i--)
	{
		signed char number = s[i] - '0';
		if (number == 1)
		{
			image.Load("res/number/small/1.png", scaleNumberS);
		}
		else if (number == 2)
		{
			image.Load("res/number/small/2.png", scaleNumberS);
		}
		else if (number == 3)
		{
			image.Load("res/number/small/3.png", scaleNumberS);
		}
		else if (number == 4)
		{
			image.Load("res/number/small/4.png", scaleNumberS);
		}
		else if (number == 5)
		{
			image.Load("res/number/small/5.png", scaleNumberS);
		}
		else if (number == 6)
		{
			image.Load("res/number/small/6.png", scaleNumberS);
		}
		else if (number == 7)
		{
			image.Load("res/number/small/7.png", scaleNumberS);
		}
		else if (number == 8)
		{
			image.Load("res/number/small/8.png", scaleNumberS);
		}
		else if (number == 9)
		{
			image.Load("res/number/small/9.png", scaleNumberS);
		}
		else
		{
			image.Load("res/number/small/0.png", scaleNumberS);
		}
		image.Render(260 - image.getWidth() * (len - i - 1) * 0.75 - 5 * (len - i - 1), 268);
	}
	image.free();
}

void game::renderScoreLarge()
{
    string s = to_string(score);
	signed char len = s.length();
	LTexture image;

	for (signed char i = 0; i < len; i++)
	{
		signed char number = s[i] - '0';
		if (number == 1)
		{
			image.Load("res/number/large/1.png", 1);
		}
		else if (number == 2)
		{
			image.Load("res/number/large/2.png", 1);
		}
		else if (number == 3)
		{
			image.Load("res/number/large/3.png", 1);
		}
		else if (number == 4)
		{
			image.Load("res/number/large/4.png", 1);
		}
		else if (number == 5)
		{
			image.Load("res/number/large/5.png", 1);
		}
		else if (number == 6)
		{
			image.Load("res/number/large/6.png", 1);
		}
		else if (number == 7)
		{
			image.Load("res/number/large/7.png", 1);
		}
		else if (number == 8)
		{
			image.Load("res/number/large/8.png", 1);
		}
		else if (number == 9)
		{
			image.Load("res/number/large/9.png", 1);
		}
		else 
		{
			image.Load("res/number/large/0.png", 1);
		}
		image.Render((SCREEN_WIDTH - (image.getWidth() * len + (len - 1) * 10)) / 2 + (i + 30) * i, 100);
	}
	image.free();
}

void game::renderBestScore()
{
	ifstream fileIn("res/data/bestScore.txt");
	fileIn >> bestScore; 
	ofstream fileOut("res/data/bestScore.txt", ios::trunc);

	if (score > bestScore)
	{
		bestScore = score;
	}
	string s = to_string(bestScore);
	signed char len = s.length();
	LTexture image;

	for (signed char i = len-1; i >= 0; i--)
	{
		signed char number = s[i] - '0';
		if (number == 1)
		{
			image.Load("res/number/small/1.png", scaleNumberS);
		}
		else if (number == 2)
		{
			image.Load("res/number/small/2.png", scaleNumberS);
		}
		else if (number == 3)
		{
			image.Load("res/number/small/3.png", scaleNumberS);
		}
		else if (number == 4)
		{
			image.Load("res/number/small/4.png", scaleNumberS);
		}
		else if (number == 5)
		{
			image.Load("res/number/small/5.png", scaleNumberS);
		}
		else if (number == 6)
		{
			image.Load("res/number/small/6.png", scaleNumberS);
		}
		else if (number == 7)
		{
			image.Load("res/number/small/7.png", scaleNumberS);
		}
		else if (number == 8)
		{
			image.Load("res/number/small/8.png", scaleNumberS);
		}
		else if (number == 9)
		{
			image.Load("res/number/small/9.png", scaleNumberS);
		}
		else
		{
			image.Load("res/number/small/0.png", scaleNumberS);
		}
		image.Render(260 - image.getWidth()*(len-i-1)*0.75 - 5*(len - i - 1), 315);
	}
	image.free();

	fileOut << bestScore; 
	fileIn.close();
	fileOut.close();
}

void game::renderTitle()
{
	LTexture image;
	image.Load("res/image/title.png", 0.35);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 50);
	image.free();
}

void game::renderMessage()
{
	timeTab++;
	LTexture image;
	image.Load("res/image/prompt.png",1.5);

	if (timeTab <= 30)
		image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 180);
	else if (timeTab > 60) timeTab = 0;

	image.free();
}

void game::renderBackground()
{
	LTexture image ;
	image.Load("res/image/background.png", 1);
	image.Render(0, 0);
	image.free();
}

void game::renderBackgroundNight()
{
	LTexture image;
	image.Load("res/image/background-night.png", 1);
	image.Render(0, 0);
	image.free();
}

void game::renderLand()
{
	LTexture image;
	image.Load("res/image/land.png", 1);
	image.Render(0, SCREEN_HEIGHT- image.getHeight());
	image.free();
}

void game::renderCoTrang()
{
	LTexture image;
	image.Load("res/medal/coTrang.png", 0.15);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 250);
	image.free();
}

void game::renderPauseTab()
{
	LTexture image;
	image.Load("res/image/pauseTab.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 230);
	image.free();
}

void game::lightTheme()
{
	LTexture image;
	image.Load("res/image/Up/bird0.png", 2.2);
	image.Render(103, 305);
	image.free();
}

void game::darkTheme()
{
	LTexture image;
	image.Load("res/image/Up/mordecai0.png", 1.4);
	image.Render(103, 305);
	image.free();
}

void game::nextButton()
{
	LTexture image;
	image.Load("res/image/nextRight.png", 1);
	image.Render(149, 322);
	image.Load("res/image/nextLeft.png", 1);
	image.Render(88, 322);
	image.free();
}

bool game::changeTheme()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (((x > 149 && x < 149+13)  || (x > 88 && x < 88 + 13)) && (y > 322 && y < 322 + 16))
	{
		return true;
	}
	return false;
}

void game::renderGameOver()
{
	LTexture image;
	image.Load("res/image/gameOver.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 150);
	image.free();
}

void game::renderMedal()
{
	LTexture image;
		
	if (score > 20 && score <= 50)
	{
		image.Load("res/medal/m1.png", scaleNumberS);
	}
	else if (score > 50)
	{
		image.Load("res/medal/m2.png", scaleNumberS);
	}
	else 
	{
		image.Load("res/medal/m0.png", scaleNumberS);
	}
	image.Render(78, 275);

	image.free();
}

void game::replay()
{
	LTexture image;
	image.Load("res/image/replay.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 380);
	image.free();
}

bool game::checkReplay()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x > (SCREEN_WIDTH - 100)/2 && x < (SCREEN_WIDTH + 100) / 2 && y > 380 && y < 380 + 60)
	{
		return true;
	}
	return false;
}

void game::Restart()
{
	levelGame = 1;
    die = false;
    score = 0;
    shiba.resetTime();
}

void game::renderLevelGame(int levelGame)
{
	LTexture image;
	if(levelGame == 1) 
		image.Load("res/image/level1.png",0.1);
	else if(levelGame == 2)
		image.Load("res/image/level2.png",0.1);
	else if(levelGame == 3)
		image.Load("res/image/level3.png",0.1);

	image.Render(20	,20);
	image.free();
}

