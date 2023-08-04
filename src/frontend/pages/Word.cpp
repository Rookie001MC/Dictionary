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
    
}

void WordPage::update() {
    if (!words.size()) {

    }
}

void WordPage::resetBox() {

}

void WordPage::addWord() {

}