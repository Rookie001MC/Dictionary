/**
 * @file frontend/pages/SingleWordInfo.cpp
 * @author Group 07 - CS163 - 2022-2023
 * @brief The page that shows the definition of a single word
 * 
 */
#include "frontend/pages/SingleWordInfo.h"
#include "frontend/pages/Word.h"
#include "frontend/styles.h"
#include "globalVars/globalVars.h"
#include "raygui.h"
#include "raylib.h"

/**
 * Construct a new SingleWordInfo::SingleWordInfo object
 * 
 * This will: 
 * - Initialize the isFullDef variable, to keep track of whether the definition of the word is fully shown or not
 * - Initialize the defHeight array, to keep track of the height of each definition
 * - Initialize the defBreakLines array, to keep track of whether the definition is broken into new lines or not
 * - Initialize the snowflakes array.
 * 
 */
SingleWordInfo::SingleWordInfo()
{
    isFullDef = false;
    for (int i = 0; i < 40; ++i)
    {
        defHeight[i]     = 240 + i * 60;
        defBreakLines[i] = false;
    }

    // Initialize snowflakes
    for (int i = 0; i < 100; i++)
    {
        snowflakes[i].x      = GetRandomValue(0, 720);
        snowflakes[i].y      = GetRandomValue(0, 1280);
        snowflakes[i].width  = GetRandomValue(2, 4);
        snowflakes[i].height = GetRandomValue(2, 4);
    }
}

/**
 * Setup and update the page:
 * 
 * - Setup the isUpdated variable, to keep track of whether the page is updated or not, especially when the user adds another definition to the word
 * - Handle the logic to clear the page when the user exits out of the word
 * - Fetch the definitions of the word, then push them into the eachDef vector for drawing 
 * - Handle scrolling for the main page and the definition edit page
 * - Initialize the snow
 */
