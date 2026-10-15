#include <stdio.h>
#include "union_find.h"

int find(int i, int id[]){
    if(i==id[i]) return i;
    
    return id[i] = find(id[i], id); //Compression 
}

void union_sets(int p, int q, int id[], int sz[], int *num_clusters){
    int root_p = find(p, id);
    int root_q = find(q, id);

    if(root_p == root_q) return;

    if(sz[root_q]<sz[root_p]){
        id[root_q] = root_p;
        sz[root_p] += sz[root_q]; 
    } else {
        id[root_p] = root_q;
        sz[root_q] += sz[root_p]; 
    }
    (*num_clusters)--;

}