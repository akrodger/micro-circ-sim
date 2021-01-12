#ifndef MCS_BASIC_ELEMENTS_H
#define MCS_BASIC_ELEMENTS_H

/*
 * Struct definitions for commonly used circuit elements by Bram Rodgers.
 * The list of elements is based on Problem 1.1 on Page 10 of
 * the textbook ``Circuit Simulation'' by Farid N. Najm.
 *
 * The following differences are present:
 * ->No scale factor is stored on the doped semiconductor devices:
 *  |->Impacts QN, QP, MN, and MP devices.
 * ->Group 1 and Group 2 distinctions for Modified Nodal Analysis are ignored:
 *  |->Impacts I, R, and C devices.
 *
 * Original Draft Dated: 02, Jan 2021
 */

/*
 * Header File Body:
 */

/*
 * Macros and Includes go here.
 */
#include<stdlib.h>
#include<stdio.h>

/*
 * Circuit Element Struct Definitions:
 */
/*
 * This struct contains a char in the same location one expects to
 * find the type identified symbol for all other MCS circuit components.
 */
typedef struct _mcs_symbol{
    char symbol;
} mcs_symbol;

typedef struct _mcs_voltage{
    char symbol;/* = 'V';         Volatage sources denoted by V*/
    unsigned long idx;           /*The numeric identifier for this element.*/
    unsigned long node_pos;      /*The + node connection for this element*/
    unsigned long node_neg;      /*The - node connection for this element*/
    double volt;                /*The number of volts the supply outputs*/
} mcs_voltage;

typedef struct _mcs_current{
    char symbol;/* = 'I';         Current sources denoted by I*/
    unsigned long idx;           /*The numeric identifier for this element.*/
    unsigned long node_pos;      /*The + node connection for this element*/
    unsigned long node_neg;      /*The - node connection for this element*/
    double amp;                 /*The number of amps the supply outputs*/
} mcs_current;

typedef struct _mcs_resistor{
    char symbol;/* = 'R';         Resistors denoted by R*/
    unsigned long idx;           /*The numeric identifier for this element.*/
    unsigned long node_pos;      /*The + node connection for this element*/
    unsigned long node_neg;      /*The - node connection for this element*/
    double ohm;                 /*The resistance of this element in Ohms*/
} mcs_resistor;

typedef struct _mcs_capacitor{
    char symbol;/* = 'C';         Capacitors denoted by C*/
    unsigned long idx;           /*The numeric identifier for this element.*/
    unsigned long node_pos;      /*The + node connection for this element*/
    unsigned long node_neg;      /*The - node connection for this element*/
    double farad;               /*The capacitance of this element in Farads*/
} mcs_capacitor;

typedef struct _mcs_inductor{
    char symbol;/* = 'L';         Inductors denoted by L*/
    unsigned long idx;           /*The numeric identifier for this element.*/
    unsigned long node_pos;      /*The + node connection for this element*/
    unsigned long node_neg;      /*The - node connection for this element*/
    double henry;               /*The inductance of this element in Henries*/
} mcs_inductor;

typedef struct _mcs_diode{
    char symbol;/* = 'D';         Diodes denoted by D*/
    unsigned long idx;           /*The numeric identifier for this element.*/
    unsigned long node_pos;      /*The + node connection for this element*/
    unsigned long node_neg;      /*The - node connection for this element*/
} mcs_diode;

typedef struct _mcs_bjt_npn{
    char symbol;/* = 'Q';         BJTs denoted by Q*/
    char dope;/* = 'N';           N for NPN doping pattern.*/
    unsigned long idx;           /*The numeric identifier for this element.*/
    unsigned long node_c;        /*The collector node for this transistor*/
    unsigned long node_b;        /*The base node for this transistor*/
    unsigned long node_e;        /*The emitter node for this transistor*/
} mcs_bjt_npn;

typedef struct _mcs_bjt_pnp{
    char symbol;/* = 'Q';         BJTs denoted by Q*/
    char dope;/* = 'P';           P for PNP doping pattern.*/
    unsigned long idx;           /*The numeric identifier for this element.*/
    unsigned long node_c;        /*The collector node for this transistor*/
    unsigned long node_b;        /*The base node for this transistor*/
    unsigned long node_e;        /*The emitter node for this transistor*/
} mcs_bjt_pnp;

typedef struct _mcs_mosfet_nc{
    char symbol;/* = 'M';         MOSFETs denoted by M*/
    char dope;/* = 'N';           N for n-channel doping pattern.*/
    unsigned long idx;           /*The numeric identifier for this element.*/
    unsigned long node_d;        /*The drain node for this transistor*/
    unsigned long node_g;        /*The gate node for this transistor*/
    unsigned long node_s;        /*The source node for this transistor*/
} mcs_mosfet_nc;

typedef struct _mcs_mosfet_pc{
    char symbol;/* = 'N';         MOSFETs denoted by M*/
    char dope;/* = 'P';           P for p-channel doping pattern.*/
    unsigned long idx;           /*The numeric identifier for this element.*/
    unsigned long node_d;        /*The drain node for this transistor*/
    unsigned long node_g;        /*The gate node for this transistor*/
    unsigned long node_s;        /*The source node for this transistor*/
} mcs_mosfet_pc;

/*
 *  This union allows us to store all the various circuit elements
 *  in data structures with one type.
 */
typedef union _mcs_element{
    mcs_symbol      elem;
    mcs_voltage     V;
    mcs_current     I;
    mcs_resistor    R;
    mcs_capacitor   C;
    mcs_inductor    L;
    mcs_diode       D;
    mcs_bjt_npn     QN;
    mcs_bjt_pnp     QP;
    mcs_mosfet_nc   MN;
    mcs_mosfet_pc   MP;
} mcs_element;
/*
 * Function Declarations:
 */
void mcs_init_voltage(mcs_voltage* V,
                      unsigned long idx,
                      unsigned long node_pos,
                      unsigned long node_neg,
                      double volt);

void mcs_init_current(mcs_current* I,
                      unsigned long idx,
                      unsigned long node_pos,
                      unsigned long node_neg,
                      double amp);

void mcs_init_resistor(mcs_resistor* R,
                       unsigned long idx,
                       unsigned long node_pos,
                       unsigned long node_neg,
                       double ohm);

void mcs_init_capacitor(mcs_capacitor* C,
                        unsigned long idx,
                        unsigned long node_pos,
                        unsigned long node_neg,
                        double farad);

void mcs_init_inductor(mcs_inductor* L,
                        unsigned long idx,
                        unsigned long node_pos,
                        unsigned long node_neg,
                        double henry);

void mcs_init_diode(mcs_diode* D,
                      unsigned long idx,
                      unsigned long node_pos,
                      unsigned long node_neg);

void mcs_init_bjt_npn(mcs_bjt_npn* QN,
                        unsigned long idx,
                        unsigned long node_c,
                        unsigned long node_b,
                        unsigned long node_e); 

void mcs_init_bjt_pnp(mcs_bjt_pnp* QP,
                        unsigned long idx,
                        unsigned long node_c,
                        unsigned long node_b,
                        unsigned long node_e);

void mcs_init_mosfet_nc(mcs_mosfet_nc* MN,
                        unsigned long idx,
                        unsigned long node_d,
                        unsigned long node_g,
                        unsigned long node_s);

void mcs_init_mosfet_pc(mcs_mosfet_pc* MP,
                        unsigned long idx,
                        unsigned long node_d,
                        unsigned long node_g,
                        unsigned long node_s);
#endif
