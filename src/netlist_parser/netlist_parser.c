/*
 * Function implementations for
 * a netlist parser. Written for simple circuit simulator by Bram Rodgers.
 * This netlist parser is based on Problem 1.1 on Page 10 of
 * the textbook ``Circuit Simulation'' by Farid N. Najm.
 *
 * Original Draft Dated: 03, Jan 2021
 */

/*
 * Macros and Includes go here: (Some common ones included)
 */
#include "netlist_parser.h"
/*
 * Locally used helper functions:
 */

void mcs_netlist_str2struct(char* nl_line, mcs_netlist** nl);
void mcs_parse_VIRCL(char* nl_line,
                     unsigned long* idx_ptr,
                     unsigned long* node_p_ptr,
                     unsigned long* node_n_ptr,
                     double* param_ptr);
void mcs_parse_diode(char* nl_line,
                     unsigned long* idx_ptr,
                     unsigned long* node_p_ptr,
                     unsigned long* node_n_ptr);
void mcs_parse_transistor(char* nl_line,
                          unsigned long* idx_ptr,
                          unsigned long* node_1_ptr,
                          unsigned long* node_2_ptr,
                          unsigned long* node_3_ptr);

/*
 * Static Local Variables:
 */

/*
 * Function Implementations:
 */


void mcs_read_netlist(const char* filename, mcs_netlist** nl){
    static const char r_only = 'r';
    static char nl_line[MCS_NETLIST_LINE_LEN+1];
    int i = 0;
    int newline_idx = 0;
    mcs_netlist** this_line = nl;
    mcs_netlist* prev_line = NULL;
    //pointer to location of the comment character '%'
    char* token_ptr = NULL;
    FILE* net_text = fopen(filename,&r_only);
    if(net_text == NULL){ //if you cant open the file
        mcs_error(FILE_READ_ONLY);//throw an error to stdout and exit.
    }
    
    do{
        //reading a single line
        newline_idx = -1;
        for(i=0; i < MCS_NETLIST_LINE_LEN; i++){
            nl_line[i] = (char) fgetc(net_text);
            if( nl_line[i] == '\n'       ||
                nl_line[i] == (char) EOF   ){
                newline_idx = i;
                nl_line[i+1]  = '\0';
                break;
            }
        }
        if(newline_idx < 0){
            //if a newline or end of file comes after max line length,
            //then error out based on formatting error.
            mcs_error(MCS_NETLIST_FMT);
        }
        //nl_line contains a Cstring with 1 line of the parsed file now.
        token_ptr = strchr(nl_line, (int) '%' );
        //To ignore everything after the comment, just change the
        //comment character to the Cstring terminating character '\0'
        if(token_ptr != NULL){
            *token_ptr = '\0';
        }
        //printf("%s\n",nl_line);
        //We can now process the string as if there are no comments.
        //Need to skip all leading spaces and tabs.
        token_ptr = NULL;
        for(i=0;i<MCS_NETLIST_LINE_LEN;i++){
            if(nl_line[i] == '\0' || nl_line[i] == '\n'){
                token_ptr = NULL;   
                break;
            }
            if(nl_line[i] != ' ' &&
               nl_line[i] != '\t'){
                token_ptr = &(nl_line[i]);
                break;
            }
        }
        //printf("%s\n",nl_line);
        //A line containing only a comment or newline is allowed,
        //so if the token_ptr is NULL then just go to the next line.
        if(token_ptr == NULL){
            continue;
        }
        //if first meaningful char is end of file, then break.
        if(*token_ptr == (char) EOF){
            break;
        }
        //The token ptr contains a pointer to a non space and non-newline char.
        //Now call the helper function which processes this
        //string into a netlist struct
        mcs_netlist_str2struct(token_ptr, this_line);
        (*this_line)->prev = prev_line;
        //Move on to next line of the file.
        prev_line = *this_line;
        this_line = &((*this_line)->next);
    }while(1);
    fclose(net_text);
}


