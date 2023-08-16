#ifndef FRONTEND_MAIN_H
#define FRONTEND_MAIN_H

#include "frontend/ResourcesLoad.h"
#include "frontend/pages/Definition.h"
#include "frontend/pages/Favorites.h"
#include "frontend/pages/Game.h"
#include "frontend/pages/History.h"
#include "frontend/pages/SingleWordInfo.h"
#include "frontend/pages/Word.h"
#include "frontend/styles.h"
#include "globalVars/globalVars.h"
#include "raygui.h"
#include "raylib.h"

void setStyles();
class FrontendMain
{
  private:
    Rectangle Header{0, 0, SCREEN_WIDTH, 120};
    HistoryPage history;
    WordPage word;
    DefPage def;
    FavoritesPage favorites;
    SingleWordInfo singleWordInfo;
    GamePage game;

  public:
    FrontendMain();
    void start();
};
#endif