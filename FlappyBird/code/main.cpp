#include "game.h"
#include "lib.h"
#include <time.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


using namespace std;

int main(int argc, char** argv)
{
    int timeFrame = 7;
    game g;
    bool isMenu = 0;
    bool isPause = 0;
    bool isDark = 0;

    while(!g.isQuit())
    {
        if (g.isDie())
        {
            if (isMenu) {
                g.sound.playHit();
            }
            g.userInput.Type = game::input::NONE;
            while(g.isDie() && !g.isQuit())
            {
                g.takeInput();
                if (isMenu == 1 && g.userInput.Type == game::input::PLAY)
                {
                    if (g.checkReplay())
                    {
                        isMenu = 0;
                    }
                    g.userInput.Type = game::input::NONE;   
                }
                if (!isDark) g.renderBackground();
                else g.renderBackgroundNight();
                g.renderLevelGame(g.levelGame);
                g.pipe.render();
                g.land.render();
                if (isMenu)
                {
                    g.renderLevelGame(g.levelGame);
                    g.shiba.render();
                    g.shiba.fall();
                    g.renderGameOver();
                    g.renderCoTrang();
                    g.renderMedal();
                    g.renderScoreSmall();
                    g.renderBestScore();
                    g.replay();
                }
                else
                {
                    g.pipe.init();
                    g.shiba.init(isDark); 
                    g.shiba.render();
                    g.renderLevelGame(g.levelGame);
                    g.renderMessage();
                    g.renderTitle();
                    if (g.userInput.Type == game::input::PLAY)
                    {
                        timeFrame = 7;
                        g.Restart();
                        isMenu = 1;
                        g.userInput.Type = game::input::NONE;
                    }
                    g.land.update();
                }
                g.display();
            }
        }
        else
        {
            g.takeInput();

            if (g.userInput.Type == game::input::PAUSE)
            {
                isPause = abs(1 - isPause);
                g.userInput.Type = game::input::NONE;
            }

            if (isPause == 0 && g.userInput.Type == game::input::PLAY)
            {
                g.sound.playBreath();
                g.shiba.resetTime(); 
                g.userInput.Type = game::input::NONE;
            }

            if (!isDark) g.renderBackground();
            else g.renderBackgroundNight();

            g.pipe.render();
            g.land.render();
            g.shiba.render();
            g.renderScoreLarge();
            g.renderLevelGame(g.levelGame);

            
            if (!isPause)
            {
                g.shiba.update(g.getPipeWidth(), g.getPipeHeight());
                g.pipe.update();
                g.land.update();
                if (LTexture::checkPoint) g.sound.playPoint();
                LTexture::checkPoint = false;
            }
            else
            {
                g.renderLevelGame(g.levelGame);
                g.shiba.render();
                g.renderCoTrang();
                g.renderPauseTab();
                g.renderScoreSmall();
                g.renderBestScore();
                g.replay();
                g.sound.renderSound();
                if (!isDark) g.lightTheme(); else g.darkTheme();
                g.nextButton();
                if (g.userInput.Type == game::input::PLAY)
                {
                    if (g.checkReplay())
                    {
                        isPause = 0;
                    }
                    else if (g.sound.checkSound())
                    {
                    }
                    else if (g.changeTheme())
                    {
                        isDark = abs(1 - isDark);               
                        g.shiba.init(isDark);
                    }
                    g.userInput.Type = game::input::NONE;
                }
            }
            
            //Hienthi Game
            g.display();
        }
        //Nang cap level
        if (LTexture::score >= 10 && LTexture::score < 20)
        {
            timeFrame = 5;
            g.levelGame = 2;
        }
        else if (LTexture::score >= 20)
        {
            timeFrame = 3;
            g.levelGame = 3;
        }
        else if(LTexture::score < 10)
        {
            timeFrame = 7;
            g.levelGame = 1;
        }


         SDL_Delay(timeFrame);     
    }
    return 0;
}
