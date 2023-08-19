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
            if (CheckCollisionPointRec(GetMousePosition(), {(float)320 + 220 * (i - 1), 500, 200, 65}))
            {
                pressed = true;
                if (quiz[i] == quiz[1])
                {
                    ans        = "Correct answer: " + quiz[i];
                    correctAns = true;
                }
                else
                {
                    ans        = "Wrong answer: " + quiz[i];
                    correctAns = false;
                }
            }
        }
    }
}

void GamePage::draw()
{
    if (gameQuiz)
    {
        playGame();
        return;
    }

    // Function switcher container
    DrawRectangleV(Vector2{0, 0}, Vector2{277, 720}, GetColor(SECONDARY_COLOR));
    DrawRectangleLinesEx({0, 0, 277, 720}, 2, BLACK);

    // Draws the function switcher
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

    DrawTextEx(Resources::displayFontBold, "CHOOSE THE QUIZ MODE", {573, 253}, 43, 1, BLACK);

    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, PRIMARY_COLOR_CONTAINER);

    if (GuiButton({450, 390, 220, 67}, "GUESS WORD"))
    {
        quiz     = r.guessKeyWord();
        mode     = 1;
        gameQuiz = true;
    }

    if (GuiButton({835, 390, 220, 67}, "GUESS DEFINITION"))
    {
        quiz     = r.guessDefinition();
        mode     = 2;
        gameQuiz = true;
    }
}

void GamePage::drawQuestion()
{
    // Define the rectangle
    Rectangle rect       = {0, 120, 1280, 100};
    Color secondaryColor = SECONDARY_COLOR_RGB;

    // Define the text to be displayed
    const char *text = quiz[0].c_str();
    Font font        = Resources::displayFontBold;
    int fontSize     = 30;
    Color textColor  = BLACK;

    // Measure the width and height of the text
    Vector2 textSize = MeasureTextEx(font, text, fontSize, 1);

    // Calculate the position to center the text within the rectangle horizontally
    float centerX = rect.x + (rect.width - textSize.x) / 2;

    // Calculate the position to center the text within the rectangle vertically
    float centerY = rect.y + (rect.height - textSize.y) / 2;

    // Check if the text exceeds the width of the rectangle
    if (textSize.x > rect.width || textSize.y > rect.height)
    {
        // Text exceeds the rectangle boundaries, perform actions based on 'mode'
        if (mode == 1)
        {
            // Clear and get a new word for mode 1
            quiz.clear();
            quiz = r.guessKeyWord();
        }
        else if (mode == 2)
        {
            // Clear and get a new definition for mode 2
            quiz.clear();
            quiz = r.guessDefinition();
        }
    }
    else
    {
        // Text fits within the rectangle, so draw it centered
        DrawRectangleV({rect.x, rect.y}, {rect.width, rect.height}, secondaryColor);
        DrawTextEx(font, text, {centerX, centerY}, fontSize, 1, textColor);
    }
}

void GamePage::playGame()
{
    drawQuestion();

    if (GuiButton({1090, 220, 90, 45}, "Next"))
    {
        if (mode == 1)
        {
            quiz.clear();
            quiz = r.guessKeyWord();
        }
        if (mode == 2)
        {
            quiz.clear();
            quiz = r.guessDefinition();
        }
        pressed = false;
    }

    if (GuiButton({30, 135, 25, 25}, "X"))
    {
        gameQuiz = false;
        quiz.clear();
        mode = 0;
    }

    // Draw 4 answer
    for (int i = 1; i <= 4; i++)
    {
        DrawRectangleGradientH(320 + 220 * (i - 1), 500, 200, 65, button_color[i - 1][0], button_color[i - 1][1]);
        if (CheckCollisionPointRec(GetMousePosition(), {(float)320 + 220 * i, 500, 200, 65}))
            DrawRectangleGradientH(320 + 220 * i, 500, 200, 65, button_color[i - 1][1], button_color[i - 1][0]);
        DrawTextEx(Resources::displayFontBold, options[i - 1].c_str(),
                   {(float)320 + 220 * (i - 1) + (200 - 40) / 2, (float)500 + (65 - 40) / 2}, 40, 1, WHITE);
    }
    if (pressed)
        DrawTextEx(Resources::displayFontBold, ans.c_str(), {320, 145}, 30, 1, correctAns ? GREEN : RED);
}