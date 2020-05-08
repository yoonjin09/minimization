
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COUNT 40
#define MAX_LENGTH 128
typedef struct{
  int num;
  int binary[128];
  int epi;
} Variable;

int main(){
  char all[100]="";
  Variable* list[2048] ; 
  Variable* Epilist[2048]; 
  int count=0; //minterm 개수
  int varcount=0; //변수 개수
  int i= 0;
  int epicount=0;
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
    //printf("%d \n",tok);
    for(int j = (varcount-1); j> -1 ; j--){
      if(tok == 0) list[a]->binary[j]=0; 
      else list[a]->binary[j]=tok%2;
      tok=tok/2;
    }
  } // 이진수로 변환
  
  for(int a=0; a<count; a++){
    int count=0;
    for(int j=0; j< varcount; j++){
       count++;
      printf("%d ",list[a]->binary[j]);
      if(count%varcount==0)printf("\n");
    }
  }//변환이 잘 됐는지 확인 나중에 삭제
  

  for(int a=0; a< count-1; a++){
    int samecount=0; //같은 자리수의 값이 같은 개수 확인용
      //printf("a: %d\n",a);
    for(int A=a+1; A<count; A++){
      //printf("A: %d\n",A);
      for(int b=0; b<varcount; b++){
        if(list[a]->binary[b] == list[A]->binary[b]) samecount++;
        //printf("same: %d\n",samecount);
      }
      if(samecount==3){
        Epilist[epicount]=(Variable*)malloc(sizeof(Variable));
        for(int b=0; b<varcount; b++){
          if(list[a]->binary[b] == list[A]->binary[b]){
            
            Epilist[epicount]->binary[b] = list[a]->binary[b]; //원래는 '-'를 넣어서 표현했지만 0,1 이 아닌 수 를 집어 넣어준 것
          }
          else Epilist[epicount]->binary[b]= 2;     
        }
        epicount++;
        list[a]->epi=1;
        //printf("epi: %d\n\n",epicount);
      }
      samecount=0;
    }
  }
  printf("%d\n\n",epicount);
  //각 자리수를 한 번씩 다 비교 즉 3개의 값이 입력 됐으면 2번, 5개의 값이 입력 됐으면 10번 확인한다

  //
  //
  //
  int epilistcount=0;
  int nextepicount=0;

  while(epilistcount!=epicount){
    epilistcount=epicount;
    for(int a=nextepicount; a< epilistcount-1; a++){
      int samecount=0; //같은 자리수의 값이 같은 개수 확인용
        //printf("a: %d\n",a);
      for(int A=a+1; A<epilistcount; A++){
        //printf("A: %d\n",A);
        for(int b=0; b<varcount; b++){
          if(Epilist[a]->binary[b] == Epilist[A]->binary[b]) samecount++;
          //printf("same: %d\n",samecount);
        }
        if(samecount==3){
          Epilist[epicount]=(Variable*)malloc(sizeof(Variable));
          for(int b=0; b<varcount; b++){
            if(Epilist[a]->binary[b] == Epilist[A]->binary[b]){
              
              Epilist[epicount]->binary[b] = Epilist[a]->binary[b]; //원래는 '-'를 넣어서 표현했지만 0,1 이 아닌 수 를 집어 넣어준 것
            }
            else Epilist[epicount]->binary[b]= 2;     
          }
          epicount++;
          Epilist[a]->epi=1;
          Epilist[A]->epi=1;
          //printf("epi: %d\n\n",epicount);
        }
        /*
        if(samecount==4){
          free(Epilist[A]);
          epicount--;
        }
        */
        samecount=0;
      }
    }
    nextepicount=epilistcount;
  }
   //printf("%d\n\n",epicount);
  //겹치지 않을 때까지 확인 가능
  
printf("%d %d\n",epilistcount,epicount);













  for(int a=0; a<epicount; a++){
    int count=0;
        for(int j=0; j< varcount; j++){
        count++;
        printf("%d ",Epilist[a]->binary[j]);
        if(count%varcount==0)printf("  %d\n",Epilist[a]->epi);
      }
  }

  for(int a=0; a< count; a++){
    free(list[a]);
  }
  for(int a=0; a< epicount; a++){
    free(Epilist[a]);
  }
  return 0;
}

