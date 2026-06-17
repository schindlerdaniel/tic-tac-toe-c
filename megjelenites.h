// Schindler Dániel XTHQ5C
#ifndef MEGJELENITES_H
#define MEGJELENITES_H

#include "jatekallas.h"



void beallitasok(int *szelesseg, int *magassag, int *atlok);


void alaphelyzet(char **palya, int szel, int mag);

void palya_kiir(char **palya, int szel, int mag);



void palya_felszabadit(char **palya, int mag);


int jatekos_lepes(JatekAllapot* allapot, char **palya, int szel, int mag,
                  char *jatekos_most, int atlok);

void jatek_inditas(JatekAllapot* allapot, char **palya, int szel, int mag,
                   int atlok, const char *filename);



void felszabadit_lepesek(JatekAllapot* allapot);




#endif
