#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

void spin(int **arcade, int n, int m, int col, int nr_rot);

int diagElem(int **a, int m, int *scor);

int liniarElemPart(int *v, int m, int *scor);

int liniarElem(int **a, int m, int *scor);

void bonusScor(int **a, int m, int *scor);

int maxScor(int **a, int n, int m);

int maxRot(int **a, int n, int m);

void labirint(int **adj, int n, int m, int *dx, int *dy, int i, int j, int **T, int *p, int *pmin);
