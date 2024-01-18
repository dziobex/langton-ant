#ifndef _FIELD_H_
#define _FIELD_H_

#include "constants.h"

// pole field:
// jeśli parzyste -> białe
// nieparzyste -> czarne

typedef struct {
    int m, n;
    char field[M_MAX][N_MAX]; //Inaczej za dużo miejsca na jedną tablicę
} field_t;

// generacja planszy - wszystkie pola są białe
void init_field(field_t* field, int m, int n);

// generuje losowo, czarne pola (ilość wg pc-% pola)
void random_obstacles(field_t* field, int pc);

#endif