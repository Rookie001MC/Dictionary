#include "frontend/pages/Game.h"
#include "frontend/styles.h"
#include "raygui.h"
#include "raylib.h"

GamePage::GamePage()
{
    for (int i = 0; i < 5; i++)
    {
        dictPagesRects[i] = {61, float(146 + (122 * i)), 165, 55};
    }
    dictPagesRects[selectedDictPage] = {51, float(140 + (122 * selectedDictPage)), 195, 65};

    // drawing snow
    for (int i = 0; i < 100; i++)
    {
        snowflakes[i].x      = GetRandomValue(0, 720);
        snowflakes[i].y      = GetRandomValue(0, 1280);
        snowflakes[i].width  = GetRandomValue(2, 4);
        snowflakes[i].height = GetRandomValue(2, 4);
    }
    r.setDictionary(currentDictionary);
    r.setPath();
}

void GamePage::update()
{
    // drawing snow
    for (int i = 0; i < 100; i++)
    {
        snowflakes[i].y += 1.5; // Adjust the speed of falling snow
        if (snowflakes[i].y > 720)
        {
            snowflakes[i].y = 0;
            snowflakes[i].x = GetRandomValue(0, 1280);
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

    // Draw the Dict Picker
    if (GuiDropdownBox(rec_dictionary,
                       (dictLanguages[0] + "\n" + dictLanguages[1] + "\n" + dictLanguages[2] + "\n" + dictLanguages[3] +
                        "\n" + dictLanguages[4])
                           .c_str(),
                       CurrentState::currentDict, dropDownBox))
    {
        dropDownBox ^= 1;
        currentDictionary = new Dictionary(dictLanguages[*CurrentState::currentDict], *CurrentState::currentDict);
        r.setDictionary(currentDictionary);
        r.setPath();
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

    // Draw snowflakes
    for (int i = 0; i < 100; i++)
    {
        DrawRectangleRec(snowflakes[i], snowflakeColor);
    }
}

void GamePage::drawQuestion()
{
    // Define the rectangle
    Rectangle rect       = {0, 120, 1280, 100};
    Color secondaryColor = SECONDARY_COLOR_RGB;

    // Define the text to be displayed
    const char *text = quiz[0].c_str();
    Font font        = Resources::wordFontBold;
    int fontSize     = WORD_FONT_SIZE;
    bool check       = false;
    Color textColor  = BLACK;

    // Measure the width and height of the text
    Vector2 textSize = MeasureTextEx(font, text, fontSize, 1);

    // Check if the text exceeds the width of the rectangle
    if (textSize.x > rect.width + 20 || textSize.y > rect.height)
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
        // Calculate the position to center the text within the rectangle horizontally
        float centerX = rect.x + (rect.width - textSize.x) / 2;

        // Calculate the position to center the text within the rectangle vertically
        float centerY = rect.y + (rect.height - textSize.y) / 2;

        // Draw the rectangle
        DrawRectangleV({rect.x, rect.y}, {rect.width, rect.height}, secondaryColor);

        // Draw the text within the rectangle
        DrawTextEx(font, text, {centerX, centerY}, fontSize, 1, textColor);
    }

    // Draw snowflakes
    for (int i = 0; i < 100; i++)
    {
        DrawRectangleRec(snowflakes[i], snowflakeColor);
    }
}

void GamePage::buildAnswer()
{
    // break the new lines
    isBreakNewLines = true;
    for (int i = 1; i <= 4; ++i)
    {
        quiz[i] = options[i - 1] + ". " + quiz[i];
        if (MeasureTextEx(Resources::displayFontBold, quiz[i].c_str(), 25, 1).x > 580)
        {
            float propotion = float(MeasureTextEx(Resources::displayFontBold, quiz[i].c_str(), 25, 1).x / 580);
            int pre         = 0;
            int position    = quiz[i].length() / (float)propotion;
            while (position < quiz[i].length())
            {
                while (quiz[i][position] != ' ' ||
                       MeasureTextEx(Resources::displayFontBold, quiz[i].substr(pre, position - pre).c_str(), 25, 1).x >
                           580)
                    position--;
                quiz[i][position] = '\n';
                pre               = position + 1;
                position += quiz[i].length() / (float)propotion;
            }
        }
    }
}

void GamePage::drawCountDown(int timeLeft)
{
    char timerText[20];
    snprintf(timerText, sizeof(timerText), "Time Left: %d", timeLeft);
    DrawTextEx(Resources::displayFontBold, timerText, {10, 230}, 27, 1, DARKGRAY);
}

void GamePage::drawTimer()
{
    currentTime      = GetTime();
    double deltaTime = currentTime - previousTime;

    if (deltaTime >= 1.0)
    {
        cnt--;
        previousTime = currentTime;
    }

    drawCountDown(cnt);
}

void GamePage::playGame()
{
    drawQuestion();

    // get the answer
    choice = r.getChoice();

    if (!isBreakNewLines)
        buildAnswer();
    if (cnt > 0 && !choosen)
        drawTimer();
    else if (cnt > 0 && choosen)
    {
        drawCountDown(cnt);
    }
    else
    {
        DrawTextEx(Resources::displayFontBold, "Time left: 0", {10, 230}, 27, 1, DARKGRAY);
    }

    if (GuiButton({1090, 222, 90, 45}, "Next"))
    {
        isBreakNewLines = false;
        pressed         = false;
        choosen         = false;
        cnt             = COUNTDOWN_DURATION + 1;
        int choice = -1, check = 0;
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

    if (GuiButton({10, 130, 25, 25}, "#113#"))
    {
        isBreakNewLines = false;
        cnt             = COUNTDOWN_DURATION + 1;
        choosen         = false;
        pressed         = false;
        int choice = -1, check = 0;
        gameQuiz = false;
        quiz.clear();
        mode = 0;
    }

    checkAns();

    for (int i = 1; i <= 4; ++i)
    {
        if (i == choice)
        {
            button_ans[i] = GetColor(CORRECT_ANS);
        }
        else
        {
            button_ans[i] = GetColor(WRONG_ANS);
        }
    }

    if (pressed)
    {
        if (check == 5)
        {
            DrawTextEx(Resources::displayFontBold, ans.c_str(), {590, 230}, 30, 1, PURPLE);
        }
        else
        {
            DrawTextEx(Resources::displayFontBold, ans.c_str(), {550, 230}, 30, 1,
                       correctAns ? GetColor(CORRECT_ANS) : RED);
        }

        if (check != choice)
        {
            switch (choice)
            {
                case 1: {
                    DrawRectangleV({1, 269}, {637, 223}, button_ans[1]);
                    DrawTextEx(Resources::displayFontBold, quiz[1].c_str(), {31, 330}, 25, 1, WHITE);
                    break;
                }
                case 2: {
                    DrawRectangleV({643, 269}, {637, 223}, button_ans[2]);
                    DrawTextEx(Resources::displayFontBold, quiz[2].c_str(), {673, 330}, 25, 1, WHITE);
                    break;
                }
                case 3: {
                    DrawRectangleV({1, 495}, {637, 223}, button_ans[3]);
                    DrawTextEx(Resources::displayFontBold, quiz[3].c_str(), {31, 556}, 25, 1, WHITE);
                    break;
                }
                case 4: {
                    DrawRectangleV({643, 495}, {637, 223}, button_ans[4]);
                    DrawTextEx(Resources::displayFontBold, quiz[4].c_str(), {673, 556}, 25, 1, WHITE);
                    break;
                }
                default: {
                    break;
                }
            }
        }

        switch (check)
        {
            case 1: {
                DrawRectangleV({1, 269}, {637, 223}, button_ans[1]);
                DrawTextEx(Resources::displayFontBold, quiz[1].c_str(), {31, 330}, 25, 1, WHITE);
                break;
            }
            case 2: {
                DrawRectangleV({643, 269}, {637, 223}, button_ans[2]);
                DrawTextEx(Resources::displayFontBold, quiz[2].c_str(), {673, 330}, 25, 1, WHITE);
                break;
            }
            case 3: {
                DrawRectangleV({1, 495}, {637, 223}, button_ans[3]);
                DrawTextEx(Resources::displayFontBold, quiz[3].c_str(), {31, 556}, 25, 1, WHITE);
                break;
            }
            case 4: {
                DrawRectangleV({643, 495}, {637, 223}, button_ans[4]);
                DrawTextEx(Resources::displayFontBold, quiz[4].c_str(), {673, 556}, 25, 1, WHITE);
                break;
            }
            default: {
                break;
            }
        }
    }
    else
    {
        // Draw 4 answer
        DrawRectangleV({1, 269}, {637, 223}, RED);
        if (CheckCollisionPointRec(GetMousePosition(), {1, 269, 637, 223}))
        {
            DrawRectangle(1, 269, 637, 223, GetColor(QUESTION_HOVER_RED));
        }
        DrawTextEx(Resources::displayFontBold, quiz[1].c_str(), {31, 330}, 25, 1, WHITE);

        DrawRectangleV({643, 269}, {637, 223}, GetColor(QUESTION_COLOR_BLUE));
        if (CheckCollisionPointRec(GetMousePosition(), {643, 269, 637, 223}))
        {
            DrawRectangle(643, 269, 637, 223, GetColor(QUESTION_HOVER_BLUE));
        }
        DrawTextEx(Resources::displayFontBold, quiz[2].c_str(), {673, 330}, 25, 1, WHITE);

        DrawRectangleV({1, 495}, {637, 223}, GetColor(QUESTION_COLOR_YELLOW));
        if (CheckCollisionPointRec(GetMousePosition(), {1, 495, 637, 223}))
        {
            DrawRectangle(1, 495, 637, 223, GetColor(QUESTION_HOVER_YELLOW));
        }
        DrawTextEx(Resources::displayFontBold, quiz[3].c_str(), {31, 556}, 25, 1, WHITE);

        DrawRectangleV({643, 495}, {637, 223}, GetColor(QUESTION_COLOR_GREEN));
        if (CheckCollisionPointRec(GetMousePosition(), {643, 495, 637, 223}))
        {
            DrawRectangle(643, 495, 637, 223, GetColor(QUESTION_HOVER_GREEN));
        }
        DrawTextEx(Resources::displayFontBold, quiz[4].c_str(), {673, 556}, 25, 1, WHITE);
    }

    // Draw snowflakes
    for (int i = 0; i < 100; i++)
    {
        DrawRectangleRec(snowflakes[i], snowflakeColor);
    }
}

void GamePage::checkAns()
{
    if (cnt <= 0)
    {
        pressed    = true;
        correctAns = true;
        ans        = "TIME OUT";
        check      = 5;
    }
    if (IsMouseButtonPressed(0) && !choosen)
    {
        choosen = true;
        if (CheckCollisionPointRec(GetMousePosition(), {1, 269, 637, 223}))
        {
            pressed = true;
            check   = 1;
        }
        else if (CheckCollisionPointRec(GetMousePosition(), {643, 269, 637, 223}))
        {
            pressed = true;
            check   = 2;
        }
        else if (CheckCollisionPointRec(GetMousePosition(), {1, 495, 637, 223}))
        {
            pressed = true;
            check   = 3;
        }
        else if (CheckCollisionPointRec(GetMousePosition(), {643, 495, 637, 223}))
        {
            pressed = true;
            check   = 4;
        }

        if (check == choice)
        {
            ans        = "YOU ARE CORRECT";
            correctAns = true;
        }
        else
        {
            ans        = "YOU ARE WRONG";
            correctAns = false;
        }
    }
}