#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int extension(char *filename, char *ext){
    char *dot = strrchr(filename, '.'); //strrchr procura a ultima aparicao de '.' no filename, o filename é um pointer que aponta para o inicio do filename e percorre-o
    if(!dot) return 0;
    return strcmp(dot, ext) == 0;

}

int main(int argc, char **argv){
    
    if(argc != 4){
        return 0; //se n tiver o .quest, .map e .position, não corre nem dá output
    }

    //verifica se as extensões estão corretas
    if(!extension(argv[1], ".quest")||!extension(argv[2], ".map")||!extension(argv[3], ".position")) return 0;

    FILE *f_quests = fopen(argv[1], "r");
    FILE *f_map = fopen(argv[2], "r");
    FILE *f_pos = fopen(argv[3], "r");

    if(f_quests==NULL || f_map==NULL || f_pos==NULL){
        if(f_quests) fclose(f_quests);
        if(f_map) fclose(f_map);
        if(f_pos) fclose(f_pos);
    }

    int C, L;
    if(fscanf(f_map, "%d %d",&C,&L) != 2){
        return 0;
    }

    int *id = (int*)malloc((C+1)*sizeof(int));
    int *sz = (int*)malloc((C+1)*sizeof(int));
    int num_clusters = C;

    for(int i=1; i<=C; i++){
        id[i]=i;
        sz[i]=1;
    }

}

typedef struct Node{
    int city_id;
    struct Node *next;
} Node;

int find(int i, int id[]){
    if(i==id[i]) return i;
    
    return id[i] = find(id[i], i); //Compression 
}

int union_sets(int p, int q, int id[], int sz[], int *num_clusters){
    int root_p = find(p, id);
    int root_q = find(q, id);

    if(root_p == root_q) return;

    if(sz[root_q]<sz[root_p]){
        id[root_p] = root_q;
        sz[root_q] += sz[root_p]; 
    } else {
        id[root_q] = root_p;
        sz[root_p] += sz[root_q]; 
    }
    (*num_clusters)--;

}