void mcs_print_element(char* nl_line, mcs_element* z){
    //We assumme that the pointer nl_line has at least 81 characters allocated.
    //First step: read the char which is stored as the first
    //entry of the union z.
    switch(z->elem.symbol){
        case 'V'://Voltage Source
        case 'I'://Current Source
        case 'R'://Resistor
        case 'C'://Capacitor
        case 'L'://Inductor
            sprintf(nl_line,"%c%lu %lu %lu %lf",z->L.symbol,z->L.idx,
                    z->L.node_pos,z->L.node_neg,z->L.henry);
            break;
        case 'D'://Diode
            sprintf(nl_line,"%c%lu %lu %lu",z->D.symbol,z->D.idx,
                    z->D.node_pos,z->D.node_neg);
            break;
        case 'Q'://BJT
            if(z->QN.dope == 'N' || z->QP.dope == 'P'){
                sprintf(nl_line,"%c%c%lu %lu %lu %lu",z->QN.symbol,
                    z->QN.dope,z->QN.idx,z->QN.node_c,
                    z->QN.node_b,z->QN.node_e);
            }else{
            mcs_error(MCS_DEV_WRITE_UNKNOWN);
            }
            break;
        case 'M'://MOSFET
            if(z->MN.dope == 'N' || z->MP.dope == 'P'){
                sprintf(nl_line,"%c%c%lu %lu %lu %lu",z->MN.symbol,
                    z->MN.dope,z->MN.idx,z->MN.node_d,
                    z->MN.node_g,z->MN.node_s);                
            }else{
            mcs_error(MCS_DEV_WRITE_UNKNOWN);
            }
            break;
        default:
            mcs_error(MCS_DEV_WRITE_UNKNOWN);
    }
}


void mcs_alloc_netlist(mcs_netlist** nl){
    *nl = (mcs_netlist*) malloc(sizeof(mcs_netlist));
    (*nl)->dev = (mcs_element*) malloc(sizeof(mcs_element));
    (*nl)->next = NULL;
    (*nl)->prev = NULL;
}


void mcs_free_netlist(mcs_netlist** nl){
    mcs_netlist* netlist = *nl;
    if(netlist != NULL){
        while((netlist)->next != NULL){
            if(netlist->prev != NULL){
                free(netlist->prev);
            }
            if(netlist->dev != NULL){
                free(netlist->dev);
            }
            netlist = netlist->next;
        }
        if(netlist->prev != NULL){
            free(netlist->prev);
        }
        if(netlist->dev != NULL){
            free(netlist->dev);
        }
        free(netlist);
    }
}




void mcs_netlist_str2struct(char* nl_line, mcs_netlist** nl){
    unsigned long dev_idx,node1,node2,node3;
    double param;
    //allocate the memory for this netlist entry
    mcs_alloc_netlist(nl);
    //read the first character of the netlist line, switching
    //on this char to initialize the netlist entry.
    switch(nl_line[0]){
        case 'V'://Voltage Source
            mcs_parse_VIRCL(nl_line,&dev_idx,&node1,&node2,&param);
            mcs_init_voltage(&((*nl)->dev->V),dev_idx,node1,node2,param);
            break;
        case 'I'://Current Source
            mcs_parse_VIRCL(nl_line,&dev_idx,&node1,&node2,&param);
            mcs_init_current(&((*nl)->dev->I),dev_idx,node1,node2,param);
            break;
        case 'R'://Resistor
            mcs_parse_VIRCL(nl_line,&dev_idx,&node1,&node2,&param);
            mcs_init_resistor(&((*nl)->dev->R),dev_idx,node1,node2,param);
            break;
        case 'C'://Capacitor
            mcs_parse_VIRCL(nl_line,&dev_idx,&node1,&node2,&param);
            mcs_init_capacitor(&((*nl)->dev->C),dev_idx,node1,node2,param);
            break;
        case 'L'://Inductor
            mcs_parse_VIRCL(nl_line,&dev_idx,&node1,&node2,&param);
            mcs_init_inductor(&((*nl)->dev->L),dev_idx,node1,node2,param);
            break;
        case 'D'://Diode
            mcs_parse_diode(nl_line,&dev_idx,&node1,&node2);
            mcs_init_diode(&((*nl)->dev->D),dev_idx,node1,node2);
            break;
        case 'Q'://BJT
            mcs_parse_transistor(nl_line,&dev_idx,&node1,&node2,&node3);
            if(nl_line[1] == 'N'){
                mcs_init_bjt_npn(&((*nl)->dev->QN),
                                        dev_idx,node1,node2,node3);
            }else if(nl_line[1] == 'P'){
                mcs_init_bjt_pnp(&((*nl)->dev->QP),
                                        dev_idx,node1,node2,node3);
            }else{
            mcs_error(MCS_DEV_READ_UNKNOWN);
            }
            break;
        case 'M'://MOSFET
            mcs_parse_transistor(nl_line,&dev_idx,&node1,&node2,&node3);
            if(nl_line[1] == 'N'){
                mcs_init_mosfet_nc(&((*nl)->dev->MN),
                                        dev_idx,node1,node2,node3);
            }else if(nl_line[1] == 'P'){
                mcs_init_mosfet_pc(&((*nl)->dev->MP),
                                        dev_idx,node1,node2,node3);
            }else{
            mcs_error(MCS_DEV_READ_UNKNOWN);
            }
            break;
        default:
            mcs_error(MCS_DEV_READ_UNKNOWN);
    }
}

