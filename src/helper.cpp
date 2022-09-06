#include "include/helper.h"
using namespace std;

Helper::Helper(){
    // do nothing
}

//================================================================================================================
// Helper class methods

void Helper::print_config(const std::set<std::pair<char,bool> > &config){
  // function to print out a set of char/bool pairs
    if (config.size() > 0){
        std::cout << "| ";
    }
    for (const auto &couple : config){
        // 'std::cout << boolalpha' is an option, but the preference is to leave the printing as 0 or 1
        std::cout << couple.first << ": " << couple.second << " | ";
    }
    std::cout << std::endl;
}


std::set<std::pair<char,bool> > Helper::random_subset(const std::vector<char> &vars, const int &size){
    // generate a subset of a given size
    std::set<char> subset{};
    srand(time(NULL));
    // source: https://stackoverflow.com/questions/9459035/why-does-rand-yield-the-same-sequence-of-numbers-on-every-run
    // user responder: https://stackoverflow.com/users/251860/robert-mason
    while (subset.size() < size)
    {
        int index = rand() % vars.size();
        char c = vars.at(index);
        if (subset.find(c) == subset.end())
        {
            subset.insert(c);
        }
    }

    std::set<std::pair<char,bool> > state_subset;
    srand(time(NULL));
    for (const auto &c : subset)
    {
        int random = rand();
        bool state = random % 2 == 0;
        state_subset.insert({c, state});
    }

    return state_subset;
}


std::unordered_set<std::pair<char, bool>, pairhash> Helper::make_unordered(const std::set<std::pair<char, bool> > &config){
    // converts the ordered set into an unordered set with the same elements
    std::unordered_set<std::pair<char, bool>, pairhash> unordered;
    for (const auto &pair : config){
        unordered.insert({pair.first, pair.second});
    }
    return unordered;
}


int Helper::choose(int n, int k){
    // compute and return n choose k

    if (k == 0 || k == n){
        return 1;
    }

    if (k == 1 || k == n-1){
        return n;
    }

    int result = 1;
    int i = n;
    int j = 2;
    while (i > n - k && j <= k){
        result *= i;
        if (result % j == 0){
            result /= j;
            j++;
        }
        i--;
    }

    return result;
}


template <typename T>
std::vector<std::vector<T> > Helper::subsets(const std::vector<T> &vec, int size){

    std::vector<std::vector<T> > all_subsets;

    if (size > vec.size()){
        // no ways to do that
        return all_subsets;
    }

    if (size == vec.size()){
        // only one way to do that
        all_subsets.push_back(vec);
        return all_subsets;
    } else if (size == 0){
        // only one way to do that
        std::vector<T> empty;
        all_subsets.push_back(empty);
        return all_subsets;
    }

    // all of the base cases are done now

    // TODO...

    return all_subsets;
}