#ifndef FRONTEND_PAGE_HISTORY
#define FRONTEND_PAGE_HISTORY

#include "dictionary/history.h"
#include "dictionary/word.h"
#include "frontend/styles.h"
#include "globalVars/globalVars.h"
#include "raylib.h"
#include <vector>

class HistoryPage
{
  private:
    std::vector<Word> words;
    std::vector<std::string> wordStrings;
    std::vector<std::string> tempSearched;
    std::vector<Rectangle> wordRects;
    std::vector<Rectangle> deleteRects;

    Rectangle dictChooserRect{1075, 140, 155, 55};
    std::vector<std::string> dictLanguages = {"ENG-ENG", "ENG-VIE", "VIE-ENG", "EMOJI", "SLANG"};

    Rectangle dictPagesRects[5];
    std::vector<std::string> dictPages = {"WORD", "Definition", "Favorites", "History", "Game"};

    short int selectedDictPage = 3;
    bool dictChooserActive     = false;

    char SearchInput[101] = "";
    Rectangle SearchInputRect{305, 140, 590, 55};
    bool SearchEdit = false;

    Rectangle ResetRect{915, 140, 135, 55};
    bool confirmDeleteAllBox = false;

    // Create the storage
    bool confirmDeleteRecordBox = false;

    // Initialize snow variables
    Rectangle snowflakes[100];
    Color snowflakeColor = GetColor(SNOW);

  public:
    HistoryPage();
    std::string TextEllipsis(const std::string &text, const Font &font, float maxWidth);
    void update();
    void draw();
    void deleteRecord();
    void getHistory(std::vector<std::string> wordStrings);
    void deleteAll();
};

#endif