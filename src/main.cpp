#include "include/CoverageCalculator.h"
#include "include/CoveringArraySizeValidator.h"
using namespace std;

int main()
{


//=======================================================================================================
    // testing minimal error set searcher
    System my_system = System();
    cout << "Minimal Error Set:" << endl;
    cout << "| ";
    for (const auto &couple: my_system.minimal_set){
        cout << "| ";
        cout << couple.first << "," << couple.second;
        cout << " | ";
    }
    cout << "|";
    cout << endl << endl;
    int guesses = my_system.find_minimal_error_set(true);
    cout << endl << "Guesses: " << guesses << endl;
    cout << endl << endl << endl;


//=======================================================================================================
    // testing subset finder
    set<pair<char, bool> > configuration;
    srand(time(NULL));
    for (char c : my_system.vars){
        configuration.insert({c, rand()%2==1});
    }
    cout << endl;
    cout << "Configuration" << endl;
    my_system.print_config(configuration);
    set<set<pair<char, bool> > > groups = Helper().subsets(configuration, 3);
    cout << endl << "Subsets of size 3:" << endl;
    for (const set<pair<char, bool> > &config : groups)
        my_system.print_config(config);
    cout << endl << endl << endl;

//=======================================================================================================
    // testing coverage calculator
    vector<char> these_vars{'A','B','C','D'};
    CoverageCalculator coverage_calculator = CoverageCalculator(these_vars);
    vector<vector<int> > settings{
                                    {0,0,0,0},
                                    {0,1,1,0},
                                    {1,0,0,1},
                                    {0,1,1,1}
                                };
    set<set<pair<char, bool> > > config_set = coverage_calculator.map_to_config_set(settings);
    
    cout << "Variables:" << endl;
    for (auto ch : these_vars){
        cout << ch << " ";
    }
    cout << endl << endl;

    cout << "Configurations:" << endl;
    for (auto &vec : settings){
        for (auto setting : vec){
            cout << setting << " ";
        }
        cout << endl;
    }
    cout << endl;

    int size = 2;
    double percentage = 100.0 * coverage_calculator.percentageCovered(config_set, size);
    cout << "Combinatorial Coverage for Subsets of Size " << size << ": " << percentage << "%" << endl;
    cout << endl << endl << endl;

//=======================================================================================================

    // testing CoveringArraySizeValidator

    // first have 2 variables
    CoveringArraySizeValidator coverage_validator = CoveringArraySizeValidator(2);
    cout << "2 variables, 1 vector --> total 2-way coverage possible?" << endl;
    cout << boolalpha << coverage_validator.covers(1, 2) << endl << endl;
    cout << "2 variables, 4 vectors --> total 2-way coverage possible?" << endl;
    cout << boolalpha << coverage_validator.covers(4, 2) << endl << endl;

    // now have 4 variables
    coverage_validator = CoveringArraySizeValidator(4);
    cout << "4 variables, 6 vectors --> total 2-way coverage possible?" << endl;
    cout << boolalpha << coverage_validator.covers(6, 2) << endl << endl;
    cout << "4 variables, 5 vectors --> total 2-way coverage possible?" << endl;
    cout << boolalpha << coverage_validator.covers(5, 2) << endl << endl;
    cout << "4 variables, 4 vectors --> total 2-way coverage possible?" << endl;
    cout << boolalpha << coverage_validator.covers(4, 2) << endl << endl;
    cout << endl << endl << endl;

//=======================================================================================================

    return 0;

}