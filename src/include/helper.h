#ifndef Helper_h
#define Helper_h

#include<iostream>
#include<vector>
#include<set>
#include<unordered_set>
#include<ctime>
#include<cmath>

/* This is a class which will only contain static methods that will be useful to reference */
class Helper{

public:

    /* A method to generate a random subset of a given size on a vector of characters */
    std::set<char> random_subset(const std::vector<char> &vars, const int &size);

    /* A method to calculate the number of possible subsets of size k there are out of a population of n different elements */
    int choose(int n, int k);

    /* A method that, given a set of elements, returns a set of sets containing all possible subsets of the original set of a given size */
    std::set<std::set<std::pair<char, bool> > > subsets(std::set<std::pair<char, bool> > &s, int size);

    /* The same thing, except with vectors instead of sets */
    std::vector<std::vector<std::vector<std::pair<char, bool> > > > subvectors(std::vector<std::vector<std::pair<char, bool> > > &s, int size);

    /* A method that, given a vector of elements, returns a set consisting of the same elements */
    std::set<char> convert_to_set(const std::vector<char> &vec);

    /* Method to convert a vector of vectors into a set of sets */
    std::set<std::set<std::pair<char, bool> > > into_sets(std::vector<std::vector<std::pair<char,bool> > > vector_set);

    /* Helper method to consider if two doubles are approximately equal */
    bool AreSame(double a, double b)
    {
        return fabs(a - b) < std::numeric_limits<double>::epsilon();
    }
};

#endif