// main function currently used for testing. will be changed in the future
#include "boost/filesystem.hpp"
#include "boost/filesystem/operations.hpp"
#include "dictionary/build.h"
#include "dictionary/history.h"
#include "dictionary/trie.h"
#include "dictionary/word.h"
#include <chrono>
#include <iostream>

#include "frontend/FrontendMain.h"
#include "frontend/ResourcesLoad.h"
#include "frontend/styles.h"

int main(int argc, const char *argv[])
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CS163 Project - The Dictionary of Everything?");
    SetTargetFPS(60);
    FrontendMain frontend;
    while(!WindowShouldClose())
    {
        frontend.start();
    }

    unloadResources();
    CloseWindow();
    return 0;
}