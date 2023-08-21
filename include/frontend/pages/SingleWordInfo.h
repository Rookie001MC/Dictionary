#ifndef FRONTEND_PAGE_SINGLEWORDINFO_H
#define FRONTEND_PAGE_SINGLEWORDINFO_H

#include "dictionary/history.h"
#include "frontend/pages/Word.h"
#include "globalVars/globalVars.h"

class SingleWordInfo
{
  private:
    void editMenu();
    void saveBox()
    {
      confirmSaveBox         = false;
      editButton             = false;
    }

    // Initialize snow variables
    Rectangle snowflakes[100];

    bool defBreakLines[55];
    int defHeight[55];
    bool isBreakNewLines = false;
    bool isFullDef       = false;
    std::vector<std::string> eachDef;
    std::vector<int> edit_height;
    bool isInfo = false;
    char NewDef[501];
    bool SearchEdit       = false;
    bool confirmDeleteBox = false, confirmSaveBox = false, editButton = false, editEachDefButton = false,
         addDefButton = false, isEdited = false;
    std::string text;
    int defChosen = -1;

    History currentFavorites      = History(favoritesDirectories[*CurrentState::currentDict], 1);
    Trie currentTrie              = PrebuiltTriesList[*CurrentState::currentDict];
    Dictionary *currentDictionary = new Dictionary(dictDirs[*CurrentState::currentDict], *CurrentState::currentDict);
    History currentHistory        = History(historyDirectories[*CurrentState::currentDict]);

  public:
    SingleWordInfo();
    ~SingleWordInfo()
    {
    }
    void buildAnswer();
    void drawSnow();
    void update();
    void deleteBox();
    void draw();
    void addDef();
    void editEachDef();
};

#endif