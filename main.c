
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COUNT 40
#define MAX_LENGTH 128
typedef struct{
        int num;
        int binary[128];
} Variable;

int main(){
  char all[100]="";
  Variable* list[100] ; 
  int count=0;
  int varcount=0;
  int i= 0;
  char * token=NULL;

  printf("변수 개수 입력: \n");
  scanf("%d", &varcount);
  getchar();
  scanf("%[^\n]s", all);
  token=strtok(all," ");

  while(token!=NULL){
    
    list[i]=(Variable*)malloc(sizeof(Variable)); // 리스트 구조체 변수 생성 
    list[i]->num = atoi(token);
    //printf("%d\n",atoi(token));
    
    printf("%d \n",list[i]->num);
    i++;
    token=strtok( NULL," ");
    count++;
  }
    printf("a: %d \n",list[0]->num);
    printf("a: %d \n",list[1]->num);
    printf("a: %d \n",list[2]->num);
  for(int a=0; a<count; a++){
    int tok=list[a]->num;
    printf("%d \n",tok);
    for(int j = (varcount-1); j> -1 ; j--){
      if(tok == 0) list[a]->binary[j]=0; 
      else list[a]->binary[j]=tok%2;
      tok=tok/2;
    }
  }
  
  for(int a=0; a<count; a++){
    for(int j=0; j< varcount; j++){
      printf("i= j= : %d \n",list[a]->binary[j]);
    }
  }

  return 0;
}

