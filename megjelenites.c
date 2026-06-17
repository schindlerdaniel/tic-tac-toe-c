// Schindler Dániel XTHQ5C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "megjelenites.h"
#include "jatekallas.h"
#include "debugmalloc.h"



void beallitasok(int *szelesseg, int *magassag, int *atlok) {

    printf("Szelesseg: ");
    scanf("%d", szelesseg);

    printf("Magassag: ");
    scanf("%d", magassag);

    printf("Atlokkal lehet nyerni? (1: igen, 0: nem): ");
    scanf("%d", atlok);

}


void alaphelyzet(char **palya, int szel, int mag){

    for (int i = 0; i < mag; i++) {
        for (int j = 0; j < szel; j++) {
            palya[i][j] = '.';
        }
    }

}


void palya_kiir(char **palya, int szel, int mag){

    printf("    ");
    for (int i = 0; i < szel; i++){
        printf("  %c ", 'A' + i);

    }

    printf("\n");

    for (int j = 0; j < mag; j++){
        printf("    ");
        for(int k = 0; k < szel; k++){
            printf("+---");

        }

        printf("+ \n");

        printf(" %d ", j+1);
        for (int l = 0; l < szel; l++){
            printf(" | %c", palya[j][l]);
        }

        printf(" |\n");
    }

    printf("    ");
    for(int m = 0; m < szel; m++){
        printf("+---");
    }

    printf("+ \n");


}


void palya_felszabadit(char** palya, int mag) {

    for (int i = 0; i < mag; i++) {
        free(palya[i]);
    }

    free(palya);

}





void uj_gyoztes(JatekAllapot* allapot, char jatekos) {

    Gyoztes* uj = malloc(sizeof(Gyoztes));
    if (uj == NULL) {
        perror("Memoriafoglalasi hiba");
        exit(1);

    }

    uj->jatekos = jatekos;
    uj->kov = allapot->gyoztes_lista;
    allapot->gyoztes_lista = uj;

}



void inicializal_lepesek(JatekAllapot* allapot){

    allapot->lepesek = NULL;
    allapot->lepesek_szama = 0;

}


void felszabadit_lepesek(JatekAllapot* allapot){

    free(allapot->lepesek);
    allapot->lepesek = NULL;
    allapot->lepesek_szama = 0;

}


void ments_lepes(JatekAllapot* allapot, int sor, int oszlop, char jatekos) {

    Lepes* uj_lepesek = realloc(allapot->lepesek, (allapot->lepesek_szama + 1) * sizeof(Lepes));

    if (uj_lepesek == NULL) {
        perror("Memoriafoglalasi hiba");
        exit(1);

    }


    allapot->lepesek = uj_lepesek;
    allapot->lepesek[allapot->lepesek_szama].sor = sor;
    allapot->lepesek[allapot->lepesek_szama].oszlop = oszlop;
    allapot->lepesek[allapot->lepesek_szama].jatekos = jatekos;
    allapot->lepesek_szama++;


}




int visszalep(JatekAllapot* allapot, char** palya) {

    if (allapot->lepesek_szama == 0) {
        printf("Nincs tovabbi visszalepesi lehetoseg!\n");
        return 0;

    }


    Lepes utolso = allapot->lepesek[allapot->lepesek_szama - 1];
    palya[utolso.sor][utolso.oszlop] = '.';
    allapot->lepesek_szama--;


    if (allapot->lepesek_szama == 0) {
        free(allapot->lepesek);
        allapot->lepesek = NULL;

    }
    else {
        Lepes* uj = realloc(allapot->lepesek, allapot->lepesek_szama * sizeof(Lepes));
        if (uj != NULL) {
            allapot->lepesek = uj;

        }

    }

    printf("Visszalepes megtortent: %c mezobol (%d, %d).\n", utolso.jatekos, utolso.sor + 1, utolso.oszlop + 1);

    return 1;


}



