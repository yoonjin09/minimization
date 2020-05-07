
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COUNT 40
#define MAX_LENGTH 128
typedef struct{
        char num[1024];
        int binary[10];
} Variable;

int main(){
  char all[100]="";
  Variable* list[100] ; 
  
  char * token=NULL;
  scanf("%[^\n]s", all);
  token=strtok(all," ");

  while(token!=NULL){
    int i= 0;
    list[i]=(Variable*)malloc(sizeof(Variable)); // 리스트 구조체 변수 생성 
    list[i]->binary[i] = atoi(token);
    printf("%d\n",atoi(token));
    
    printf("%d \n",list[i]->binary[i]);
    i++;
    token=strtok( NULL," ");
  }
  return 0;
}
