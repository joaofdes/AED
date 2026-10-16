#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tasks.h"
#include "union_find.h"

void task1(int num_clusters, FILE *f_results) {
    fprintf(f_results, "Task1 %d\n\n", num_clusters);
}

void task2(int C, int num_clusters,int id[], Node **head, FILE *f_results){
    fprintf(f_results, "Task2 %d\n", num_clusters);
    int *printed = (int*)calloc(C+1, sizeof(int));

    for(int i = 1; i<=C; i++){
        int root = find(i, id);
    
        if(!printed[root] && head[root] != NULL){
            fprintf(f_results, "Cluster:");
        
            Node *current = head[root];
            while(current != NULL){
                fprintf(f_results, " %d", current->city_id);
                current = current->next;
            }
            fprintf(f_results, "\n");
        }
        printed[root] = 1;
    }

    fprintf(f_results, "\n");
    free(printed);
}

// cidade mais perto de city q nao ta no mesmo cluster
// uso a distancia ao quadrado pq da a mesma ordem e evita sqrt
// empate fica com o menor id pq so troco quando e estritamente menor
void task3(int C, int city, int id[], int x[], int y[], FILE *f_results){
    if(city < 1 || city > C){
        fprintf(f_results, "Task3 %d -2\n\n", city);
        return;
    }

    int root = find(city, id);
    int best = -2;
    long long best_d = 0;

    for(int j = 1; j <= C; j++){
        if(find(j, id) == root) continue;

        long long dx = x[j] - x[city];
        long long dy = y[j] - y[city];
        long long d = dx*dx + dy*dy;

        if(best == -2 || d < best_d){
            best = j;
            best_d = d;
        }
    }

    fprintf(f_results, "Task3 %d %d\n\n", city, best);
}

// vai lendo as tasks do .quests por ordem
// da 0 se a Task3 vier sem numero
int all_tasks(FILE *f_quests, FILE *f_results, int C, int num_clusters, int id[], Node **head, int x[], int y[]){

    char task_name[20];

    while(fscanf(f_quests, "%19s", task_name)==1){
        if(strcmp(task_name, "Task1") == 0){
            task1(num_clusters, f_results);
        
        } else if(strcmp(task_name, "Task2") == 0){
            task2(C, num_clusters, id, head, f_results);

        } else if(strcmp(task_name, "Task3") == 0){
            int city;
            if(fscanf(f_quests, "%d", &city) != 1) return 0;
            task3(C, city, id, x, y, f_results);
        }
    
    }
    return 1;
}
