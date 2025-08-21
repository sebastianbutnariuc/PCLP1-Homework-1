#include "functions.h"

int main(void) {
	int nr_task = 0;
	scanf("%d", &nr_task);

	int **arcade, n = 0, m = 0;

    scanf("%d %d", &n, &m);
    arcade = malloc(n * sizeof(int*));
    if (!arcade) {
        printf("eroare alocare\n");
        return -1;
    }
    for (int i = 0; i < n; i++) {
        arcade[i] = malloc(m * sizeof(int));
        if (!arcade[i]) {
            for (int j = 0; j < i; j++) {
                free(arcade[j]);
            }
            free(arcade);
	        printf("eroare alocare\n");
            return -1;
        }
        for (int j = 0; j < m; j++) {
            scanf("%d", &arcade[i][j]);
        }
    }

	switch (nr_task) {
		case 1: {
			int col = 0, nr_rot = 0;

			scanf("%d %d", &col, &nr_rot);
			spin(arcade, n, m, col, nr_rot);

     		for (int i = 0; i < n; i++) {
         		for (int j = 0; j < m; j++) {
             		printf("%d ", arcade[i][j]);
         		}
         	printf("\n");
     		}
		}
			break;
		
		case 2: {
			int scor = 0, nrComb = 0;

			bonusScor(arcade, m, &scor); 
    		nrComb += diagElem(arcade, m, &scor); 
    		nrComb += liniarElem(arcade, m, &scor); 
    
    		printf("%d\n%d\n", nrComb, scor);
		}
			break;
		
		case 3: {
			int col = 0, nr_rot = 0, T = 0, scor = 0;

			scanf("%d", &T);
			
    		for (int l = 0; l < T; l++)
   			{
        		scanf("%d %d", &col, &nr_rot);
        		spin(arcade, n, m, col, nr_rot);
        		bonusScor(arcade, m, &scor);
        		diagElem(arcade, m, &scor);
        		liniarElem(arcade, m, &scor);
    		}
			

    		printf("%d\n", scor);
		}
			break;
		
		case 4: {
			printf("%d\n", maxScor(arcade, n, m));
		}
			break;
		
		case 5: {
			printf("%d\n", maxRot(arcade, n, m));
		}	
			break;
		case 6: {
			int p = 0, pmin = INT_MAX, *dx, *dy, **T;

   			dx = malloc(4 * sizeof(int));
    		if (!dx) {
        		free(dx);
        		printf("eroare alocare\n");
				return -1;
    		}
    		dy = malloc(4 * sizeof(int));
    		if (!dy) {
        		free(dy);
        		printf("eroare alocare\n");
				return -1;
    		}

    		dx[0] = -1;
    		dx[1] = 0;
    		dx[2] = 1;
    		dx[3] = 0;

    		dy[0] = 0;
    		dy[1] = 1;
    		dy[2] = 0;
    		dy[3] = -1;

			int y = arcade[0][0];

    		for (int i = 0; i < n; i++) {
        		for (int j = 0; j < m; j++) {
					int x = arcade[i][j];
            		arcade[i][j] = abs(x - y);
        		}
    		}

    		T = malloc(n * sizeof(int*));
    		if (!T) {
        		free(T);
        		printf("eroare alocare\n");
				return -1;
    		}

    		for (int i = 0; i < n; i++) {
       		T[i] = malloc(m * sizeof(int));
        		if(!T[i]) {
            		for (int j = 0; j < i; j++) {
                		free(T[j]);
            		}
            		free(T);
            		printf("eroare alocare\n");
					return -1;
        		}
        		for (int j = 0; j < m; j++) {
            		T[i][j] = 0;
        		}
    		}

			if (3 * m < 61) {
        		labirint(arcade, 3, m, dx, dy, 0, 0, T, &p, &pmin);
    		}
    
   			printf("%d\n", pmin);

			for (int i = 0; i < n; i++) {
        		free(T[i]);
			}
    		free(T);
    		free(dx);
    		free(dy); 
		}
		break; 
		
	}
    
	for (int i = 0; i < n; i++) {
		free(arcade[i]);
	}
	free(arcade);
    return 0;
}
