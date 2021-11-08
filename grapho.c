#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct node {
    int qn;
    struct node **connexions;
    
    int value;
};

struct node* new_node(struct node *ptr, int value)
{
    ptr = (struct node*) malloc(sizeof(struct node));
    ptr->connexions = NULL;
    ptr->qn = 0;
    ptr->value = value;
    return ptr;
}

void connect(struct node *origin, struct node *destination)
{
    struct node **tmp_connexions;
    
    if(origin != NULL && destination != NULL && destination != origin)
    {
        tmp_connexions = (struct node**) malloc(sizeof(struct node) * (origin->qn + 1));
        for(int i = 0; i < origin->qn; i++){
            if(destination == origin->connexions[i]){ return; }
            tmp_connexions[i] = origin->connexions[i];
        }
        free(origin->connexions);
        tmp_connexions[origin->qn] = destination;
        origin->connexions = tmp_connexions;
        origin->qn++;
    }
}

void disconnect(struct node *origin, struct node *destination)
{
    struct node **tmp_connexions;
    
    if(origin != NULL && destination != NULL && destination != origin)
    {
        tmp_connexions = (struct node**) malloc(sizeof(struct node) * (origin->qn - 1));
        int j = 0;
        for(int i = 0; i < origin->qn; i++){
            if(destination != origin->connexions[i]){
                tmp_connexions[j++] = origin->connexions[i];
            }
        }
        free(origin->connexions);
        origin->connexions = tmp_connexions;
        origin->qn--;
    }
}


// ------------ PRINTING GRAPHO --------------
short is_node_in_list(struct node *ptr, struct node **list, int size_of_list){
    for(int i = 0; i < size_of_list; i++){ if(list[i] == ptr) return 1; }
    return 0;
}

void print_ways(struct node *n, struct node **traveled, int qtraveled, int deph)
{
    if(traveled == NULL){
        qtraveled = 1;
        traveled = (struct node**) malloc(sizeof(struct node) * (n->qn + 1));
        traveled[0] = n;
        for(int j = 0; j < deph; j++){ printf("\t"); }
        deph++;
        printf("[%p] %d\n", n, n->value);
    }else{
        struct node** tmpTraveled = malloc(sizeof(struct node) * (qtraveled + n->qn));
        for(int i = 0; i < qtraveled; i++){
            tmpTraveled[i] = traveled[i];
        }
        // free(traveled);
        traveled = tmpTraveled;
    }
    
    for(int i = 0; i < n->qn; i++){
        if(is_node_in_list(n->connexions[i], traveled, qtraveled) == 0){
            traveled[qtraveled++] = n->connexions[i];
            for(int j = 0; j < deph; j++){ printf("\t"); }
            printf(" -> [%p] %d\n", n->connexions[i], n->connexions[i]->value);
            print_ways(n->connexions[i], traveled, qtraveled, deph + 1);
        }else{
            for(int j = 0; j < deph; j++){ printf("\t"); }
            printf("<-> [%p] %d ...\n", n->connexions[i], n->connexions[i]->value);
        }
    }
}

int main()
{
    struct node *grapho;
    
    grapho = new_node(NULL, 5);
    
    connect(grapho, new_node(NULL, 3));
    connect(grapho, new_node(NULL, 2));
    connect(grapho, new_node(NULL, 6));
    connect(grapho->connexions[1], new_node(NULL, 7));
    connect(grapho->connexions[1]->connexions[0], grapho);
    connect(grapho->connexions[2], grapho);
    connect(grapho->connexions[0], grapho->connexions[1]->connexions[0]);
    
    disconnect(grapho->connexions[1], grapho->connexions[1]->connexions[0]);
    print_ways(grapho->connexions[0], NULL, 0, 0);
    return 0;
};
