#include "include/problem.h"
using namespace std;

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

bool Problem::works(const std::unordered_set<std::pair<char,bool>, pairhash> &configuration){
    for (const auto &couple : this->minimal_set){
        if (configuration.find(couple) == configuration.end()){
            // one of the required state assignments for a failure is missing
            return true;
        }
    }
    return false;
}

std::unordered_set<std::pair<char,bool>, pairhash> Problem::permute_until_break(int &guesses, std::unordered_set<std::pair<char,bool>, pairhash> &current_configuration, bool print){

    // set the one element in the configuration to its opposite, and then recursively call the rest
    for (auto &couple : current_configuration){
        std::pair<char, bool> new_couple {couple.first, !couple.second};
        current_configuration.erase(couple);
        current_configuration.insert(new_couple);
    }

}

std::unordered_set<std::pair<char,bool>, pairhash> Problem::find_first_random_break(int &guesses, bool print){
    
    // first generate a random configuration of variable settings
    std::unordered_set<std::pair<char,bool>, pairhash> current_configuration;
    for (const auto &chr : this->vars){
        current_configuration.insert({chr, rand() % 2 == 0});
    }
    guesses++;
    
    // check if this configuration results in an error
    if (!this->works(current_configuration)){
        return current_configuration;
    }

    // go through all possible states of the variables (O(2^n)) until the configuration causes an error
    return this->permute_until_break(guesses, current_configuration, print);

}

int Problem::find_minimal_error_set(bool print){
    int guesses = 0; // initialize our number of guesses

    std::unordered_set<std::pair<char,bool>, pairhash> current_configuration = this->find_first_random_break(guesses, print);


    return guesses;

}