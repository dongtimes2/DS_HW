#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define WORDS_NUMBER 5757
#define NO_ERROR "All the words were successfully read!\n"
#define WELCOME_MESSAGE "Welcome to Search!\n"
#define COMMAND_PROMPT ">"

void init();
void sort();
void print_result(int n);
int prompt_name(char *, char*);
int search(char*);
int compare(char*, int);

char buffer[WORDS_NUMBER];
char data[WORDS_NUMBER][5];



int main(void){

    char key[5];

    init();

    printf(WELCOME_MESSAGE);

    while(1){
        restart:
        if(prompt_name(COMMAND_PROMPT, key)!=0)
        goto restart;
        printf("%d\n", search(key));
    }

    return 0;
}



void init(){
    FILE *words = fopen("words.dat", "r");
    if(words==NULL){}
    else{
        printf(NO_ERROR);
    }

    int i,j;

    //쓸대가리없는 앞부분 날리기
    for(i=0; i<4; i++){
        fgets(buffer, 100, words);
    }

    //진또배기들 저장하기
    for (i = 0; i < WORDS_NUMBER; i++){
        fgets(buffer, 100, words);
        data[i][0] = buffer[0];
        data[i][1] = buffer[1];
        data[i][2] = buffer[2];
        data[i][3] = buffer[3];
        data[i][4] = buffer[4];
    }
    fclose(words);
}

int prompt_name(char *s, char *p){
    char *q;
    char c;

    while (1) {
        printf("%s ", s);
        fflush(stdout);
        q=p;
        while (1) {
            c=getchar();
            if (c==EOF)
            exit(0);      // Should let exit() take care of the sudden EOF.
            if (c=='\n')
            break;
            if (q<p+5)
            *q=c;
            q++;
        }
        if (q==p+5)
        return 0;   // got a good name //
        if (q==p){
            printf("(Please type five lowercase letters and RETURN.)\n");
            return 1;   // just a <return>  //
        }
        printf("(Please type five lowercase letters and RETURN.)\n");
    }
}

int compare(char key[5], int m){
    //음수이면 key값이 작음. 양수이면 key값이 큼
    int i, result;
    char temp[5];
    for(i=0; i<5; i++){
        temp[i] = data[m][i];
    }
    return (result = strcmp(key, temp));
}

int search(char key[5]){

    //index 초기화
    int l=0;
    int u=WORDS_NUMBER-1;

    while(l<=u){
        int m=(l+u)/2;
        int result = compare(key, m);

        //key값이 작을 때
        if(result<0)
        u=m-1;

        //key값이 클 때
        else if(result>0)
        l=m+1;

        //key값이 같을 때
        else
        return m;
    }
    //찾는 값이 없을 때
    return -1;
}

void print_result(int n){

    int i, j;

    if (n==-1)
    printf("%d\n", -1);

    else{
        for(i=0; i<5; i++){
            printf("%c", data[n][i]);
        }
        printf("\n");
    }
}
