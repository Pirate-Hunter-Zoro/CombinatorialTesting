#include "include/coverage.h"
#include "include/totalCoverage.h"
using namespace std;

int main()
{


//=======================================================================================================
    // testing minimal error set searcher
    Problem my_problem = Problem();
    for (const auto &chr: my_problem.vars)
        cout << chr << endl;
    cout << endl;
    for (const auto &couple: my_problem.minimal_set)
        cout << couple.first << ", " << couple.second << endl;
    cout << endl;
    int guesses = my_problem.find_minimal_error_set(true);
    cout << endl << guesses << endl;
    cout << endl << endl << endl;


//=======================================================================================================
    // testing subset finder
    set<pair<char, bool> > configuration;
    srand(time(NULL));
    for (char c : my_problem.vars){
        configuration.insert({c, rand()%2==1});
    }
    cout << endl;
    cout << "Configuration" << endl;
    my_problem.print_set(configuration);
    set<set<pair<char, bool> > > groups = my_problem.subsets(configuration, 3);
    cout << endl << "Subsets of size 3:" << endl;
    for (const set<pair<char, bool> > &config : groups)
        my_problem.print_set(config);
    cout << endl << endl << endl;

//=======================================================================================================
    // testing coverage calculator
    vector<char> these_vars{'A','B','C','D'};
    Coverage my_coverage = Coverage(these_vars);
    vector<vector<int> > settings{
                                    {0,0,0,0},
                                    {0,1,1,0},
                                    {1,0,0,1},
                                    {0,1,1,1}
                                };
    set<set<pair<char, bool> > > config_set = my_coverage.map_to_config_set(settings);
    
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
    double percentage = 100.0 * my_coverage.percentageCovered(config_set, size);
    cout << "Combinatorial Coverage for Subsets of Size " << size << ": " << percentage << "%" << endl;


//=======================================================================================================


    return 0;

}