#include "include/coverage.h"
using namespace std;

//=======================================================================================================
// Methods

Coverage::Coverage(vector<char> the_vars)
    : System(the_vars)
    {

    }

double Coverage::percentageCovered(set<set<pair<char, bool> > > config_set, int size){
    // given a set of configurations, determine the combinatorial coverage of this set assuming a minimal error set of size 'size'

    int total = choose(this->numVars, size) * pow(2, size);
    // total number of possible error sets of the given size

    int covered = 0;

    unordered_set<string> found;

    for (set<pair<char, bool> > config : config_set){
        covered += this->Subsets(config, found, size, 0);
    }

    return 1.0 * covered / total;

}

int Coverage::Subsets(set<pair<char, bool> > &config, unordered_set<string> &found, int size, int start){
    // given a configuration and a collection of subsets already found, how many new subsets can be found within this configuration

    int new_found = 0;
    // how many new subsets of the given size have we found with this configuration?

    set<set<pair<char, bool> > > subsets = this->subsets(config, size);
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

    return new_found;

}

set<set<pair<char, bool> > > Coverage::map_to_config_set(const vector<vector<int> > &settings){
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