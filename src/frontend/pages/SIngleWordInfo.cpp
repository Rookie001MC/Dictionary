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
    if (fullDef == "\0") {
        std::string tmp;
        for (int i = 0; i < Var::selectedWord.getDefinitionCount(); ++i) {
            tmp = Var::selectedWord.getDefinition(i);
            eachDef.push_back(tmp);
            fullDef += tmp + "\n";
        }
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

void SingleWordInfo::editMenu() {
    if (editEachDefButton)
    {
        editEachDef();
        return;
    }
    if (confirmSaveBox)
    {
        saveBox();
        return;
    }
    if (addDefButton)
    {
        addDef();
        return;
    }

    if (IsKeyPressed(KEY_UP) && edit_height[0] < 200)
    {
        for (int i = 0; i <= eachDef.size(); i++)
            edit_height[i] += 40;
    }
    if (IsKeyPressed(KEY_DOWN) && edit_height.back() >= 540)
    {
        for (int i = 0; i <= eachDef.size(); i++)
            edit_height[i] -= 40;
    }

    for (int i = 0; i < eachDef.size(); i++)
    {
        DrawTextEx(Resources::wordFontBold, eachDef[i].c_str(), {48, (float)edit_height[i] + 8}, 25, 1, BLACK);
        DrawRectangleLinesEx({41, (float)edit_height[i], 1110, (float)edit_height[i + 1] - edit_height[i] - 20}, 2, BLACK);
        if (GuiButton({1158, (float)edit_height[i], 65, 40}, "Edit"))
        {
            edit_height.clear();
           // defChosen = i;
            editEachDefButton = true;
           // strcpy(newdata, selectedWord->defs[defChosen]->data.c_str());
            return;
        }
    }
    DrawRectangleRec({0, 100, 1280, 90}, BG_COLOR_RGB);
    DrawTextEx(Resources::wordFontBold, "EDIT MENU", {70, 133}, 40, 1, RED);
    if (GuiButton({750, 130, 100, 50}, "SAVE"))
        confirmSaveBox = true;
    if (GuiButton({880, 130, 170, 50}, "ADD MORE"))
    {
        addDefButton = true;
        // newData = "\0";
        // defChosen = eachDef.size();
        // newdata[0] = '\0';
    }
}