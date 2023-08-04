#ifndef GLOBAL_VARS
#define GLOBAL_VARS

#include "raylib.h"

enum Page
{
    DICT_HOME = 0, 
    DICT_DEF_SEARCH,
    DICT_FAVORITES,
    DICT_HISTORY,
    DICT_WORD,
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
    static Page currentPage;
    static int currentDict;
};


#endif