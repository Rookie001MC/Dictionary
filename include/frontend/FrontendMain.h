#ifndef FRONTEND_MAIN_H
#define FRONTEND_MAIN_H

#include "frontend/pages/Favorites.h"
#include "raylib.h"
#include "frontend/ResourcesLoad.h"
#include "frontend/styles.h"
#include "frontend/pages/History.h"
#include "frontend/pages/Word.h"
#include "frontend/pages/Definition.h"
#include "globalVars/globalVars.h"
#include "raylib.h"

void setStyles();
class FrontendMain
{
    private:
        Rectangle Header{0,0, SCREEN_WIDTH, 120};
        HistoryPage history;
        WordPage word;
        DefPage def;
        FavoritesPage favorites;
    public:
        FrontendMain();
        void start();

};
#endif