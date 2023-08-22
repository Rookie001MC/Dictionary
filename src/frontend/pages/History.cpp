#include "frontend/pages/History.h"
#include "dictionary/word.h"
#include "frontend/styles.h"
#include "globalVars/globalVars.h"
#include "raygui.h"
#include "raylib.h"

HistoryPage::HistoryPage()
{
    for (int i = 0; i < 5; i++)
    {
        dictPagesRects[i] = {61, float(146 + (122 * i)), 165, 55};
    }
    dictPagesRects[selectedDictPage] = {51, float(140 + (122 * selectedDictPage)), 195, 65};

    for (int i = 0; i < words.size(); i++)
    {
        wordRects.push_back({307, float(225 + 130 * i), 921, 120});
    }

    // drawing snow
    for (int i = 0; i < 100; i++)
    {
        snowflakes[i].x      = GetRandomValue(0, 720);
        snowflakes[i].y      = GetRandomValue(0, 1280);
        snowflakes[i].width  = GetRandomValue(2, 4);
        snowflakes[i].height = GetRandomValue(2, 4);
    }
}

// Truncate the text and add ellipsis if it exceeds the specified width
std::string HistoryPage::TextEllipsis(const std::string &text, const Font &font, float maxWidth)
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

void HistoryPage::update()
{
    currentHistory = History(historyDirectories[*CurrentState::currentDict]);
    if (!words.size() && !wordStrings.size() && !tempSearched.size())
    {
        // Get the history strings
        wordStrings = currentHistory.get();

        getHistory(wordStrings);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !dictChooserActive && !confirmDeleteAllBox && !confirmDeleteRecordBox)
    {
        for (int i = 0; i < words.size(); ++i)
        {
            if (GetMousePosition().y > 180 && CheckCollisionPointRec(GetMousePosition(), wordRects[i]) &&
                !CheckCollisionPointRec(GetMousePosition(), deleteRects[i]))
            {
                CurrentState::currentWord = words[i];
                CurrentState::currentPage = static_cast<Page>(5);
            }
        }
    }

    if ((IsKeyPressed(KEY_UP) || GetMouseWheelMove() == 1) && wordRects[0].y < 200)
    {
        for (int i = 0; i < words.size(); i++)
        {
            wordRects[i].y += 40;
        }
    }

    if ((IsKeyPressed(KEY_DOWN)) ||
        GetMouseWheelMove() == -1 && wordRects[words.size() - 1].y + wordRects[words.size() - 1].height > 800)
    {
        for (int i = 0; i < words.size(); i++)
        {
            wordRects[i].y -= 40;
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

void HistoryPage::draw()
{

    if (confirmDeleteAllBox)
    {
        deleteAll();
        return;
    }
    if (confirmDeleteRecordBox)
    {
        deleteRecord();
        return;
    }
    if (words.empty() && wordStrings.empty() && tempSearched.empty())
    {
        DrawTextEx(Resources::displayFontBold, "History is empty!", {715, 384}, TEXT_FONT_SIZE, 0, TEXT_COLOR_RGB);
        DrawTextEx(Resources::displayFontBold, "Go search something!", {689, 439}, TEXT_FONT_SIZE, 0, TEXT_COLOR_RGB);
    }

    Vector2 mousePos = GetMousePosition();

    // Draws each word
    for (int i = 0; i < words.size(); i++)
    {
        std::string wordWithTypeTmp = words[i].getKey();
        if (!words[i].getType().empty())
        {
            wordWithTypeTmp += " (" + words[i].getType() + ")";
        }

        DrawRectangleGradientV(wordRects[i].x, wordRects[i].y, wordRects[i].width, wordRects[i].height, BOX_COLOR_RGB,
                               BOX_COLOR_RGB);

        if (CheckCollisionPointRec(mousePos, wordRects[i]) && !CheckCollisionPointRec(mousePos, deleteRects[i]) &&
            mousePos.y > 180 && !dictChooserActive)
        {
            DrawRectangleGradientV(wordRects[i].x, wordRects[i].y, wordRects[i].width, wordRects[i].height,
                                   GetColor(RESULT_COLOR_CONTAINER_HOVER), GetColor(RESULT_COLOR_CONTAINER_HOVER));
        }

        Vector2 textPosition = {wordRects[i].x + 10, wordRects[i].y + 10};
        DrawTextEx(Resources::wordFontBold, wordWithTypeTmp.c_str(), textPosition, WORD_FONT_SIZE, 0, TEXT_COLOR_RGB);

        for (int j = 0; j < std::min(2, int(words[i].getDefinitionCount())); j++)
        {
            Vector2 definitionPosition = {wordRects[i].x + 14, wordRects[i].y + 35 * j + 50};

            // Measure the text to determine if it fits within the rectangle
            Vector2 textSize =
                MeasureTextEx(Resources::displayFontRegular, words[i].getDefinition(j).c_str(), TEXT_FONT_SIZE, 1);

            if (definitionPosition.x + textSize.x <= wordRects[i].x + wordRects[i].width &&
                definitionPosition.y + textSize.y <= wordRects[i].y + wordRects[i].height)
            {
                // Draw the text if it fits within the rectangle
                DrawTextEx(Resources::displayFontRegular, words[i].getDefinition(j).c_str(), definitionPosition,
                           TEXT_FONT_SIZE, 1, TEXT_COLOR_RGB);
            }
            else
            {
                // Calculate available width for truncated text (consider space for ellipsis)
                float availableWidth = wordRects[i].width - 16 - (definitionPosition.x - wordRects[i].x);

                // Truncate the text to fit within the available width and add ellipsis
                std::string truncatedText =
                    TextEllipsis(words[i].getDefinition(j).c_str(), Resources::displayFontRegular, availableWidth);

                // Draw the truncated text with ellipsis
                DrawTextEx(Resources::displayFontRegular, truncatedText.c_str(), definitionPosition, TEXT_FONT_SIZE, 1,
                           TEXT_COLOR_RGB);
            }
        }

        if (GuiButton({wordRects[i].x + 850, wordRects[i].y + 10, 30, 30}, "#143#"))
        {
            CurrentState::currentWord = words[i];
            confirmDeleteRecordBox ^= 1;
        }
    }
    // Search Box container
    DrawRectangleRec({277, 100, 1280, 115}, BG_COLOR_RGB);
    DrawRectangleLinesEx({270, 0, 1280, 215}, 2, BLACK);

    // draw the Search Box
    if (GuiTextBox(SearchInputRect, SearchInput, 101, SearchEdit))
    {
        SearchEdit ^= 1;
    }
    if (SearchInput[0] == '\0')
        DrawTextEx(Resources::displayFontRegular, "Search...", {330, 155}, TEXT_FONT_SIZE, 0, GRAY);
    if (GuiButton(ResetRect, "RESET"))
    {
        confirmDeleteAllBox ^= 1;
    }
    // Search logic, should be only in the wordString vector, therefore it should be simple.
    if (SearchEdit)
    {
        if (GetKeyPressed() && !(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN)))
        {
            words.clear();
            wordRects.clear();
            tempSearched.clear();

            // Find the words that match the substring or the entire string in the entire history
            // If we do, then we push the word to the tempSearched vector, which will be passed to the getHistory
            // function
            for (int i = 0; i < wordStrings.size(); i++)
            {
                if (wordStrings[i].find(SearchInput) != std::string::npos)
                {
                    tempSearched.push_back(wordStrings[i]);
                }
            }

            // If the tempSearched vector is not empty, then we pass it to the getHistory function
            if (!tempSearched.empty())
            {
                getHistory(tempSearched);
            }
        }
    }
    if (SearchInput[0] != '\0')
    {
        if (tempSearched.empty())
        {
            wordRects.clear();
            words.clear();
            DrawTextEx(Resources::displayFontBold, "That word does not exist in the history!", {523, 384},
                       TEXT_FONT_SIZE, 1, TEXT_COLOR_RGB);
        }
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
            // Clear the words and wordRects vectors still in memory
            words.clear();
            wordStrings.clear();
            wordRects.clear();

            // Set the new page
            CurrentState::currentPage = static_cast<Page>(i);
        }
    }

    // Draw the Dict Picker
    if (GuiDropdownBox(dictChooserRect,
                       (dictLanguages[0] + "\n" + dictLanguages[1] + "\n" + dictLanguages[2] + "\n" + dictLanguages[3] +
                        "\n" + dictLanguages[4])
                           .c_str(),
                       CurrentState::currentDict, dictChooserActive))
    {
        dictChooserActive ^= 1;

        // Update the trie object
        currentTrie = PrebuiltTriesList[*CurrentState::currentDict];

        words.clear();
        wordStrings.clear();

        currentHistory.save();
        currentHistory = History(historyDirectories[*CurrentState::currentDict]);
    }

    // Draw snowflakes
    for (int i = 0; i < 100; i++)
    {
        DrawRectangleRec(snowflakes[i], snowflakeColor);
    }
}

void HistoryPage::deleteRecord()
{
    if (GuiWindowBox({300, 170, 600, 250}, ""))
    {
        confirmDeleteRecordBox ^= 1;
    }
    std::string promptText = "Are you sure you want to delete this from your history?";
    DrawTextEx(Resources::displayFontRegular, promptText.c_str(),
               {850 - MeasureTextEx(Resources::displayFontRegular, promptText.c_str(), TEXT_FONT_SIZE, 0).x, 220},
               TEXT_FONT_SIZE, 0, TEXT_COLOR_RGB);
    DrawTextEx(Resources::wordFontRegular, CurrentState::currentWord.getKey().c_str(), {620, 260}, WORD_FONT_SIZE, 0,
               TEXT_COLOR_RGB);
    if (GuiButton({400, 330, 100, 50}, "YES"))
    {

        // Delete the word from the history
        if (currentHistory.find(CurrentState::currentWord.getKey()) != -1)
        {
            currentHistory.remove(CurrentState::currentWord.getKey());
        }
        currentHistory.save();
        // Update the words vector
        words.clear();
        wordStrings.clear();

        getHistory(currentHistory.get());

        CurrentState::currentWord = Word();
        confirmDeleteRecordBox ^= 1;
    }
    if (GuiButton({700, 330, 100, 50}, "NO"))
    {
        confirmDeleteRecordBox ^= 1;
    }
}

void HistoryPage::getHistory(std::vector<std::string> wordStrings)
{
    // Search through the trie for the words
    for (int i = 0; i < wordStrings.size(); i++)
    {
        Word tmp;

        currentTrie.search(wordStrings[i], tmp);
        if (tmp.getKey() != "")
        {
            words.push_back(tmp);
            wordRects.push_back({307, float(225 + 130 * i), 921, 120});
            deleteRects.push_back({wordRects[i].x + 850, wordRects[i].y + 10, 30, 30});
        }
    }
}
void HistoryPage::deleteAll()
{
    if (GuiWindowBox({300, 170, 600, 250}, ""))
    {
        confirmDeleteAllBox ^= 1;
    }
    std::string promptText = "Are you sure you want to delete all your history?";
    DrawTextEx(Resources::displayFontRegular, promptText.c_str(),
               {850 - MeasureTextEx(Resources::displayFontRegular, promptText.c_str(), TEXT_FONT_SIZE, 0).x, 220},
               TEXT_FONT_SIZE, 0, TEXT_COLOR_RGB);
    if (GuiButton({400, 330, 100, 50}, "YES"))
    {
        // Delete all the words from the history
        confirmDeleteAllBox ^= 1;
        currentHistory.clear();
        currentHistory.save();
        words.clear();
        wordStrings.clear();
    }
    if (GuiButton({700, 330, 100, 50}, "NO"))
    {
        confirmDeleteAllBox ^= 1;
    }
}