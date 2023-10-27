#pragma once

#include "doge.h"
#include "pipe.h"
#include "land.h"
#include "sound.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class game:LTexture
{
public:
    struct input
    {
        enum type { QUIT, PLAY, NONE, PAUSE};
        type Type;
    };
    input userInput;
    doge shiba;
    pipe pipe;
    sound sound;
    land land;
public:
    game();

    ~game();

    bool initGraphic();

    bool isQuit() 
    {
        return quit; 
    }

    bool isDie()
    {
        return die;
    }

    int getPipeWidth()
    {
        return pipe.width();
    }

    int getPipeHeight()
    {
        return pipe.height();
    }

    void takeInput();

    void display();

    void releaseGraphic();

    void renderScoreSmall();

    void renderScoreLarge();

    void renderBestScore();

    void renderTitle();

    void renderCoTrang();

    void renderMessage();

    void renderBackground();

    void renderBackgroundNight();

    void renderLand();

    void renderPauseTab();

    void lightTheme();

    void darkTheme();

    void nextButton();

    bool changeTheme();

    void renderGameOver();

    void renderMedal();

    void replay();

    void renderLevelGame(int levelGame);

    bool checkReplay();

    void Restart();

    int levelGame = 1;
    short int bestScore;
    short int timeTab = 0;

private: 
    const double scaleNumberS = 0.65;
};