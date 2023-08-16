#ifndef FRONTEND_PAGE_GAME
#define FRONTEND_PAGE_GAME

#include "dictionary/word.h"
#include "frontend/pages/Word.h"
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

  public:
    GamePage();
    ~GamePage()
    {
    }
    void draw();
    void update();
};

#endif