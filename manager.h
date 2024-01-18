#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "ant.h"
#include "field.h"

char* pleasant_character(field_t* field, ant_t* ant, int x, int y);

void print_field(field_t* field, ant_t* ant);

// tudu: z pliku (field_t* ant_t* char* filename) 
void get_from_file(field_t* dest_field, ant_t* dest_ant, char* filename);

#endif