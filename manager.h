#ifndef _MANAGER_H_
#define _MANAGER_H_

#include <stdio.h>
#include "ant.h"
#include "field.h"

typedef struct __inte_pair {
    int a, b;
} pair_int;

char* pleasant_character(field_t* field, ant_t* ant, int x, int y);

void print_field(field_t* field, ant_t* ant);

char* read_input(FILE* input_file);
unsigned int ant_strlen(char* string);
pair_int anttaker(char* string);
void antmaker(ant_t *ant, pair_int positions, char* string, int row);

void field_editor(field_t* field, char* string, int row);

// tudu: z pliku (field_t* ant_t* char* filename) 
void get_from_file(field_t* dest_field, ant_t* dest_ant, char* filename);

#endif