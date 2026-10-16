#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aux.h" 
#include "union_find.h"
#include "list.h"
#include "tasks.h"
#include "position.h"

int main(int argc, char **argv){
    
    if(argc != 4 || !check_extensions(argv)) return 0; 
    
    FILE *f_quests = fopen(argv[1], "r");
    FILE *f_map = fopen(argv[2], "r");
    FILE *f_pos = fopen(argv[3], "r");
    FILE *f_results = NULL;

    if(!f_quests || !f_map || !f_pos){
        close_files(f_map, f_pos, f_quests, f_results);
        return 0;
    }

    int C, L;
    if(fscanf(f_map, "%d %d", &C, &L) != 2 || C < 1){
        close_files(f_map, f_pos, f_quests, f_results);
        return 0;
    }

    int *x = (int*)calloc(C+1, sizeof(int));
    int *y = (int*)calloc(C+1, sizeof(int));

    /* Posicoes invalidas: terminar sem criar nenhum output */
    if(!read_positions(f_pos, C, x, y)){
        close_files(f_map, f_pos, f_quests, f_results);
        free(x); free(y);
        return 0;
    }

    f_results = create_results(argv[1]);
    if(!f_results){
        close_files(f_map, f_pos, f_quests, f_results);
        free(x); free(y);
        return 0;
    }

    int *id = (int*)malloc((C+1)*sizeof(int));
    int *sz = (int*)malloc((C+1)*sizeof(int));
    int num_clusters = C;

    for(int i=1; i<=C; i++){
        id[i] = i;
        sz[i] = 1;
    }

    int u, v;
    for(int i=1; i<=L; i++){
        fscanf(f_map, "%d %d", &u, &v);
        union_sets(u, v, id, sz, &num_clusters);
    }

    Node **head = (Node**)calloc(C+1, sizeof(Node*));
    Node **tail = (Node**)calloc(C+1, sizeof(Node*));   

    for(int i = 1; i<=C; i++){
        int root = find(i, id);
        tails(&head[root], &tail[root], i);
    }

    all_tasks(f_quests, f_results, C, num_clusters, id, head, x, y);
    
    close_files(f_map, f_pos, f_quests, f_results);
    
    free_lists(head, C);

    free(id); free(sz);
    free(head); free(tail);
    free(x); free(y);

    return 0;
}
