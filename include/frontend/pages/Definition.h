#ifndef FRONTEND_PAGE_DEFINITION
#define FRONTEND_PAGE_DEFINITION

#include "dictionary/trie.h"
#include "dictionary/word.h"
#include "frontend/styles.h"
#include "dictionary/searchDefinition.h"
#include "dictionary/history.h"
#include "globalVars/globalVars.h"
#include "raylib.h"
#include <cstring>
#include <iostream>
#include <vector>
class DefPage
{
  private:
    Trie currentTrie      = PrebuiltTriesList[*CurrentState::currentDict];
    Dictionary* currentDictionary = new Dictionary(dictDirs[*CurrentState::currentDict], *CurrentState::currentDict);
    History currentHistory = History(historyDirectories[*CurrentState::currentDict]);

    bool SearchEdit       = false;
    char SearchInput[101] = "";
    Rectangle rec_dictionary{1075, 140, 155, 55};
    Rectangle rec_reset{915, 140, 135, 55};
    Rectangle rec_search{305, 140, 590, 55};
    Rectangle rec_result[20];

    bool dropDownBox = false, confirmResetBox = false, addWordButton = false;
    std::string text;

    std::vector<RelevantWord> words;
    RelevantWord r;

    std::vector<std::string> dictLanguages = {"ENG-ENG", "ENG-VIE", "VIE-ENG", "EMOJI", "SLANG"};

    Rectangle dictPagesRects[5];
    bool pressed = false;
    std::vector<std::string> dictPages = {"WORD", "Definition", "Favorites", "History", "Game"};

    short int selectedDictPage = 1;

    // Initialize snow variables
    Rectangle snowflakes[100];
    Color snowflakeColor = GetColor(SNOW);

  public:
    DefPage();
    void draw();
    std::string TextEllipsis(const std::string &text, const Font &font, float maxWidth);
    void update();
    void resetBox();
    void addDef();
    ~DefPage()
    {
    }
};

#endif