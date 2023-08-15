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
        Rectangle dictChooserRect{1075, 140, 155, 55};
        std::vector <std::string> dictLanguages = {"ENG-ENG", "ENG-VIE", "VIE-ENG", "EMOJI", "SLANG"};

        Rectangle dictPagesRects[5];
        std::vector<std::string> dictPages = {"WORD", "Definition", "Favorites", "History", "Game"};
     
        short int selectedDictPage = 3;
        bool dictChooserActive = false;
    
    public:
        HistoryPage();
        ~HistoryPage() {
            delete currentDict;
        }
        void update();
        void draw();
};  

#endif