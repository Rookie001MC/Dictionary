#ifndef FRONTEND_PAGE_FAVORITES
#define FRONTEND_PAGE_FAVORITES

#include "dictionary/history.h"
#include "dictionary/word.h"
#include "frontend/styles.h"
#include "globalVars/globalVars.h"
#include "raylib.h"
#include <vector>

class FavoritesPage
{
  private:
    std::vector<Word> words;
    std::vector<std::string> wordStrings;
    std::vector<Rectangle> wordRects;
    std::vector<Rectangle> deleteRects;

    Rectangle dictChooserRect{1075, 140, 155, 55};
    std::vector<std::string> dictLanguages = {"ENG-ENG", "ENG-VIE", "VIE-ENG", "EMOJI", "SLANG"};

    Rectangle dictPagesRects[5];
    std::vector<std::string> dictPages = {"WORD", "Definition", "Favorites", "History", "Game"};

    short int selectedDictPage = 2;
    bool dictChooserActive     = false;
    bool confirmDeleteRecordBox = false;

    // Both history and favorites uses the same function
    History currentFavorites = History(favoritesDirectories[*CurrentState::currentDict], 1);
    Trie currentTrie         = PrebuiltTriesList[*CurrentState::currentDict];

    // Initialize snow variables
    Rectangle snowflakes[100];
    Color snowflakeColor = GetColor(SNOW);

  public:
    FavoritesPage();
    std::string TextEllipsis(const std::string &text, const Font &font, float maxWidth);
    void update();
    void draw();
    void getFavorites(std::vector<std::string> wordStrings);
    void deleteRecord();
};

#endif
