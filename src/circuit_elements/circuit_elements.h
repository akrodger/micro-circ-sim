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
    const char symbol = 'V';    /*Volatage sources denoted by V*/
    unsigned int idx;           /*The numeric identifier for this element.*/
    unsigned int node_pos;      /*The + node connection for this element*/
    unsigned int node_neg;      /*The - node connection for this element*/
    double volt;                /*The number of volts the supply outputs*/
} mcs_voltage;

typedef struct _mcs_current{
    const char symbol = 'I';    /*Current sources denoted by I*/
    unsigned int idx;           /*The numeric identifier for this element.*/
    unsigned int node_pos;      /*The + node connection for this element*/
    unsigned int node_neg;      /*The - node connection for this element*/
    double amp;                 /*The number of amps the supply outputs*/
} mcs_current;

typedef struct _mcs_resistor{
    const char symbol = 'R';    /*Resistors denoted by R*/
    unsigned int idx;           /*The numeric identifier for this element.*/
    unsigned int node_pos;      /*The + node connection for this element*/
    unsigned int node_neg;      /*The - node connection for this element*/
    double ohm;                 /*The resistance of this element in Ohms*/
} mcs_resistor;

typedef struct _mcs_capacitor{
    const char symbol = 'C';    /*Capacitors denoted by C*/
    unsigned int idx;           /*The numeric identifier for this element.*/
    unsigned int node_pos;      /*The + node connection for this element*/
    unsigned int node_neg;      /*The - node connection for this element*/
    double farad;               /*The capacitance of this element in Farads*/
} mcs_capacitor;

typedef struct _mcs_inductor{
    const char symbol = 'L';    /*Inductors denoted by L*/
    unsigned int idx;           /*The numeric identifier for this element.*/
    unsigned int node_pos;      /*The + node connection for this element*/
    unsigned int node_neg;      /*The - node connection for this element*/
    double henry;               /*The inductance of this element in Henries*/
} mcs_inductor;

typedef struct _mcs_diode{
    const char symbol = 'D';    /*Diodes denoted by D*/
    unsigned int idx;           /*The numeric identifier for this element.*/
    unsigned int node_pos;      /*The + node connection for this element*/
    unsigned int node_neg;      /*The - node connection for this element*/
} mcs_diode;

typedef struct _mcs_bjt_npn{
    const char symbol = 'Q';    /*BJTs denoted by Q*/
    const char dope = 'N';      /*N for NPN doping pattern.*/
    unsigned int idx;           /*The numeric identifier for this element.*/
    unsigned int node_c;        /*The collector node for this transistor*/
    unsigned int node_b;        /*The base node for this transistor*/
    unsigned int node_e;        /*The emitter node for this transistor*/
} mcs_bjt_npn;

typedef struct _mcs_bjt_pnp{
    const char symbol = 'Q';    /*BJTs denoted by Q*/
    const char dope = 'P';      /*P for PNP doping pattern.*/
    unsigned int idx;           /*The numeric identifier for this element.*/
    unsigned int node_c;        /*The collector node for this transistor*/
    unsigned int node_b;        /*The base node for this transistor*/
    unsigned int node_e;        /*The emitter node for this transistor*/
} mcs_bjt_pnp;

typedef struct _mcs_mosfet_nc{
    const char symbol = 'M';    /*MOSFETs denoted by M*/
    const char dope = 'N';      /*N for n-channel doping pattern.*/
    unsigned int idx;           /*The numeric identifier for this element.*/
    unsigned int node_d;        /*The drain node for this transistor*/
    unsigned int node_g;        /*The gate node for this transistor*/
    unsigned int node_s;        /*The source node for this transistor*/
} mcs_mosfet_nc;

typedef struct _mcs_mosfet_pc{
    const char symbol = 'N';    /*MOSFETs denoted by M*/
    const char dope = 'P';      /*P for p-channel doping pattern.*/
    unsigned int idx;           /*The numeric identifier for this element.*/
    unsigned int node_d;        /*The drain node for this transistor*/
    unsigned int node_g;        /*The gate node for this transistor*/
    unsigned int node_s;        /*The source node for this transistor*/
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
                      unsigned int idx,
                      unsigned int node_pos,
                      unsigned int node_neg,
                      double volt);

void mcs_init_current(mcs_current* I,
                      unsigned int idx,
                      unsigned int node_pos,
                      unsigned int node_neg,
                      double amp);

void mcs_init_resistor(mcs_resistor* R,
                       unsigned int idx,
                       unsigned int node_pos,
                       unsigned int node_neg,
                       double ohm);

void mcs_init_capacitor(mcs_capacitor* C,
                        unsigned int idx,
                        unsigned int node_pos,
                        unsigned int node_neg,
                        double farad);

void mcs_init_inductor(mcs_inductor* L,
                        unsigned int idx,
                        unsigned int node_pos,
                        unsigned int node_neg,
                        double henry);

void mcs_init_diode(mcs_diode* D,
                      unsigned int idx,
                      unsigned int node_pos,
                      unsigned int node_neg);

void mcs_init_bjt_npn(mcs_bjt_npn* QN,
                        unsigned int idx,
                        unsigned int node_c,
                        unsigned int node_b,
                        unsigned int node_e); 

void mcs_init_bjt_pnp(mcs_bjt_pnp* QP,
                        unsigned int idx,
                        unsigned int node_c,
                        unsigned int node_b,
                        unsigned int node_e);

void mcs_init_mosfet_nc(mcs_mosfet_nc* MN,
                        unsigned int idx,
                        unsigned int node_d,
                        unsigned int node_g,
                        unsigned int node_s);

void mcs_init_mosfet_pc(mcs_mosfet_pc* MP,
                        unsigned int idx,
                        unsigned int node_d,
                        unsigned int node_g,
                        unsigned int node_s);
#endif
