#include <stdlib.h>
#include "list.h"
#include "union_find.h"

void build_lists(int C, int id[], Node **head, Node **tail) {
    for(int i = 1; i <= C; i++) {
        int root = find(i, id);
        tails(&head[root], &tail[root], i);
    }
}

void tails(Node **head, Node **tail, int city){
    Node *new = (Node *)malloc(sizeof(Node));
    new->city_id = city;
    new->next = NULL;

    if(*head==NULL){
        *head = new;
        *tail = new;
    } else{
        (*tail)->next =new;
        *tail = new;
    }
    return;
}

void free_lists(Node **head, int C){

    for(int i=1; i<=C; i++){
        Node *current = head[i];
        while(current != NULL){
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
}