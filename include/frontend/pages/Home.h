#ifndef FRONTEND_PAGE_HOME
#define FRONTEND_PAGE_HOME

#include <iostream>
#include <cstring>
#include <vector>
#include "raylib.h"
#include "frontend/styles.h"
#include "dictionary/word.h"

class HomePage {
    private:
        Rectangle rec_dictionary{1075, 140, 155, 55};
        Rectangle rec_reset{760, 140, 135, 55};
        Rectangle rec_random{915, 140, 135, 55};
        Rectangle rec_search{305, 140, 420, 55};
    

        std::vector<Word *> words;
        std::vector<Rectangle> wordRects;

        Rectangle dictPagesRects[4];
        std::vector<std::string> dictPages = {"WORD", "Definition", "Favorites", "History"};

    public:
        HomePage();
        void draw();
        void update();
        ~HomePage() {}

};

#endif