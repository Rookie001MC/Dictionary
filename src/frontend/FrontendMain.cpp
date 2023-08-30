/**
 * @file FrontendMain.cpp
 * @author Group 07 - CS163 - 2022-2023
 * @brief The main frontend class that handles the drawing and updating of the frontend.
 * @version 1.0
 */

#include "globalVars/globalVars.h"
#define RAYGUI_IMPLEMENTATION

#include "frontend/FrontendMain.h"

/**
 * @brief Set the styles of the program
 * 
 */
FrontendMain::FrontendMain()
{
    setStyles();
}

/**
 * @brief Start the frontend
 * This will also draw some of the elements of the frontend, namely the header and the title
 */
void FrontendMain::start()
{
    // Logic to update the data for the current Page of the dictionary
    switch (CurrentState::currentPage)
    {
        case Page::DICT_WORD: {
            word.update();
            break;
        }
        case Page::DICT_DEF_SEARCH: {
            def.update();
            break;
        }
        case Page::DICT_FAVORITES: {
            favorites.update();
            break;
        }
        case Page::DICT_HISTORY: {
            history.update();
            break;
        }
        case Page::DICT_GAME: {
            game.update();
            break;
        }
        case Page::SINGLE_WORD_INFO: {
            singleWordInfo.update();
            break;
        }
        default:
            break;
    }

    // Logic to draw the current Page of the dictionary
    BeginDrawing();
    {
        ClearBackground(BG_COLOR_RGB);
        switch (CurrentState::currentPage)
        {
            case Page::DICT_WORD: {
                word.draw();
                break;
            }
            case Page::DICT_DEF_SEARCH: {
                def.draw();
                break;
            }
            case Page::DICT_FAVORITES: {
                favorites.draw();
                break;
            }
            case Page::DICT_HISTORY: {
                history.draw();
                break;
            }
            case Page::DICT_GAME: {
                game.draw();
                break;
            }
            case Page::SINGLE_WORD_INFO: {
                singleWordInfo.draw();
                break;
            }
            default:
                break;
        }

        DrawTextureV(Resources::headerImage, {Header.x, Header.y}, WHITE);
        DrawTextEx(Resources::titleFont, "THE DICTIONARY", {500, Header.height / 2 - 30}, 50, 0, WHITE);
    }
    EndDrawing();
}
