#include "functions.h"

void spin(int **arcade, int n, int m, int col, int nr_rot) {
    int *cp_col;
    //copiez coloana careia i se aplica operatia intr-un vector
    cp_col = malloc(n * sizeof(int));
    if(!cp_col) {
        printf("eroare alocare\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        cp_col[i] = arcade[i][col];
    }

    for (int i = 0; i < nr_rot % n; i++) {
        //copiez elementele vectorului (fara primul) defazat cu un element in coloana
        for (int j = 0; j < n - 1; j++) {
            arcade[j + 1][col] = cp_col[j]; 
        }
        //primul element din coloana devine ultimul din vector
        arcade[0][col] = cp_col[n - 1];
        //copiez coloana noua in vector
        for (int j = 0; j < n; j++) {
            cp_col[j] = arcade[j][col];
        }
    } 
    free (cp_col);
}

int diagElem(int **a, int m, int *scor) {
    //cate diagonale principale sunt
    //pe x_poz[i + 1] se noteaza elementul de la mijlocul diagonalei pe coloana corespunzatoare
    int nrDiag = 0, *x_poz, sevenDiagSec = 0, nrX = 0; 
    //initial se calculeaza nrDiag = nrDiagPrinc

    x_poz = malloc (m * sizeof(int));
    if(!x_poz) {
        printf("eroare alocare\n");
        return -1;
    }

    for (int i = 0; i < m - 2; i++) {
        if (a[0][i] == a[1][i + 1] && a[1][i + 1] == a[2][i + 2]) {
            nrDiag++;
            x_poz[i + 1] = a[1][i + 1];   
        } else {
            x_poz[i + 1] = 0;
        }
    }

    for (int i = 0; i < m - 2; i++) {
        if (a[0][i + 2] == a[1][i + 1] && a[1][i + 1] == a[2][i]) {
            if (!x_poz[i + 1]) {
                nrDiag++;
                if (a[1][i + 1] == 7) {
                    sevenDiagSec++;
                }
            } else if (x_poz[i + 1] != 7) {
                *scor += 21; 
                x_poz[i + 1] = 0;
                nrX++;
            } else {
                *scor += 42; 
                x_poz[i + 1] = 0;
                nrX++;
            }
        }
    }
    
    *scor += (nrDiag + sevenDiagSec - nrX) * 7; 
   
    for (int i = 1; i < m - 1; i++) {
        if (x_poz[i] == 7) {
            *scor += 7; 
        }
    }
    
    free(x_poz);
    return nrDiag;
}    

int liniarElemPart(int *v, int m, int *scor) {
    int length1 = 1, lengthMax = 1, temp = 0, elem = 0;

    temp = v[0];
    for(int i = 1; i < m; i++) {
        if (v[i] == temp) {
            length1++;
        } else {
            temp = v[i];
            length1 = 1;
        }
        if (length1 > lengthMax) {
                lengthMax = length1;
                elem = temp;
            }
    }
  
    if (lengthMax >= 3) {
        *scor += lengthMax;
        if (elem == 7) {
            *scor += lengthMax;
        }
        return 1;
    }
    return 0;
}

int liniarElem(int **a, int m, int *scor) {
    int nrComb = 0;

    for (int i = 0; i < 3; i++) {
        nrComb += liniarElemPart(a[i], m, scor);
    }

    return nrComb;
}

void bonusScor(int **a, int m, int *scor) {
    int nrSimb = 0, *v;
    v = malloc(10 * sizeof(int));
    if (!v) {
        printf("eroare alocare\n");
        return;
    }
    for(int i = 0; i < 10; i++) {
        v[i] = 0;
    }

    for (int i = 0; i < 3 && nrSimb <= 4; i++) {
        for (int j = 0; j < m && nrSimb <= 4; j++) {
            if(!v[a[i][j]]) {
                v[a[i][j]] = 1;
                nrSimb++;
            }
        }
    }

    if(nrSimb <= 2) {
        *scor += 100;
    } else if (nrSimb <= 4) {
        *scor += 15;
    }
    free(v);
}

int maxScor(int **a, int n, int m) {
    int scor = 0, save = 0, scorMax = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int nr = 0; nr < 10; nr++) {
                if (a[i][j] != nr) {
                    scor = 0;
                    save = a[i][j];
                    a[i][j] = nr;
                    bonusScor(a, m, &scor);
                    diagElem(a, m, &scor);
                    liniarElem(a, m, &scor);
                    a[i][j] = save;
                    if (scor > scorMax) {
                        scorMax = scor;
                    }
                } else {
                    continue;
                }
            }
        }
    }

    return scorMax;
}

int maxRot(int **a, int n, int m) {
    int scor = 0, scorMax = 0;

    for (int i = 0; i < m - 1; i++) {
        for (int j = i + 1; j < m; j++) {
            scor = 0;
            bonusScor(a, m, &scor);
            diagElem(a, m, &scor);
            liniarElem(a, m, &scor);
            if (scor > scorMax) {
                scorMax = scor;
            }
            for (int ri = 1; ri < n; ri++) {
                spin(a, n, m, i, 1);
                scor = 0;
                bonusScor(a, m, &scor);
                diagElem(a, m, &scor);
                liniarElem(a, m, &scor);
                if (scor > scorMax) {
                    scorMax = scor;
                }
                for (int rj = 1; rj < n; rj++) {
                    scor = 0;
                    spin(a, n, m, j, 1);
                    bonusScor(a, m, &scor);
                    diagElem(a, m, &scor);
                    liniarElem(a, m, &scor);
                    if (scor > scorMax) {
                        scorMax = scor;
                    }
                }
                spin(a, n, m, j, 1);
            }
            spin(a, n, m, i, 1);
        }
    }

    return scorMax;
}

void labirint(int **adj, int n, int m, int *dx, int *dy, int i, int j, int **T, int *p, int *pmin) {
    if (*p > *pmin) {
        return;
    }

    int ii = 0, jj = 0;
    const int dir = 4;

    if (i == (n - 1) && j == (m - 1)) {
        //afisare(T, n ,m);
        // printf("%d\n\n", *p);
        *p += adj[i][j];
        if (*p < *pmin) {
            *pmin = *p;
            //printf("\n%d\n", *p);
        }
        *p -= adj[i][j];
        return;
    } 
        for (int k = 0; k < dir; k++) {
            ii = i + dx[k];
            jj = j + dy[k];
            if(ii >= 0 && ii < n && jj >= 0 && jj < m && !T[ii][jj]) {
                T[ii][jj] = 1;
                *p += adj[i][j];
                labirint(adj, n, m, dx, dy, ii, jj, T, p, pmin);
                *p -= adj[i][j];
                T[ii][jj] = 0;
            }
            
        }
        
    
}
