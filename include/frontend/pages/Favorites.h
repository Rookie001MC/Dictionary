#ifndef FRONTEND_PAGE_FAVORITES
#define FRONTEND_PAGE_FAVORITES

#include "raylib.h"
#include "frontend/styles.h"
#include "dictionary/word.h"
#include <vector>

class FavoritesPage
{
    private:
        int *currentDict = new int{0};
        std::vector<Word *> words;
        std::vector<Rectangle> wordRects;
        Rectangle dictChooserRect{1075, 140, 155, 55};
        std::vector <std::string> dictLanguages = {"ENG-ENG", "ENG-VIE", "VIE-ENG", "EMOJI", "SLANG"};

        Rectangle dictPagesRects[4];
        std::vector<std::string> dictPages = {"WORD", "Definition", "Favorites", "History"};
     
        short int selectedDictPage = 2;
        bool dictChooserActive = false;
    
    public:
        FavoritesPage();
        void update();
        void draw();
};  

#endif
