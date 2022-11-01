#include "include/System.h"
using namespace std;

//================================================================================================================
// following are methods of the System class 

/**
 * @brief Construct a new System:: System object
 * 
 * @param the_vars - a vector of characters to describe the variables
 */
System::System(const vector<char> the_vars)
    : vars(the_vars), numVars(the_vars.size()){
        // initialize the helper
        helper = Helper();
        srand(time(NULL));
        // generate a random subset of the variables to make up the minimal error set, and randomly set each value to on or off for the configuration
        minimal_set = this->assign_values(helper.random_subset(the_vars, rand() % the_vars.size()));
        // create an unordered version for faster searching
        unordered_min = helper.make_unordered(minimal_set);
    }

/**
 * @brief Given an input configuration, does it contain the minimal error set? If so, the system DOES NOT work
 * 
 * @param configuration 
 * @return true 
 * @return false 
 */
bool System::works(const set<pair<char,bool> > &configuration){
    int found = 0;
    for (const auto &couple : configuration){
        if (this->unordered_min.find(couple) != this->unordered_min.end()){
            // one of the elements in the minimal set was matched
            found++;
        }
    }
    return found != this->minimal_set.size(); // because if all of the minimal_set elements were found, the configuration DOESN'T work
}

/**
 * @brief A simple helper method to print out a configuration
 * 
 * @param config 
 */
void System::print_config(const set<pair<char, bool> > &config)
{
    // function to print out a set of char/bool pairs
    if (config.size() > 0)
    {
        cout << "|";
    }
    for (const auto &couple : config)
    {
        // 'cout << boolalpha' is an option, but the preference is to leave the printing as 0 or 1
        cout << " " << couple.first << ":" << couple.second << " |";
    }
    cout << endl;
}

/**
 * @brief Given a set of variables/characters, randomly assign each an on/off value
 * 
 * @param varSet 
 * @return set<pair<char,bool> > 
 */
set<pair<char,bool> > System::assign_values(const set<char> &varSet){
    set<pair<char,bool> > configuration;

    for (const auto &chr : varSet)
    {
        bool val = rand() % 2 == 0;
        configuration.insert({chr, val});
    }

    return configuration;
}

// ================================================================================================================================================
// the following are methods that dance between vectors of booleans to configurations, as well as vectors and sets and unordered sets

/**
 * @brief given an array of booleans, match them as the states of all the variables in the System instance's configuration
 *
 * @param states
 * @return set<pair<char,bool> >
 */
set<pair<char,bool> > System::map_to_config(vector<bool> states){
    set<pair<char,bool> > config;
    for (auto chr : this->vars){
        // config.size() is increasing
        config.insert({chr, states.at(config.size())});
    }
    return config;
}

/**
 * @brief given a configuration, simply return a vector of the respective boolean values for on or off
 *
 * @param config - a set of char/bool pairs
 * @return vector<bool>
 */
vector<bool> System::map_to_states(const set<pair<char,bool> > &config){
    vector<bool> states;
    for (const auto &couple : config){
        states.push_back(couple.second);
    }
    return states;
}

// ================================================================================================================================================
// The following methods are for the purposes of generating configurations and changing them until the minimal error set is discovered

/**
 * @brief recursive helper method to systematically change the configuration of a System until it breaks
 * 
 * @param guesses - integer
 * @param states - a vector of booleans
 * @param start - the boolean position at which we try changing or not changing before a recursive call
 * @param print - boolean
 * @return set<pair<char,bool> > 
 */
set<pair<char,bool> > System::permute_until_break(int &guesses, const vector<bool> &states, int start, bool print){
    // map the boolean vector into a configuration
    set<pair<char,bool> > config = this->map_to_config(states);

    // print if specified
    if (print){
        this->print_config(config);
    }

    // base case
    if (!this->works(config)){
        return config;
    }

    // another base case - the end index was passed before a break occured, so this recursive path did not find the minimal error set
    int len = this->vars.size();
    if (start >= len){
        set<pair<char,bool> > empty;
        return empty;
        // the later recursion knows that if an empty set is returned, a configuration containing the minimal error set was not found
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
    set<pair<char,bool> > potential1 = this->permute_until_break(guesses, new_states, start+1, print);
    if (potential1.size() > 0){ // eventually produced a set that contains the error set
        return potential1;
    }

    // leave the first as is, then recursively call the rest
    guesses++;
    return this->permute_until_break(guesses, states, start+1, print);

}

/**
 * @brief 
 * 
 * @param guesses 
 * @param print 
 * @return set<pair<char,bool> > 
 */
set<pair<char,bool> > System::find_first_random_break(int &guesses, bool print){

    // first generate a random configuration of variable settings
    set<pair<char,bool> > current_configuration = this->assign_values(helper.convert_to_set(this->vars));
    guesses++;

    // get ahold of the on/off values of our variables as a vector of booleans
    vector<bool> states = this->map_to_states(current_configuration);
    
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

/**
 * @brief Method to brute force systematically find the minimal error set of a System
 * 
 * @param print 
 * @return int - how many guesses it took to pinpoint the minimal error set
 */
int System::find_minimal_error_set(bool print){
    int guesses = 0; // initialize our number of guesses

    // brute force find the first instance of failure
    set<pair<char,bool> > current_configuration = this->find_first_random_break(guesses, print);

    // if we are printing, this line is to separate the first break discovery from the trimming down to the minimal error set
    if (print){
        cout << endl;
    }

    // obtain an array of the boolean values for on/off
    vector<bool> states = this->map_to_states(current_configuration);

    // now switch each configuration variable, and see if that switch causes the System to function, meaning that the variable was a member of the minimal error set
    for (size_t index(0); index < this->vars.size(); index++){
        // switch the variable
        states.at(index) = !states.at(index);
        set<pair<char, bool> > new_config = this->map_to_config(states);
        guesses++;

        // print if we are printing
        if (print){
            print_config(new_config);
        }

        // check if the System works after the change
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

    // if we are printing, report the minimal error set
    if (print){
        cout << "\nMinimal Error Set:" << endl;
        this->print_config(current_configuration);
    }

    // return the number of guesses it took to pinpoint the minimal error set
    return guesses;

}