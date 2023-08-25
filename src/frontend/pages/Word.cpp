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
        rec_result[i] = {307, (float)225 + 130 * i, 921, 120};

    // drawing snow
    for (int i = 0; i < 100; i++)
    {
        snowflakes[i].x      = GetRandomValue(0, 720);
        snowflakes[i].y      = GetRandomValue(0, 1280);
        snowflakes[i].width  = GetRandomValue(2, 6);
        snowflakes[i].height = GetRandomValue(2, 6);
    }
}

void WordPage::update()
{
    if (IsMouseButtonPressed(0) && !dropDownBox && !confirmResetBox && !addWordButton)
    {
        for (int i = 0; i < words.size(); ++i)
        {
            if (GetMousePosition().y > 180 && CheckCollisionPointRec(GetMousePosition(), rec_result[i]))
            {
                CurrentState::currentDictHistory.add(words[i].getKey());
                CurrentState::currentDictHistory.save();
                memset(SearchInput, 0, sizeof(SearchInput));
                CurrentState::currentWord = words[i];
                CurrentState::currentPage = static_cast<Page>(5);
            }
        }
    }

    if (SearchInput[0] == '\0')
    {
        words.clear();
    }

    if ((IsKeyPressed(KEY_UP) || GetMouseWheelMove() == 1) && rec_result[0].y < 200)
    {
        for (int i = 0; i < words.size(); ++i)
        {
            rec_result[i].y += 40;
        }
    }

    if ((IsKeyPressed(KEY_DOWN) || GetMouseWheelMove() == -1) && rec_result[words.size() - 1].y >= 540)
    {
        for (int i = 0; i < words.size(); ++i)
        {
            rec_result[i].y -= 40;
        }
    }

    // drawing snow
    for (int i = 0; i < 100; i++)
    {
        snowflakes[i].y += 1; // Adjust the speed of falling snow
        if (snowflakes[i].y > 720)
        {
            snowflakes[i].y = 0;
            snowflakes[i].x = GetRandomValue(0, 1280);
        }
    }
}

// Truncate the text and add ellipsis if it exceeds the specified width
std::string WordPage::TextEllipsis(const std::string &text, const Font &font, float maxWidth)
{
    std::string ellipsis      = "...";
    std::string truncatedText = text;

    Vector2 textSize = MeasureTextEx(font, text.c_str(), TEXT_FONT_SIZE, 1);

    if (textSize.x > maxWidth)
    {
        // Subtract the ellipsis width from the available width
        maxWidth -= MeasureTextEx(font, ellipsis.c_str(), TEXT_FONT_SIZE, 1).x;

        while (MeasureTextEx(font, truncatedText.c_str(), TEXT_FONT_SIZE, 1).x > maxWidth && !truncatedText.empty())
        {
            // Remove characters from the end until the text fits within maxWidth
            truncatedText.pop_back();
        }

        // Add ellipsis
        truncatedText += ellipsis;
    }

    return truncatedText;
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

    if (words.empty() && SearchInput[0] == '\0')
    {
        DrawTextEx(Resources::displayFontBold, "Start typing to search...", {715, 390}, TEXT_FONT_SIZE, 1,
                   TEXT_COLOR_RGB);
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

        std::string wordsTmp = words[i].getKey();
        if (!words[i].getType().empty())
            wordsTmp += " (" + words[i].getType() + ")";

        Vector2 textPosition = {rec_result[i].x + 10, rec_result[i].y + 10};
        DrawTextEx(Resources::wordFontBold, wordsTmp.c_str(), textPosition, WORD_FONT_SIZE - 1, 2, TEXT_COLOR_RGB);

        for (int j = 0; j < std::min(2, int(words[i].getDefinitionCount())); j++)
        {
            Vector2 definitionPosition = {rec_result[i].x + 14, rec_result[i].y + 35 * j + 50};

            // Measure the text to determine if it fits within the rectangle
            Vector2 textSize =
                MeasureTextEx(Resources::displayFontRegular, words[i].getDefinition(j).c_str(), TEXT_FONT_SIZE, 1);

            if (definitionPosition.x + textSize.x <= rec_result[i].x + rec_result[i].width &&
                definitionPosition.y + textSize.y <= rec_result[i].y + rec_result[i].height)
            {
                // Draw the text if it fits within the rectangle
                DrawTextEx(Resources::displayFontRegular, words[i].getDefinition(j).c_str(), definitionPosition,
                           TEXT_FONT_SIZE, 1, TEXT_COLOR_RGB);
            }
            else
            {
                // Calculate available width for truncated text (consider space for ellipsis)
                float availableWidth = rec_result[i].width - 16 - (definitionPosition.x - rec_result[i].x);

                // Truncate the text to fit within the available width and add ellipsis
                std::string truncatedText =
                    TextEllipsis(words[i].getDefinition(j).c_str(), Resources::displayFontRegular, availableWidth);

                // Draw the truncated text with ellipsis
                DrawTextEx(Resources::displayFontRegular, truncatedText.c_str(), definitionPosition, TEXT_FONT_SIZE, 1,
                           TEXT_COLOR_RGB);
            }
        }
    }

    DrawRectangleRec({277, 100, 1280, 115}, BG_COLOR_RGB);
    DrawRectangleLinesEx({270, 0, 1280, 215}, 2, BLACK);

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
        for (int i = 0; i < sizeof(SearchInput); ++i)
        {
            SearchInput[i] = '\0';
        }

        r.setDictionary(CurrentState::currentDictObject);
        r.setPath();
        randomWord = r.viewRandomWord();
        for (int i = 0; i < randomWord.getKey().length(); ++i)
        {
            SearchInput[i] = randomWord.getKey()[i];
        }
        words.clear();
        words.push_back(randomWord);
    }

    // Function switcher container
    DrawRectangleV(Vector2{0, 0}, Vector2{277, 720}, GetColor(SECONDARY_COLOR));
    DrawRectangleLinesEx({0, 0, 277, 720}, 2, BLACK);

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
    if (GuiDropdownBox(rec_dictionary,
                       (dictLanguages[0] + "\n" + dictLanguages[1] + "\n" + dictLanguages[2] + "\n" + dictLanguages[3] +
                        "\n" + dictLanguages[4])
                           .c_str(),
                       CurrentState::currentDict, dropDownBox))
    {
        dropDownBox ^= 1;
        words.clear();
        confirmResetBox = false;
        for (int i = 0; i < sizeof(SearchInput); ++i)
        {
            SearchInput[i] = '\0';
        }

        CurrentState::currentTrie = PrebuiltTriesList[*CurrentState::currentDict];

        switch (*CurrentState::currentDict)
        {
            case 0:
                CurrentState::currentDictObject = &engEng;
                break;
            case 1:
                CurrentState::currentDictObject = &engVie;
                break;
            case 2:
                CurrentState::currentDictObject = &vieEng;
                break;
            case 3:
                CurrentState::currentDictObject = &emoji;
                break;
            case 4:
                CurrentState::currentDictObject = &slang;
                break;            
        }

        CurrentState::currentDictHistory.save();
        CurrentState::currentDictHistory = History(historyDirectories[*CurrentState::currentDict]);
    }

    if (SearchInput[0] != '\0')
    {
        if (words.empty())
        {
            DrawTextEx(Resources::displayFontBold, "No word match this search !!!", {310, 240}, 25, 1, RED);
            if (GuiLabelButton({310, 270, 80, 40}, "Add this word"))
            {
                addWordButton = true;
            }
        }
    }

    if (SearchEdit)
    {
        if (GetKeyPressed() && !(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN)))
        {
            words.clear();
            words = CurrentState::currentTrie.wordSuggest(SearchInput);
        }
    }

    // Draw snowflakes
    for (int i = 0; i < 100; i++)
    {
        DrawRectangleRec(snowflakes[i], snowflakeColor);
    }
}

