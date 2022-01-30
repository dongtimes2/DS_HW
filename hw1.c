#include <stdio.h>
#include "backend1.h"

#define NUMBER_OF_RECORDS 5

// External Variables

char data_name[NUMBER_OF_RECORDS][3];
char data_number[NUMBER_OF_RECORDS][4];

int k=0;  // index of the first empty slot

void add(char name[3], char number[4])
{
  if (k<NUMBER_OF_RECORDS) {
    data_name[k][0]=name[0];
    data_name[k][1]=name[1];
    data_name[k][2]=name[2];
    data_number[k][0]=number[0];
    data_number[k][1]=number[1];
    data_number[k][2]=number[2];
    data_number[k][3]=number[3];
    print_name(k);
    printf(" : ");
    print_number(k);
    printf(" was successfully added!\n");
    k++;
  }
  else
    printf("Can't add.  Address book is full.\n");
}


// Returns the index of the found record.
// Returns -1, if not found.
int search_index(char name[3])
{
    int i,j;
	for (i = 0; i < k; i++) {
		int result = 0;

		for (j = 0; j < 3; j++) {
			if (data_name[i][j] == name[j]) {
				result++;
			}
		}
		if (result == 3)
			return i;
	}
	return -1;
}


void search(char name[3])
{
  int s_result;

  s_result=search_index(name);
  if (s_result==-1)
    printf("Couldn't find the name.\n");
  else {
    print_name(s_result);
    printf(" : ");
    print_number(s_result);
    printf(" was found.\n");
  }
}


void delete(char name[3])
{
    int d_result;
    int i,j,l;
	d_result = search_index(name);
	if(d_result==-1)
		printf("Couldn't find the name.\n");
	else{
		for(i=d_result; i<k-1; i++){
			for(j=0; j<3; j++){
				data_name[i][j]=data_name[i+1][j];
			}
			for(l=0; l<4; l++){
				data_number[i][l]=data_number[i+1][l];
			}
		}
	   k--;
     printf("The name was successfully deleted.\n");
	}
}


// Prints ith name.
void print_name(int i)
{
  print_data(data_name[i], 3);
}

// Prints ith number.
void print_number(int i)
{
  print_data(data_number[i], 4);
}


void print_data(char * s, int n)
{
  int i;
  for (i=0; i<n; i++)
    putchar(s[i]);
}

void print_list()
{
  int i;
  for (i=0; i<k; i++) {
    print_name(i);
    printf(" : ");
    print_number(i);
    printf("\n");
  }
}
