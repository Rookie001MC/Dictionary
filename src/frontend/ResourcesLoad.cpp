/**
 * @file ResourcesLoad.cpp
 * @author Group 07 - CS163 - 2022-2023
 * @brief File to load and unload all the resources needed for the program
 * @version 1.0
 */

#include "frontend/ResourcesLoad.h"

/**
 * @brief Load all the resources needed for the program.
 * @note This is only called once at the start of the program.
 * 
 */
void loadResources()
{
    std::cout << "\033[1;32mLoading resources...\033[0m" << std::endl;

    // Set the directories of the types of resources
    std::string staticFolder = Resources::currentExeDir + "../static/";
    std::string fontFolder   = staticFolder + "fonts/";
    std::string imageFolder  = staticFolder + "img/";

    // Set the fonts
    // Font source: https://fonts.google.com/
    std::string displayFont = "FiraSans";
    std::string wordFont    = "PlayfairDisplay";

    // Load the fonts
    Resources::titleFont = LoadFontEx((fontFolder + wordFont + "/" + wordFont + "-Bold.ttf").c_str(), 50, 0, 250);

    Resources::displayFontRegular =
        LoadFontEx((fontFolder + displayFont + "/" + displayFont + "-Regular.ttf").c_str(), TEXT_FONT_SIZE, 0, 250);
    Resources::displayFontBold =
        LoadFontEx((fontFolder + displayFont + "/" + displayFont + "-Bold.ttf").c_str(), TEXT_FONT_SIZE, 0, 250);

    Resources::wordFontRegular =
        LoadFontEx((fontFolder + wordFont + "/" + wordFont + "-Regular.ttf").c_str(), WORD_FONT_SIZE, 0, 250);
    Resources::wordFontBold =
        LoadFontEx((fontFolder + wordFont + "/" + wordFont + "-Bold.ttf").c_str(), WORD_FONT_SIZE, 0, 250);
    Resources::wordFontItalic =
        LoadFontEx((fontFolder + wordFont + "/" + wordFont + "-Italic.ttf").c_str(), WORD_FONT_SIZE, 0, 250);


    // Load the header image
    Resources::headerImage = LoadTexture((imageFolder + "header.png").c_str());
}

/**
 * @brief Unload all the resources.
 * @note This is only called once at the end of the program.
 */
void unloadResources()
{
    std::cout << "\033[1;31mUnloading resources...\033[0m" << std::endl;
    UnloadFont(Resources::titleFont);
    UnloadFont(Resources::displayFontRegular);
    UnloadFont(Resources::displayFontBold);
    UnloadFont(Resources::wordFontRegular);
    UnloadFont(Resources::wordFontBold);
    UnloadFont(Resources::wordFontItalic);
    UnloadTexture(Resources::headerImage);
}