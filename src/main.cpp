#include "include/problem.h"
using namespace std;

int main()
{

    Problem my_problem = Problem();
    for (const auto &chr: my_problem.vars)
        cout << chr << endl;

    cout << endl;
    
    for (const auto &couple: my_problem.minimal_set)
        cout << couple.first << ", " << couple.second << endl;

    cout << endl;

    int guesses = 0;
    my_problem.find_first_random_break(guesses, true);

    cout << guesses << endl;

    return 0;

}