void WordPage::resetBox()
{
    if (GuiWindowBox({300, 170, 600, 250}, ""))
        confirmResetBox = false;
    text = "Are you sure to reset ?";
    DrawTextEx(Resources::displayFontBold, text.c_str(),
               {600 - MeasureTextEx(Resources::displayFontBold, text.c_str(), 27, 1).x / 2, 220}, 27, 1, BLACK);
    if (GuiButton({400, 330, 100, 50}, "YES"))
    {
        confirmResetBox = false;
        memset(SearchInput, 0, sizeof(SearchInput));
        words.clear();
        reset(*CurrentState::currentDictObject, CurrentState::currentTrie);

        CurrentState::currentDictHistory.clear();
        CurrentState::currentDictHistory.save();
        
        CurrentState::currentDictFavorites.clear();
        CurrentState::currentDictFavorites.save();
    }
    if (GuiButton({700, 330, 100, 50}, "NO"))
    {
        confirmResetBox = false;
    }
}

void WordPage::addWord()
{
    if (GuiWindowBox({250, 170, 680, 400}, ""))
    {
        isEdited      = false;
        addWordButton = false;
    }

    text = "Are you sure to add this word?";
    DrawTextEx(Resources::displayFontBold, text.c_str(),
               {600 - MeasureTextEx(Resources::displayFontBold, text.c_str(), 27, 1).x / 2, 220}, 27, 1, BLACK);

    std::string type = "Please input the type for this word !";
    DrawTextEx(Resources::displayFontRegular, type.c_str(),
               {600 - MeasureTextEx(Resources::displayFontBold, type.c_str(), 27, 1).x / 2, 260}, 27, 1, BLACK);

    // draw the Search Box
    if (GuiTextBox({300, 300, 550, 50}, NewType, 500, TypeEdit))
    {
        TypeEdit ^= 1;
    }

    std::string def = "Please input the definition for this word !";
    DrawTextEx(Resources::displayFontRegular, def.c_str(),
               {600 - MeasureTextEx(Resources::displayFontBold, def.c_str(), 27, 1).x / 2, 370}, 27, 1, BLACK);

    if (GuiTextBox({300, 410, 550, 50}, NewDef, 500, DefEdit))
    {
        DefEdit ^= 1;
    }

    if (!isEdited)
    {
        isEdited = true;
        memset(NewType, 0, sizeof(NewType));
    }

    if (GuiButton({390, 490, 100, 50}, "ENTER"))
    {
        isEdited      = false;
        addWordButton = false;
        Word newWord(SearchInput, NewType, NewDef);
        CurrentState::currentTrie.insert(newWord);
        memset(SearchInput, 0, sizeof(SearchInput));
        memset(NewDef, 0, sizeof(NewDef));
        memset(NewType, 0, sizeof(NewType));
    }
    if (GuiButton({690, 490, 100, 50}, "CANCEL"))
    {
        isEdited      = false;
        addWordButton = false;
    }
}