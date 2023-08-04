#include "frontend/ResourcesLoad.h"
#include "frontend/styles.h"
#include "globalVars/globalVars.h"
#include "dictionary/filePathHandler.h"
#include "raylib.h"

void loadResources(const char* exeDir)
{ 
    std::string staticFolder = getExeDir(exeDir) + "../static/";
    std::string fontFolder   = staticFolder + "fonts/";
    std::string imageFolder  = staticFolder + "img/";

    std::string displayFont = "FiraSans";
    std::string wordFont    = "PlayfairDisplay";

    Resources::titleFont = LoadFontEx((fontFolder + wordFont + "/" + wordFont+ "-Bold.ttf").c_str(), 50, 0, 250);

    Resources::displayFontRegular = LoadFontEx((fontFolder + displayFont + "/" + displayFont + "-Regular.ttf").c_str(),TEXT_FONT_SIZE, 0, 250);
    Resources::displayFontBold    = LoadFontEx((fontFolder + displayFont + "/" + displayFont + "-Bold.ttf").c_str(), TEXT_FONT_SIZE, 0, 250);



    Resources::wordFontRegular = LoadFontEx((fontFolder + wordFont + "/" + wordFont + "-Regular.ttf").c_str(), WORD_FONT_SIZE, 0, 250);
    Resources::wordFontBold    = LoadFontEx((fontFolder + wordFont + "/" + wordFont + "-Bold.ttf").c_str(), WORD_FONT_SIZE, 0, 250);
    Resources::wordFontItalic  = LoadFontEx((fontFolder + wordFont + "/" + wordFont + "-Italic.ttf").c_str(), WORD_FONT_SIZE, 0, 250);

    Resources::headerImage = LoadTexture((imageFolder + "header.png").c_str());
}

void unloadResources()
{
    UnloadFont(Resources::titleFont);
    UnloadFont(Resources::displayFontRegular);
    UnloadFont(Resources::displayFontBold);
    UnloadFont(Resources::wordFontRegular);
    UnloadFont(Resources::wordFontBold);
    UnloadFont(Resources::wordFontItalic);
    UnloadTexture(Resources::headerImage);
}