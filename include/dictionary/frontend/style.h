#ifndef PALETTE_H
#define PALETTE_H

#include "raygui.h"
#include "raylib.h"

#define PRIMARY_COLOR (0x9c4144)
#define SECONDARY_COLOR (0x845400)
#define OUTLINE_COLOR (0x857372)

#define TEXT_COLOR (0x082100)

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define DISPLAY_FONT_SIZE 40
#define WORD_FONT_SIZE 30
#define TEXT_FONT_SIZE 14

#define MAX_INPUT_CHAR 256

#define ITEM_HEIGHT 30
#define DEFAULT_PADDING                                                                                                \
    (Vector2)                                                                                                          \
    {                                                                                                                  \
        20.0f, 20.0f                                                                                                   \
    }
#define DEFAULT_TEXT_MARGIN                                                                                            \
    (Vector2)                                                                                                          \
    {                                                                                                                  \
        6.0f, 6.0f                                                                                                     \
    }
#define DEFAULT_ITEM_MARGIN                                                                                            \
    (Vector2)                                                                                                          \
    {                                                                                                                  \
        20.0f, 20.0f                                                                                                   \
    }
#endif