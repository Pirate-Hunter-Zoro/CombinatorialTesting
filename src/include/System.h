#ifndef System_h
#define System_h

#include "Helper.h"

/** This is simply an object with a (secretly) known minimal error set that is causing a "problem", and has helper methods to simulate finding the minimal error set */
class System: public Helper
{
public:

    /* List of characters to represent the different variables that our System has */
    const std::vector<char> vars;

    /* The minimal error set of our system, which is the smallest set of variables set to configurations that causes the "error" in our System */
    std::set<std::pair<char, bool> > minimal_set;

    /* The total number of variables in our System, which equals vars.size() */
    const int numVars;

    /* A Helper object to help with producing some calculations */
    Helper helper;



    /* Constructor for the System, responsible for setting up the minimal error set as both an ordered and unordered set, as well as the vars and numVars members */
    System(std::vector<char> the_vars = {'A','B','C','D','E'});



    /* Given a set of characters (representing variables), assign them on/off values to create a configuration */
    std::set<std::pair<char,bool> > assign_values(const std::set<char> &varSet);

    /* Given a configuration of variables set to certain values, print it */
    void print_config(const std::set<std::pair<char, bool> > &config);

    /* Given an input configuration of variables set to certain values, see if it generates and error in the system */
    bool works(const std::set<std::pair<char,bool> > &configuration);



    /* Given a vector of booleans, map those on/off booleans to the variables of the System to generate a configuration */
    std::set<std::pair<char,bool> > map_to_config(std::vector<bool> states);

    /* Given a configuration, simply return a vector of the boolean values */
    std::vector<bool> map_to_states(const std::set<std::pair<char,bool> > &config);



    /* Recursive helper method to systematically brute force change the variable settings in a configuration until the System's minimal error set is contained */
    std::set<std::pair<char,bool> > permute_until_break(int &guesses, const std::vector<bool> &states, int start=0, bool print=false);

    /* Wrapper method to call permute_until_break */
    std::set<std::pair<char,bool> > find_first_random_break(int &guesses, bool print=false);

    /* Method which calls find_first_random_break and then peels down the configuration to the System's minimal error set */
    int find_minimal_error_set(bool print=false);

};

#endif