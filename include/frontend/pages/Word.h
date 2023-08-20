#ifndef FRONTEND_PAGE_WORD
#define FRONTEND_PAGE_WORD

#include "dictionary/build.h"
#include "dictionary/history.h"
#include "dictionary/trie.h"
#include "dictionary/word.h"
#include "dictionary/random.h"
#include "frontend/styles.h"
#include "globalVars/globalVars.h"
#include "raylib.h"
#include <cstring>
#include <iostream>
#include <vector>

class WordPage
{
  private:
    Trie currentTrie      = PrebuiltTriesList[*CurrentState::currentDict];
    Dictionary* currentDictionary = new Dictionary(dictDirs[*CurrentState::currentDict], *CurrentState::currentDict);
    History currentHistory = History(historyDirectories[*CurrentState::currentDict]);

    bool SearchEdit       = false;
    char SearchInput[101] = "";
    Rectangle rec_result[20];
    Rectangle rec_dictionary{1075, 140, 155, 55};
    Rectangle rec_reset{760, 140, 135, 55};
    Rectangle rec_random{915, 140, 135, 55};
    Rectangle rec_search{305, 140, 440, 55};

    bool dropDownBox = false, confirmResetBox = false, addWordButton = false;
    std::string text;

    std::vector<Word> words;
    Word randomWord;
    Random r;
    std::vector<std::string> dictLanguages = {"ENG-ENG", "ENG-VIE", "VIE-ENG", "EMOJI", "SLANG"};

    Rectangle dictPagesRects[5];
    std::vector<std::string> dictPages = {"WORD", "Definition", "Favorites", "History", "Game"};

    short int selectedDictPage = 0;

    Word tmp;

    // Initialize snow variables
    Rectangle snowflakes[100];
    Color snowflakeColor = GetColor(SNOW);

  public:
    WordPage();
    std::string TextEllipsis(const std::string& text, const Font& font, float maxWidth);
    void draw();
    void update();
    void resetBox();
    void addWord();
    ~WordPage()
    {
    }
};

#endif