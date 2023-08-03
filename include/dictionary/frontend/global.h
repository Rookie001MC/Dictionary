#ifndef GLOBAL_H
#define GLOBAL_H

#include <vector>
#include "raygui.h"
#include "raylib.h"
#include "filePath.h"
#include "resources.h"
#include "frontendInit.h"
#include "style.h"
#include "dictMain.h"
struct ResourcesPath
{
    static Font displayRegularFont;
    static Font displayBoldFont;

    static Font wordRegularFont;
    static Font wordBoldFont;
    static Font wordItalicFont;

    static Texture2D headerImage;
};

enum PAGE
{
    DICT_MAIN = 0,
    DICT_WORD_DEF,
    DICT_EDIT,
    DICT_FAVORITES,
    DICT_HISTORY,
};

const int CurrentPage = DICT_MAIN;
#endif