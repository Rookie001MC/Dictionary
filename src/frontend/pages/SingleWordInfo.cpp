#include "frontend/pages/SingleWordInfo.h"
#include "frontend/pages/Word.h"
#include "frontend/styles.h"
#include "globalVars/globalVars.h"
#include "raygui.h"
#include "raylib.h"

SingleWordInfo::SingleWordInfo()
{
    isFullDef = false;
    for (int i = 0; i < 40; ++i)
    {
        defHeight[i]     = 240 + i * 60;
        defBreakLines[i] = false;
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

void SingleWordInfo::update()
{
    isUpdated        = true;
    currentFavorites = History(favoritesDirectories[*CurrentState::currentDict], 1);
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

    // for the main page of single word info
    if ((IsKeyPressed(KEY_UP) || GetMouseWheelMove() == 1) && defHeight[0] < 230)
    {
        for (int i = 0; i < CurrentState::currentWord.getDefinitionCount(); ++i)
        {
            defHeight[i] += 40;
        }
    }

    if ((IsKeyPressed(KEY_DOWN) || GetMouseWheelMove() == -1) &&
        defHeight[std::min(40, (int)eachDef.size()) - 1] >= 540)
    {
        for (int i = 0; i < CurrentState::currentWord.getDefinitionCount(); ++i)
        {
            defHeight[i] -= 40;
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

void SingleWordInfo::buildAnswer()
{
    // break the new lines
    isBreakNewLines = true;
    for (int i = 0; i < eachDef.size(); ++i)
    {
        if (MeasureTextEx(Resources::displayFontBold, eachDef[i].c_str(), 25, 1).x > 1220)
        {
            defBreakLines[i] = true;
            float propotion  = float(MeasureTextEx(Resources::displayFontBold, eachDef[i].c_str(), 25, 1).x / 1220);
            int pre          = 0;
            int position     = eachDef[i].length() / (float)propotion;
            while (position < eachDef[i].length())
            {
                while (
                    eachDef[i][position] != ' ' ||
                    MeasureTextEx(Resources::displayFontBold, eachDef[i].substr(pre, position - pre).c_str(), 25, 1).x >
                        1220)
                    position--;
                eachDef[i][position] = '\n';
                pre                  = position + 1;
                position += eachDef[i].length() / (float)propotion;
            }
        }
    }
}

void SingleWordInfo::draw()
{
    if (!isUpdated)
        update();
    if (editButton)
    {
        editMenu();
        return;
    }
    if (confirmDeleteBox)
    {
        deleteBox();
        return;
    }

    if (!isBreakNewLines)
        buildAnswer();

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

    // draw the line that divide the key and definition
    DrawRectangleLinesEx({-5, 0, 1290, 200}, 2, BLACK);
    DrawRectangleV({0, 120}, {1280, 79}, GetColor(SECONDARY_COLOR));

    if (GuiButton({10, 130, 25, 25}, "#113#"))
    {
        isInfo = true;
    }

    std::string selectedTmp =
        CurrentState::currentWord.getKey() + ' ' + '(' + CurrentState::currentWord.getType() + ')';
    DrawTextEx(Resources::displayFontBold, selectedTmp.c_str(), {105, 135}, 40, 2, GetColor(WRONG_ANS));

    if (GuiButton({700, 133, 135, 55}, "EDIT"))
    {
        editButton = true;
        return;
    }

    // Find the word in the Favortite list first.
    if (currentFavorites.find(CurrentState::currentWord.getKey()) == -1)
    {
        if (GuiButton({855, 133, 195, 55}, "ADD FAVORITE"))
        {
            currentFavorites.add(CurrentState::currentWord.getKey());
            currentFavorites.save();
        }
    }
    else
    {
        if (GuiButton({855, 133, 195, 55}, "REMOVE FAVORITE"))
        {
            currentFavorites.remove(CurrentState::currentWord.getKey());
            currentFavorites.save();
        }
    }
    if (GuiButton({1065, 133, 135, 55}, "DELETE"))
    {
        confirmDeleteBox = true;
    }

    drawSnow();
}

void SingleWordInfo::addDef()
{
    for (int i = 0; i < 40; ++i)
    {
        defHeight[i]     = 240 + i * 60;
        defBreakLines[i] = false;
    }
    if (GuiWindowBox({250, 170, 650, 300}, ""))
        addDefButton = false;

    text = "Please input new definition !";
    DrawTextEx(Resources::displayFontBold, text.c_str(),
               {580 - MeasureTextEx(Resources::displayFontBold, text.c_str(), 27, 1).x / 2, 220}, 27, 1, BLACK);

    // draw the Search Box
    if (GuiTextBox({300, 290, 550, 50}, NewDef, 500, SearchEdit))
    {
        SearchEdit ^= 1;
    }

    if (GuiButton({390, 390, 100, 50}, "ENTER"))
    {
        addDefButton = false;
        isFullDef    = false;
        eachDef.clear();
        edit_height.clear();
        CurrentState::currentWord.addDefinition(NewDef);
        currentTrie.insert(CurrentState::currentWord);
    }

    if (GuiButton({690, 390, 100, 50}, "BACK"))
    {
        addDefButton = false;
    }
}

void SingleWordInfo::drawSnow()
{
    Color snowflakeColor = GetColor(SNOW);

    // Draw snowflakes
    for (int i = 0; i < 100; i++)
    {
        DrawRectangleRec(snowflakes[i], snowflakeColor);
    }
}

void SingleWordInfo::deleteBox()
{
    if (GuiWindowBox({300, 170, 600, 250}, ""))
        confirmDeleteBox = false;

    text = "Are you sure to delete ?";
    DrawTextEx(Resources::displayFontBold, text.c_str(),
               {600 - MeasureTextEx(Resources::displayFontBold, text.c_str(), 27, 1).x / 2, 220}, 27, 1, BLACK);
    if (GuiButton({400, 330, 100, 50}, "YES"))
    {
        confirmDeleteBox = false;
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

    // for the edit menu
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

    edit_height.push_back(230);
    for (int i = 1; i <= eachDef.size(); i++)
    {
        edit_height.push_back(MeasureTextEx(Resources::displayFontRegular, eachDef[i - 1].c_str(), 25, 1).y +
                              edit_height[i - 1] + 35);
    }

    for (int i = 0; i < eachDef.size(); i++)
    {
        DrawTextEx(Resources::displayFontRegular, eachDef[i].c_str(), {48, (float)edit_height[i] + 8}, 25, 1, BLACK);
        DrawRectangleLinesEx({41, (float)edit_height[i], 1130, (float)edit_height[i + 1] - edit_height[i] - 20}, 2,
                             BLACK);
        if (GuiButton({1180, (float)edit_height[i], 65, 40}, "Edit"))
        {
            defChosen         = i;
            editEachDefButton = true;
            return;
        }
    }

    // draw the line that divide the key and definition
    DrawRectangleLinesEx({-5, 0, 1290, 200}, 2, BLACK);
    DrawRectangleV({0, 120}, {1280, 79}, GetColor(SECONDARY_COLOR));

    if (GuiButton({10, 130, 25, 25}, "#113#"))
    {
        editButton = false;
    }

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

void SingleWordInfo::editEachDef()
{
    for (int i = 0; i < 40; ++i)
    {
        defHeight[i]     = 240 + i * 60;
        defBreakLines[i] = false;
    }

    isBreakNewLines = false;
    if (GuiWindowBox({250, 170, 650, 300}, ""))
    {
        editEachDefButton = false;
        isEdited          = false;
    }

    text = "Edit Definition";
    DrawTextEx(Resources::displayFontBold, text.c_str(),
               {580 - MeasureTextEx(Resources::displayFontBold, text.c_str(), 27, 1).x / 2, 220}, 27, 1, BLACK);

    // draw the Search Box
    if (GuiTextBox({300, 290, 550, 50}, NewDef, 500, SearchEdit))
    {
        SearchEdit ^= 1;
    }

    if (!isEdited)
    {
        isEdited = true;
        memset(NewDef, 0, sizeof(NewDef));
        for (int i = 0; i < CurrentState::currentWord.getDefinition(defChosen).size(); ++i)
        {
            NewDef[i] = CurrentState::currentWord.getDefinition(defChosen)[i];
        }
    }

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