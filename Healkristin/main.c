#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aux.h" 
#include "union_find.h"
#include "list.h"
#include "tasks.h"

int main(int argc, char **argv){
    
    if(argc != 4 || !check_extensions(argv)) return 0; 
    
    FILE *f_quests = fopen(argv[1], "r");
    FILE *f_map = fopen(argv[2], "r");
    FILE *f_pos = fopen(argv[3], "r");
    FILE *f_results = create_results(argv[1]);

    if(!f_quests || !f_map || !f_pos || !f_results){
        close_files(f_map, f_pos, f_quests, f_results);
    }

    int C, L;
    if(fscanf(f_map, "%d %d", &C, &L) != 2) return 0;

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


    char results_name[100];
    strcpy(results_name, argv[1]);
    char *dot_ext = strrchr(results_name, '.');
    if(dot_ext) strcpy(dot_ext, ".results");


    Node **head = (Node**)calloc(C+1, sizeof(Node*));
    Node **tail = (Node**)calloc(C+1, sizeof(Node*));   

    for(int i = 1; i<=C; i++){
        int root = find(i, id);
        tails(&head[root], &tail[root], i);
    }


    char task_name[20];
    while(fscanf(f_quests, "%s", task_name) == 1){
        if(strcmp(task_name, "Task1") == 0){
            task1(num_clusters, f_results);
        } else if(strcmp(task_name, "Task2") == 0){
            task2(C, num_clusters, id, head, f_results);
        }
    }
    
    fclose(f_quests);
    fclose(f_map);
    fclose(f_pos);
    fclose(f_results);
    
    free_lists(head, C);

    free(id); free(sz);
    free(head); free(tail);

    return 0;
}
