#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int extension(char *filename, char *ext){
    char *dot = strrchr(filename, '.'); //strrchr procura a ultima aparicao de '.' no filename, o filename é um pointer que aponta para o inicio do filename e percorre-o
    if(!dot) return 0;
    return strcmp(dot, ext) == 0;

}


typedef struct Node{
    int city_id;
    struct Node *next;
} Node;

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

void tails(Node **head, Node **tail, int city){
    Node *new = (Node *)malloc(sizeof(Node));
    new->city_id = city;
    new->next = NULL;

    if(*head==NULL){
        *head = new;
        *tail = new;
    } else{
        (*tail)->next = new;
        *tail = new;
    }
    return;
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
        return 0;
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

    int u, v;
    for(int i=1; i<=L; i++){
        fscanf(f_map,"%d %d", &u, &v);
        union_sets(u, v, id, sz, &num_clusters);
    }


    Node **head = (Node**)calloc(C+1, sizeof(Node*));
    Node **tail = (Node**)calloc(C+1, sizeof(Node*));

    for(int i = 1; i<=C; i++){
        int root = find(i, id);
        tails(&head[root],&tail[root],i);
    }

    fclose(f_quests);
    fclose(f_map);
    fclose(f_pos);

    for(int i=1; i<=C; i++){
        Node *current = head[i];
        while(current != NULL){
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }

    free(id);
    free(sz);
    free(head);
    free(tail);

}
