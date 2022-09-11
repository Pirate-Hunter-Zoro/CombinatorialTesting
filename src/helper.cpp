#include "include/helper.h"
using namespace std;

Helper::Helper(){
    // do nothing
}

//================================================================================================================
// Helper class methods

void Helper::print_config(const set<pair<char,bool> > &config){
  // function to print out a set of char/bool pairs
    if (config.size() > 0){
        cout << "| ";
    }
    for (const auto &couple : config){
        // 'cout << boolalpha' is an option, but the preference is to leave the printing as 0 or 1
        cout << couple.first << ": " << couple.second << " | ";
    }
    cout << endl;
}


set<pair<char,bool> > Helper::random_subset(const vector<char> &vars, const int &size){
    // generate a subset of a given size
    set<char> subset{};
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

    set<pair<char,bool> > state_subset;
    srand(time(NULL));
    for (const auto &c : subset)
    {
        int random = rand();
        bool state = random % 2 == 0;
        state_subset.insert({c, state});
    }

    return state_subset;
}


unordered_set<pair<char, bool>, pairhash> Helper::make_unordered(const set<pair<char, bool> > &config){
    // converts the ordered set into an unordered set with the same elements
    unordered_set<pair<char, bool>, pairhash> unordered;
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
    int j = k;
    while (i > n - k && j > 0){
        result *= i;
        if (result % j == 0){
            result /= j;
            j--;
        }
        i--;
    }

    return result;
}


set<set<pair<char, bool> > > Helper::subsets(set<pair<char, bool> > &s, int size){
    // this method WILL modify the configuration for the purposes of not having to make a bunch of copies
    // if this is not preferred, remove the '&' in front of the 's'

    set<set<pair<char, bool> > > all_subsets;

    if (size > s.size()){
        // no ways to do that
        return all_subsets;
    }

    if (size == s.size()){
        // only one way to do that
        all_subsets.insert(s);
        return all_subsets;
    } else if (size == 0){
        // only one way to do that
        set<pair<char, bool> > empty;
        all_subsets.insert(empty);
        return all_subsets;
    }

    // all of the base cases are done now

    while (s.size() > size){
        // take out the first element and find all subsets of size-1 remaining
        // then tack on this first element
        // i.e. one iteration of this while loop finds all possible subsets of the given size where the first element MUST be included
        pair<char, bool> first = *s.begin();
        s.erase(s.begin());
        set<pair<char, bool> > copy = s;
        set<set<pair<char, bool> > > lastSubsets = this->subsets(copy, size-1);
        for (auto subset : lastSubsets){
            // I would copy by address but for some reason each subset is 'const' and I cannot figure out how to change that...
            subset.insert(first);
            all_subsets.insert(subset);
        }
    }

    // now that vec.size() == size
    all_subsets.insert(s);

    return all_subsets;
}

void Helper::print_set(const set<pair<char, bool> > &s){
    for (const auto &i : s){
        cout << i.first << ":" << i.second << " ";
    }
    cout << endl;
}