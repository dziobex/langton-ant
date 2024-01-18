#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "field.h"

// domyślnie cała plansza jest biała (pusta)
void init_field(field_t* field, int m, int n) {
    field->m = m;
    field->n = n;

    for ( int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j)
            field->field[i][j] = 0;
    }
}

// generuje losowo czarne pola (przeszkody)
void random_obstacles(field_t* field, int pc) {
    int blackies = ((field->m * field->n) / 100) * pc;
    
    while ( --blackies >= 0 ) {
        int x = rand() % field->m;
        int y = rand() % field->n;

        if ( field->field[x][y] == 0)
            field->field[x][y] = 1; // = "█";
        else
            ++blackies;
    }
}