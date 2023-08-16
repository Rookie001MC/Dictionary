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
    if (editButton)
    {
        editMenu();
        return;
    }
    if (confirmDeleteBox)
    {
        deleteBox(-1);
        return;
    }

    if (GuiWindowBox({73, 160, 1140, 510}, "")) {
        isInfo = true;
    }
    std::string selectedTmp = Var::selectedWord.getKey() + ' ' + '(' + Var::selectedWord.getType() + ')';
    DrawTextEx(Resources::wordFontBold, selectedTmp.c_str(), {105, 200}, 45, 2, BLACK);

    for (int i = 0; i < std::min(4, int(Var::selectedWord.getDefinitionCount())); ++i) {
        DrawTextEx(Resources::wordFontBold, Var::selectedWord.getDefinition(i).c_str(), {105, (float)(270 + i*65)}, 25, 2, BLACK);
    }

    if (GuiButton({700, 590, 135, 55}, "EDIT")) {
        edit_height.push_back(200);
        editButton = true;
        for (int i = 1; i <= eachDef.size(); i++)
        {
            edit_height.push_back(MeasureTextEx(Resources::wordFontBold, eachDef[i - 1].c_str(), 25, 1).y + edit_height[i - 1] + 35);
        }
        return;
    }
    if (GuiButton({855, 590, 165, 55}, "ADD FAVORITE")) {

    }
    if (GuiButton({1040, 590, 135, 55}, "DELETE")) {

    }
}