#include "frontend/pages/Home.h"
#include "frontend/styles.h"
#include "globalVars/globalVars.h"
#include "dictionary/word.h"
#include "raygui.h"
#include "raylib.h"

WordPage::WordPage() {
    for (int i = 0; i < 4; i++)
    {
        dictPagesRects[i] = {61, float(146 + (151 * i)), 165, 55};
    }
  //  dictPagesRects[selectedDictPage] = {51, float(136 + (150 * selectedDictPage)), 195, 65};

    for (int i = 0; i < words.size(); i++)
    {
        wordRects.push_back({300, float(220 + 100 * i), 949, 87});
    }
}

void WordPage::update() {
    if (!words.size()) {

    }
}

void WordPage::draw() {

    Vector2 mousePos = GetMousePosition();

    // Draws the function switcher
    for (int i = 0; i < dictPages.size(); i++)
    {
        if (GuiButton(dictPagesRects[i], dictPages[i].c_str()))
        {
            CurrentState::currentDict = i;
        }
    }

    for (int i = 0; i < words.size(); i++)
    {
        // Draws each word
        DrawRectangleV({wordRects[i].x, wordRects[i].y}, {wordRects[i].width, wordRects[i].height},
                       SECONDARY_COLOR_CONTAINER_RGB);
        DrawRectangleLinesEx(wordRects[i], 2, OUTLINE_COLOR_RGB);

        if (CheckCollisionPointRec(mousePos, wordRects[i]) && !dropDownBox)
        {
            DrawRectangleV({wordRects[i].x, wordRects[i].y}, {wordRects[i].width, wordRects[i].height},
                           SECONDARY_COLOR_RGB);
        }

        DrawTextEx(Resources::wordFontRegular, words[i]->getKey().c_str(), {wordRects[i].x + 10, wordRects[i].y + 10},
                   WORD_FONT_SIZE, 0, TEXT_COLOR_RGB);
    }
}