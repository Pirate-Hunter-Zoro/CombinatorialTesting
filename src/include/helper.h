#ifndef helper_h
#define helper_h

#include<iostream>
#include<vector>
#include<utility>
#include<functional>
#include<set>
#include<unordered_set>
#include<ctime>
#include<cmath>

//================================================================================================================

// The following stucture comes from this source:
// https://stackoverflow.com/questions/20590656/error-for-hash-function-of-pair-of-ints
// The stackoverflow user was: https://stackoverflow.com/users/923854/casey
struct pairhash {
public:
  template <typename T, typename U>
  std::size_t operator()(const std::pair<T, U> &x) const
  {
    return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
  }
};
// Now pairs can become hashable if we include this structure as an argument when creating an unordered_set

class Helper{

public:

    Helper();

    void print_config(const std::set<std::pair<char,bool> > &config);  

    std::set<std::pair<char,bool> > random_subset(const std::vector<char> &vars, const int &size);

    std::unordered_set<std::pair<char, bool>, pairhash> make_unordered(const std::set<std::pair<char, bool> > &config);
    
    int choose(int n, int k);

    template <typename T>
    std::vector<std::vector<T> > subsets(const std::vector<T> &vec, int size);

};

#endif