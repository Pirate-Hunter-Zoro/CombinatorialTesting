#include "include/problem.h"
using namespace std;

int main()
{

    Problem my_problem = Problem();
    for (const auto &chr: my_problem.vars)
        cout << chr << endl;
    
    for (const auto &couple: my_problem.minimal_set)
        cout << couple.first << ", " << couple.second << endl;

    return 0;

}