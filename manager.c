#include "manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "field.h"
#include "ant.h"

char* pleasant_character(field_t* field, ant_t* ant, int x, int y) {
    int is_black = (field->field[x][y] == 1);

    // na tym polu nie stoi mruwa - zwroć normalny kloc
    if (x != ant->x || y != ant->y)
        return is_black == 0 ? BLACK : WHITE;

    // ładna mruwka na planszy
    if ( ant->direction == 0)                                   // ^
        return is_black == 0 ? BLACK_UP : WHITE_UP;
    if ( ant->direction == 1)                                   // >
        return is_black == 0 ? BLACK_LEFT : WHITE_LEFT;
    if ( ant->direction == 2)                                   // v
        return is_black == 0 ? BLACK_DOWN : WHITE_DOWN;
    if ( ant->direction == 3)                                   // <
        return is_black == 0 ? BLACK_RIGHT : WHITE_RIGHT;
    
    return " ";
}

// wypis stanu planszy na konsolę
void print_field(field_t* field, ant_t* ant) {
    for (int i = 0; i < field->m; ++i) {
        for ( int j = 0; j < field->n; ++j) // printf("%c", field.field[i][j]);
            printf("%s|", pleasant_character(field, ant, i, j));
        printf("\n");
    }
}

// pobieranie stanu planszy ze wskazanego pliku
void get_from_file(field_t* dest_field, ant_t* dest_ant, char* filename) {

    FILE *opener = fopen(filename, "r");

    if ( opener == NULL )
        printf(":()");

    //int new_m = 0, new_n = 0;
    //int ant_x = 0, ant_y = 0;

    char buffer[3000];

    while( fgets(buffer, 3000, opener) != NULL ) {
        printf("%i: %s\n", strlen(buffer), buffer);
    }

    fclose(opener);
}