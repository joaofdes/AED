#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <stdio.h>

int find(int i, int id[]);
void union_sets(int p, int q, int id[], int sz[], int *num_clusters);
void init_union_find(int C, int id[], int sz[]);
void process_map_connections(FILE *f_map, int L, int id[], int sz[], int *num_clusters);

#endif