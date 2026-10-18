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

Cache *cache_create(int C){
    Cache *cache = (Cache*)malloc(sizeof(Cache));
    cache->near = (int*)calloc(C+1, sizeof(int));
    cache->dist = (long long*)calloc(C+1, sizeof(long long));
    cache->t4 = (int*)calloc(C+1, sizeof(int));
    return cache;
}

void cache_free(Cache *cache){
    free(cache->near);
    free(cache->dist);
    free(cache->t4);
    free(cache);
}

// calcula (so se ainda nao tiver na cache) a cidade de fora mais perta de a
// uso a distancia ao quadrado pq da a mesma coisa e assim n tenho de usar sqrt (e dizem no enunciado :P)
// empate fica com o menor id
static void nearest_outside(int C, int a, int id[], int x[], int y[], Cache *cache){
    if(cache->near[a] != 0) return;

    int root = find(a, id);
    int best = -2;
    long long best_d = 0;

    for(int j = 1; j <= C; j++){
        if(find(j, id) == root) continue;

        long long dx = x[j] - x[a];
        long long dy = y[j] - y[a];
        long long d = dx*dx + dy*dy;

        if(best == -2 || d < best_d){
            best = j;
            best_d = d;
        }
    }

    cache->near[a] = best;
    cache->dist[a] = best_d;
}

// cidade mais perto do city que nao ta no mm cluster
void task3(int C, int city, int id[], int x[], int y[], Cache *cache, FILE *f_results){
    if(city < 1 || city > C){
        fprintf(f_results, "Task3 %d -2\n\n", city);
        return;
    }

    nearest_outside(C, city, id, x, y, cache);

    fprintf(f_results, "Task3 %d %d\n\n", city, cache->near[city]);
}

// cidade de fora do cluster q ta mais perto do cluster todo (nao so da cidade dada)
// pra cada cidade do cluster uso a mais perta de fora (a mm da task3, vem da cache se ja tiver) e fico com a menor
// empate fica com o menor id da cidade de fora
// a resposta fica guardada por cluster pq e igual pra todas as cidades dele
void task4(int C, int city, int id[], int x[], int y[], Node **head, Cache *cache, FILE *f_results){
    if(city < 1 || city > C){
        fprintf(f_results, "Task4 %d -2\n\n", city);
        return;
    }

    int root = find(city, id);

    if(cache->t4[root] == 0){
        int best = -2;
        long long best_d = 0;

        for(Node *a = head[root]; a != NULL; a = a->next){
            int c = a->city_id;
            nearest_outside(C, c, id, x, y, cache);

            int j = cache->near[c];
            if(j == -2) break;   // so ha um cluster, nao ha mais nada a ver

            long long d = cache->dist[c];
            if(best == -2 || d < best_d || (d == best_d && j < best)){
                best = j;
                best_d = d;
            }
        }

        cache->t4[root] = best;
    }

    fprintf(f_results, "Task4 %d %d\n\n", city, cache->t4[root]);
}

// lê as tasks do .quests por ordem
// da 0 se a Task3 ou a Task4 vier sem numero (aquele return 0 q perguntei em civil)
int all_tasks(FILE *f_quests, FILE *f_results, int C, int num_clusters, int id[], Node **head, int x[], int y[], Cache *cache){

    char task_name[20];

    while(fscanf(f_quests, "%19s", task_name)==1){
        if(strcmp(task_name, "Task1") == 0){
            task1(num_clusters, f_results);
        
        } else if(strcmp(task_name, "Task2") == 0){
            task2(C, num_clusters, id, head, f_results);

        } else if(strcmp(task_name, "Task3") == 0){
            int city;
            if(fscanf(f_quests, "%d", &city) != 1) return 0;
            task3(C, city, id, x, y, cache, f_results);

        } else if(strcmp(task_name, "Task4") == 0){
            int city;
            if(fscanf(f_quests, "%d", &city) != 1) return 0;
            task4(C, city, id, x, y, head, cache, f_results);
        }
    
    }
    return 1;
}
