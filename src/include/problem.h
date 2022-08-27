#ifndef problem_h
#define problem_h

#include<iostream>
#include<vector>
#include<utility>
#include<functional>
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
    Problem(std::vector<char> the_vars = {'A','B','C','D','E'}, int size = 3);
    const std::vector<char> vars; 
    std::unordered_set<std::pair<char,bool>, pairhash> minimal_set; 
    bool works(const std::unordered_set<std::pair<char,bool>, pairhash> &configuration);
    std::unordered_set<std::pair<char,bool>, pairhash> map_to_config(bool states[]);
    std::unordered_set<std::pair<char,bool>, pairhash> permute_until_break(int &guesses, std::unordered_set<std::pair<char,bool>, pairhash> &current_configuration, bool print=false);
    std::unordered_set<std::pair<char,bool>, pairhash> find_first_random_break(int &guesses, bool print=false);
    int find_minimal_error_set(bool print=false);
};

#endif