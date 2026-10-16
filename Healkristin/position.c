#include <stdio.h>
#include <stdlib.h>
#include "position.h"

/* Le o ficheiro .position para os vetores x[] e y[] (indexados por 1..C).
 * Devolve 1 se valido; 0 se o formato estiver errado, alguma coordenada
 * estiver fora de [1..Xmax]x[1..Ymax], algum id estiver fora de 1..C
 * (ou repetido) ou faltar alguma cidade. */
int read_positions(FILE *f_pos, int C, int x[], int y[]){
    int x_max, y_max;
    if(fscanf(f_pos, "%d %d", &x_max, &y_max) != 2) return 0;
    if(x_max < 1 || y_max < 1) return 0;

    int *seen = (int*)calloc(C+1, sizeof(int));
    int count = 0, city, cx, cy, n;
    int ok = 1;

    while((n = fscanf(f_pos, "%d %d %d", &city, &cx, &cy)) == 3){
        if(city < 1 || city > C || seen[city] ||
           cx < 1 || cx > x_max || cy < 1 || cy > y_max){
            ok = 0;
            break;
        }
        seen[city] = 1;
        x[city] = cx;
        y[city] = cy;
        count++;
    }

    if(ok && (n != EOF || count != C)) ok = 0;

    free(seen);
    return ok;
}
