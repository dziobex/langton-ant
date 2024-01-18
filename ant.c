#include <stdio.h>
#include <stdlib.h>

#include "ant.h"

void init_ant(ant_t* ant, int x, int y, char dir) {
    ant->x = x;
    ant->y = y;

    ant->direction = dir;                           // idzie domyślnie
}

void move_ant(ant_t* ant, field_t* field) {
    if (field->field[ant->x][ant->y] == 0) {        // biały
        // w prawo
        ant->direction++;
    } else {                                        // czany
        // w lewo
        ant->direction--;
    }
    ant->direction = (ant->direction + 4) % 4;

    // zmień kolor na przeciwny
    field->field[ant->x][ant->y] = field->field[ant->x][ant->y] == 0 ? 1 : 0;

    // poprzednie koordynaty
    int p_x = ant->x, p_y = ant->y;

    // przesuń mruwe do przodu
    switch (ant->direction) {
        case 0:     // czyli ^
            ant->y--;
            break;
        case 1:     // czyli >
            ant->x++;
            break;
        case 2:     // czyli v
            ant->y++;
            break;
        case 3:     // czyli <
            ant->x--;
            break;
        default:
            break;
    }

    // reset pozycji - czyli gdy mrówka teoretycznie wyjdzie poza planszę - nie powinno być no możliwe!!!!
    if ( ant->x < 0 || ant->x >= field->m )
        ant->x = p_x;
    if ( ant->y < 0 || ant->y >= field->m )
        ant->y = p_y;
}