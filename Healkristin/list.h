#ifndef LIST_H
#define LIST_H

typedef struct Node {
    int city_id;
    struct Node *next;
} Node;

void tails(Node **head, Node **tail, int city);
void free_lists(Node **head, int C);
void build_lists(int C, int id[], Node **head, Node **tail);


#endif