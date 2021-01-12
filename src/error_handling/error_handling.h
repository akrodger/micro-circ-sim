#ifndef MCS_ERROR_HANDLING_H
#define MCS_ERROR_HANDLING_H

/*
 * A simple library for error handling of MicroCircSim by Bram Rodgers.
 * Original Draft Dated: 11, Jan 2021
 */

/*
 * Header File Body:
 */

/*
 * Macros and Includes go here.
 */
#include<stdlib.h>
#include<stdio.h>

#define MCS_DEFAULT_ERR_STR "\nError: default error type called.\n"
#define MCS_FILE_READ_ONLY_STR "\nError: Could not open read only file.\n"
#define MCS_NETLIST_FMT_STR "\nError: netlist formatted incorrectly.\n"
#define MCS_DEV_UNKNOWN_STR "\nError: unknown netlist device.\n"
#define MCS_NUM_PARSER_STR "\nError: error in parsing netlist parameters.\n"
/*
 * Object and Struct Definitions:
 */

enum MCS_ERROR_TYPE{
    DEFAULT_ERR     = -1,
    FILE_READ_ONLY  =  0,
    MCS_NETLIST_FMT =  1,
    MCS_DEV_UNKNOWN =  2,
    MCS_NUM_PARSER  =  3
};

/*
 * Function Declarations:
 */

void mcs_error(enum MCS_ERROR_TYPE e);

#endif
