#ifndef FRONTEND_PAGE_FAVORITES
#define FRONTEND_PAGE_FAVORITES

#include "dictionary/word.h"
#include "frontend/styles.h"
#include "globalVars/globalVars.h"
#include "dictionary/history.h"
#include "raylib.h"
#include <vector>

class FavoritesPage
{
  private:
    std::vector<Word> words;
    std::vector<std::string> wordStrings;
    std::vector<Rectangle> wordRects;
    Rectangle dictChooserRect{1075, 140, 155, 55};
    std::vector<std::string> dictLanguages = {"ENG-ENG", "ENG-VIE", "VIE-ENG", "EMOJI", "SLANG"};

    Rectangle dictPagesRects[5];
    std::vector<std::string> dictPages = {"WORD", "Definition", "Favorites", "History", "Game"};

    short int selectedDictPage = 2;
    bool dictChooserActive     = false;

    std::vector<std::string> favoritesDirectories = {
      Resources::currentExeDir + "../tmp/engeng/favourite.txt",
      Resources::currentExeDir + "../tmp/engvie/favourite.txt",
      Resources::currentExeDir + "../tmp/vieeng/favourite.txt",
      Resources::currentExeDir + "../tmp/emoji/favourite.txt",
      Resources::currentExeDir + "../tmp/slang/favourite.txt"
    };

    // Both history and favorites uses the same function
    History currentFavorites = History(favoritesDirectories[*CurrentState::currentDict], 1);
    Trie currentTrie = PrebuiltTriesList[*CurrentState::currentDict];
  public:
    FavoritesPage();
  std::string TextEllipsis(const std::string &text, const Font &font, float maxWidth);
    void update();
    void draw();
};

#endif
