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
        return is_black == 0 ? BLACK_RIGHT : WHITE_RIGHT;
    if ( ant->direction == 2)                                   // v
        return is_black == 0 ? BLACK_DOWN : WHITE_DOWN;
    if ( ant->direction == 3)                                   // <
        return is_black == 0 ? BLACK_LEFT : WHITE_LEFT;
    
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

char* read_input(FILE* input_file) {
    /*Funkcja dla wczytywania stringa dowolnej długości.
    Powinna być możliwa do użycia dla dowolnego programu C
    który wymaga wczytywania.*/
    
    #define BUFFER 128
    char* in = NULL;
    char buf[BUFFER];
    size_t in_length = 0, temp_length = 0;
    do {
        if (fgets(buf, BUFFER, input_file) != NULL) {
            buf[strcspn(buf, "\n")] = 0;
            temp_length = strlen(buf);
            in = realloc(in, in_length+temp_length+1);
            strcpy(in+in_length, buf);
            in_length += temp_length;
        } else {
            /*Jednak czasami NULL może być wejściem*/
            return NULL;
        }
    } while (temp_length == BUFFER-1 && buf[BUFFER-2] != '\n');
    
    return in;
}

unsigned int ant_strlen(char* string) {
    /* Funkcja ma za zadanie dać długość stringa, nawet ze znakami █ lub mrówki.
     * niestety, same z siebie te znaki mają długość 3, nie 1. Zatem potrzeba
     * własnego iteratora. Czemu nie wchar_t? Ponieważ nie drukuje █ poprawnie.
     * znaki mrówki nie będą drukowane poprawnie w konsoli, więc trudno.
     */

    int iter = 0; 
    unsigned int len = 0;
    char running_buffer[3];
    while (string[iter] != '\0') {
        memcpy(running_buffer, string+iter, 3);
        ++len;
        if( (running_buffer[0]) == ' ') {
            ++iter;
        } else {
            iter += 3;
        }
    }

    return len;
}

pair_int anttaker(char* string) {
    //łapie z danego stringa pozycję mrówki.
    //Zwraca -1, jeśli nie istnieje.
    //NIE DZIAŁA - ZAMIEŃ NA WIDE CHAR ALBO COŚ CO POZWOLI NA PORÓWNANIA
    pair_int iter_len;
        iter_len.a = -1;
        iter_len.b = -1;
    int iter = 0, len = 0; 
    char running_buffer[4];
    running_buffer[3] = '\0';
    while (string[iter] != '\0') {
        memcpy(running_buffer, string+iter, 3);
        if( (running_buffer[0]) == ' ') {
            ++iter;
        } else {
            if(strcmp(running_buffer, BLACK) != 0) {
                iter_len.a = iter;
                iter_len.b = len;
                return iter_len;
            }
            iter += 3;
        }
        ++len;
    }
    return iter_len;
}

void antmaker(ant_t* ant, pair_int position, char* string, int row) {
    /* Edytuje dane mrówki.
     * Bazuje to na pozycji mrówki, stringu, oraz rzędzie w którym się znajduje.
     * //NIE DZIAŁA - ZAMIEŃ NA WIDE CHAR ALBO COŚ CO POZWOLI NA PORÓWNANIA
     */

    char ant_buffer[4];
    ant_buffer[3] = '\0';
    memcpy(ant_buffer, string+position.a, 3);
    if(strcmp(ant_buffer, WHITE_UP) == 0 || strcmp(ant_buffer, BLACK_UP) == 0 ) {
        ant->direction = 0;
    } else if(strcmp(ant_buffer, WHITE_RIGHT) == 0 || strcmp(ant_buffer, BLACK_RIGHT) == 0 ) {
        ant->direction = 1;
    } else if(strcmp(ant_buffer, WHITE_DOWN) == 0 || strcmp(ant_buffer, BLACK_DOWN) == 0 ) {
        ant->direction = 2;
    } else {
        ant->direction = 3;
    }
    ant->x = row;
    ant->y = position.b; 
}

void field_editor(field_t* field, char* string, int row) {
    //Zmienia stan rzędu pola na podstawie stringa wejściowego.
    unsigned int iter = 0, len = 0;
    char running_buffer[4];
    running_buffer[3] = '\0';
    while (string[iter] != '\0') {
        memcpy(running_buffer, string+iter, 3);
        if( (running_buffer[0]) == ' ') {
            field->field[row][len] = 1;
            ++iter;
        } else {
            if(strcmp(running_buffer, BLACK) != 0) {
                if(strcmp(running_buffer, BLACK_UP) == 0 || strcmp(running_buffer, BLACK_DOWN) == 0 || strcmp(running_buffer, BLACK_LEFT) == 0 || strcmp(running_buffer, BLACK_RIGHT) == 0) {
                    field->field[row][len] = 0;
                } else field->field[row][len] = 1;
            } else field->field[row][len] = 0;
            iter += 3;
        }
        ++len;
    }
}

// pobieranie stanu planszy ze wskazanego pliku
void get_from_file(field_t* dest_field, ant_t* dest_ant, char* filename) {
    FILE *opener = fopen(filename, "r");

    if ( opener == NULL ) {
        fprintf(stderr, "Podano nieprawilowy plik wejsciowy. Ups!\n" );
        exit(EXIT_FAILURE);
    }

    int new_m = 0, new_n = 0;
    //int ant_x = 0, ant_y = 0;
    unsigned int utemp = 0;

    char* input_buf;
    while ((input_buf = read_input(opener)) != NULL) {
        // printf("%04u: %s\n", ant_strlen(input_buf), input_buf);
        ++new_m;
        if(new_n == 0) new_n = ant_strlen(input_buf);
        if((utemp = anttaker(input_buf).b) != -1) {
            antmaker(dest_ant, anttaker(input_buf), input_buf, new_m - 1);
        } 
        field_editor(dest_field, input_buf, new_m - 1);
    }

    dest_field->m = new_m - 1;
    dest_field->n = new_n;

    fclose(opener);
}