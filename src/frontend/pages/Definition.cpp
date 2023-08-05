#include "frontend/pages/Definition.h"
#include "frontend/styles.h"
#include "globalVars/globalVars.h"
#include "dictionary/word.h"
#include "raygui.h"
#include "raylib.h"

DefPage::DefPage() {
    for (int i = 0; i < 4; i++)
    {
        dictPagesRects[i] = {61, float(146 + (151 * i)), 165, 55};
    }
    dictPagesRects[selectedDictPage] = {51, float(136 + (150 * selectedDictPage)), 195, 65};

    for (int i = 0; i < words.size(); i++)
    {
        wordRects.push_back({300, float(220 + 100 * i), 949, 87});
    }
}

void DefPage::update() {
    if (selectedDictPage != 0)
    {
    }
    // if (selectedDictPage != 0)
    // {
    //     if (SearchInput[0] == '\0')
    //         words.clear();
    //     short tmp = selectedDictPage;
    //     selectedDictPage = 0;
    //     return static_cast<CurrentState::currentPage>(tmp);
    // }
    // return DICT_DEF_SEARCH;
}

void DefPage::draw() {
    if (confirmResetBox)
    {
        resetBox();
        return;
    }
    if (addWordButton)
    {
        addDef();
    }

    Vector2 mousePos = GetMousePosition();

    // draw the Search Box
     DrawRectangleV(Vector2{0, 0}, Vector2{277, 720}, GetColor(SECONDARY_COLOR));
    DrawRectangleLinesEx(rec_search, 3, BLACK);
    if (GuiTextBox(rec_search, SearchInput, 101, SearchEdit))
    {
        SearchEdit ^= 1;
    }
    if (SearchInput[0] == '\0')
        DrawText("Search...", 325, 155, 30, LIGHTGRAY);
    
    //draw the reset button
    if (GuiButton(rec_reset, "RESET"))
        confirmResetBox = true;

    if (GuiButton(rec_random, "RANDOM"))
    {
    }

    // Draws the function switcher
    for (int i = 0; i < dictPages.size(); i++)
    {
        if (i == selectedDictPage) {
            GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, PRIMARY_COLOR_CONTAINER_HOVER);
        }
        else {
            GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, PRIMARY_COLOR_CONTAINER);
        }
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

    // Draw the Dict Picker
        if (GuiDropdownBox(rec_dictionary, (dictLanguages[0] + "\n" + dictLanguages[1] + "\n" + dictLanguages[2] + "\n" + dictLanguages[3]).c_str(), modeChosen, dropDownBox))
    {
        dropDownBox ^= 1;
        confirmResetBox = false;
    }
}

void DefPage::resetBox() {
    if (GuiWindowBox({300, 170, 600, 250}, ""))
        confirmResetBox = false;
    text = "Are you sure to reset ?"; 
    DrawTextEx(Resources::wordFontBold, text.c_str(), {600 - MeasureTextEx(Resources::wordFontBold, text.c_str(), 27, 1).x / 2, 220}, 27, 1, BLACK);
    if (GuiButton({400, 330, 100, 50}, "YES"))
        confirmResetBox = false;
    if (GuiButton({700, 330, 100, 50}, "NO"))
    {
        confirmResetBox = false;
    }
}

void DefPage::addDef() {
    if (GuiWindowBox({300, 170, 600, 250}, ""))
        addWordButton = false;
    text = "Are you sure to add this word?";
    DrawTextEx(Resources::wordFontBold, text.c_str(), {600 - MeasureTextEx(Resources::wordFontBold, text.c_str(), 27, 1).x / 2, 220}, 27, 1, BLACK);
    if (GuiButton({400, 330, 100, 50}, "YES"))
        addWordButton = false;
    if (GuiButton({700, 330, 100, 50}, "CANCEL"))
    {
        addWordButton = false;
    }
}