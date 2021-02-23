/*
 * A simple library for error handling of MicroCircSim by Bram Rodgers.
 * Original Draft Dated: 11, Jan 2021
 */

/*
 * Macros and Includes go here: (Some common ones included)
 */
#include "error_handling.h"
/*
 * Locally used helper functions:
 */

/*
 * Static Local Variables:
 */

/*
 * Function Implementations:
 */


void mcs_error(enum MCS_ERROR_TYPE e){
    switch(e){
        case FILE_READ_ONLY:
            printf(MCS_FILE_READ_ONLY_STR);
            break;
        case MCS_NETLIST_FMT:
            printf(MCS_NETLIST_FMT_STR);
            break;
        case MCS_DEV_READ_UNKNOWN:
            printf(MCS_DEV_READ_UNKNOWN_STR);
            break;
        case MCS_NUM_PARSER:
            printf(MCS_NUM_PARSER_STR);
            break;
        case MCS_DEV_WRITE_UNKNOWN:
            printf(MCS_DEV_WRITE_UNKNOWN_STR);
            break;
        default:
            printf(MCS_DEFAULT_ERR_STR);
    }
    exit(1);
}
 
