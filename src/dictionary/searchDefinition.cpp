#include "dictionary/searchDefinition.h"

void searchDefinition(const std::string &definitionFromUser)
{
    std::ifstream read;
    read.open("output.txt"); // engengRandom.txt
    std::string line;
    std::string def             = "";
    int numberOfShownDefinition = 0;
    int defaultShownDefinition  = 10;
    while (std::getline(read, line))
    {
        if (line.find(definitionFromUser) != std::string::npos)
        {
            // get the word and its content
            std::string keyWord = line.substr(0, line.find('#') - 1); // get the word

            int startType    = line.find('#') + 1;
            int endType      = line.find_first_of('@') - 2;
            std::string type = line.substr(startType, endType - startType + 1);

            std::cout << keyWord << " (" << type << "):"
                      << "\n";

            int index = endType + 2;
            while (index < line.length())
            {
                int nextAtPos = line.find('@', index + 1);
                if (nextAtPos == std::string::npos)
                    break;
                def   = line.substr(index + 1, nextAtPos - index - 2);
                index = nextAtPos;
                std::cout << def << "\n";
            }

            // Option for user to see more definition
            ++numberOfShownDefinition;
            if (numberOfShownDefinition == defaultShownDefinition)
            {
                std::cout << "Do you want to see more? (Y/N): ";
                char choice;
                std::cin >> choice;
                while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
                {
                    std::cout << "Invalid choice. Please enter again: ";
                    std::cin >> choice;
                }
                if (choice == 'Y' || choice == 'y')
                    defaultShownDefinition += 5;
                else
                    break;
            }
            std::cout << "\n";
        }
    }
    if (def == "")
        std::cout << "No keyword matches your definition\n";
    read.close();
}
