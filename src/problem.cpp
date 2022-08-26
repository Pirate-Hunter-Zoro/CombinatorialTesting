#include "include/problem.h"
using namespace std;

std::unordered_set<std::pair<char,bool>, pairhash> random_subset(const vector<char> &vars, const int &size)
{
    std::unordered_set<char> subset{};
    srand(time(NULL));
    while (subset.size() < size)
    {
        int index = rand() % vars.size();
        char c = vars.at(index);
        if (subset.find(c) == subset.end())
        {
            subset.insert(c);
        }
    }

    std::unordered_set<std::pair<char,bool>, pairhash> state_subset;
    srand(time(NULL));
    for (const auto &c : subset)
    {
        int random = rand();
        bool state = random % 2 == 0;
        state_subset.insert({c, state});
    }

    return state_subset;

}

Problem::Problem(const std::vector<char> the_vars, int size)
    : vars(the_vars), minimal_set(random_subset(the_vars, size)){}