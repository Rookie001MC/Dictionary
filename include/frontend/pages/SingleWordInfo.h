#ifndef FRONTEND_PAGE_SINGLEWORDINFO_H
#define FRONTEND_PAGE_SINGLEWORDINFO_H

#include "frontend/pages/Word.h"
#include "globalVars/globalVars.h"

class SingleWordInfo
{
  private:
    void deleteBox(short type)
    {
    }
    void editMenu();
    void editEachDef()
    {
    }
    void addDef()
    {
    }
    void saveBox()
    {
    }

    std::string fullDef = "\0";
    std::vector<std::string> eachDef;
    std::vector<int> edit_height;
    bool isInfo = false;
    char newdata[501];
    bool confirmDeleteBox = false, confirmSaveBox = false, editButton = false, editEachDefButton = false,
         addDefButton = false;

    History currentFavorites = History(favoritesDirectories[*CurrentState::currentDict], 1);

  public:
    SingleWordInfo();
    ~SingleWordInfo()
    {
    }
    void update();
    void draw();
};

#endif