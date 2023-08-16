#define RAYGUI_IMPLEMENTATION

#include "frontend/FrontendMain.h"


FrontendMain::FrontendMain()
{            
            setStyles();
}

void FrontendMain::start()
        {
            switch (CurrentState::currentPage)
            {
                case Page::DICT_WORD:
                {
                    word.update();
                    break;
                }
                case Page::DICT_DEF_SEARCH:
                {
                    def.update();
                    break;
                }
                case Page::DICT_FAVORITES:
                {
                    favorites.update();
                    break;
                }
                case Page::DICT_HISTORY:
                {
                    history.update();
                    break;
                }
                case Page::DICT_GAME:
                {
                    game.update();
                    break;
                }
                case Page::SINGLE_WORD_INFO:
                {
                    singleWordInfo.update();
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
                        word.draw();
                        break;
                    }
                    case Page::DICT_DEF_SEARCH:
                    {
                        def.draw();
                        break;
                    }
                    case Page::DICT_FAVORITES:
                    {
                        favorites.draw();
                        break;
                    }
                    case Page::DICT_HISTORY:
                    {
                        history.draw();
                        break;
                    }
                    case Page::DICT_GAME:
                    {
                        game.draw();
                        break;
                    }
                    case Page::SINGLE_WORD_INFO:
                    {
                        singleWordInfo.draw();
                        break;
                    }
                    default: break;
                } 
            
            DrawTextureV(Resources::headerImage, {Header.x, Header.y}, WHITE);
            DrawTextEx(Resources::titleFont, "THE DICTIONARY", {500, Header.height / 2 - 30 }, 50, 0, WHITE);
            }
            EndDrawing();
        }