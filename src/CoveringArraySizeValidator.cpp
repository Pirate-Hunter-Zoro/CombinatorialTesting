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