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
    Color button_color[4][2] = {{RED, MAROON},
                                {YELLOW, GOLD},
                                {BLUE, DARKBLUE},
                                {LIME, GREEN}};
    std::string options[4] = {"A", "B", "C", "D"};
    bool pressed = false;
    Rectangle rec_next{1030, 115, 135, 65};
    int mode = 0;
    std::string ans = "";
    bool correctAns = false;

  public:
    GamePage();
    ~GamePage()
    {
    }
    void draw();
    void update();
    void playGame();
};

#endif