#include "dictionary/random.h"


void Random::setDictionary(Dictionary* dict)
{
    this->dictionary = dict;
}

void Random::setMode(Dictionary* dict)
{
    this->mode = dict->getDictionaryType();
}

void Random::setPath()
{
    switch(mode)
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
    int dictType = getMode();
    switch(dictType)
    {
        case 0:                     // engeng
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
            int sharpPos = line.find('#');
            int atPos = line.find_first_of('@');
            std::string keyWord = line.substr(0, sharpPos - 1);
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

int randomInFour()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 4);
    return dis(gen);
}

std::string get1stDefinitionFromText(const std::string &line)
{
    std::string definition;
    int start = line.find_first_of(':') + 2;
    int end = line.find('@', start + 1);  
    definition = line.substr(start, end - start);
    return definition;
}
void random4Definitions()
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

    std::string keyWordQuestion;
    std::string correctAns, incorrectAns1, incorrectAns2, incorrectAns3;
    std::ifstream fin;
    fin.open("../data/engengRandom.txt");
    std::string line;
    int lineNum = 0;
    while (std::getline(fin, line))
    {
        lineNum++;
        if (lineNum == randomCorrectAns)
        {
            keyWordQuestion = getKeyWordFromText(line);
            correctAns = get1stDefinitionFromText(line);
        }
        else if (lineNum == wrongAns1)
            incorrectAns1 = get1stDefinitionFromText(line);
        else if (lineNum == wrongAns2)
            incorrectAns2 = get1stDefinitionFromText(line);
        else if (lineNum == wrongAns3)
            incorrectAns3 = get1stDefinitionFromText(line);
    }
    // Random the position of the correct answer -> more entertaining
    int positionOfCorrectAns = randomInFour();
    std::cout << "You are given the keyword: " << keyWordQuestion << std::endl;
    std::cout << "Which of the following definitions is correct?" << std::endl;
    
    // Generate the 4 answers for user to choose 
    if (positionOfCorrectAns == 1)
    {
        std::cout << "1. " << correctAns << std::endl;
        std::cout << "2. " << incorrectAns1 << std::endl;
        std::cout << "3. " << incorrectAns2 << std::endl;
        std::cout << "4. " << incorrectAns3 << std::endl;
    }
    else if (positionOfCorrectAns == 2)
    {
        std::cout << "1. " << incorrectAns1 << std::endl;
        std::cout << "2. " << correctAns << std::endl;
        std::cout << "3. " << incorrectAns2 << std::endl;
        std::cout << "4. " << incorrectAns3 << std::endl;
    }
    else if (positionOfCorrectAns == 3)
    {
        std::cout << "1. " << incorrectAns1 << std::endl;
        std::cout << "2. " << incorrectAns2 << std::endl;
        std::cout << "3. " << correctAns << std::endl;
        std::cout << "4. " << incorrectAns3 << std::endl;
    }
    else
    {
        std::cout << "1. " << incorrectAns1 << std::endl;
        std::cout << "2. " << incorrectAns2 << std::endl;
        std::cout << "3. " << incorrectAns3 << std::endl;
        std::cout << "4. " << correctAns << std::endl;
    }

    std::cout << "Your answer: ";
    // User answers the question
    int userAns;
    std::cin >> userAns;
    if (userAns == positionOfCorrectAns)
        std::cout << "Correct!" << std::endl;
    else
    {
        std::cout << "Incorrect!" << std::endl;
        std::cout << "The correct answer is: " << positionOfCorrectAns << ". " << correctAns << std::endl;
    }
    fin.close();
}
void quizWith4Definitions()
{
    char userChoice;
    do
    {
        random4Definitions();
        std::cout << "Do you want to continue? Enter Y (or y) to continue or enter any other key to exit!" << "\n";
        std::cout << "Your choice: ";
        std::cin >> userChoice;
    } while (userChoice == 'Y' || userChoice == 'y');
} 

std::string getKeyWordFromText(const std::string &line)
{
    std::string keyWord;
    int start = 0;
    int end = line.find('#') - 1;
    keyWord = line.substr(start, end - start + 1);
    return keyWord;
}
void random4KeyWords()
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
    std::ifstream fin;
    fin.open("../data/engengRandom.txt");
    std::string line;
    int lineNum = 0;
    while (std::getline(fin, line))
    {
        lineNum++;
        if (lineNum == randomCorrectAns)
        {
            question = get1stDefinitionFromText(line);
            correctAns = getKeyWordFromText(line);
        }
        else if (lineNum == wrongAns1)
            incorrectAns1 = getKeyWordFromText(line);
        else if (lineNum == wrongAns2)
            incorrectAns2 = getKeyWordFromText(line);
        else if (lineNum == wrongAns3)
            incorrectAns3 = getKeyWordFromText(line);   
    }
    // Random the position of the correct answer -> more entertaining
    int positionOfCorrectAns = randomInFour();
    std::cout << "You are given the definition: " << question << std::endl;
    std::cout << "Which of the following keywords contains this definition?" << std::endl;
    
    // Generate the 4 answers for user to choose 
    if (positionOfCorrectAns == 1)
    {
        std::cout << "1. " << correctAns << std::endl;
        std::cout << "2. " << incorrectAns1 << std::endl;
        std::cout << "3. " << incorrectAns2 << std::endl;
        std::cout << "4. " << incorrectAns3 << std::endl;
    }
    else if (positionOfCorrectAns == 2)
    {
        std::cout << "1. " << incorrectAns1 << std::endl;
        std::cout << "2. " << correctAns << std::endl;
        std::cout << "3. " << incorrectAns2 << std::endl;
        std::cout << "4. " << incorrectAns3 << std::endl;
    }
    else if (positionOfCorrectAns == 3)
    {
        std::cout << "1. " << incorrectAns1 << std::endl;
        std::cout << "2. " << incorrectAns2 << std::endl;
        std::cout << "3. " << correctAns << std::endl;
        std::cout << "4. " << incorrectAns3 << std::endl;
    }
    else
    {
        std::cout << "1. " << incorrectAns1 << std::endl;
        std::cout << "2. " << incorrectAns2 << std::endl;
        std::cout << "3. " << incorrectAns3 << std::endl;
        std::cout << "4. " << correctAns << std::endl;
    }

    std::cout << "Your answer: ";
    // User answers the question
    int userAns;
    std::cin >> userAns;
    if (userAns == positionOfCorrectAns)
        std::cout << "Correct!" << std::endl;
    else
    {
        std::cout << "Incorrect!" << std::endl;
        std::cout << "The correct answer is: " << positionOfCorrectAns << ". " << correctAns << std::endl;
    }
    fin.close();
}

void quizWith4KeyWords()
{
    char userChoice;
    do
    {
        random4KeyWords();
        std::cout << "Do you want to continue? Enter Y (or y) to continue or enter any other key to exit!" << "\n";
        std::cout << "Your choice: ";
        std::cin >> userChoice;
    } while (userChoice == 'Y' || userChoice == 'y');
}