#include <fstream>
#include <string>
#include <vector>

// class used for history and favorite feature due to their similarities
class History
{
  private:
    std::string path;
    std::vector<std::string> storage;
    int search(std::vector<std::string> vct, std::string key);

  public:
    History(std::string);
    ~History();
    std::vector<std::string> get();
    void add(std::string key);    // add to memory but does not modify the file
    void remove(std::string key); // remove from memory but does not modify the file
    void save();                  // modify the file
};