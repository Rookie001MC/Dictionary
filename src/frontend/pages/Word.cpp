#include "frontend/pages/Word.h"
#include "frontend/styles.h"
#include "globalVars/globalVars.h"
#include "dictionary/word.h"
#include "raygui.h"
#include "raylib.h"

WordPage::WordPage() {
    CurrentState::currentPage = Page::DICT_WORD;
    // for (int i = 0; i < 20; i++)
    //     rec_result[i] = {320, (float)200 + 125 * i, 830, 120};
    // for (int i = 0; i < 5; i++)
    //     rec_modes[i] = {30, (float)125 + 90 * i, 245, 60};
    // rec_modes[menuChosen] = {20, (float)115 + 90 * menuChosen, 265, 80};
}

void WordPage::draw() {
    if (confirmResetBox)
    {
        resetBox();
        return;
    }
    if (addWordButton)
    {
        addWord();
    }

    Vector2 mousePos = GetMousePosition();

    // draw the Search Box
    DrawRectangle(302, 146, 442, 55, WHITE);
    if (SearchInput[0] == '\0') {
        DrawText("Search...", 325, 135, 30, LIGHTGRAY);
    }
    
    //draw the reset button
    if (GuiButton(rec_reset, "RESET"))
        confirmResetBox = true;

    
}

void WordPage::update() {
    if (!words.size()) {

    }
}

void WordPage::resetBox() {
    if (GuiWindowBox({300, 170, 600, 250}, ""))
        confirmResetBox = false;
    text = "Are you sure to reset " // + dictionary[*modeChosen] + "?";
   // DrawTextEx(fnt, text.c_str(), {600 - MeasureTextEx(fnt, text.c_str(), 27, 1).x / 2, 220}, 27, 1, BLACK);
    if (GuiButton({400, 330, 100, 50}, "NO"))
        confirmResetBox = false;
    if (GuiButton({700, 330, 100, 50}, "YES"))
    {
        // word.clear();
        // data[*modeChosen].resetData();
        // confirmResetBox = false;
    }
}

void WordPage::addWord() {

}