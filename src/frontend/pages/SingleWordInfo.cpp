#include "frontend/pages/SingleWordInfo.h"
#include "frontend/pages/Word.h"
#include "frontend/styles.h"
#include "globalVars/globalVars.h"
#include "raygui.h"
#include "raylib.h"

SingleWordInfo::SingleWordInfo()
{
    for (int i = 0; i < 20; ++i)
    {
        defHeight[i]     = 220 + i * 60;
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
    currentFavorites = History(favoritesDirectories[*CurrentState::currentDict], 1);
    if (isInfo)
    {
        eachDef.clear();
        isFullDef                 = false;
        isInfo                    = false;
        CurrentState::currentPage = static_cast<Page>(0);
    }

    if (!isFullDef)
    {
        std::string tmp;
        isFullDef = true;

        for (int i = 0; i < CurrentState::currentWord.getDefinitionCount(); ++i)
        {
            tmp = CurrentState::currentWord.getDefinition(i);
            eachDef.push_back(tmp);
        }
    }

    if ((IsKeyPressed(KEY_UP) || GetMouseWheelMove() == 1) && defHeight[0] < 300)
    {
        for (int i = 0; i < CurrentState::currentWord.getDefinitionCount(); ++i)
        {
            defHeight[i] += 40;
        }
    }

    if ((IsKeyPressed(KEY_DOWN) || GetMouseWheelMove() == -1) &&
        defHeight[std::min(20, (int)eachDef.size()) - 1] >= 540)
    {
        for (int i = 0; i < CurrentState::currentWord.getDefinitionCount(); ++i)
        {
            defHeight[i] -= 40;
        }
    }

    // drawing snow
    for (int i = 0; i < 100; i++)
    {
        snowflakes[i].y += 1.5 ; // Adjust the speed of falling snow
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
    if (editButton)
    {
        editMenu();
        return;
    }
    if (confirmDeleteBox)
    {
        deleteBox(-1);
        return;
    }

    for (int i = 0; i < std::min(20, (int)eachDef.size()); ++i)
    {
        if (!isBreakNewLines)
            buildAnswer();
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
    DrawTextEx(Resources::wordFontBold, selectedTmp.c_str(), {115, 135}, 47, 2, BLACK);

    if (GuiButton({700, 133, 135, 55}, "EDIT"))
    {
        edit_height.push_back(200);
        editButton = true;
        for (int i = 1; i <= eachDef.size(); i++)
        {
            edit_height.push_back(MeasureTextEx(Resources::displayFontRegular, eachDef[i - 1].c_str(), 25, 1).y +
                                  edit_height[i - 1] + 35);
        }
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
    }

    drawSnow();
}

void SingleWordInfo::drawSnow() {
    Color snowflakeColor = GetColor(SNOW);

    // Draw snowflakes
    for (int i = 0; i < 100; i++)
    {
        DrawRectangleRec(snowflakes[i], snowflakeColor);
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

    if ((IsKeyPressed(KEY_UP) || GetMouseWheelMove() == 1) && edit_height[0] < 200)
    {
        for (int i = 0; i <= eachDef.size(); i++)
            edit_height[i] += 40;
    }
    if ((IsKeyPressed(KEY_DOWN) || GetMouseWheelMove() == -1) && edit_height.back() >= 540)
    {
        for (int i = 0; i <= eachDef.size(); i++)
            edit_height[i] -= 40;
    }

    for (int i = 0; i < eachDef.size(); i++)
    {
        DrawTextEx(Resources::displayFontRegular, eachDef[i].c_str(), {48, (float)edit_height[i] + 8}, 25, 1, BLACK);
        DrawRectangleLinesEx({41, (float)edit_height[i], 1110, (float)edit_height[i + 1] - edit_height[i] - 20}, 2,
                             BLACK);
        if (GuiButton({1158, (float)edit_height[i], 65, 40}, "Edit"))
        {
            edit_height.clear();
            // defChosen = i;
            editEachDefButton = true;
            // strcpy(newdata, selectedWord->defs[defChosen]->data.c_str());
            return;
        }
    }

    DrawRectangleRec({0, 100, 1280, 90}, GetColor(SECONDARY_COLOR));
    DrawRectangleLinesEx({-5, 0, 1289, 190}, 2, BLACK);

    DrawTextEx(Resources::displayFontBold, "EDIT MENU", {70, 136}, 40, 1, RED);
    if (GuiButton({750, 130, 100, 50}, "SAVE"))
        confirmSaveBox = true;
    if (GuiButton({880, 130, 170, 50}, "ADD MORE"))
    {
        addDefButton = true;
        // newData = "\0";
        // defChosen = eachDef.size();
        // newdata[0] = '\0';
    }
}