void mcs_parse_VIRCL(char* nl_line,
                     unsigned long* idx_ptr,
                     unsigned long* node_p_ptr,
                     unsigned long* node_n_ptr,
                     double* param_ptr){
    char* token_ptr = &(nl_line[1]);
    char* end_ptr = NULL;
    errno = 0;//reset error number to zero before calling
    *idx_ptr = strtoul(token_ptr, &end_ptr, 10);
    if((*idx_ptr == 0 && errno != 0) || (token_ptr == end_ptr)){
        mcs_error(MCS_NUM_PARSER);
    }
    token_ptr = strtok(end_ptr," \t");
    *node_p_ptr = strtoul(token_ptr, &end_ptr, 10);
    if((*node_p_ptr == 0 && errno != 0) || (token_ptr == end_ptr)){
        mcs_error(MCS_NUM_PARSER);
    }
    token_ptr = strtok(NULL," \t");
    errno = 0;
    *node_n_ptr = strtoul(token_ptr, &end_ptr, 10);
    if((*node_n_ptr == 0 && errno != 0) || (token_ptr == end_ptr)){
        mcs_error(MCS_NUM_PARSER);
    }
    token_ptr = strtok(NULL," \t");
    errno = 0;
    *param_ptr = strtod(token_ptr,&end_ptr);
    if((*node_n_ptr == 0.0 && errno != 0) || (token_ptr == end_ptr)){
        mcs_error(MCS_NUM_PARSER);
    }
}


void mcs_parse_diode(char* nl_line,
                     unsigned long* idx_ptr,
                     unsigned long* node_p_ptr,
                     unsigned long* node_n_ptr){
    char* token_ptr = &(nl_line[1]);
    char* end_ptr = NULL;
    errno = 0;//reset error number to zero before calling
    *idx_ptr = strtoul(token_ptr, &end_ptr, 10);
    if((*idx_ptr == 0 && errno != 0) || (token_ptr == end_ptr)){
        mcs_error(MCS_NUM_PARSER);
    }
    token_ptr = strtok(end_ptr," \t");
    errno = 0;
    *node_p_ptr = strtoul(token_ptr, &end_ptr, 10);
    if((*node_p_ptr == 0 && errno != 0) || (token_ptr == end_ptr)){
        mcs_error(MCS_NUM_PARSER);
    }
    token_ptr = strtok(NULL," \t");
    errno = 0;
    *node_n_ptr = strtoul(token_ptr, &end_ptr, 10);
    if((*node_n_ptr == 0 && errno != 0) || (token_ptr == end_ptr)){
        mcs_error(MCS_NUM_PARSER);
    }
}

void mcs_parse_transistor(char* nl_line,
                          unsigned long* idx_ptr,
                          unsigned long* node_1_ptr,
                          unsigned long* node_2_ptr,
                          unsigned long* node_3_ptr){
    char* token_ptr = &(nl_line[2]);
    char* end_ptr = NULL;
    errno = 0;//reset error number to zero before calling
    *idx_ptr = strtoul(token_ptr, &end_ptr, 10);
    if((*idx_ptr == 0 && errno != 0) || (token_ptr == end_ptr)){
        mcs_error(MCS_NUM_PARSER);
    }
    token_ptr = strtok(end_ptr," \t");
    errno = 0;
    *node_1_ptr = strtoul(token_ptr, &end_ptr, 10);
    if((*node_1_ptr == 0 && errno != 0) || (token_ptr == end_ptr)){
        mcs_error(MCS_NUM_PARSER);
    }
    token_ptr = strtok(NULL," \t");
    errno = 0;
    *node_2_ptr = strtoul(token_ptr, &end_ptr, 10);
    if((*node_2_ptr == 0 && errno != 0) || (token_ptr == end_ptr)){
        mcs_error(MCS_NUM_PARSER);
    }
    token_ptr = strtok(NULL," \t");
    errno = 0;
    *node_3_ptr = strtoul(token_ptr, &end_ptr, 10);
    if((*node_3_ptr == 0 && errno != 0) || (token_ptr == end_ptr)){
        mcs_error(MCS_NUM_PARSER);
    }
}
