#include "include/problem.h"
using namespace std;

//================================================================================================================
// helper functions

template <typename T1, typename T2>
void print_config(const std::set<std::pair<T1,T2> > &config){
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

std::set<std::pair<char,bool> > random_subset(const vector<char> &vars, const int &size){
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

std::unordered_set<pair<char, bool>, pairhash> make_unordered(const std::set<pair<char, bool> > &config){
    // converts the ordered set into an unordered set with the same elements
    std::unordered_set<pair<char, bool>, pairhash> unordered;
    for (const auto &pair : config){
        unordered.insert({pair.first, pair.second});
    }
    return unordered;
}

int choose(int n, int k){
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

//================================================================================================================
// following are methods of the Problem class

Problem::Problem(const std::vector<char> the_vars)
    : vars(the_vars), numVars(the_vars.size()){
        srand(time(NULL));
        minimal_set = random_subset(the_vars, rand() % the_vars.size());
        unordered_min = make_unordered(minimal_set);
    }

bool Problem::works(const std::set<std::pair<char,bool> > &configuration){
    int found = 0;
    for (const auto &couple : configuration){
        if (this->unordered_min.find(couple) != this->unordered_min.end()){
            // one of the elements in the minimal set was matched
            found++;
        }
    }
    return found != this->minimal_set.size(); // because if all of the minimal_set elements were found, the configuration DOESN'T work
}

// ================================================================================================================================================
// The following methods are for the purposes of generating configurations and changing them until the minimal error set is discovered

std::set<std::pair<char,bool> > Problem::map_to_config(vector<bool> states){
    // given an array of booleans, match them as the states of all the variables in the class instance's configuration
    std::set<std::pair<char,bool> > config;
    for (auto chr : this->vars){
        config.insert({chr, states.at(config.size())});
    }
    return config;
}

void Problem::map_to_states(const std::set<std::pair<char,bool> > &config, vector<bool> &states){
    // given a configuration, simply return an array of the respective boolean values for on or off
    for (const auto &couple : config){
        states.push_back(couple.second);
    }
}

std::set<std::pair<char,bool> > Problem::permute_until_break(int &guesses, const vector<bool> &states, int start, bool print){

    std::set<std::pair<char,bool> > config = this->map_to_config(states);

    if (print){
        print_config(config);
    }

    int len = this->vars.size();

    if (!this->works(config)){
        return config;
    }

    if (start >= len){
        std::set<std::pair<char,bool> > empty;
        return empty;
    }

    // change the first state, then recursively call the rest
    vector<bool> new_states;
    for (size_t i(0); i<len; i++){
        if (i == start){
            new_states.push_back(!states.at(i));
        } else {
            new_states.push_back(states.at(i));
        }
    }
    guesses++;
    std::set<std::pair<char,bool> > potential1 = this->permute_until_break(guesses, new_states, start+1, print);
    if (potential1.size() > 0){ // eventually produced a set that contains the error set
        return potential1;
    }

    // leave the first as is, then recursively call the rest
    guesses++;
    return this->permute_until_break(guesses, states, start+1, print);

}

std::set<std::pair<char,bool> > Problem::find_first_random_break(int &guesses, bool print){
    
    vector<bool> states;

    // first generate a random configuration of variable settings
    std::set<std::pair<char,bool> > current_configuration;
    for (const auto &chr : this->vars){
        bool val = rand() % 2 == 0;
        current_configuration.insert({chr, val});
        states.push_back(val);
    }
    guesses++;
    
    // check if this configuration results in an error
    if (!this->works(current_configuration)){
        if (print){
            print_config(current_configuration);
        }
        return current_configuration;
    }

    // go through all possible states of the variables (O(2^n)) until the configuration causes an error
    return this->permute_until_break(guesses, states, 0, print);

}

int Problem::find_minimal_error_set(bool print){
    int guesses = 0; // initialize our number of guesses

    // brute force find the first instance of failure
    std::set<std::pair<char,bool> > current_configuration = this->find_first_random_break(guesses, print);

    if (print){
        cout << endl;
    }

    // obtain an array of the boolean values for on/off
    vector<bool> states; 
    this->map_to_states(current_configuration, states);

    std::set<std::pair<char, bool> > new_config;
    for (size_t index(0); index < this->vars.size(); index++){
        states.at(index) = !states.at(index);
        new_config = this->map_to_config(states);
        guesses++;
        if (print){
            print_config(new_config);
        }
        if (!this->works(new_config)){
            // pair was not important for the error set
            if (print){
                cout << "Erasing: " << this->vars.at(index) << ", " << !states.at(index) << endl;
            }
            pair<char, bool> this_pair {this->vars.at(index), !states.at(index)};
            current_configuration.erase(this_pair);
            // search for what the pair was originally to remove it
        } else {
            // pair WAS important for the error set
            states.at(index) = !states.at(index);
            // switch back
        }
    }

    if (print){
        cout << "\nMinimal Error Set:" << endl;
        print_config(current_configuration);
    }

    return guesses;

}

double Problem::percentageCovered(const std::vector<std::vector<std::pair<char, bool> > > &state_vectors, int size){
    // given a set of configurations, determine the combinatorial coverage of this set assuming a minimal error set of size 'size'

    int total = choose(this->numVars, size) * pow(2, size);
    // total number of possible error sets of the given size

    int covered = 0;

    unordered_set<string> found;

    for (const vector<pair<char, bool> > &config : state_vectors){
        covered += this->recSubsets(config, found, size, 0);
    }

    return 1.0 * covered / total;

}

int Problem::recSubsets(const std::vector<std::pair<char, bool> > &config, std::unordered_set<std::string> &found, int size, int start){

    return 0;

}