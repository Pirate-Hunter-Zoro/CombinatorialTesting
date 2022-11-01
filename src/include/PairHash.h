#ifndef PairHash_h
#define PairHash_h

#include<iostream>

// The following stucture comes from this source:
// https://stackoverflow.com/questions/20590656/error-for-hash-function-of-pair-of-ints
// The stackoverflow user was: https://stackoverflow.com/users/923854/casey
struct PairHash
{
public:
    std::size_t operator()(const std::pair<char, bool> &x) const
    {
        return std::hash<char>()(x.first) ^ std::hash<bool>()(x.second);
    }
};
// Now pairs can become hashable if we include this structure as an argument when creating an unordered_set

#endif