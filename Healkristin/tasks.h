#ifndef TASKS_H
#define TASKS_H

#include <stdio.h>
#include "list.h"

void task1(int num_clusters, FILE *f_results);
void task2(int C, int num_clusters, int id[], Node **head, FILE *f_results);
void all_tasks(FILE *f_quests, FILE *f_results, int C, int num_clusters, int id[], Node **head);

#endif