#ifndef FRONTEND_PAGE_HISTORY
#define FRONTEND_PAGE_HISTORY

#include "raylib.h"
#include "frontend/styles.h"
#include "dictionary/word.h"
#include <vector>

class HistoryPage
{
    private:
        int *currentDict = new int{0};
        std::vector<Word *> words;
        std::vector<Rectangle> wordRects;
        Rectangle dictChooserRect {1101, 146, 150, 55};
        std::vector <std::string> dictLanguages = {"ENG-ENG", "ENG-VIE", "VIE-ENG", "EMOJI", "SLANG"};

        Rectangle dictPagesRects[4];
        std::vector<std::string> dictPages = {"WORD", "Definition", "Favorites", "History"};
     
        short int selectedDictPage = 3;
        bool dictChooserActive = false;
    
    public:
        HistoryPage();
        void update();
        void draw();
};  

#endif