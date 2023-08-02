#include "global.h"

void resourceLoad(const std::string path)
{
    // path of the current executable
    std::string currentResource = (getCurrentExeDir(path)).string();


    // Load fonts
    ResourcesPath::displayRegularFont = loadFont(displayRegularFont, DISPLAY_FONT_SIZE);
    ResourcesPath::displayBoldFont = loadFont(displayBoldFont, DISPLAY_FONT_SIZE);

    ResourcesPath::wordRegularFont = loadFont(wordRegularFont, WORD_FONT_SIZE);
    ResourcesPath::wordBoldFont = loadFont(wordBoldFont, WORD_FONT_SIZE);
    ResourcesPath::wordItalicFont = loadFont(wordItalicFont, WORD_FONT_SIZE);

    // Load images
    ResourcesPath::headerImage = LoadTexture(headerImage.c_str());    
}

Font loadFont(const std::string path, const int fontSize)
{
    Font font = LoadFontEx(path.c_str(), fontSize, nullptr, 256);
    return font;
}

