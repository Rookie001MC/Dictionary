#ifndef FRONTEND_MAIN_H
#define FRONTEND_MAIN_H

#include "raylib.h"
#include "frontend/ResourcesLoad.h"
#include "frontend/styles.h"
#include "frontend/pages/History.h"
#include "globalVars/globalVars.h"
#include "raylib.h"

void setStyles();
class FrontendMain
{
    private:
        Rectangle Header{0,0, SCREEN_WIDTH, 120};
        HistoryPage history;
    public:
        FrontendMain();
        void start();

};
#endif