#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <unistd.h>

#include "manager.h"

#include "field.h"
#include "ant.h"
#include "constants.h"

// wyświetla jak użyć programu (argumenty etc)
void help(char* fname) {
    printf("\nPotrzebujesz pomocy?\nUzycie programu: ./%s [-m] [-n] [-i] [-d] [-s] [-o] [-p]\n", fname);
    printf("Oznaczenia komend:\n");
    printf("\t-m <liczba wierszy> - wymagana liczba calkowita z przedzialu <5; 1000>\n");
    printf("\t-n <liczba kolumn> - wymagana liczba calkowita z przedzialu <5; 1000>\n");
    printf("\t-i <liczba iteracji> - wymagana liczba calkowita z przedzialu <1; 2000>\n");
    printf("\t-d <kierunek poczatkowy mrowki> - liczby: 0, 1, 2, 3 oznaczajace w kolejnosci: gora, prawo, dol, lewo\n");
    printf("\t-s <nazwa pliku docelowego> - 1. czlon nazw plikow do ktorych beda zapisywane wyniki iteracji\n");
    printf("\t-o <nazwa pliku do wczytania> - plik z ktorego zostanie wczytany stan planszy\n");
    printf("\t-p <%% zapelnionych pol planszy> - liczba calkowita <0; 100> informujaca ile %% planszy ma byc pokryte czarnymi kafelkami\n");
}

int main( int argc, char** argv ) {
    srand(time(NULL));

    // m, n, i, name, dir
    // wiersze, kolumny, nr iteracji, nazwa pliku, kierunek
    // lub wczyt - tylko name

    int c;
    extern char *optarg;
    extern int optind, opterr, optopt;

    // m, n - wiersze, kolumny
    // i - liczba iteracji
    // p - % zapełnienia
    // d - kierunek
    // o - open, plik skąd się wczyta plansze
    // s - save, plik wynikowy (1. człon nazwy)

    int m = 0, n = 0, p = 0, it_count = 1, d = 0;
    char* open_filename;
    char* save_filename;

    // flagi
    int file_opened = 0, file_saved = 0;

    while ((c = getopt(argc, argv, "m:n:i:d:s:o:p:")) != -1) {
        switch (c) {
            case 'm': {
                m = atoi(optarg);
                break;
            }
            case 'n': {
                n = atoi(optarg);
                break;
            }
            case 'i': {
                it_count = atoi(optarg);
                break;
            }
            case 'p': {
                p = atoi(optarg);
                break;
            }
            case 'd': {
                d = atoi(optarg);
                break;
            }
            case 's': {
                file_saved = 1;
                save_filename = malloc(strlen(optarg));
                memcpy(save_filename, optarg, strlen(optarg));
                save_filename[strlen(optarg)] = '\0';
                printf("Zapisac w = %s\n", optarg);
                break;
            }
            case 'o': {
                // jesli o, to tylko z i, ewentualnie z s!
                file_opened = 1;
                open_filename = malloc(strlen(optarg));
                memcpy(open_filename, optarg, strlen(optarg));
                open_filename[strlen(optarg)] = '\0';
                printf("Otworzyc z = %s\n", optarg);
                break;
            }
            case '?': {
                printf("Nieznany argument: %c\n", optopt);
                help(argv[0]);
                break;
            }
            default: {  // używanie
                help(argv[0]);
                exit(EXIT_FAILURE);
            }
        }
    }

    // wywołanie komendy pomocy
    if (argc == 1) {
        help(argv[0]);
        exit(EXIT_FAILURE);
    }
    
    // wykrywanie błędów (dla numeru iteracji)
    if ( it_count < 1 || it_count > 2000) {
        printf("Niepoprawna liczba iteracji (i): %i\n", it_count);
        help(argv[0]);
        exit(EXIT_FAILURE);
    }
    
    field_t field;
    ant_t ant;

    // żaden plik nie został otwarty
    if (file_opened == 0) {
        // wykrywanie błędów (dla nie-otwierania pliku)
        if ( m < 5 || m > 1000) {
            printf("Niepoprawna liczba kolumn (m): %i\n", m);
            help(argv[0]);
            exit(EXIT_FAILURE);
        }
        if ( n < 5 || n > 1000) {
            printf("Niepoprawna liczba wierszy (n): %i\n", n);
            help(argv[0]);
            exit(EXIT_FAILURE);
        }
        if ( p < 0 || p > 100) {
            printf("Niepoprawny %% zapelnienia (p): %i\n", p);
            help(argv[0]);
            exit(EXIT_FAILURE);
        }
        if ( d < 0 || d > 3) {
            printf("Niepoprawny kierunek mruwki: %i\n", d);
            help(argv[0]);
            exit(EXIT_FAILURE);
        }

        init_field(&field, m, n);
        random_obstacles(&field, p);
        // pozycja mruwy na środku planszy
        int ant_x = m / 2;
        int ant_y = n / 2;
        init_ant(&ant, ant_x, ant_y, d);
    } else
        get_from_file(&field, &ant, open_filename);

    if ( file_saved == 1 ) {
        for ( int i = 0; i < it_count; ++i ) {
            // filename_nriteracji
            char n_fname[1000];

            if ( file_saved == 1)
                sprintf(n_fname, "%s_%d", save_filename, i+1);

            FILE *out = file_saved == 1 ? fopen(n_fname, "w") : stdout;

            for (int i = 0; i < field.m; ++i) {
                for ( int j = 0; j < field.n; ++j)
                    fprintf(out, "%s", pleasant_character(&field, &ant, i, j));
                fprintf(out, "\n");
            }
            fprintf(out, "\n");

            move_ant(&ant, &field);

            fclose(out);
        }
    } else {
        FILE *out = stdout;
        for ( int i = 0; i < it_count; ++i ) {
            for (int i = 0; i < field.m; ++i) {
                for ( int j = 0; j < field.n; ++j)
                    fprintf(out, "%s", pleasant_character(&field, &ant, i, j));
                fprintf(out, "\n");
            }
            fprintf(out, "\n");

            move_ant(&ant, &field);
        }
    }

    return EXIT_SUCCESS;
}