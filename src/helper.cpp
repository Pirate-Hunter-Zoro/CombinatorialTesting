#include "include/Helper.h"
using namespace std;

// Helper class methods

/**
 * @brief Given a generic vector, generate and return random subset of the elements, choosing as many elements as specified with size
 * 
 * @param vars 
 * @param size 
 * @return set<pair<char,bool> > 
 */
set<char> Helper::random_subset(const vector<char> &vars, const int &size){
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

    return subset;
}

/**
 * @brief Classic combinatorics - simply return the number of ways to choose k objects out of n total objects
 * 
 * @param n 
 * @param k 
 * @return int 
 */
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

/**
 * @brief Given a generic set, return a set of all the possible subsets of a given size of this set
 * 
 * @param s 
 * @param size 
 * @return set<set<pair<char, bool> > 
 */
set<set<pair<char, bool> > > Helper::subsets(set<pair<char,bool> > &s, int size)
{
    // this method WILL modify the configuration for the purposes of not having to make a bunch of copies
    // if this is not preferred, remove the '&' in front of the 's' here and in the Helper.h file

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
        set<set<pair<char, bool> > > lastSubsets = Helper::subsets(copy, size-1);
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

/**
 * @brief Given a vector of vectors, return a vector of all the possible subvectors of a given size of this vector of vectors
 *
 * @param s
 * @param size
 * @return std::vector<std::vector<std::vector<char, bool> > >
 */
std::vector<std::vector<std::vector<std::pair<char, bool> > > > Helper::subvectors(std::vector<std::vector<std::pair<char, bool> > > &s, int size){
    vector<vector<vector<pair<char, bool> > > > all_subvectors;

    if (size > s.size())
    {
        // no ways to do that
        return all_subvectors;
    }

    if (size == s.size())
    {
        // only one way to do that
        all_subvectors.push_back(s);
        return all_subvectors;
    }
    else if (size == 0)
    {
        // only one way to do that
        vector<vector<pair<char, bool> > > empty;
        all_subvectors.push_back(empty);
        return all_subvectors;
    }

    // all of the base cases are done now

    while (s.size() > size)
    {
        // take out the first element and find all subsets of size-1 remaining
        // then tack on this first element
        // i.e. one iteration of this while loop finds all possible subsets of the given size where the first element MUST be included
        vector<pair<char, bool> > first = *s.begin();
        s.erase(s.begin());
        vector<vector<pair<char, bool> > > copy = s;
        vector<vector<vector<pair<char, bool> > > > lastSubvectors = this->subvectors(copy, size - 1);
        for (auto subvector : lastSubvectors)
        {
            // I would copy by address but for some reason each subset is 'const' and I cannot figure out how to change that...
            subvector.insert(subvector.begin(), first);
            all_subvectors.push_back(subvector);
        }
    }

    // now that vec.size() == size, one possible subset of size 'size' IS s
    all_subvectors.push_back(s);

    return all_subvectors;
}

/**
 * @brief Method to convert a generic vector into a set with the same elements
 * 
 * @tparam char
 * @param vec 
 * @return set<char> 
 */
set<char> Helper::convert_to_set(const vector<char> &vec){
    set<char> the_set;
    for (const auto item : vec)
        the_set.insert(item);
    return the_set;
}

/**
 * @brief Method to convert from vector of vectors into set of sets
 * 
 * @return set<set<pair<char, bool> > > 
 */
set<set<pair<char, bool> > > Helper::into_sets(vector<vector<pair<char, bool> > > vector_set){
    set<set<pair<char,bool> > > set_of_sets;
    for (vector<pair<char,bool> > &vec : vector_set){
        set<pair<char,bool> > set_version;
        for (pair<char,bool> couple : vec){
            set_version.insert(couple);
        }
        set_of_sets.insert(set_version);
    }

    return set_of_sets;
}