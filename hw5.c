#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend-bst.h"

#define POOL_SIZE 10

// record structure
struct record {
    char name[3];
    char number[4];
    struct record * left;
    struct record * right;
};

void print_name(struct record *);
void print_number(struct record *);

// pool of memory
static struct record pool[POOL_SIZE]; // static because pool is strictly private
struct record * top=pool;  // a pointer variable for pool stack top.

// comparison function for records
int compare(char key[3], struct record *);

// data
struct record * data = NULL; // Initially NULL.


void init_pool() // Initialize the pool; Use right instead of next!!!
{
    int i;
    struct record *r=pool;
    struct record *s;

    pool[POOL_SIZE-1].right=NULL;

    for(i=1;i<POOL_SIZE;i++) {
        s=r++;
        s->right=r;
    }
}

// Get a node from the pool. Returns NULL if pool is empty.
// When calling new_node(), make sure to check if it is NULL.
struct record * new_node()
{
    struct record *r;

    if(top==NULL)
    return NULL;

    r=top;
    top=r->right;  // Again, right instead of next.
    return r;
}

// Push a node to the pool.
void free_node(struct record *r)
{
    r->right=top;  // Again, right instead of next.
    top=r;
}


/***********************
Address Book by binary search tree
**************************/

void search(char name[3])
{
    struct record *r; // Pointer to record being compared.
    //data or left/right field of a node.
    int result;
    r=data;

    while (r!=NULL) {
        if ((result=compare(name,r))<0)
        r=r->left;
        else if (result==0) {
            print_name(r);
            printf(" : ");
            print_number(r);
            printf(" was found.\n");
            return;
        }
        else // case >0
        r=r->right;
    }
    printf("Couldn't find the name.\n");
}


void add(char *name, char *number)
{
    struct record *q = new_node();
    struct record *p;
    struct record *r;
    if(q==NULL)
    printf("Can't add.  The pool is empty!\n");
    else{
        p=data;
        while(p!=NULL){
            int result1 = compare(name, p);
            //입력된 것이 같거나 작으면 왼쪽으로
            if(result1<=0){
                r=p;
                p=p->left;
            }
            //입력된 것이 크면 오른쪽으로
            else{
                r=p;
                p=p->right;
            }
        }
        q->name[0]=name[0];
        q->name[1]=name[1];
        q->name[2]=name[2];
        q->number[0]=number[0];
        q->number[1]=number[1];
        q->number[2]=number[2];
        q->number[3]=number[3];
        q->left = NULL;
        q->right = NULL;

        if(data==NULL){
            data=q;
            printf("The name was successfully added!\n");
        }
        else{
            int result2 = compare(name, r);
            //입력된 것이 같거나 작으면 왼쪽
            if(result2<=0){
                r->left = q;
                printf("The name was successfully added!\n");
            }
            //입력된 것이 크면 오른쪽
            else{
                r->right = q;
                printf("The name was successfully added!\n");
            }
        }
    }
}


// The most complicated.
void delete(char name[3])
{
    struct record *p = data;
    struct record *q = NULL; //부모노드
    struct record *r = NULL; //자식노드
    struct record *s = NULL; //successor
    struct record *sub =NULL; //successor 보조

    while (p!=NULL) {
        int result = compare(name, p);
        if (result<0){
            q=p;
            p=p->left;
        }
        else if (result>0){
            q=p;
            p=p->right;
        }
        else{
            //자식 노드가 없을 경우
            if((p->left == NULL) && (p->right == NULL)){
                //대가리가 아닌 경우
                if(q!=NULL){
                    if(q->left == p)
                    q->left = NULL;
                    else
                    q->right = NULL;
                }
                //대가리인 경우
                else
                data = NULL;
                free_node(p);
                printf("The name was deleted.\n");
            }

            //자식 노드가 한 개일 경우
            else if((p->left == NULL) || (p->right == NULL)){
                if(p->left == NULL)
                r=p->right;
                else
                r=p->left;
                //대가리가 아닌 경우
                if(q!=NULL){
                    if(q->left == p){
                        q->left = r;
                    }
                    else
                    q->right = r;
                }
                //대가리인 경우
                else
                data = r;
                free_node(p);
                printf("The name was deleted.\n");
            }
            //자식 노드가 두 개일 경우. 대가리 여부는 관계없음
            else{
                r = p->right; //자식은 내 오른쪽
                s = p->right;
                while(s->left != NULL){
                    sub=s;
                    s = s->left;
                }
                if(r->left != NULL)
                sub->left = s->right;
                else
                p->right = s->right;

                p->name[0]=s->name[0];
                p->name[1]=s->name[1];
                p->name[2]=s->name[2];
                p->number[0]=s->number[0];
                p->number[1]=s->number[1];
                p->number[2]=s->number[2];
                p->number[3]=s->number[3];
                free_node(s);
                printf("The name was deleted.\n");
            }
            return;
        }
    }
    printf("Couldn't find the name.\n");
}


/* Just a wrapper of strncmp().
Regard strncmp(a,b) as a-b.
Negative value if key is less than r.
​0​ if key and r are equal.
Positive value if key is greater than r. */
int compare(char key[3], struct record *r)
{
    return strncmp(key, r->name, 3);
}


void print_data(char * s, int n)
{
    int i;
    for (i=0; i<n; i++)
    putchar(s[i]);
}

void print_name(struct record *r)
{
    print_data(r->name, 3);
}

void print_number(struct record *r)
{
    print_data(r->number, 4);
}

void print_inorder(struct record *t)
{
    if(t!=NULL){
        print_inorder(t->left);
        print_name(t);
        printf(" : ");
        print_number(t);
        printf("\n");
        print_inorder(t->right);
    }
}

void print_list()
{
    print_inorder(data);
}


// returns the height of the BST.
int height(struct record *t)
{
    if(t==NULL)
    return -1;
    else{
        int rnum;
        int lnum;
        rnum = height(t->right) +1;
        lnum = height(t->left) +1;

        return rnum>=lnum ? rnum:lnum;
    }
}

void print_height()
{
    printf("The Address Book BST's height is %d.\n", height(data));
}
