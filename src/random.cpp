#include "dictionary/random.h"

int getRandomNumber()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 144307); // 144307 is the number of words in the dictionary
    return dis(gen);
}

void viewRandomWord()
{
    std::ifstream fin;
    fin.open("../data/engengRandom.txt");
    int randomNum = getRandomNumber();
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
            std::cout << keyWord << "\n";
            std::cout << "Type: " << wordType << "\n";
            std::cout << "Definition: " << "\n";
            int index = atPos + 1;
            while (index < line.length())
            {
                int nextAtPos = line.find('@', index);
                if (nextAtPos == std::string::npos)
                    break;
                std::string definition = line.substr(index, nextAtPos - index);
                std::cout << definition << "\n";
                index = nextAtPos + 1;
            }
        }
    }
}

int randomInFour()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 4);
    return dis(gen);
}

std::string getDefinitionFromText(const std::string &line)
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
    fin.open("output.txt");
    std::string line;
    int lineNum = 0;
    while (std::getline(fin, line))
    {
        lineNum++;
        if (lineNum == randomCorrectAns)
        {
            int atPos = line.find('#');
            keyWordQuestion = line.substr(0, atPos - 1);
            correctAns = getDefinitionFromText(line);
        }
        else if (lineNum == wrongAns1)
            incorrectAns1 = getDefinitionFromText(line);
        else if (lineNum == wrongAns2)
            incorrectAns2 = getDefinitionFromText(line);
        else if (lineNum == wrongAns3)
            incorrectAns3 = getDefinitionFromText(line);
    }
    // Random the position of the correct answer -> more entertaining
    int positionOfCorrectAns = randomInFour();
    std::cout << "You are given the keyword: " << keyWordQuestion << std::endl;
    std::cout << "Which of the following definitions is correct?" << std::endl;
    
    // Generate the 4 answers for user to choose 
    if (positionOfCorrectAns == 1)
        std::cout << "1. " << correctAns << std::endl;
    else
        std::cout << "1. " << incorrectAns1 << std::endl;
    if (positionOfCorrectAns == 2)
        std::cout << "2. " << correctAns << std::endl;
    else
        std::cout << "2. " << incorrectAns2 << std::endl;
    if (positionOfCorrectAns == 3)
        std::cout << "3. " << correctAns << std::endl;
    else
        std::cout << "3. " << incorrectAns3 << std::endl;
    if (positionOfCorrectAns == 4)
        std::cout << "4. " << correctAns << std::endl;
    else
        std::cout << "4. " << incorrectAns1 << std::endl;

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
}
void quizWith4Definitions()
{
    char userChoice;
    do
    {
        random4Definitions();
        std::cout << "Do you want to continue? (Y/N): ";
        std::cin >> userChoice;
    } while (userChoice == 'Y' || userChoice == 'y');
}