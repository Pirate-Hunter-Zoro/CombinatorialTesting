#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

class CoverageTester{

private:
    int size;
    std::unordered_set<std::string> prohibited;
    std::unordered_set<std::string> searchable;

public:
    CoverageTester(int size);

    void add_prohibited(std::string new_prohibited);
    void remove_prohibited(std::string prohibited);

    void remove_searchable(std::string searchable);
    void reset_searchable();

    int count_until_covered(int count, std::unordered_set<std::string> found, std::string start_vector);

};