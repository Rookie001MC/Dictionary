#include "frontend/pages/Game.h"
#include "raygui.h"
#include "raylib.h"

GamePage::GamePage()
{
    for (int i = 0; i < 5; i++)
    {
        dictPagesRects[i] = {61, float(146 + (122 * i)), 165, 55};
    }
    dictPagesRects[selectedDictPage] = {51, float(140 + (122 * selectedDictPage)), 195, 65};

    r.setDictionary(currentDictionary);
    r.setPath();
}

void GamePage::update()
{
if (IsMouseButtonPressed(0))
    {
        for (int i = 1; i <= 4; i++)
        {
            if (CheckCollisionPointRec(GetMousePosition(), {(float)320 + 220 * (i-1), 500, 200, 65}))
            {
                pressed = true;
                if (quiz[i] == quiz[1])
                {
                    ans = "Correct answer: " + quiz[i];
                    correctAns = true;
                }
                else
                {
                    ans = "Wrong answer: " + quiz[i];
                    correctAns = false;
                }
            }
        }
    }
}

void GamePage::draw()
{
    if (gameQuiz) {
        playGame();
        return;
    }

    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, PRIMARY_COLOR_CONTAINER);

    // Function switcher container
    DrawRectangleV(Vector2{0, 0}, Vector2{277, 720}, GetColor(SECONDARY_COLOR));
    DrawRectangleLinesEx({0, 0, 277, 720}, 2, BLACK);
    
    //Draws the function switcher
    for (int i = 0; i < dictPages.size(); i++)
    {
        if (i == selectedDictPage)
        {
            GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, PRIMARY_COLOR_CONTAINER_HOVER);
        }
        else
        {
            GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, PRIMARY_COLOR_CONTAINER);
        }
        if (GuiButton(dictPagesRects[i], dictPages[i].c_str()))
        {
            quiz.clear();
            CurrentState::currentPage = static_cast<Page>(i);
        }
    }

    DrawTextEx(Resources::displayFontBold, "CHOOSE THE QUIZ MODE", {570, 250}, 40, 1, BLACK);

    if (GuiButton({410, 390, 220, 67}, "GUESS WORD")) {
        quiz = r.guessKeyWord();
        mode = 1;
        gameQuiz = true;
    }

    if (GuiButton({730, 390, 220, 67}, "GUESS DEFINITION")) {
        quiz = r.guessDefinition();
        mode = 2;
        gameQuiz = true;
    }
}

void GamePage::playGame() {
    if (GuiButton({1260, 135, 25, 25}, "X")) {
        gameQuiz = false;
        quiz.clear();
        mode = 0;
    }

    DrawRectangleV({0, 120}, {1280, 170}, SECONDARY_COLOR_RGB);
    DrawTextEx(Resources::displayFontBold, quiz[0].c_str(), {580, 140}, 40, 1, BLACK);

    if (GuiButton(rec_next, "Next"))
    {
        if (mode == 1) {
            quiz.clear();
            quiz = r.guessKeyWord();
        }
        if (mode == 2) {
            quiz.clear();
            quiz = r.guessDefinition();
        }
        pressed = false;
    }

    // Draw 4 answer
    for (int i = 1; i <= 4; i++)
    {
        DrawRectangleGradientH(320 + 220 * (i-1), 500, 200, 65, button_color[i-1][0], button_color[i-1][1]);
        if (CheckCollisionPointRec(GetMousePosition(), {(float)320 + 220 * i, 500, 200, 65}))
            DrawRectangleGradientH(320 + 220 * i, 500, 200, 65, button_color[i-1][1], button_color[i-1][0]);
        DrawTextEx(Resources::displayFontBold, options[i-1].c_str(), {(float)320 + 220 * (i-1) + (200 - 40) / 2, (float)500 + (65 - 40) / 2}, 40, 1, WHITE);
    }
    if (pressed)
        DrawTextEx(Resources::displayFontBold, ans.c_str(), {320, 145}, 30, 1, correctAns ? GREEN : RED);

}