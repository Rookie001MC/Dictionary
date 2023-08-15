#include "frontend/pages/SingleWordInfo.h"
#include "frontend/pages/Word.h"
#include "globalVars/globalVars.h"
#include "raygui.h"
#include "raylib.h"

SingleWordInfo::SingleWordInfo() {

}

void SingleWordInfo::update() {
    if (isInfo) {
        isInfo = false;
        CurrentState::currentPage = static_cast<Page>(0);
    }
}

void SingleWordInfo::draw() {
    if (GuiWindowBox({50, 120, 1100, 460}, "")) {
        isInfo = true;
    }
    DrawTextEx(Resources::wordFontBold, selectedWord.getKey().c_str(), {310, 215}, 25, 1, BLUE);
}