#ifndef Coverage_h
#define Coverage_h

#include "System.h"

class Coverage: public System{

public:
    Coverage(std::vector<char> the_vars = {'A','B','C','D','E'});
    
    double percentageCovered(std::set<std::set<std::pair<char, bool> > > config_set, int size);
    int Subsets(std::set<std::pair<char, bool> > &config, std::unordered_set<std::string> &found, int size, int start);
    std::set<std::set<std::pair<char, bool> > > map_to_config_set(const std::vector<std::vector<int> > &settings);

};

#endif