int jatekos_lepes(JatekAllapot* allapot, char **palya, int szel, int mag, char *jatekos_most, int atlok) {

    int sor;
    char oszlop;
    int nyeres_feltetel = jeldb(szel, mag);

    printf("Adjon meg egy mezot '%c' (pl.: A3), vagy 'u' a visszalepeshez: ", *jatekos_most);
    scanf(" %c", &oszlop);

    if (oszlop == 'U' || oszlop == 'u') {
        if (visszalep(allapot, palya)) {
            if (*jatekos_most == 'X') {
                *jatekos_most = 'O';
            }
            else {
                *jatekos_most = 'X';

            }
        }

        return 0;
    }


    scanf("%d", &sor);
    printf("\n");

    int oszlopi = oszlop - 'A';
    int sori = sor - 1;

    if (oszlopi < 0 || oszlopi >= szel || sor < 1 || sor > mag) {
        printf("Ervenytelen mezo.\n");
        return 0;

    }

    if (palya[sori][oszlopi] != '.') {
        printf("A mezo mar foglalt.\n");
        return 0;

    }

    palya[sori][oszlopi] = *jatekos_most;

    ments_lepes(allapot, sori, oszlopi, *jatekos_most);

    char gyoztes = ellenoriz_gyoztes(palya, szel, mag, nyeres_feltetel, atlok);
    if (gyoztes == 'X' || gyoztes == 'O') {
        palya_kiir(palya, szel, mag);
        printf("\n\nGyoztes: %c\n", gyoztes);
        uj_gyoztes(allapot, gyoztes);
        return 1;
    }

    if (*jatekos_most == 'X'){
        *jatekos_most = 'O';
    }
    else{
        *jatekos_most = 'X';
    }

    return 0;

}




void ment_gyoztes(const char *fajlnev, JatekAllapot* allapot, char gyoztes)
{
    FILE *fp = fopen(fajlnev, "a");
    if (fp == NULL) {
        perror("Fájl megnyitása sikertelen");
        return;

    }

    if (gyoztes == 'X'){
        fprintf(fp, "%s nyert\n", allapot->jatekos1_nev);
    }
    else {
        fprintf(fp, "%s nyert\n", allapot->jatekos2_nev);
    }

    fclose(fp);

}




void felszabadit_gyoztesek(JatekAllapot* allapot) {

    Gyoztes *aktualis = allapot->gyoztes_lista;

    while (aktualis != NULL) {
        Gyoztes *kov = aktualis->kov;
        free(aktualis);
        aktualis = kov;
    }

    allapot->gyoztes_lista = NULL;

}


void jatek_inditas(JatekAllapot* allapot, char **palya, int szel, int mag, int atlok, const char *filename) {
    int uj_jatek = 1;

    while (uj_jatek) {


        felszabadit_lepesek(allapot);
        inicializal_lepesek(allapot);


        alaphelyzet(palya, szel, mag);
        palya_kiir(palya, szel, mag);

        char jatekos_most = 'X';
        int vege = 0;

        while (!vege) {
            vege = jatekos_lepes(allapot, palya, szel, mag, &jatekos_most, atlok);
            palya_kiir(palya, szel, mag);

        }


        char gyoztes = jatekos_most;

        if (gyoztes == 'X'){
            printf("\nA jatek veget ert! %s a nyertes.\n", allapot->jatekos1_nev);
        }
        else{
            printf("\nA jatek veget ert! %s a nyertes.\n", allapot->jatekos2_nev);
        }

        uj_gyoztes(allapot, gyoztes);


        if (filename != NULL) {
            ment_gyoztes(filename, allapot, gyoztes);
        }

        printf("\nSzeretne uj jatekot inditani? (1 = igen, 0 = nem): ");
        scanf("%d", &uj_jatek);

    }

}


void cleanup(JatekAllapot* allapot, char **palya, int mag) {

    felszabadit_gyoztesek(allapot);
    felszabadit_lepesek(allapot);
    palya_felszabadit(palya, mag);
    free(allapot->jatekos1_nev);
    free(allapot->jatekos2_nev);
    allapot->jatekos1_nev = NULL;
    allapot->jatekos2_nev = NULL;


}











