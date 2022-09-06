#include "include/coverage.h"
using namespace std;

//=======================================================================================================
// Methods

Coverage::Coverage(std::vector<char> the_vars)
    : Problem(the_vars)
    {}

double Coverage::percentageCovered(int size){
    // given a set of configurations, determine the combinatorial coverage of this set assuming a minimal error set of size 'size'

    int total = choose(this->numVars, size) * pow(2, size);
    // total number of possible error sets of the given size

    int covered = 0;

    unordered_set<string> found;

    for (const vector<pair<char, bool> > &config : this->state_vectors){
        covered += this->recSubsets(config, found, size, 0);
    }

    return 1.0 * covered / total;

}

int Coverage::recSubsets(const std::vector<std::pair<char, bool> > &config, std::unordered_set<std::string> &found, int size, int start){

    return 0;

}