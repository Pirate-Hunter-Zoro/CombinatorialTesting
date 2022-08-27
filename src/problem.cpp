#include "include/problem.h"
using namespace std;

// first we will make a helper function to print a set of pairs
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

// following are methods of the Problem class

std::unordered_set<std::pair<char,bool>, pairhash> random_subset(const vector<char> &vars, const int &size)
{
    std::unordered_set<char> subset{};
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

    std::unordered_set<std::pair<char,bool>, pairhash> state_subset;
    srand(time(NULL));
    for (const auto &c : subset)
    {
        int random = rand();
        bool state = random % 2 == 0;
        state_subset.insert({c, state});
    }

    return state_subset;

}

Problem::Problem(const std::vector<char> the_vars, int size)
    : vars(the_vars), minimal_set(random_subset(the_vars, size)){}

bool Problem::works(const std::set<std::pair<char,bool> > &configuration){
    int found = 0;
    for (const auto &couple : configuration){
        if (this->minimal_set.find(couple) != this->minimal_set.end()){
            // one of the elements in the minimal set was matched
            found++;
        }
    }
    return found != this->minimal_set.size(); // because if all of the minimal_set elements were found, the configuration DOESN'T work
}

// ================================================================================================================================================
// The following methods are for the purposes of generating configurations and changing them until the minimal error set is discovered

std::set<std::pair<char,bool> > Problem::map_to_config(bool states[]){
    // given an array of booleans, match them as the states of all the variables in the class instance's configuration
    std::set<std::pair<char,bool> > config;
    for (auto chr : this->vars){
        // whatever you placed in most recently into the set is listed first, and so on...
        config.insert({chr, states[this->vars.size() - 1 - config.size()]});
    }
    return config;
}

std::set<std::pair<char,bool> > Problem::permute_until_break(int &guesses, bool states[], int start, bool print){

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
    bool new_states[len];
    for (size_t i(0); i<len; i++){
        if (i == start){
            new_states[i] = !states[i];
        } else {
            new_states[i] = states[i];
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
    
    bool states[this->vars.size()];

    // first generate a random configuration of variable settings
    std::set<std::pair<char,bool> > current_configuration;
    int size = this->vars.size();
    for (const auto &chr : this->vars){
        bool val = rand() % 2 == 0;
        current_configuration.insert({chr, val});
        states[size - 1 - current_configuration.size()] = val;
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

    std::set<std::pair<char,bool> > current_configuration = this->find_first_random_break(guesses, print);


    return guesses;

}