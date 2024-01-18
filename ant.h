#ifndef _ANT_H_
#define _ANT_H_

#include "field.h"
#include "constants.h"

typedef struct {
    int x, y; // pozycja mruwy
    char direction; // kierunek mruwy
} ant_t;

// tworzy mruwke, stawia ją na planszy
void init_ant(ant_t* ant, int x, int y, char dir);
// przemiesza mrówkę, zgodnie z algorytmem
void move_ant(ant_t* ant, field_t* field);

#endif