#ifndef FRONTEND_PAGE_HISTORY
#define FRONTEND_PAGE_HISTORY

#include "dictionary/word.h"
#include "frontend/styles.h"
#include "globalVars/globalVars.h"
#include "dictionary/history.h"
#include "raylib.h"
#include <vector>

class HistoryPage
{
  private:
    std::vector<Word> words;
    std::vector <std::string> wordStrings;
    std::vector<Rectangle> wordRects;
    Rectangle dictChooserRect{1075, 140, 155, 55};
    std::vector<std::string> dictLanguages = {"ENG-ENG", "ENG-VIE", "VIE-ENG", "EMOJI", "SLANG"};

    Rectangle dictPagesRects[5];
    std::vector<std::string> dictPages = {"WORD", "Definition", "Favorites", "History", "Game"};

    short int selectedDictPage = 3;
    bool dictChooserActive     = false;

    // We should be able to load the history file depending on the current active dictionary

    // Declare the possible history files 
    std::vector<std::string> historyDirectories = {
      Resources::currentExeDir + "../tmp/engeng/history.txt",
      Resources::currentExeDir + "../tmp/engvie/history.txt",
      Resources::currentExeDir + "../tmp/vieeng/history.txt",
      Resources::currentExeDir + "../tmp/emoji/history.txt",
      Resources::currentExeDir + "../tmp/slang/history.txt"
    };

    // Create the storage
    History currentHistory = History(historyDirectories[*CurrentState::currentDict]);
    Trie currentTrie = PrebuiltTriesList[*CurrentState::currentDict];
  public:
    HistoryPage();
    std::string TextEllipsis(const std::string &text, const Font &font, float maxWidth);
    void update();
    void draw();
};

#endif