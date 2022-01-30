#include <stdio.h>
#include "backend.h"

/****************************************
Implement Breadth-First Search on the graph constructed in "backend.c" and
use it in the find_path() below.

You can access functions and data structures constructed in "backend.c" via
"backend.h"
*****************************************/

//*********************Queue*************
#define POOL_SIZE 10*5757

int queue[POOL_SIZE];

int front=-1;
int rear=0;

void push(int x){
    if(rear>POOL_SIZE) return;
    queue[rear]=x;
    rear+=1;
}

int pop(){
    if(rear-front<=1) return;
    front+=1;
    return queue[front];
}

//***************************************


//*********************BFS***************

int parent[POOL_SIZE];

void BFS(int start){
    int j;
    int state[POOL_SIZE];

    for(j=0; j<POOL_SIZE; j++)
    state[j]=0;

    for(j=0; j<POOL_SIZE; j++)
    parent[j]=-1;

    state[start]=1;
    push(start);

    while(rear-front>1){
        int current = pop();
        struct node *v=NULL;
        for(v=adj_list[current]; v!=NULL; v=v->next){
            int i=v->index;
            if(state[i]==0){
                state[i]=1;
                parent[i]=current;
                push(i);
            }
        }
        state[current]=2;
    }
}

//***************************************

//**************shortest_path************

void shortest_path(int start, int goal){
    BFS(start);
    int g=goal;

    int j=0;
    int p[POOL_SIZE];
    for(j=0; j<POOL_SIZE; j++)
    p[j]=-1;



    int i=0;
    j=0;

    if(start-goal==0){
        printf("Sorry. There is no path from ");
        print_word(start);
        printf(" to ");
        print_word(goal);
        printf(".\n");
        return;
    }

    while(g!=start){
        p[i]=g;
        i++;

        if(parent[g]==-1){
            printf("Sorry. There is no path from ");
            print_word(start);
            printf(" to ");
            print_word(goal);
            printf(".\n");
            return;
        }

        g=parent[g];
    }

    p[i]=start;

    while(i>=0){
        printf("          %d ", j++);
        print_word(p[i]);
        printf("\n");
        i--;
    }
}


//***************************************

void find_path(char start[5], char goal[5])
{
    int i,j,k,l;

    i=search_index(start);
    j=search_index(goal);

    if (i<0) {
        printf("Sorry. ");
        print_five_chars(start);
        printf(" is not in the dicitonary.");
    }
    else if (j<0) {
        printf("Sorry. ");
        print_five_chars(goal);
        printf(" is not in the dicitonary.");
    }
    else {
        shortest_path(i, j);
    }
}
