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
    std::vector<Rectangle> deleteRects;

    Rectangle dictChooserRect{1075, 140, 155, 55};
    std::vector<std::string> dictLanguages = {"ENG-ENG", "ENG-VIE", "VIE-ENG", "EMOJI", "SLANG"};

    Rectangle dictPagesRects[5];
    std::vector<std::string> dictPages = {"WORD", "Definition", "Favorites", "History", "Game"};

    short int selectedDictPage = 3;
    bool dictChooserActive     = false;

    // We should be able to load the history file depending on the current active dictionary

    // Create the storage
    History currentHistory = History(historyDirectories[*CurrentState::currentDict]);
    Trie currentTrie = PrebuiltTriesList[*CurrentState::currentDict];
    bool confirmDeleteRecordBox = false;
  public:
    HistoryPage();
    std::string TextEllipsis(const std::string &text, const Font &font, float maxWidth);
    void update();
    void draw();
    void deleteRecord();
    void getHistory(std::vector<std::string> wordStrings);
};

#endif