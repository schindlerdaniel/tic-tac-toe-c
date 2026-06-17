// Schindler Dániel XTHQ5C
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "jatekallas.h"
#include "debugmalloc.h"


int jeldb(int szel, int mag) {


    if (szel * mag <= 9) {
        return 3;
    }


    int jeldarab = ceil(sqrt(szel * mag) / 2.0);

    if (jeldarab < 3) {
        jeldarab = 3;
    }

    return jeldarab;
}



char ellenoriz_gyoztes(char **palya, int szel, int mag, int nyeres_feltetel, int atlok) {


    for (int i = 0; i < mag; i++) {
        for (int j = 0; j <= szel - nyeres_feltetel; j++) {

            char kezdo = palya[i][j];
            if (kezdo != '.') {
                int db = 1;

                for (int k = 1; k < nyeres_feltetel; k++) {
                    if (palya[i][j+k] == kezdo)
                        db++;
                    else
                        break;
                }

                if (db == nyeres_feltetel)
                    return kezdo;
            }

        }
    }


    for (int j = 0; j < szel; j++) {
        for (int i = 0; i <= mag - nyeres_feltetel; i++) {

            char kezdo = palya[i][j];
            if (kezdo != '.') {
                int db = 1;

                for (int k = 1; k < nyeres_feltetel; k++) {
                    if (palya[i+k][j] == kezdo)
                        db++;
                    else
                        break;
                }

                if (db == nyeres_feltetel)
                    return kezdo;
            }

        }

    }


    if (atlok == 1) {


        for (int i = 0; i <= mag - nyeres_feltetel; i++) {
            for (int j = 0; j <= szel - nyeres_feltetel; j++) {

                char kezdo = palya[i][j];
                if (kezdo != '.') {
                    int db = 1;

                    for (int k = 1; k < nyeres_feltetel; k++) {
                        if (palya[i+k][j+k] == kezdo)
                            db++;
                        else
                            break;
                    }

                    if (db == nyeres_feltetel)
                        return kezdo;
                }
            }

        }


        for (int i = 0; i <= mag - nyeres_feltetel; i++) {
            for (int j = nyeres_feltetel - 1; j < szel; j++) {

                char kezdo = palya[i][j];
                if (kezdo != '.') {
                    int db = 1;

                    for (int k = 1; k < nyeres_feltetel; k++) {
                        if (palya[i + k][j - k] == kezdo)
                            db++;
                        else
                            break;
                    }

                    if (db == nyeres_feltetel)
                        return kezdo;
                }

            }
        }

    }

    return '\0';


}











