#ifndef problem_h
#define problem_h

#include "helper.h"

class Problem: public Helper
{
public:
    Problem(std::vector<char> the_vars = {'A','B','C','D','E'});
    const std::vector<char> vars; 
    std::set<std::pair<char,bool> > minimal_set; 
    std::unordered_set<std::pair<char,bool>, pairhash> unordered_min;
    const int numVars;

    bool works(const std::set<std::pair<char,bool> > &configuration);

    std::set<std::pair<char,bool> > map_to_config(std::vector<bool> states);
    void map_to_states(const std::set<std::pair<char,bool> > &config, std::vector<bool> &states);

    std::set<std::pair<char,bool> > permute_until_break(int &guesses, const std::vector<bool> &states, int start=0, bool print=false);
    std::set<std::pair<char,bool> > find_first_random_break(int &guesses, bool print=false);
    int find_minimal_error_set(bool print=false);

};

#endif