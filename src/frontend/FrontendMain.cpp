#define RAYGUI_IMPLEMENTATION

#include "frontend/FrontendMain.h"
#include "frontend/ResourcesLoad.h"
#include "frontend/styles.h"
#include "frontend/pages/History.h"
#include "frontend/pages/Word.h"
#include "globalVars/globalVars.h"
#include "raylib.h"
#include "raygui.h"

void setStyles()
{
    GuiSetStyle(DEFAULT, TEXT_SIZE, DISPLAY_FONT_SIZE);

    GuiSetStyle(TEXTBOX, TEXT_COLOR_NORMAL, 0x082100);

    GuiSetStyle(DROPDOWNBOX, BASE_COLOR_NORMAL, PRIMARY_COLOR_CONTAINER);
    GuiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
    GuiSetStyle(DROPDOWNBOX, DROPDOWN_ITEMS_SPACING, 0);

    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, PRIMARY_COLOR_CONTAINER);
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, PRIMARY_COLOR_CONTAINER_HOVER);
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, OUTLINE_COLOR);
    GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, OUTLINE_COLOR);
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, TEXT_COLOR);
    GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, TEXT_COLOR);

    GuiSetStyle(LISTVIEW, SCROLLBAR_WIDTH, 18);

    GuiSetFont(Resources::displayFontRegular);
}

FrontendMain::FrontendMain()
{
            loadResources();     
            setStyles();
}

void FrontendMain::start()
        {
            switch (CurrentState::currentPage)
            {
                case Page::DICT_WORD:
                {
                    //wordPage.update();
                    return;
                }
                // case Page::DICT_DEF_SEARCH:
                // {
                //     return; // definition
                // }
                // case Page::DICT_FAVORITES:
                // {
                //     return; // favorite
                // }
                case Page::DICT_HISTORY:
                {
                    history.update();
                    break;
                }
                default: break;
            }
            BeginDrawing();
            {
                ClearBackground(BG_COLOR_RGB);
                switch (CurrentState::currentPage)
                {
                    case Page::DICT_WORD:
                    {
                        DrawRectangle(0, 0, 300, 600, RED);
                        break;
                    }
                    case Page::DICT_HISTORY:
                    {
                        history.draw();
                        break;
                    }
                    default: break;
                } 
            
            DrawTextureV(Resources::headerImage, {Header.x, Header.y}, WHITE);
            DrawTextEx(Resources::titleFont, "The Dictionary of Everything?", {Header.x + 50, Header.height / 2 - 30 }, 50, 0, WHITE);
            }
            EndDrawing();
        }