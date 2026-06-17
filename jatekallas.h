// Schindler Dániel XTHQ5C
#ifndef JATEKALLAS_H
#define JATEKALLAS_H





typedef struct Gyoztes {
    char jatekos;
    struct Gyoztes* kov;
} Gyoztes;



typedef struct {
    int sor;
    int oszlop;
    char jatekos;
} Lepes;



typedef struct {
    char* jatekos1_nev;
    char* jatekos2_nev;

    Gyoztes* gyoztes_lista;
    Lepes* lepesek;
    int lepesek_szama;
} JatekAllapot;



int jeldb(int szel, int mag);

char ellenoriz_gyoztes(char** palya, int szel, int mag,
                       int nyeres_feltetel, int atlok);


void uj_gyoztes(JatekAllapot* allapot, char jatekos);

void ments_lepes(JatekAllapot* allapot, int sor, int oszlop, char jatekos);

int visszalep(JatekAllapot* allapot, char** palya);

void inicializal_lepesek(JatekAllapot* allapot);

void felszabadit_lepesek(JatekAllapot* allapot);


void ment_gyoztes(const char *fajlnev, JatekAllapot* allapot, char gyoztes);



void felszabadit_gyoztesek(JatekAllapot* allapot);





#endif
