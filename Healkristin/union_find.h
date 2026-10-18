#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <stdio.h>

int find(int i, int id[]);
void union_sets(int p, int q, int id[], int sz[], int *num_clusters);

#endif