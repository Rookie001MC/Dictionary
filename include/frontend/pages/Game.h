#ifndef FRONTEND_PAGE_GAME
#define FRONTEND_PAGE_GAME

#include <iostream>
#include <cstring>
#include <vector>
#include "raylib.h"
#include "frontend/pages/Word.h"
#include "dictionary/word.h"

class GamePage {
    private:
        Rectangle dictPagesRects[5];
        std::vector<std::string> dictPages = {"WORD", "Definition", "Favorites", "History", "Game"};
        short int selectedDictPage = 4;
    public:
        GamePage();
        ~GamePage() 
        {
        }
        void draw();
        void update();
};

#endif