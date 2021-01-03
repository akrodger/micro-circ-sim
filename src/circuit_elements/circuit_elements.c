/*
 * C Source file Template by Bram Rodgers.
 * Original Draft Dated: 25, Feb 2018
 */

/*
 * Macros and Includes go here: (Some common ones included)
 */
#include "circuit_elements.h"
/*
 * Locally used helper functions:
 */

/*
 * Static Local Variables:
 */

/*
 * Function Implementations:
 */
void mcs_init_voltage(mcs_voltage* V,
                      unsigned int idx,
                      unsigned int node_pos,
                      unsigned int node_neg,
                      double volt){
    V->idx      = idx;
    V->node_pos = node_pos;
    V->node_neg = node_neg;
    V->volt     = volt;
}

void mcs_init_current(mcs_current* I,
                      unsigned int idx,
                      unsigned int node_pos,
                      unsigned int node_neg,
                      double amp){
    I->idx      = idx;
    I->node_pos = node_pos;
    I->node_neg = node_neg;
    I->amp      = amp;
}

void mcs_init_resistor(mcs_resistor* R,
                       unsigned int idx,
                       unsigned int node_pos,
                       unsigned int node_neg,
                       double ohm){
    R->idx      = idx;
    R->node_pos = node_pos;
    R->node_neg = node_neg;
    R->ohm      = ohm;
}

void mcs_init_capacitor(mcs_capacitor* C,
                        unsigned int idx,
                        unsigned int node_pos,
                        unsigned int node_neg,
                        double farad){
    C->idx      = idx;
    C->node_pos = node_pos;
    C->node_neg = node_neg;
    C->farad    = farad;
}

void mcs_init_inductor(mcs_inductor* L,
                        unsigned int idx,
                        unsigned int node_pos,
                        unsigned int node_neg,
                        double henry){
    L->idx      = idx;
    L->node_pos = node_pos;
    L->node_neg = node_neg;
    L->volt     = henry;
}

void mcs_init_diode(mcs_diode* D,
                      unsigned int idx,
                      unsigned int node_pos,
                      unsigned int node_neg){
    D->idx      = idx;
    D->node_pos = node_pos;
    D->node_neg = node_neg;
}

void mcs_init_bjt_npn(mcs_bjt_npn* QN,
                        unsigned int idx,
                        unsigned int node_c,
                        unsigned int node_b,
                        unsigned int node_e){
    QN->idx      = idx;
    QN->node_pos = node_c;
    QN->node_neg = node_b;
    QN->node_e   = node_e;
}

void mcs_init_bjt_pnp(mcs_bjt_pnp* QP,
                        unsigned int idx,
                        unsigned int node_c,
                        unsigned int node_b,
                        unsigned int node_e){
    QN->idx      = idx;
    QN->node_pos = node_c;
    QN->node_neg = node_b;
    QN->node_e   = node_e;
}

void mcs_init_mosfet_nc(mcs_mosfet_nc* MN,
                        unsigned int idx,
                        unsigned int node_d,
                        unsigned int node_g,
                        unsigned int node_s){
    QN->idx      = idx;
    QN->node_pos = node_c;
    QN->node_neg = node_b;
    QN->node_e   = node_e;
}

void mcs_init_mosfet_pc(mcs_mosfet_pc* MP,
                        unsigned int idx,
                        unsigned int node_d,
                        unsigned int node_g,
                        unsigned int node_s){
    QN->idx      = idx;
    QN->node_pos = node_c;
    QN->node_neg = node_b;
    QN->node_e   = node_e;
}

 
