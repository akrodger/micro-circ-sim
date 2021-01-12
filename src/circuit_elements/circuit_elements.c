/*
 * Function implementations of initializers for
 * structs for commonly used circuit elements by Bram Rodgers.
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
                      unsigned long idx,
                      unsigned long node_pos,
                      unsigned long node_neg,
                      double volt){
    V->symbol   = 'V';
    V->idx      = idx;
    V->node_pos = node_pos;
    V->node_neg = node_neg;
    V->volt     = volt;
}

void mcs_init_current(mcs_current* I,
                      unsigned long idx,
                      unsigned long node_pos,
                      unsigned long node_neg,
                      double amp){
    I->symbol   = 'I';
    I->idx      = idx;
    I->node_pos = node_pos;
    I->node_neg = node_neg;
    I->amp      = amp;
}

void mcs_init_resistor(mcs_resistor* R,
                       unsigned long idx,
                       unsigned long node_pos,
                       unsigned long node_neg,
                       double ohm){
    R->symbol   = 'R';
    R->idx      = idx;
    R->node_pos = node_pos;
    R->node_neg = node_neg;
    R->ohm      = ohm;
}

void mcs_init_capacitor(mcs_capacitor* C,
                        unsigned long idx,
                        unsigned long node_pos,
                        unsigned long node_neg,
                        double farad){
    C->symbol   = 'C';
    C->idx      = idx;
    C->node_pos = node_pos;
    C->node_neg = node_neg;
    C->farad    = farad;
}

void mcs_init_inductor(mcs_inductor* L,
                        unsigned long idx,
                        unsigned long node_pos,
                        unsigned long node_neg,
                        double henry){
    L->symbol   = 'L';
    L->idx      = idx;
    L->node_pos = node_pos;
    L->node_neg = node_neg;
    L->henry    = henry;
}

void mcs_init_diode(mcs_diode* D,
                      unsigned long idx,
                      unsigned long node_pos,
                      unsigned long node_neg){
    D->symbol   = 'D';
    D->idx      = idx;
    D->node_pos = node_pos;
    D->node_neg = node_neg;
}

void mcs_init_bjt_npn(mcs_bjt_npn* QN,
                        unsigned long idx,
                        unsigned long node_c,
                        unsigned long node_b,
                        unsigned long node_e){
    QN->symbol = 'Q';
    QN->dope   = 'N';
    QN->idx    = idx;
    QN->node_c = node_c;
    QN->node_b = node_b;
    QN->node_e = node_e;
}

void mcs_init_bjt_pnp(mcs_bjt_pnp* QP,
                        unsigned long idx,
                        unsigned long node_c,
                        unsigned long node_b,
                        unsigned long node_e){
    QP->symbol = 'Q';
    QP->dope   = 'P';
    QP->idx    = idx;
    QP->node_c = node_c;
    QP->node_b = node_b;
    QP->node_e = node_e;
}

void mcs_init_mosfet_nc(mcs_mosfet_nc* MN,
                        unsigned long idx,
                        unsigned long node_d,
                        unsigned long node_g,
                        unsigned long node_s){
    MN->symbol = 'M';
    MN->dope   = 'N';
    MN->idx    = idx;
    MN->node_d = node_d;
    MN->node_g = node_g;
    MN->node_s = node_s;
}

void mcs_init_mosfet_pc(mcs_mosfet_pc* MP,
                        unsigned long idx,
                        unsigned long node_d,
                        unsigned long node_g,
                        unsigned long node_s){
    MP->symbol = 'M';
    MP->dope   = 'P';
    MP->idx    = idx;
    MP->node_d = node_d;
    MP->node_g = node_g;
    MP->node_s = node_s;
}

 
