#include "dictMain.h"
#include "global.h"

void dictMain()
{
    // Update
    //----------------------------------------------------------------------------------

    // Draw

    BeginDrawing();
    {
        switch(CurrentPage)
        {
            case PAGE::DICT_MAIN:
            {
                return;
            }
            case PAGE::DICT_FAVORITES:
            {
                return;
            }
            case PAGE::DICT_HISTORY:
            {
                return;
            }
        }
    }
    EndDrawing();

}