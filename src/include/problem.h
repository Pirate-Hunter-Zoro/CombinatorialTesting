#ifndef problem_h
#define problem_h

#include<iostream>
#include<vector>
#include<utility>
#include<functional>
#include<set>
#include<unordered_set>
#include<ctime>

// The following stucture comes from the following source:
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

class Problem
{
public:
    Problem(std::vector<char> the_vars = {'A','B','C','D','E'});
    const std::vector<char> vars; 
    std::set<std::pair<char,bool> > minimal_set; 
    std::unordered_set<std::pair<char,bool>, pairhash> unordered_min;

    bool works(const std::set<std::pair<char,bool> > &configuration);

    std::set<std::pair<char,bool> > map_to_config(std::vector<bool> states);
    void map_to_states(const std::set<std::pair<char,bool> > &config, std::vector<bool> &states);

    std::set<std::pair<char,bool> > permute_until_break(int &guesses, const std::vector<bool> &states, int start=0, bool print=false);
    std::set<std::pair<char,bool> > find_first_random_break(int &guesses, bool print=false);
    int find_minimal_error_set(bool print=false);
};

#endif