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
    if (GuiWindowBox({73, 160, 1140, 510}, "")) {
        isInfo = true;
    }
    std::string selectedTmp = Var::selectedWord.getKey() + ' ' + '(' + Var::selectedWord.getType() + ')';
    DrawTextEx(Resources::wordFontBold, selectedTmp.c_str(), {105, 200}, 45, 2, BLACK);

    for (int i = 0; i < std::min(4, int(Var::selectedWord.getDefinitionCount())); ++i) {
        DrawTextEx(Resources::wordFontBold, Var::selectedWord.getDefinition(i).c_str(), {105, (float)(270 + i*65)}, 25, 2, BLACK);
    }
}