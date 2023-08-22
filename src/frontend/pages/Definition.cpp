#include "frontend/pages/Definition.h"
#include "dictionary/word.h"
#include "frontend/styles.h"
#include "globalVars/globalVars.h"
#include "raygui.h"
#include "raylib.h"

DefPage::DefPage()
{
    for (int i = 0; i < 5; i++)
    {
        dictPagesRects[i] = {61, float(146 + (122 * i)), 165, 55};
    }
    dictPagesRects[selectedDictPage] = {51, float(140 + (122 * selectedDictPage)), 195, 65};

    for (int i = 0; i < 20; i++)
        rec_result[i] = {307, (float)225 + 130 * i, 921, 120};

    // drawing snow
    for (int i = 0; i < 100; i++)
    {
        snowflakes[i].x      = GetRandomValue(0, 720);
        snowflakes[i].y      = GetRandomValue(0, 1280);
        snowflakes[i].width  = GetRandomValue(2, 4);
        snowflakes[i].height = GetRandomValue(2, 4);
    }
}

void DefPage::update()
{
    if (IsMouseButtonPressed(0) && !dropDownBox)
    {
        for (int i = 0; i < words.size(); ++i)
        {
            if (GetMousePosition().y > 180 && CheckCollisionPointRec(GetMousePosition(), rec_result[i]))
            {
                CurrentState::currentWord = words[i].getWord();
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
        snowflakes[i].y += 1.5; // Adjust the speed of falling snow
        if (snowflakes[i].y > 720)
        {
            snowflakes[i].y = 0;
            snowflakes[i].x = GetRandomValue(0, 1280);
        }
    }
}

// Truncate the text and add ellipsis if it exceeds the specified width
std::string DefPage::TextEllipsis(const std::string &text, const Font &font, float maxWidth)
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

void DefPage::draw()
{
    if (confirmResetBox)
    {
        resetBox();
        return;
    }
    if (addWordButton)
    {
        addDef();
    }
    if (words.empty() && SearchInput[0] == '\0')
    {
        DrawTextEx(Resources::displayFontBold, "Start typing to search...", {715, 390}, TEXT_FONT_SIZE, 1, TEXT_COLOR_RGB);
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

        std::string wordsTmp = words[i].getWord().getKey();
        if (!words[i].getWord().getType().empty())
            wordsTmp += " (" + words[i].getWord().getType() + ")";

        Vector2 textPosition = {rec_result[i].x + 10, rec_result[i].y + 10};
        DrawTextEx(Resources::wordFontBold, wordsTmp.c_str(), textPosition, WORD_FONT_SIZE, 2, TEXT_COLOR_RGB);

        for (int j = 0; j < std::min(2, int(words[i].getWord().getDefinitionCount())); j++)
        {
            Vector2 definitionPosition = {rec_result[i].x + 14, rec_result[i].y + 35 * j + 50};

            // Measure the text to determine if it fits within the rectangle
            Vector2 textSize = MeasureTextEx(Resources::displayFontRegular, words[i].getWord().getDefinition(j).c_str(),
                                             TEXT_FONT_SIZE, 1);

            if (definitionPosition.x + textSize.x <= rec_result[i].x + rec_result[i].width &&
                definitionPosition.y + textSize.y <= rec_result[i].y + rec_result[i].height)
            {
                // Draw the text if it fits within the rectangle
                DrawTextEx(Resources::displayFontRegular, words[i].getWord().getDefinition(j).c_str(),
                           definitionPosition, TEXT_FONT_SIZE, 1, TEXT_COLOR_RGB);
            }
            else
            {
                // Calculate available width for truncated text (consider space for ellipsis)
                float availableWidth = rec_result[i].width - 16 - (definitionPosition.x - rec_result[i].x);

                // Truncate the text to fit within the available width and add ellipsis
                std::string truncatedText = TextEllipsis(words[i].getWord().getDefinition(j).c_str(),
                                                         Resources::displayFontRegular, availableWidth);

                // Draw the truncated text with ellipsis
                DrawTextEx(Resources::displayFontRegular, truncatedText.c_str(), definitionPosition, TEXT_FONT_SIZE, 1,
                           TEXT_COLOR_RGB);
            }
        }
    }

    // draw the background of textbox
    DrawRectangleRec({277, 100, 1280, 115}, BG_COLOR_RGB);
    DrawRectangleLinesEx({270, 0, 1280, 215}, 2, BLACK);

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

    // draw the Search Box
    if (GuiTextBox(rec_search, SearchInput, 101, SearchEdit))
    {
        SearchEdit ^= 1;
    }
    if (SearchInput[0] == '\0')
        DrawTextEx(Resources::displayFontRegular, "Search...", {330, 155}, TEXT_FONT_SIZE, 0, GRAY);

    if (GuiButton(rec_reset, "RESET"))
    {
        confirmResetBox = true;
    }

    // Draw the Dict Picker
    if (GuiDropdownBox(rec_dictionary,
                       (dictLanguages[0] + "\n" + dictLanguages[1] + "\n" + dictLanguages[2] + "\n" + dictLanguages[3] +
                        "\n" + dictLanguages[4])
                           .c_str(),
                       CurrentState::currentDict, dropDownBox))
    {
        dropDownBox ^= 1;
        currentTrie     = PrebuiltTriesList[*CurrentState::currentDict];
        confirmResetBox = false;
        for (int i = 0; i < sizeof(SearchInput); ++i)
        {
            SearchInput[i] = '\0';
        }
        words.clear();
    }

    if (words.empty() && pressed)
    {
        DrawTextEx(Resources::displayFontBold, "No definition match this search !!!", {310, 240}, 25, 1, RED);
    }

    if (GetKeyPressed())
    {
        pressed = false;
    }

    if (SearchInput[0] != '\0')
    {
        if (!pressed && words.empty())
            DrawTextEx(Resources::displayFontBold, "...", {310, 240}, 30, 1, BLACK);
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        pressed = true;
        words.clear();
        words = r.searchDefinition(SearchInput, currentTrie);
    }
    // Draw snowflakes
    for (int i = 0; i < 100; i++)
    {
        DrawRectangleRec(snowflakes[i], snowflakeColor);
    }
}

void DefPage::resetBox()
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
    }
    if (GuiButton({700, 330, 100, 50}, "NO"))
    {
        confirmResetBox = false;
    }
}

void DefPage::addDef()
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