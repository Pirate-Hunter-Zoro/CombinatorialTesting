#ifndef CoverageCalculator_h
#define CoverageCalculator_h

#include "Helper.h"

/** This class is capable of taking in a set of configurations and calculating what percentage of certain t-way faults are covered by the set of configurations */
class CoverageCalculator {

public:
    
    /** The total number of variables we want to cover t-way faults for */
    int num_vars;

    /** The list of variable names */
    std::vector<char> vars;

    /** A Helper to assist with calculations */
    Helper helper;

    /** Constructor */
    CoverageCalculator(std::vector<char> the_vars = {'A','B','C','D','E'});
    
    /** Method to calculate the percentage of size-way faults covered wiht a given covering array config_set */
    double percentageCovered(std::set<std::set<std::pair<char, bool> > > config_set, int size);

    /** Method to calculate the number of */
    int NewSubsets(std::set<std::pair<char, bool> > &config, std::unordered_set<std::string> &found, int size);

    /** Given a vector of vectors of integeres 0 or 1, map said vector into a covering array */
    std::set<std::set<std::pair<char, bool> > > map_to_config_set(const std::vector<std::vector<int> > &settings);

};

#endif