#include "frontend/pages/Word.h"
#include "dictionary/word.h"
#include "frontend/styles.h"
#include "globalVars/globalVars.h"
#include "dictionary/trie.h"
#include "raygui.h"
#include "raylib.h"

Word selectedWord;

WordPage::WordPage()
{
    for (int i = 0; i < 4; i++)
    {
        dictPagesRects[i] = {61, float(146 + (151 * i)), 165, 55};
    }
    dictPagesRects[selectedDictPage] = {51, float(136 + (150 * selectedDictPage)), 195, 65};

    for (int i = 0; i < 20; i++)
        rec_result[i] = {307, (float)205 + 130 * i, 900, 120};
}

void WordPage::update()
{
    if (!isBuild) {
        build(dict, trie);
        isBuild = true;
    }
    if (IsMouseButtonPressed(0) && !dropDownBox) {
        for (int i = 0; i < words.size(); ++i) {
            if (GetMousePosition().y > 180 && CheckCollisionPointRec(GetMousePosition(), rec_result[i]))
            {
                selectedWord = words[i];
                // words.clear();
                // return DEFINITION;
            }
        }
    }
}

void WordPage::draw()
{
    if (confirmResetBox)
    {
        resetBox();
        return;
    }
    if (addWordButton)
    {
        addWord();
        return;
    }

    Vector2 mousePos = GetMousePosition();

    // draw the Search Box
    if (GuiTextBox(rec_search, SearchInput, 101, SearchEdit))
    {
        SearchEdit ^= 1;
    }
    if (SearchInput[0] == '\0')
        DrawTextEx(Resources::displayFontRegular, "Search...", {330, 155}, TEXT_FONT_SIZE, 0, GRAY);

    // draw the reset button
    if (GuiButton(rec_reset, "RESET"))
        confirmResetBox = true;

    if (GuiButton(rec_random, "RANDOM"))
    {
    }

    // Function switcher container
    DrawRectangleV(Vector2{0, 0}, Vector2{277, 720}, GetColor(SECONDARY_COLOR));
    // Draws the function switcher
    for (int i = 0; i < dictPages.size(); i++)
    {
        if (i == selectedDictPage)
        {
            GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, PRIMARY_COLOR_CONTAINER_HOVER);
        }
        else
        {
            GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, PRIMARY_COLOR_CONTAINER);
        }
        if (GuiButton(dictPagesRects[i], dictPages[i].c_str()))
        {
            CurrentState::currentPage = static_cast<Page>(i);
        }
    }

    if (SearchInput[0] == '\0') {
        words.clear();
    }

    // Draws each word
    for (int i = 0; i < words.size(); ++i) {
        DrawRectangleGradientV(rec_result[i].x, rec_result[i].y, rec_result[i].width, rec_result[i].height, BOX_COLOR_RGB, BOX_COLOR_RGB);

        if (CheckCollisionPointRec(mousePos, rec_result[i]) && mousePos.y > 180 && !dropDownBox)
                DrawRectangleGradientV(rec_result[i].x, rec_result[i].y, rec_result[i].width, rec_result[i].height, PRIMARY_COLOR_CONTAINER_HOVER_RGB, PRIMARY_COLOR_CONTAINER_HOVER_RGB);
        std::string wordsTmp = words[i].getKey() + ' ' + '(' + words[i].getType() + ')';
        DrawTextEx(Resources::wordFontBold, wordsTmp.c_str(), {rec_result[i].x + 10, rec_result[i].y + 10}, 34, 2, BLACK);
        for (int j = 0; j < std::min(2, int(words[i].getDefinitionCount())); j++) {
            DrawTextEx(Resources::wordFontBold, words[i].getDefinition(j).c_str(), {rec_result[i].x + 14, rec_result[i].y + 35 * j + 50}, 25, 2, WHITE);
        }
    }

    // Draw the Dict Picker
    if (GuiDropdownBox(
            rec_dictionary,
            (dictLanguages[0] + "\n" + dictLanguages[1] + "\n" + dictLanguages[2] + "\n" + dictLanguages[3]).c_str(),
            modeChosen, dropDownBox))
    {
        dropDownBox ^= 1;
        confirmResetBox = false;
    }

    if (SearchInput[0] != '\0') {
        if (words.empty()) {
            DrawTextEx(Resources::wordFontBold, "No word match this search !!!", {310, 215}, 25, 1, RED);
                    if (GuiLabelButton({320, 250, 80, 40}, "Add this word")) {
                        addWordButton = true;
                    }
                        
        }
    }

    if (SearchEdit) {
        if (GetKeyPressed()) {
            if (trie.search(SearchInput, tmp)) {
                words.clear();
                words = trie.wordSuggest(SearchInput);
            }
            else words.clear();
        }
    }
}

void WordPage::resetBox()
{
    if (GuiWindowBox({300, 170, 600, 250}, ""))
        confirmResetBox = false;
    text = "Are you sure to reset ?";
    DrawTextEx(Resources::wordFontBold, text.c_str(),
               {600 - MeasureTextEx(Resources::wordFontBold, text.c_str(), 27, 1).x / 2, 220}, 27, 1, BLACK);
    if (GuiButton({400, 330, 100, 50}, "YES")) {
        confirmResetBox = false;
        memset(SearchInput, 0, sizeof(SearchInput));
        words.clear();
    }
    if (GuiButton({700, 330, 100, 50}, "NO"))
    {
        confirmResetBox = false;
    }
}

void WordPage::addWord()
{
    if (GuiWindowBox({300, 170, 600, 250}, ""))
        addWordButton = false;
    text = "Are you sure to add this word?";
    DrawTextEx(Resources::wordFontBold, text.c_str(),
               {600 - MeasureTextEx(Resources::wordFontBold, text.c_str(), 27, 1).x / 2, 220}, 27, 1, BLACK);
    if (GuiButton({400, 330, 100, 50}, "YES"))
        addWordButton = false;
    if (GuiButton({700, 330, 100, 50}, "CANCEL"))
    {
        addWordButton = false;
    }
}