#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend.h"
#include "memory.h"

void print_name(struct record *);
void print_number(struct record *);
void print_data(char *, int);


// comparison function for records
int compare(char key[3], struct record *);

// data
struct record * data = NULL; // Initially NULL.


void init()
{
    init_pool();
}


void add(char *name, char *number)
{
    struct record *p = new_node();
    if(p==NULL)
    printf("Can't add.  The address book is full!\n");
    else{
        p->name[0]=name[0];
        p->name[1]=name[1];
        p->name[2]=name[2];
        p->number[0]=number[0];
        p->number[1]=number[1];
        p->number[2]=number[2];
        p->number[3]=number[3];
        p->next=NULL;
        if(data==NULL)
        data=p;
        else{
            int result=compare(name,data);

            //뒤쪽에 올 때
            if(result>0) {
                struct record *q=data;
                while(compare(name, q->next)>0) {
                    q=q->next;
                }
                p->next=q->next;
                q->next=p;
            }
            //동일할 때
            else if(result == 0) {
                p->next = data;
                data=p;
            }
            //앞쪽에 올 때
            else {
                p->next = data;
                data=p;
            }
        }
    }
}


void search(char name[3])
{
    struct record *r=data;
    int result;

    while(r!=NULL && (result=compare(name,r))!=0)
    r=r->next;
    if(r==NULL)
    printf("Couldn't find the name.\n");
    else {
        print_name(r);
        printf(" : ");
        print_number(r);
        printf(" was found.\n");
    }
}


void delete(char name[3])
{
    struct record *p=data;
    struct record *q=NULL;
    int result;

    while(p!=NULL && (result=compare(name,p))!=0){
        q=p;
        p=p->next;
    }

    //값이 없을 때
    if(p==NULL)
    printf("Couldn't find the name.\n");

    //첫노드일 때
    else if(p==data){
        struct record *del_link = data;
        data = data->next;
        free_node(del_link);
        printf("The name was deleted.\n");
    }

    //마지막 노드일 때
    else if(p->next == NULL){
        q->next = NULL;
        free_node(p);
        printf("The name was deleted.\n");
    }

    //중간 노드일 때
    else{
        q->next = p->next;
        free_node(p);
        printf("The name was deleted.\n");
    }
}


/* Just a wrapper of strncmp(), except for the case r is NULL.
Regard strncmp(a,b) as a-b, that is,
Negative value if key is less than r.
​0​ if key and r are equal.
Positive value if key is greater than r. */
int compare(char key[3], struct record *r)
{
    if (r==NULL)
    return -1;
    else
    return strncmp(key, r->name, 3);
}

// Prints ith name.
void print_name(struct record *r)
{
    print_data(r->name, 3);
}

// Prints ith number.
void print_number(struct record *r)
{
    print_data(r->number, 4);
}

void print_data(char * s, int n)
{
    int i;
    for (i=0; i<n; i++)
    putchar(s[i]);
}

void print_list()
{
    struct record *start = data;
    while(start != NULL){
        print_name(start);
        printf(" : ");
        print_number(start);
        printf("\n");
        start = start->next;
    }
}
