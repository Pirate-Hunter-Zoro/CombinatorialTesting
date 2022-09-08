#include "include/coverage.h"
using namespace std;

int main()
{

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

    return 0;

}