void SingleWordInfo::update()
{
    isUpdated        = true;
    currentDictFavorites = new History(favoritesDirectories[*CurrentState::currentDict], 1);
    currentTrie      = PrebuiltTriesList[*CurrentState::currentDict];
    currentDictHistory   = new History(historyDirectories[*CurrentState::currentDict]);

    // Clear the page when the user exits out of the word 
    if (isInfo)
    {
        eachDef.clear();
        edit_height.clear();
        for (int i = 0; i < 40; ++i)
        {
            defHeight[i]     = 240 + i * 60;
            defBreakLines[i] = false;
        }
        isUpdated                 = false;
        isFullDef                 = false;
        isBreakNewLines           = false;
        isInfo                    = false;
        CurrentState::currentPage = static_cast<Page>(0);
    }

    // Fetch the definitions of the word, then push them into the eachDef vector for drawing
    else if (!isFullDef)
    {
        std::string tmp;
        isFullDef = true;
        eachDef.clear();

        for (int i = 0; i < CurrentState::currentWord.getDefinitionCount(); ++i)
        {
            tmp = CurrentState::currentWord.getDefinition(i);
            eachDef.push_back(tmp);
        }
    }

    // Scrolling for the main page
    if ((IsKeyPressed(KEY_UP) || GetMouseWheelMove() == 1) && defHeight[0] < 230)
    {
        for (int i = 0; i < CurrentState::currentWord.getDefinitionCount(); ++i)
        {
            defHeight[i] += 40;
        }
    }

    // Scrolling for the definition edit page
    if ((IsKeyPressed(KEY_DOWN) || GetMouseWheelMove() == -1) &&
        defHeight[std::min(40, (int)eachDef.size()) - 1] >= 540)
    {
        for (int i = 0; i < CurrentState::currentWord.getDefinitionCount(); ++i)
        {
            defHeight[i] -= 40;
        }
    }

    // Initialize the snow
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

/**
 * Draw each of the definition of the word 
 * 
 * Since each definition can be very long, we need to be able to break it into new lines.
 */
void SingleWordInfo::buildAnswer()
{
    isBreakNewLines = true;
    // Go through each definition
    for (int i = 0; i < eachDef.size(); ++i)
    {
        // If the definition is too long, we need to break it into new lines
        if (MeasureTextEx(Resources::displayFontBold, eachDef[i].c_str(), 25, 1).x > 1180)
        {
            // Remember that this definition needs to be broken
            defBreakLines[i] = true;
            // We need to calculate how many lines we need to break this definition into
            float proportion  = float(MeasureTextEx(Resources::displayFontBold, eachDef[i].c_str(), 25, 1).x / 1180);
            // We need to remember the current position
            int pre          = 0;
            // We need to find the position to break the line
            int position     = eachDef[i].length() / (float)proportion;
            // We need to break the line until we cannot break it anymore
            while (position < eachDef[i].length())
            {
                // We need to find the last space before the position
                while (
                    eachDef[i][position] != ' ' ||
                    MeasureTextEx(Resources::displayFontBold, eachDef[i].substr(pre, position - pre).c_str(), 25, 1).x >
                        1180)
                    position--;
                // We need to break the line at the position
                eachDef[i][position] = '\n';
                // We need to remember the next position
                pre                  = position + 1;
                // We need to find the next position to break the line
                position += eachDef[i].length() / (float)proportion;
            }
        }
    }
}

void SingleWordInfo::draw()
{
    // If the page is not updated, update it
    if (!isUpdated)
        update();

    // Switch to the edit page if the user clicks on the edit button 
    if (editButton)
    {
        editMenu();
        return;
    }

    // Switch to deleting the definition if the user clicks on the delete button
    if (confirmDeleteBox)
    {
        deleteBox();
        return;
    }

    // Break each of the definition into new lines 
    if (!isBreakNewLines)
        buildAnswer();

    // Draw the definitions
    for (int i = 0; i < std::min(40, (int)eachDef.size()); ++i)
    {
        if (defBreakLines[i])
        {
            defHeight[i + 1] += 19;
            defHeight[i + 2] += 5;
            defBreakLines[i] = false;
        }
        DrawTextEx(Resources::displayFontRegular, eachDef[i].c_str(), {75, (float)defHeight[i]}, TEXT_FONT_SIZE, 1,
                   BLACK);
    }

    // Draw the line that divide the key and definition
    DrawRectangleLinesEx({-5, 0, 1290, 200}, 2, BLACK);
    DrawRectangleV({0, 120}, {1280, 79}, GetColor(SECONDARY_COLOR));

    // Button to exit out of the word into
    if (GuiButton({10, 130, 25, 25}, "#113#"))
    {
        isInfo = true;
    }

    // Get the word and its type
    std::string selectedTmp = CurrentState::currentWord.getKey();
    std::string type        = CurrentState::currentWord.getType();

    // Draw the word and its type

    // If this is a long word, we need to draw the word and its type on different lines
    if (MeasureTextEx(Resources::displayFontBold, type.c_str(), 32, 2).x > 400)
    {
        type = "(" + type + ")";
        DrawTextEx(Resources::displayFontBold, type.c_str(), {100, 165}, 25, 1, GetColor(WRONG_ANS));
        DrawTextEx(Resources::displayFontBold, selectedTmp.c_str(), {100, 130}, 35, 2, GetColor(WRONG_ANS));
    }
    // If this is a short word, append the type to the temp word so that we can draw the word and its type on the same line
    else
    {
        if (MeasureTextEx(Resources::displayFontBold, type.c_str(), 32, 2).x < 600)
        {
            if (!type.empty())
            {
                selectedTmp += " (" + type + ")";
            }
        }
        DrawTextEx(Resources::displayFontBold, selectedTmp.c_str(), {108, 140}, 35, 2, GetColor(WRONG_ANS));
    }

    // Draw the edit definitions button
    if (GuiButton({700, 133, 135, 55}, "EDIT"))
    {
        editButton = true;
        return;
    }

    // Draw the Add Favorite button, depending on whether the word is already in the favorite list or not
    if (currentDictFavorites->find(CurrentState::currentWord.getKey()) == -1)
    {
        if (GuiButton({855, 133, 195, 55}, "ADD FAVORITE"))
        {
            currentDictFavorites->add(CurrentState::currentWord.getKey());
            currentDictFavorites->save();
        }
    }
    else
    {
        if (GuiButton({855, 133, 195, 55}, "REMOVE FAVORITE"))
        {
            currentDictFavorites->remove(CurrentState::currentWord.getKey());
            currentDictFavorites->save();
        }
    }

    // Draw the Delete Word button
    if (GuiButton({1065, 133, 135, 55}, "DELETE"))
    {
        confirmDeleteBox = true;
    }

    // Có tuyết == ít bug mà :D 
    drawSnow();
}

/**
 * Draw the page that allows the user to add a new definition to the word
 * 
 */
void SingleWordInfo::addDef()
{
    // Is this actually necessary??? ~ Thắng - Code Documenter
    for (int i = 0; i < 40; ++i)
    {
        defHeight[i]     = 240 + i * 60;
        defBreakLines[i] = false;
    }

    // Draw the dialog and handle the exit button
    if (GuiWindowBox({250, 170, 650, 300}, ""))
        addDefButton = false;

    // Draw the prompt
    text = "Please input new definition !";
    DrawTextEx(Resources::displayFontBold, text.c_str(),
               {580 - MeasureTextEx(Resources::displayFontBold, text.c_str(), 27, 1).x / 2, 220}, 27, 1, BLACK);

    // Draw the text box for the user to input the new definition
    // @note Yes we actually reuse the search box edit check for this
    if (GuiTextBox({300, 290, 550, 50}, NewDef, 500, SearchEdit))
    {
        SearchEdit ^= 1;
    }

    // Draw the ENTER button, and handle adding a new definition to the word
    if (GuiButton({390, 390, 100, 50}, "ENTER"))
    {
        addDefButton = false;
        isFullDef    = false;
        eachDef.clear();
        edit_height.clear();
        CurrentState::currentWord.addDefinition(NewDef);
        currentTrie.insert(CurrentState::currentWord);
    }

    // Draw the BACK button, and handle going back to the main page
    if (GuiButton({690, 390, 100, 50}, "BACK"))
    {
        addDefButton = false;
    }
}

/**
 * @brief oooooh snowy
 * 
 */
void SingleWordInfo::drawSnow()
{
    Color snowflakeColor = GetColor(SNOW);

    // Draw snowflakes
    for (int i = 0; i < 100; i++)
    {
        DrawRectangleRec(snowflakes[i], snowflakeColor);
    }
}

/**
 * @brief Prompt the user to confirm deleting the word
 * 
 */
void SingleWordInfo::deleteBox()
{
    // Draw the dialog and handle the exit button
    if (GuiWindowBox({300, 170, 600, 250}, ""))
        confirmDeleteBox = false;

    // Draw the prompt
    text = "Are you sure to delete ?";
    DrawTextEx(Resources::displayFontBold, text.c_str(),
               {600 - MeasureTextEx(Resources::displayFontBold, text.c_str(), 27, 1).x / 2, 220}, 27, 1, BLACK);

    // Draw the YES and NO buttons, and handle the user's choice
    if (GuiButton({400, 330, 100, 50}, "YES"))
    {
        confirmDeleteBox = false;
        eachDef.clear();
        edit_height.clear();
        for (int i = 0; i < 40; ++i)
        {
            defHeight[i]     = 240 + i * 60;
            defBreakLines[i] = false;
        }
        isUpdated                 = false;
        isFullDef                 = false;
        isBreakNewLines           = false;
        isInfo                    = false;
        currentTrie.remove(CurrentState::currentWord.getKey());
        CurrentState::currentPage = static_cast<Page>(0);
    }
    if (GuiButton({700, 330, 100, 50}, "NO"))
    {
        confirmDeleteBox = false;
    }
}

void SingleWordInfo::editMenu()
{
    if (editEachDefButton)
    {
        editEachDef();
        return;
    }
    if (confirmSaveBox)
    {
        saveBox();
        return;
    }
    if (addDefButton)
    {
        addDef();
        return;
    }

    buildAnswer();

    // Handling Scrolling for the Edit Menu
    if ((IsKeyPressed(KEY_UP) || GetMouseWheelMove() == 1) && edit_height[0] < 230)
    {
        for (int i = 0; i <= eachDef.size(); i++)
            edit_height[i] += 40;
    }
    if ((IsKeyPressed(KEY_DOWN) || GetMouseWheelMove() == -1) && edit_height.back() >= 540)
    {
        for (int i = 0; i <= eachDef.size(); i++)
            edit_height[i] -= 40;
    }

    // Setup the boxes of each definition
    
    // Height of the first definition
    edit_height.push_back(230);

    // Height for each subsequent definition
    for (int i = 1; i <= eachDef.size(); i++)
    {
        edit_height.push_back(MeasureTextEx(Resources::displayFontRegular, eachDef[i - 1].c_str(), 25, 1).y +
                              edit_height[i - 1] + 35);
    }

    // Draw the text of each Definition and their respective Edit buttons 
    for (int i = 0; i < eachDef.size(); i++)
    {
        DrawTextEx(Resources::displayFontRegular, eachDef[i].c_str(), {48, (float)edit_height[i] + 8}, 25, 1, BLACK);
        DrawRectangleLinesEx({41, (float)edit_height[i], 1135, (float)edit_height[i + 1] - edit_height[i] - 20}, 2,
                             BLACK);
        if (GuiButton({1180, (float)edit_height[i], 65, 40}, "Edit"))
        {
            defChosen         = i;
            editEachDefButton = true;
            return;
        }
    }

    // Draw the line that divide the key and definition
    DrawRectangleLinesEx({-5, 0, 1290, 200}, 2, BLACK);
    DrawRectangleV({0, 120}, {1280, 79}, GetColor(SECONDARY_COLOR));

    if (GuiButton({10, 130, 25, 25}, "#113#"))
    {
        editButton = false;
    }

    // Draw the extra function buttons
    DrawTextEx(Resources::displayFontBold, "EDIT MENU", {105, 135}, 47, 1, GetColor(WRONG_ANS));
    if (GuiButton({750, 133, 100, 50}, "SAVE"))
        confirmSaveBox = true;
    if (GuiButton({880, 133, 170, 50}, "ADD MORE"))
    {
        for (int i = 0; i < 40; ++i)
        {
            defHeight[i]     = 240 + i * 60;
            defBreakLines[i] = false;
        }
        isBreakNewLines = false;
        memset(NewDef, 0, sizeof(NewDef));
        addDefButton = true;
    }
    drawSnow();
}

/**
 * @brief Handle editing a single definition for a word
 * 
 */
void SingleWordInfo::editEachDef()
{
    // Disable drawing the other elements in the page
    for (int i = 0; i < 40; ++i)
    {
        defHeight[i]     = 240 + i * 60;
        defBreakLines[i] = false;
    }

    isBreakNewLines = false;

    // Get the definition that the user wants to edit
    if (!isEdited)
    {
        isEdited = true;
        memset(NewDef, 0, sizeof(NewDef));
        for (int i = 0; i < CurrentState::currentWord.getDefinition(defChosen).size(); ++i)
        {
            NewDef[i] = CurrentState::currentWord.getDefinition(defChosen)[i];
        }
    }
    
    // Draw the edit window
    if (GuiWindowBox({250, 170, 650, 300}, ""))
    {
        editEachDefButton = false;
        editEachDefButton = false;
        isEdited          = false;
    }

    // Draw the Edit title
    text = "Edit Definition";
    DrawTextEx(Resources::displayFontBold, text.c_str(),
               {580 - MeasureTextEx(Resources::displayFontBold, text.c_str(), 27, 1).x / 2, 220}, 27, 1, BLACK);

    // Draw the Text box to edit the selected definition
    if (GuiTextBox({300, 290, 550, 50}, NewDef, 500, SearchEdit))
    {
        SearchEdit ^= 1;
    }

    // Handle changing the selected definition
    if (GuiButton({390, 390, 100, 50}, "ENTER"))
    {
        isEdited          = false;
        editEachDefButton = false;
        isFullDef         = false;
        eachDef.clear();
        edit_height.clear();
        CurrentState::currentWord.editDefinition(defChosen, NewDef);
        currentTrie.insert(CurrentState::currentWord);
    }

    // Handle deleting the definition out of the word
    if (GuiButton({690, 390, 100, 50}, "DELETE"))
    {
        isEdited          = false;
        editEachDefButton = false;
        isFullDef         = false;
        eachDef.clear();
        edit_height.clear();
        CurrentState::currentWord.removeDefinition(defChosen);
        currentTrie.insert(CurrentState::currentWord);
    }
}