#ifndef coverage_h
#define coverage_h

#include "problem.h"

class Coverage: public Problem{

    std::vector<std::vector<std::pair<char, bool> > > state_vectors;

public:
    Coverage(std::vector<char> the_vars = {'A','B','C','D','E'});
    double percentageCovered(int size);
    int recSubsets(const std::vector<std::pair<char, bool> > &config, std::unordered_set<std::string> &found, int size, int start);

};

#endif