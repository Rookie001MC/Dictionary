#include "frontend/pages/Word.h"
#include "dictionary/trie.h"
#include "dictionary/word.h"
#include "frontend/styles.h"
#include "globalVars/globalVars.h"
#include "raygui.h"
#include "raylib.h"

WordPage::WordPage()
{
    for (int i = 0; i < 5; i++)
    {
        dictPagesRects[i] = {61, float(146 + (122 * i)), 165, 55};
    }
    dictPagesRects[selectedDictPage] = {51, float(140 + (150 * selectedDictPage)), 195, 65};

    for (int i = 0; i < 20; i++)
        rec_result[i] = {307, (float)210 + 130 * i, 921, 120};
}

void WordPage::update()
{
    if (IsMouseButtonPressed(0) && !dropDownBox)
    {
        for (int i = 0; i < words.size(); ++i)
        {
            if (GetMousePosition().y > 180 && CheckCollisionPointRec(GetMousePosition(), rec_result[i]))
            {
                CurrentState::currentWord = words[i];
                CurrentState::currentPage = static_cast<Page>(5);
            }
        }
    }

    if (SearchInput[0] == '\0')
    {
        words.clear();
    }

    if (IsKeyPressed(KEY_UP) && rec_result[0].y < 200)
    {
        for (int i = 0; i < words.size(); ++i)
        {
            rec_result[i].y += 40;
        }
    }

    if (IsKeyPressed(KEY_DOWN) && rec_result[words.size() - 1].y >= 540)
    {
        for (int i = 0; i < words.size(); ++i)
        {
            rec_result[i].y -= 40;
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

    // Draws each word
    for (int i = 0; i < words.size(); ++i)
    {
        DrawRectangleGradientV(rec_result[i].x, rec_result[i].y, rec_result[i].width, rec_result[i].height,
                               BOX_COLOR_RGB, BOX_COLOR_RGB);

        if (CheckCollisionPointRec(mousePos, rec_result[i]) && mousePos.y > 180 && !dropDownBox)
            DrawRectangleGradientV(rec_result[i].x, rec_result[i].y, rec_result[i].width, rec_result[i].height,
                                   GetColor(RESULT_COLOR_CONTAINER_HOVER), GetColor(RESULT_COLOR_CONTAINER_HOVER));

        std::string wordsTmp = words[i].getKey() + ' ' + '(' + words[i].getType() + ')';
        Vector2 textPosition = {rec_result[i].x + 10, rec_result[i].y + 10};
        DrawTextEx(Resources::wordFontBold, wordsTmp.c_str(), textPosition, WORD_FONT_SIZE, 2, BLACK);

        for (int j = 0; j < std::min(2, int(words[i].getDefinitionCount())); j++)
        {
            Vector2 definitionPosition = {rec_result[i].x + 14, rec_result[i].y + 35 * j + 50};

            // Measure the text to determine if it fits within the rectangle
            Vector2 textSize = MeasureTextEx(Resources::displayFontRegular, words[i].getDefinition(j).c_str(), TEXT_FONT_SIZE, 1);

            if (definitionPosition.x + textSize.x <= rec_result[i].x + rec_result[i].width &&
                definitionPosition.y + textSize.y <= rec_result[i].y + rec_result[i].height)
            {
                // Draw the text only if it fits within the rectangle
                DrawTextEx(Resources::displayFontRegular, words[i].getDefinition(j).c_str(), definitionPosition, TEXT_FONT_SIZE, 1,
                           WHITE);
            }
        }
    }

    DrawRectangleRec({277, 100, 1280, 107}, BG_COLOR_RGB);

    // draw the Search Box
    if (GuiTextBox(rec_search, SearchInput, 101, SearchEdit))
    {
        SearchEdit ^= 1;
    }
    if (SearchInput[0] == '\0')
    {
        DrawTextEx(Resources::displayFontRegular, "Search...", {330, 155}, TEXT_FONT_SIZE, 0, GRAY);
        words.clear();
    }

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

    // Draw the Dict Picker
    if (GuiDropdownBox(
            rec_dictionary,
            (dictLanguages[0] + "\n" + dictLanguages[1] + "\n" + dictLanguages[2] + "\n" + dictLanguages[3]).c_str(),
            CurrentState::currentDict, dropDownBox))
    {
        dropDownBox ^= 1;
        currentTrie = PrebuiltTriesList[*CurrentState::currentDict];
        words.clear();
        SearchInput[0]  = '\0';
        confirmResetBox = false;
    }

    if (SearchInput[0] != '\0')
    {
        if (words.empty())
        {
            DrawTextEx(Resources::wordFontBold, "No word match this search !!!", {310, 215}, 25, 1, RED);
            if (GuiLabelButton({320, 250, 80, 40}, "Add this word"))
            {
                addWordButton = true;
            }
        }
    }

    if (SearchEdit)
    {
        if (GetKeyPressed() && !IsKeyPressed(KEY_UP) && !IsKeyPressed(KEY_DOWN))
        {
            if (currentTrie.search(SearchInput, tmp))
            {
                words.clear();
                words = currentTrie.wordSuggest(SearchInput);
            }
            else
                words.clear();
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
    if (GuiButton({400, 330, 100, 50}, "YES"))
    {
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
    {
        addWordButton = false;
    }
    if (GuiButton({700, 330, 100, 50}, "CANCEL"))
    {
        addWordButton = false;
    }
}