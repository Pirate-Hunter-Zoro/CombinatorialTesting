#include "include/CoverageCalculator.h"
using namespace std;

//=======================================================================================================
// Methods

/**
 * @brief Construct a new Coverage Calculator:: Coverage Calculator object
 * Initializes the helper, num_vars, and vars attributes
 * @param the_vars 
 */
CoverageCalculator::CoverageCalculator(vector<char> the_vars)
    : num_vars(the_vars.size()), vars(the_vars)
    {
        this->helper = Helper();
    }

/**
 * @brief Given a set of configurations, calculate the proportion of faults of the given size which are covered by the set
 * 
 * @param config_set 
 * @param size 
 * @return double 
 */
double CoverageCalculator::percentageCovered(set<set<pair<char, bool> > > config_set, int size){
    // given a set of configurations, determine the combinatorial coverage of this set assuming a minimal error set of size 'size'

    int total = helper.choose(this->num_vars, size) * pow(2, size);
    // total number of possible error sets of the given size

    int covered = 0;

    unordered_set<string> found;

    for (set<pair<char, bool> > config : config_set){
        covered += this->NewSubsets(config, found, size);
    }

    return 1.0 * covered / total;

}

/**
 * @brief Given a configuration, and a set of the found faults of the given size, return the number of new faults of the given size this configuration introduces
 * 
 * @param config 
 * @param found 
 * @param size 
 * @return int 
 */
int CoverageCalculator::NewSubsets(set<pair<char, bool> > &config, unordered_set<string> &found, int size){
    // given a configuration and a collection of subsets already found, how many new subsets can be found within this configuration

    int new_found = 0;
    // how many new subsets of the given size have we found with this configuration?

    // break up into all the faults that can be picked out of this configuration
    set<set<pair<char, bool> > > subsets = this->helper.subsets(config, size);

    // analyze each subset
    for (set<pair<char, bool> > subset : subsets){
        string string_rep = "";
        for (pair<char, bool> couple : subset){
            string variable = to_string(couple.first);
            string setting = to_string(couple.second);
            string_rep += variable + ":" + setting + " ";
        }
        // is this a subset we already found?
        if (found.find(string_rep) != found.end()){
            continue;
        }
        // otherwise
        found.insert(string_rep);
        new_found++;

    }

    // return the number of new subsets found
    return new_found;

}

/**
 * @brief Given a matrix of 0 or 1 integers, corresponding to variable values, map this into a covering array, or set of configurations
 * 
 * @param settings 
 * @return set<set<pair<char, bool> > > 
 */
set<set<pair<char, bool> > > CoverageCalculator::map_to_config_set(const vector<vector<int> > &settings){
    // given a matrix of settings, turn that into a set of configurations

    set<set<pair<char, bool> > > config_set;

    for (const auto &vec : settings){
        set<pair<char, bool> > config;
        for (size_t i(0); i<vec.size(); i++){
            config.insert({this->vars.at(i), vec.at(i)});
        }
        config_set.insert(config);
    }

    return config_set;

}