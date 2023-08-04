#ifndef FRONTEND_PAGE_WORD
#define FRONTEND_PAGE_WORD

#include <iostream>
#include <cstring>
#include <vector>
#include "raylib.h"
#include "frontend/styles.h"
#include "dictionary/word.h"
#include "globalVars/globalVars.h"

class WordPage {
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
     
        short int selectedDictPage = 0;

    public:
        WordPage();
        void draw();
        CurrentState::currentPage update();
        void resetBox();
        void addWord();
        ~WordPage() {
            delete modeChosen;
        }

};

#endif