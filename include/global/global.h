#ifndef GLOBAL_VARS
#define GLOBAL_VARS

#include "raylib.h"

struct Resources
{
    Font displayFontRegular;
    Font displayFontBold;

    Font wordFontRegular;
    Font wordFontBold;
    Font wordFontItalic;
};

enum Page
{
    DICT_MAIN = 0, // This should also be able to search for definitions, I guess???
    DICT_HISTORY,
    DICT_FAVORITES,
    DICT_WORD,
};

struct PageState
{
    int page = Page::DICT_MAIN;     
};

#endif