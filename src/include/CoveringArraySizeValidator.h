#ifndef SizeCoverageCalculator_h
#define SizeCoverageCalculator_h

#include "CoverageCalculator.h"
#include "System.h"

/** This class is capable of determining if, given a certain number of configurations, it is possible to achieve total t-way coverage with that many configurations */
class CoveringArraySizeValidator{

    public:
    /** The character value for A */
    static const int START_CHAR_VALUE = 65;

    /** Reference to the most recent set of covering arrays that achieved a certain coverage */
    std::vector<std::vector<std::vector<std::pair<char,bool> > > > most_recent_covering_arrays;

    /** The number of variables this Validator is concerned with considering */
    int num_vars;

    /** The vector of */
    std::vector<char> the_vars;

    /** Constructor */
    CoveringArraySizeValidator(int num_vars);

    /** Method to determine if num_vectors configurations of a given size are sufficient to achieve total t-way coverage */
    bool covers(int num_vectors, int t);

    /** Generate every possible configuration of the variables */
    std::vector<std::vector<std::pair<char, bool> > > allConfigs();

    /** Recursive Hlper for generating all configurations */
    std::vector<std::vector<std::pair<char, bool> > > recAllConfigs(std::vector<std::pair<char,bool> > current_config, std::vector<std::vector<std::pair<char, bool> > > &configs_found, int current_index);
};

#endif