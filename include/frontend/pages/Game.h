#ifndef FRONTEND_PAGE_GAME
#define FRONTEND_PAGE_GAME

#include "dictionary/word.h"
#include "frontend/pages/Word.h"
#include "dictionary/random.h"
#include "raylib.h"
#include <cstring>
#include <iostream>
#include <vector>

class GamePage
{
  private:
    Rectangle dictPagesRects[5];
    std::vector<std::string> dictPages = {"WORD", "Definition", "Favorites", "History", "Game"};
    short int selectedDictPage         = 4;
    Random r;
    Dictionary* currentDictionary = new Dictionary(dictDirs[*CurrentState::currentDict], *CurrentState::currentDict);
    std::vector<std::string> quiz;
    bool gameQuiz = false;
    std::string options[4] = {"A", "B", "C", "D"};
    bool pressed = false;
    int mode = 0;
    std::string ans = "";
    bool correctAns = false, start = false, choosen = false;
    int ansOption = 0;
    bool isBreakNewLines = false;

    int COUNTDOWN_DURATION = 15;
    int cnt = COUNTDOWN_DURATION;
    double currentTime = GetTime();
    double previousTime = currentTime;

  public:
    GamePage();
    ~GamePage()
    {
    }
    void draw();
    void buildAnswer();
    void drawTimer();
    void checkAns();
    void drawQuestion();
    void update();
    void playGame();
    void drawCountDown(int timeLeft);
};

#endif