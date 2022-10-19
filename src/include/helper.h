#ifndef Helper_h
#define Helper_h

#include<iostream>
#include<vector>
#include<set>
#include<unordered_set>
#include<ctime>
#include<cmath>

//================================================================================================================

/* This is a class which will only contain static methods that will be useful to reference */
class Helper{

public:

    /* A method to generate a random subset of a given size on a vector of characters */
    template <typename T>
    static std::set<T> random_subset(const std::vector<T> &vars, const int &size);

    /* A method to take in a set of items and return an unordered set of the same elements */
    template <typename T, typename Hasher>
    static std::unordered_set<T, Hasher> make_unordered(const std::set<T> &config);
    
    /* A method to calculate the number of possible subsets of size k there are out of a population of n different elements */
    static int choose(int n, int k);

    /* A method that, given a set of elements, returns a set of sets containing all possible subsets of the original set of a given size */
    template <typename T>
    static std::set<std::set<T> > subsets(std::set<T> &s, int size);

};

#endif