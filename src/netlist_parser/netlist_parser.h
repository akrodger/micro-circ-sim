#ifndef MCS_NETLIST_PARSER_H
#define MCS_NETLIST_PARSER_H

/*
 * A netlist parser for a simple circuit simulator by Bram Rodgers.
 * This netlist parser is based on Problem 1.1 on Page 10 of
 * the textbook ``Circuit Simulation'' by Farid N. Najm.
 *
 * Original Draft Dated: 02, Jan 2021
 */

/*
 * Header File Body:
 */

/*
 * Macros and Includes go here.
 */
#include<string.h>
#include<errno.h>
#include"../circuit_elements/circuit_elements.h"
#include"../error_handling/error_handling.h"

/*
 * No line of a netlist file should be longer than 80 chars.
 */
#define MCS_NETLIST_LINE_LEN 80

/*
 * Linked List of Circuit Elements Struct Definition:
 */
typedef struct _mcs_netlist{
    /*A pointer to the mcs_element for this list element.*/
    mcs_element* dev;
    /*Pointer to Previous Element of Linked List*/
    struct _mcs_netlist* prev;
    /*Pointer to Next Element of Linked List*/
    struct _mcs_netlist* next;
} mcs_netlist;

/*
 * Function Declarations:
 */

/*
 * Read a netlist from a file. Store it in *nl.
 *
 * 
 */
void mcs_read_netlist(const char* filename, mcs_netlist** nl);

/*
 * Write a netlist to a file.
 *
 * 
 */
void mcs_write_netlist(char* filename, mcs_netlist* nl);

/*
 * Read the mcs_element struct and output its data to a Cstring.
 * It is assumed that nl_line has at least MCS_NETLIST_LINE_LEN+1 chars
 * allocated to it.
 */
void mcs_print_element(char* nl_line, mcs_element* z);

/*
 * Allocate the memory required to store a netlist linked list element
 * Sets (*nl)->prev and (*nl)->next to NULL.
 * Allocs (*nl)->dev to be sizeof an mcs_element.
 */
void mcs_alloc_netlist(mcs_netlist** nl);

/*
 * Free every element of the Netlist linked list and set all pointers to NULL.
 */
void mcs_free_netlist(mcs_netlist** nl);
#endif
