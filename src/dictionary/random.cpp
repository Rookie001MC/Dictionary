#include "dictionary/random.h"

void Random::setDictionary(Dictionary *dict)
{
    this->dictionary = dict;
}

Dictionary *Random::getDictionary()
{
    return this->dictionary;
}
void Random::setPath()
{
    int mode = dictionary->getDictionaryType();
    switch (mode)
    {
        case 0:
            path = "../data/engengRandom.txt";
            break;
        case 1:
            path = "../data/engvieRandom.txt";
            break;
        case 2:
            path = "../data/vieengRandom.txt";
            break;
        case 3:
            path = "../data/emojiRandom.txt";
            break;
        case 4:
            path = "../data/slangRandom.txt";
            break;
    }
}

std::string Random::getPath()
{
    return this->path;
}
int Random::getRandomNumber()
{
    int totalWords = 0;
    int dictType   = dictionary->getDictionaryType();
    switch (dictType)
    {
        case 0: // engeng
            totalWords = 144307;
            break;
        case 1: // engvie
            totalWords = 58099;
            break;
        case 2: // vieeng
            totalWords = 23467;
            break;
        case 3: // emoji
            totalWords = 678;
            break;
        case 4:
            totalWords = 7635;
            break;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, totalWords);
    return dis(gen);
}

std::string get1stDefinitionFromText(const std::string &line)
{
    std::string definition;
    int start  = line.find_first_of('@') + 2;
    int end    = line.find('@', start + 1) - 2;
    definition = line.substr(start, end - start + 1);
    return definition;
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

int Random::randomFourAnswer()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 4);
    return dis(gen);
}

std::vector<std::string> Random::guessDefinition()
{
    std::vector<std::string> quiz;
    // Random the line that contains the correct keyword and definition
    int randomKeyWord = getRandomNumber();
    randomChoice      = randomFourAnswer();
    // Only get the definition of the wrong ans
    // While loop to make sure that 4 numbers are different from each other
    int ans1 = getRandomNumber();
    while (ans1 == randomKeyWord)
        ans1 = getRandomNumber();
    int ans2 = getRandomNumber();
    while (ans2 == randomKeyWord || ans2 == ans1)
        ans2 = getRandomNumber();
    int ans3 = getRandomNumber();
    while (ans3 == randomKeyWord || ans3 == ans1 || ans3 == ans2)
        ans3 = getRandomNumber();

    std::string keyWordQuestion;
    std::string correctAns, incorrectAns1, incorrectAns2, incorrectAns3;
    std::ifstream fin(getPath());

    std::string line;
    int lineNum = 0;
    while (std::getline(fin, line))
    {
        lineNum++;
        if (lineNum == randomKeyWord)
        {
            keyWordQuestion = getKeyWordFromText(line);
            if (getDictionary()->getDictionaryType() == 0) // for engeng dictionary
            {
                int start  = line.find_first_of(':') + 2;
                int end    = line.find('@', start + 1) - 3;
                correctAns = line.substr(start, end - start + 1);
            }
            else
            {
                correctAns = get1stDefinitionFromText(line);
            }
        }
        else if (lineNum == ans1)
        {
            if (getDictionary()->getDictionaryType() == 0) // for engeng dictionary
            {
                int start     = line.find_first_of(':') + 2;
                int end       = line.find('@', start + 1) - 3;
                incorrectAns1 = line.substr(start, end - start + 1);
            }
            else
                incorrectAns1 = get1stDefinitionFromText(line);
        }
        else if (lineNum == ans2)
        {
            if (getDictionary()->getDictionaryType() == 0) // for engeng dictionary
            {
                int start     = line.find_first_of(':') + 2;
                int end       = line.find('@', start + 1) - 3;
                incorrectAns2 = line.substr(start, end - start + 1);
            }
            else
                incorrectAns2 = get1stDefinitionFromText(line);
        }
        else if (lineNum == ans3)
        {
            if (getDictionary()->getDictionaryType() == 0) // for engeng dictionary
            {
                int start     = line.find_first_of(':') + 2;
                int end       = line.find('@', start + 1) - 3;
                incorrectAns3 = line.substr(start, end - start + 1);
            }
            else
                incorrectAns3 = get1stDefinitionFromText(line);
        }
    }
    fin.close();
    quiz.push_back(keyWordQuestion);
    quiz.push_back(correctAns);
    quiz.push_back(incorrectAns1);
    quiz.push_back(incorrectAns2);
    quiz.push_back(incorrectAns3);

    std::swap(quiz[1], quiz[randomChoice]);

    return quiz;
}

std::string getKeyWordFromText(const std::string &line)
{
    std::string keyWord;
    int start = 0;
    int end   = line.find('#') - 1;
    keyWord   = line.substr(start, end - start + 1);
    return keyWord;
}
std::vector<std::string> Random::guessKeyWord()
{
    // Random the line that contains the correct keyword and definition
    int randomDef = getRandomNumber();
    randomChoice  = randomFourAnswer();
    // Only get the definition of the wrong ans
    // While loop to make sure that 4 numbers are different from each other
    int ans1 = getRandomNumber();
    while (ans1 == randomDef)
        ans1 = getRandomNumber();
    int ans2 = getRandomNumber();
    while (ans2 == randomDef || ans2 == ans1)
        ans2 = getRandomNumber();
    int ans3 = getRandomNumber();
    while (ans3 == randomDef || ans3 == ans1 || ans3 == ans2)
        ans3 = getRandomNumber();

    std::string question;
    std::string correctAns, incorrectAns1, incorrectAns2, incorrectAns3;
    std::ifstream fin(getPath());

    std::string line;
    int lineNum = 0;
    while (std::getline(fin, line))
    {
        lineNum++;
        if (lineNum == randomDef)
        {
            correctAns = getKeyWordFromText(line);
            if (getDictionary()->getDictionaryType() == 0) // for engeng dictionary
            {
                int start  = line.find_first_of(':') + 2;
                int end    = line.find('@', start + 1) - 3;
                question = line.substr(start, end - start + 1);
            }
            else
                question = get1stDefinitionFromText(line);
        }
        else if (lineNum == ans1)
            incorrectAns1 = getKeyWordFromText(line);
        else if (lineNum == ans2)
            incorrectAns2 = getKeyWordFromText(line);
        else if (lineNum == ans3)
            incorrectAns3 = getKeyWordFromText(line);
    }
    fin.close();
    std::vector<std::string> quiz;
    quiz.push_back(question);
    quiz.push_back(correctAns);
    quiz.push_back(incorrectAns1);
    quiz.push_back(incorrectAns2);
    quiz.push_back(incorrectAns3);

    std::swap(quiz[1], quiz[randomChoice]);

    return quiz;
}

int Random::getChoice()
{
    return randomChoice;
}
