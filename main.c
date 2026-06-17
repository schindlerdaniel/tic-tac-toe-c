// Schindler Dániel XTHQ5C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "megjelenites.h"
#include "jatekallas.h"
#include "debugmalloc.h"

int main()
{

    printf("\t\tTIC-TAC-TOE\n\n");


    JatekAllapot allapot;
    allapot.gyoztes_lista = NULL;
    allapot.lepesek = NULL;
    allapot.lepesek_szama = 0;
    allapot.jatekos1_nev = NULL;
    allapot.jatekos2_nev = NULL;



    printf("Elso jatekos neve (X): ");
    char nev1[100];
    scanf("%99s", nev1);

    printf("Masodik jatekos neve (O): ");
    char nev2[100];
    scanf("%99s", nev2);


    allapot.jatekos1_nev = malloc(strlen(nev1) + 1);
    allapot.jatekos2_nev = malloc(strlen(nev2) + 1);
    strcpy(allapot.jatekos1_nev, nev1);
    strcpy(allapot.jatekos2_nev, nev2);


    int szelesseg, magassag, atlok;
    beallitasok(&szelesseg, &magassag, &atlok);

    printf("A nyereshez %d jel kell egymas melle.\n", jeldb(szelesseg, magassag));



    char **palya = malloc(magassag * sizeof(char*));
    for (int i = 0; i < magassag; i++) {
        palya[i] = malloc(szelesseg * sizeof(char));
    }



    jatek_inditas(&allapot, palya, szelesseg, magassag, atlok, "results.txt");










    cleanup(&allapot, palya, magassag);

    return 0;
}










