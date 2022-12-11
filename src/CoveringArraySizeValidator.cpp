#include "include/CoveringArraySizeValidator.h"

using namespace std;

/**
 * @brief Construct a new Covering Array Size Validator:: Covering Array Size Validator object
 * 
 * @param num_vars - the number of variables in the system
 */
CoveringArraySizeValidator::CoveringArraySizeValidator(int num_vars)
    : num_vars(num_vars){
        // given the number of variables, create out list of characters to represent the variables
        for (size_t i(0); i<num_vars; i++){
            the_vars.push_back(char(START_CHAR_VALUE+i));
        }
    }

/**
 * @brief Method to return whether it is possible to achieve total coverage of all possible t-way faults given num_vectors configurations in a covering array
 * 
 * @param num_vectors 
 * @param t 
 * @return true 
 * @return false 
 */
bool CoveringArraySizeValidator::covers(int num_vectors, int t){
    Helper helper = Helper();
    System system = System(the_vars);
    CoverageCalculator coverage_calculator = CoverageCalculator(the_vars);
    most_recent_covering_arrays.clear();
    // we need to get our hands on every possible collection of num_vectors configurations
    // first, what are all possible configurations?
    vector<vector<pair<char,bool> > > all_configs = this->allConfigs();
    set<set<pair<char, bool> > > to_sets_configs = helper.into_sets(all_configs);
    vector<vector<vector<pair<char,bool> > > > covering_arrays_of_size = helper.subvectors(all_configs, num_vectors);

    // have we achieved total coverage?
    bool covered = false;

    for (auto covering_array : covering_arrays_of_size){
        // look at every possible covering array of the given size 'num_vectors', and calculate its t-way coverage
        set<set<pair<char,bool> > > to_sets_version = helper.into_sets(covering_array);
        if (helper.AreSame(coverage_calculator.percentageCovered(to_sets_version, t), 1.0)){
            for (const auto &config : to_sets_version){
                system.print_config(config);
            }
            cout << endl;
            break;
        }
    }

    return covered;
}

/**
 * @brief Method to generate all possible configurations
 * 
 * @return vector<vector<pair<char,bool> > > 
 */
vector<vector<pair<char,bool> > > CoveringArraySizeValidator::allConfigs(){
    vector<vector<pair<char,bool> > > started;
    vector<pair<char,bool> > first_config;
    for (char c : the_vars){
        first_config.push_back({c, true});
    }
    return this->recAllConfigs(first_config, started, 0);
}

/**
 * @brief Recursive helper to generate all possible configurations
 * 
 * @param base_line - current configuration to change
 * @param started - set of configurations
 * @param explored - which variable to try flipping
 * @return vector<vector<pair<char, bool> > > 
 */
vector<vector<pair<char, bool> > > CoveringArraySizeValidator::recAllConfigs(vector<pair<char,bool> > current_config, vector<vector<pair<char, bool> > > &configs_found, int current_index)
{
    if (current_index >= the_vars.size()){
        // we're done
        configs_found.push_back(current_config);
        return configs_found;
    }
    // first, explore everything while keeping the value at current_index in current_config the same
    this->recAllConfigs(current_config, configs_found, current_index+1);

    // now, try changing the value at current_index and then do another recursive call
    pair<char, bool> altered_element; 
    pair<char, bool> current_element = current_config.at(current_index);
    altered_element.first = current_element.first;
    altered_element.second = !current_element.second; // switch from on to off
    // replace
    current_config.at(current_index) = altered_element;

    // recursive call again
    this->recAllConfigs(current_config, configs_found, current_index+1);

    // finally, return the collection of all possible configurations
    return configs_found;
}