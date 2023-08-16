#ifndef BACKEND_SEARCH_DEF_H
#define BACKEND_SEARCH_DEF_H

#include <iostream>
#include <fstream>
#include <string>

// Search exact definition that user enters
// In the future, max-heap will be used to show the most relevant definition (50% match and more will be shown in priority)
void searchDefinition(const std::string &definitionFromUser);


#endif