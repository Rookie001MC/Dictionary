#include "dictionary/random.h"

void Random::setDictionary(Dictionary *dict)
{
    this->dictionary = dict;
}

void Random::setMode(Dictionary *dict)
{
    this->mode = dict->getDictionaryType();
}

void Random::setPath()
{
    switch (mode)
    {
        case 0:
            path = "../data/engengRandom.txt";
            break;
            // More to come
    }
}
int Random::getMode()
{
    this->mode = mode;
}

std::string Random::getPath()
{
    this->path = path;
}
int Random::getRandomNumber()
{
    int totalWords = 0;
    int dictType   = getMode();
    switch (dictType)
    {
        case 0: // engeng
            totalWords = 144307;
            break;
            // More to come
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, totalWords);
    return dis(gen);
}
Word Random::viewRandomWord()
{
    std::ifstream fin(getPath());
    int randomNum = getRandomNumber();
    Word randomWord;
    std::string line;
    int currentLine = 0;
    while (std::getline(fin, line))
    {
        ++currentLine;
        if (currentLine == randomNum)
        {
            int sharpPos         = line.find('#');
            int atPos            = line.find_first_of('@');
            std::string keyWord  = line.substr(0, sharpPos - 1);
            std::string wordType = line.substr(sharpPos + 1, atPos - sharpPos - 2);
            std::vector<std::string> definitions;
            randomWord.setKey(keyWord);
            randomWord.setType(wordType);

            int index = atPos + 1;
            while (index < line.length())
            {
                int nextAtPos = line.find('@', index);
                if (nextAtPos == std::string::npos)
                    break;
                std::string def = line.substr(index, nextAtPos - index);
                randomWord.addDefinition(def);
                index = nextAtPos + 1;
            }
        }
    }
    fin.close();
    return randomWord;
}

int Random::randomInFour()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 4);
    return dis(gen);
}

std::string get1stDefinitionFromText(const std::string &line)
{
    std::string definition;
    int start  = line.find_first_of(':') + 2;
    int end    = line.find('@', start + 1);
    definition = line.substr(start, end - start);
    return definition;
}

std::vector<std::string> Random::random4DefinitionsAnd1KeyWord()
{
    std::vector<std::string> quiz;
    // Random the line that contains the correct keyword and definition
    int randomCorrectAns = getRandomNumber();

    // Only get the definition of the wrong ans
    // While loop to make sure that 4 numbers are different from each other
    int wrongAns1 = getRandomNumber();
    while (wrongAns1 == randomCorrectAns)
        wrongAns1 = getRandomNumber();
    int wrongAns2 = getRandomNumber();
    while (wrongAns2 == randomCorrectAns || wrongAns2 == wrongAns1)
        wrongAns2 = getRandomNumber();
    int wrongAns3 = getRandomNumber();
    while (wrongAns3 == randomCorrectAns || wrongAns3 == wrongAns1 || wrongAns3 == wrongAns2)
        wrongAns3 = getRandomNumber();

    std::string keyWordQuestion;
    std::string correctAns, incorrectAns1, incorrectAns2, incorrectAns3;
    std::ifstream fin(getPath());

    std::string line;
    int lineNum = 0;
    while (std::getline(fin, line))
    {
        lineNum++;
        if (lineNum == randomCorrectAns)
        {
            keyWordQuestion = getKeyWordFromText(line);
            correctAns      = get1stDefinitionFromText(line);
        }
        else if (lineNum == wrongAns1)
            incorrectAns1 = get1stDefinitionFromText(line);
        else if (lineNum == wrongAns2)
            incorrectAns2 = get1stDefinitionFromText(line);
        else if (lineNum == wrongAns3)
            incorrectAns3 = get1stDefinitionFromText(line);
    }
    fin.close();
    quiz.push_back(keyWordQuestion);
    quiz.push_back(correctAns);
    quiz.push_back(incorrectAns1);
    quiz.push_back(incorrectAns2);
    quiz.push_back(incorrectAns3);

    return quiz;
}
// void quizWith4Definitions()
// {
//     char userChoice;
//     do
//     {
//         random4Definitions();
//         std::cout << "Do you want to continue? Enter Y (or y) to continue or enter any other key to exit!" << "\n";
//         std::cout << "Your choice: ";
//         std::cin >> userChoice;
//     } while (userChoice == 'Y' || userChoice == 'y');
// }

std::string getKeyWordFromText(const std::string &line)
{
    std::string keyWord;
    int start = 0;
    int end   = line.find('#') - 1;
    keyWord   = line.substr(start, end - start + 1);
    return keyWord;
}
std::vector<std::string> Random::random4KeyWordsAnd1Def()
{
    // Random the line that contains the correct keyword and definition
    int randomCorrectAns = getRandomNumber();
    // Only get the definition of the wrong ans
    // While loop to make sure that 4 numbers are different from each other
    int wrongAns1 = getRandomNumber();
    while (wrongAns1 == randomCorrectAns)
        wrongAns1 = getRandomNumber();
    int wrongAns2 = getRandomNumber();
    while (wrongAns2 == randomCorrectAns || wrongAns2 == wrongAns1)
        wrongAns2 = getRandomNumber();
    int wrongAns3 = getRandomNumber();
    while (wrongAns3 == randomCorrectAns || wrongAns3 == wrongAns1 || wrongAns3 == wrongAns2)
        wrongAns3 = getRandomNumber();

    std::string question;
    std::string correctAns, incorrectAns1, incorrectAns2, incorrectAns3;
    std::ifstream fin(getPath());

    std::string line;
    int lineNum = 0;
    while (std::getline(fin, line))
    {
        lineNum++;
        if (lineNum == randomCorrectAns)
        {
            question   = get1stDefinitionFromText(line);
            correctAns = getKeyWordFromText(line);
        }
        else if (lineNum == wrongAns1)
            incorrectAns1 = getKeyWordFromText(line);
        else if (lineNum == wrongAns2)
            incorrectAns2 = getKeyWordFromText(line);
        else if (lineNum == wrongAns3)
            incorrectAns3 = getKeyWordFromText(line);
    }
    fin.close();
    std::vector<std::string> quiz;
    quiz.push_back(question);
    quiz.push_back(correctAns);
    quiz.push_back(incorrectAns1);
    quiz.push_back(incorrectAns2);
    quiz.push_back(incorrectAns3);

    return quiz;
}

// void quizWith4KeyWords()
// {
//     char userChoice;
//     do
//     {
//         random4KeyWords();
//         std::cout << "Do you want to continue? Enter Y (or y) to continue or enter any other key to exit!" << "\n";
//         std::cout << "Your choice: ";
//         std::cin >> userChoice;
//     } while (userChoice == 'Y' || userChoice == 'y');
// }