#ifndef GLOBAL_VARS
#define GLOBAL_VARS

#include "raylib.h"

enum Page
{
    DICT_WORD = 0,   // Main menu
    DICT_DEF_SEARCH, // Definition search
    DICT_FAVORITES,  // Favorites
    DICT_HISTORY,    // History
};
struct Resources
{
    static Font titleFont;

    static Font displayFontRegular;
    static Font displayFontBold;

    static Font wordFontRegular;
    static Font wordFontBold;
    static Font wordFontItalic;

    static Texture2D headerImage;
};
struct CurrentState
{
    static Page currentPage; // Current page (e.g. what search mode it's currently on, word search, definition search, etc.)
    static int currentDict;  // Current dict (e.g. what dictionary it's currently on, ENG-ENG, ENG-VIE, etc.)
};

#endif