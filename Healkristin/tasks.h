#ifndef TASKS_H
#define TASKS_H

#include <stdio.h>
#include "list.h"

void task1(int num_clusters, FILE *f_results);
void task2(int C, int num_clusters, int id[], Node **head, FILE *f_results);
// guarda o q ja foi calculado pra nao repetir contas
// near[a]: cidade de fora mais perto de a (0 = ainda nao calculei, -2 = nao ha)
// dist[a]: distancia ao quadrado ate essa cidade
// t4[root]: resposta da task4 desse cluster (0 = ainda nao calculei)
typedef struct {
    int *near;
    long long *dist;
    int *t4;
} Cache;

Cache *cache_create(int C);
void cache_free(Cache *cache);

void task3(int C, int city, int id[], int x[], int y[], Cache *cache, FILE *f_results);
void task4(int C, int city, int id[], int x[], int y[], Node **head, Cache *cache, FILE *f_results);
int all_tasks(FILE *f_quests, FILE *f_results, int C, int num_clusters, int id[], Node **head, int x[], int y[], Cache *cache);

#endif