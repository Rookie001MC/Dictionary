#ifndef FRONTEND_PAGE_DEFINITION
#define FRONTEND_PAGE_DEFINITION

#include <iostream>
#include <cstring>
#include <vector>
#include "raylib.h"
#include "frontend/styles.h"
#include "dictionary/word.h"

class DefPage {
    private:
        int* modeChosen = new int{0};
        bool SearchEdit = false;
        char SearchInput[101] = "";
        Rectangle rec_dictionary{1075, 140, 155, 55};
        Rectangle rec_reset{760, 140, 135, 55};
        Rectangle rec_random{915, 140, 135, 55};
        Rectangle rec_search{305, 140, 420, 55};
    
        bool dropDownBox = false, confirmResetBox = false, addWordButton = false;
        std::string text;

        std::vector<Word *> words;
        std::vector<Rectangle> wordRects;
        std::vector <std::string> dictLanguages = {"ENG-ENG", "ENG-VIE", "VIE-ENG", "EMOJI", "SLANG"};

        Rectangle dictPagesRects[4];
        std::vector<std::string> dictPages = {"WORD", "Definition", "Favorites", "History"};
     
        short int selectedDictPage = 1;

    public:
        DefPage();
        void draw();
        void update();
        void resetBox();
        void addDef();
        ~DefPage() {
            delete modeChosen;
        }

};

#endif