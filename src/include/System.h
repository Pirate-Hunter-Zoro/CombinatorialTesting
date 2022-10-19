#ifndef System_h
#define System_h

#include "Helper.h"
#include "PairHash.h"

class System: public Helper
{
    /* List of characters to represent the different variables that our System has */
    const std::vector<char> vars;

    /* The minimal error set of our system, which is the smallest set of variables set to configurations that causes the "error" in our System */
    std::set<std::pair<char, bool> > minimal_set;

    /* The minimal error set of our system, except in the form of an unordered set (for quicker searching) */
    std::unordered_set<std::pair<char, bool>, PairHash> unordered_min;

    /* The total number of variables in our System, which equals vars.size() */
    const int numVars;

public:

    /* Constructor for the System, responsible for setting up the minimal error set as both an ordered and unordered set, as well as the vars and numVars members */
    System(std::vector<char> the_vars = {'A','B','C','D','E'});

    std::set<std::pair<char,bool> > assign_values(const std::set<char> &varSet);

    void print_config(const std::set<std::pair<char, bool> > &config);

    void print_set_config(const std::set<std::pair<char, bool> > &s);

    bool works(const std::set<std::pair<char,bool> > &configuration);

    std::set<std::pair<char,bool> > map_to_config(std::vector<bool> states);

    void map_to_states(const std::set<std::pair<char,bool> > &config, std::vector<bool> &states);

    std::set<std::pair<char,bool> > permute_until_break(int &guesses, const std::vector<bool> &states, int start=0, bool print=false);

    std::set<std::pair<char,bool> > find_first_random_break(int &guesses, bool print=false);

    int find_minimal_error_set(bool print=false);

};

#endif