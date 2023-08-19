#include "frontend/pages/Favorites.h"
#include "dictionary/word.h"
#include "frontend/styles.h"
#include "globalVars/globalVars.h"
#include "raygui.h"
#include "raylib.h"

FavoritesPage::FavoritesPage()
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
}

// Truncate the text and add ellipsis if it exceeds the specified width
std::string FavoritesPage::TextEllipsis(const std::string &text, const Font &font, float maxWidth)
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



void FavoritesPage::update()
{
    currentFavorites = History(favoritesDirectories[*CurrentState::currentDict]);
    if (!words.size())
    {
        wordStrings = currentFavorites.get();
        for (int i = 0; i < wordStrings.size(); i++)
        {
            Word tmp;

            currentTrie.search(wordStrings[i], tmp);

            if (tmp.getKey() != "")
            {
                words.push_back(tmp);
                wordRects.push_back({307, float(225 + 130 * i), 921, 120});
            }
        }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !dictChooserActive)
    {
        for (int i = 0; i < words.size(); ++i)
        {
            if (GetMousePosition().y > 180 && CheckCollisionPointRec(GetMousePosition(), wordRects[i]))
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

    if ((IsKeyPressed(KEY_DOWN)) || GetMouseWheelMove() == -1 && wordRects[words.size() - 1].y + wordRects[words.size() - 1].height > 800)
    {
        for (int i = 0; i < words.size(); i++)
        {
            wordRects[i].y -= 40;
        }
    }
}

void FavoritesPage::draw()
{
    Vector2 mousePos = GetMousePosition();

    // Draws each word
    for (int i = 0; i < words.size(); i++)
    {
        std::string wordWithTypeTmp = words[i].getKey();
        if(!words[i].getType().empty())
        {
            wordWithTypeTmp += " (" + words[i].getType() + ")";
        }


        DrawRectangleV({wordRects[i].x, wordRects[i].y}, {wordRects[i].width, wordRects[i].height},
                       SECONDARY_COLOR_CONTAINER_RGB);
        DrawRectangleLinesEx(wordRects[i], 2, OUTLINE_COLOR_RGB);

        if (CheckCollisionPointRec(mousePos, wordRects[i]) && mousePos.y > 180 && !dictChooserActive)
            DrawRectangleGradientV(wordRects[i].x, wordRects[i].y, wordRects[i].width, wordRects[i].height,
                                   GetColor(RESULT_COLOR_CONTAINER_HOVER), GetColor(RESULT_COLOR_CONTAINER_HOVER));

        if (CheckCollisionPointRec(mousePos, wordRects[i]) && !dictChooserActive)
        {
            DrawRectangleV({wordRects[i].x, wordRects[i].y}, {wordRects[i].width, wordRects[i].height},
                           SECONDARY_COLOR_RGB);
        }

        DrawTextEx(Resources::wordFontBold, wordWithTypeTmp.c_str(), {wordRects[i].x + 10, wordRects[i].y + 10},
                   WORD_FONT_SIZE, 0, TEXT_COLOR_RGB);


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
    if (GuiDropdownBox(
            dictChooserRect,
            (dictLanguages[0] + "\n" + dictLanguages[1] + "\n" + dictLanguages[2] + "\n" + dictLanguages[3] + "\n" + dictLanguages[4]).c_str(),
            CurrentState::currentDict, dictChooserActive))
    {
        dictChooserActive ^= 1;

        // Update the trie object
        currentTrie = PrebuiltTriesList[*CurrentState::currentDict];

        words.clear();
        wordStrings.clear();

        // Update the history object
        currentFavorites.save();
        currentFavorites = History(favoritesDirectories[*CurrentState::currentDict], 1);

    }

        // Draw the Search Box (disabled)
        DrawRectangle(305, 140, 420, 55, BG_COLOR_RGB);
    
}