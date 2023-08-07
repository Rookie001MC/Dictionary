#include "frontend/pages/Word.h"
#include "dictionary/word.h"
#include "frontend/styles.h"
#include "globalVars/globalVars.h"
#include "raygui.h"
#include "raylib.h"

WordPage::WordPage()
{
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

void WordPage::update()
{
    // if (GetMouseWheelMove() == -1 && rec_result[word.size() - 1].y > 475)
    // {
    //     for (int i = 0; i < word.size(); i++)
    //     {
    //         rec_result[i].y -= 40;
    //     }
    // }
    // else if (GetMouseWheelMove() == 1 && rec_result[0].y < 200)
    // {
    //     for (int i = 0; i < word.size(); i++)
    //     {
    //         rec_result[i].y += 40;
    //     }
    // }

    if (selectedDictPage != 0)
    {
        //  return static_cast<Page>(selectedDictPage);
    }
    //   return Page::DICT_WORD
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

        // Draws each word
    for (int i = 0; i < words.size(); i++)
    {
        DrawRectangleV({wordRects[i].x, wordRects[i].y}, {wordRects[i].width, wordRects[i].height},
                       SECONDARY_COLOR_CONTAINER_RGB);
        DrawRectangleLinesEx(wordRects[i], 2, OUTLINE_COLOR_RGB);

        if (CheckCollisionPointRec(mousePos, wordRects[i]) && !dropDownBox)
        {
            DrawRectangleV({wordRects[i].x, wordRects[i].y}, {wordRects[i].width, wordRects[i].height},
                           SECONDARY_COLOR_RGB);
        }

        DrawTextEx(Resources::wordFontBold, words[i]->getKey().c_str(), {wordRects[i].x + 10, wordRects[i].y + 10},
                   WORD_FONT_SIZE, 0, TEXT_COLOR_RGB);
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

    // if (!word.size())
    // {
    //     if (SearchInput[0] == '\0')
    //         word = data[*modeChosen].getSearchHistory();
    //     else
    //     {
    //         word = data[*modeChosen].SearchWord(SearchInput);
    //         if (!word.size())
    //         {
    //             DrawTextEx(fnt, "No word match this search !!!", {300, 205}, 25, 1, RED);
    //             if (GuiLabelButton({320, 250, 80, 40}, "Add this word"))
    //                 addWordButton = true;
    //         }
    //     }
    // }
}

void WordPage::resetBox()
{
    if (GuiWindowBox({300, 170, 600, 250}, ""))
        confirmResetBox = false;
    text = "Are you sure to reset ?";
    DrawTextEx(Resources::wordFontBold, text.c_str(),
               {600 - MeasureTextEx(Resources::wordFontBold, text.c_str(), 27, 1).x / 2, 220}, 27, 1, BLACK);
    if (GuiButton({400, 330, 100, 50}, "YES"))
        confirmResetBox = false;
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