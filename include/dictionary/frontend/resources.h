#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>
#include "raylib.h"


/* Directories definition */
const std::string staticDir = "/static/";
const std::string fontDir = staticDir + "fonts/";
const std::string imageDir = staticDir + "img/";


// Images
// ---------------------
const std::string headerImage = imageDir + "header.png";

// Fonts
// ---------------------
const std::string displayRegularFont = fontDir + "FiraSans/FiraSans-Regular.ttf";
const std::string displayBoldFont = fontDir + "FiraSans/FiraSans-Bold.ttf";

const std::string wordRegularFont = fontDir + "PlayfairDisplay/PlayfairDisplay-Regular.ttf";
const std::string wordBoldFont = fontDir + "PlayfairDisplay/PlayfairDisplay-Bold.ttf";
const std::string wordItalicFont = fontDir + "PlayfairDisplay/PlayfairDisplay-Italic.ttf";
// ---------------------

// Loader function
void resourceLoad(const std::string path);
Font loadFont(const std::string path, const int fontSize);
#endif