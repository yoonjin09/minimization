
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COUNT 40
#define MAX_LENGTH 128
typedef struct{
  int num;
  int binary[128];
  int epi;
  char numeric[128];
  int numericcount; // 0020 이면 0과 2로 numericcount 2
  int isdontcare; //1이면 minterm, 0이면 dontcare
} Variable;

int main(){
  char all[100]="";
  char dontcare[100]="";
  Variable* list[2048] ; 
  Variable* Epilist[2048];
  Variable* tokenlist[2048]; 
  int count=0; //minterm 개수
  int varcount=0; //변수 개수
  int i= 0;
  int epicount=0;
  char * token=NULL;
  int mintermcount=0;
  int dontcarecount=0;
  int ipisdontcare=0; //isdontcare에 1,0을 넣어주기 위한 변수

  printf("변수 개수 입력: \n");
  scanf("%d", &varcount);
  printf("minterm 과 dont care 개수: \n");
  scanf("%d %d", &mintermcount, &dontcarecount);
  getchar();
  scanf("%[^\n]s", all);
  if(dontcarecount!=0){
    getchar();
    scanf("%[^\n]s", dontcare);
    strcat(all," ");
    strcat(all,dontcare);
  }
  
  token=strtok(all," ");

  while(token!=NULL){
    
    list[i]=(Variable*)malloc(sizeof(Variable)); // 리스트 구조체 변수 생성 
    list[i]->num = atoi(token);
    if(ipisdontcare < mintermcount){
      list[i]->isdontcare =1;
      ipisdontcare++;
    }
    else list[i]->isdontcare =0;
    
    list[i]->numeric[0]=list[i]->num;
    list[i]->numeric[1]=-1; 
    list[i]->numericcount++;
    //printf("%d\n",atoi(token));
    
    printf("%d \n",list[i]->num);
    i++;
    token=strtok( NULL," ");
    count++;
  }

    printf("a: %d \n",list[0]->num);
    printf("a: %d \n",list[1]->numeric[1]);
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
  

  for(int a=0; a< count; a++){
    int samecount=0; //같은 자리수의 값이 같은 개수 확인용
    int confirmsamecount=count; //모든 값에 대해 samecount가 3이하이면 그것도 추가
      //printf("a: %d\n",a);
    for(int A=0; A<count; A++){
      //printf("A: %d\n",A);
      for(int b=0; b<varcount; b++){
        if(list[a]->binary[b] == list[A]->binary[b]) samecount++;
        //printf("same: %d\n",samecount);
      }
      if(samecount==3){
        Epilist[epicount]=(Variable*)malloc(sizeof(Variable));
        
        
        Epilist[epicount]->numeric[Epilist[epicount]->numericcount]= list[a]->numeric[0];
        Epilist[epicount]->numericcount++;
        Epilist[epicount]->numeric[Epilist[epicount]->numericcount]= list[A]->numeric[0];
         Epilist[epicount]->numericcount++;
        Epilist[epicount]->numeric[(Epilist[epicount]->numericcount)+1]= -1;
         
        
        for(int b=0; b<varcount; b++){
          if(list[a]->binary[b] == list[A]->binary[b]){
            
            Epilist[epicount]->binary[b] = list[a]->binary[b]; //원래는 '-'를 넣어서 표현했지만 0,1 이 아닌 수 를 집어 넣어준 것
          }
          else Epilist[epicount]->binary[b]= 2;     
        }
        
            
        confirmsamecount--;
        epicount++;
        list[a]->epi=1;
        //printf("epi: %d\n\n",epicount);
      }
      
      
      samecount=0;
    }
    if(confirmsamecount == count){
         Epilist[epicount]=(Variable*)malloc(sizeof(Variable));
         Epilist[epicount]=list[a];
         Epilist[epicount]->numeric[Epilist[epicount]->numericcount]= list[a]->numeric[0];
        //Epilist[epicount]->numericcount++;
        epicount++;
        list[a]->epi=0;

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

          for(int nucount = 0; nucount<Epilist[a]->numericcount;nucount++){
          Epilist[epicount]->numeric[Epilist[epicount]->numericcount]= Epilist[a]->numeric[nucount];
          Epilist[epicount]->numericcount++;
          }

          for(int nucount = 0; nucount<Epilist[A]->numericcount;nucount++){
          Epilist[epicount]->numeric[Epilist[epicount]->numericcount]= Epilist[A]->numeric[nucount];
          Epilist[epicount]->numericcount++;
          }
          Epilist[epicount]->numeric[(Epilist[epicount]->numericcount)+1]= -1;
        
            ////////////////////////////
          
        

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














   int tokencount=0;
    for(int a=0; a< epicount; a++){
      int samecount=0; //같은 자리수의 값이 같은 개수 확인용
        //printf("a: %d\n",a);

        if(Epilist[a]->epi == 0){
          tokenlist[tokencount]=(Variable*)malloc(sizeof(Variable));

          tokenlist[tokencount]=Epilist[a];
          

        tokencount++;
        
        }
        
        for(int x=0; x<tokencount-1; x++){
          for(int b=0; b<varcount; b++){
            if(tokenlist[tokencount-1]->binary[b] == tokenlist[x]->binary[b]) samecount++;
                        
          }
          if(samecount == 4){
              free(tokenlist[tokencount-1]);
              tokencount--;
             continue;
            }
          
          samecount=0;
        }


      }
   
  
  
printf("\n");
for(int a=0; a<tokencount; a++){
    int count=0;
        for(int j=0; j< varcount; j++){
        count++;
        printf("%d ",tokenlist[a]->binary[j]);
        if(count%varcount==0){
          printf("  %d  %d :",tokenlist[a]->epi, tokenlist[a]->num);
          for(int k=0; k<tokenlist[a]->numericcount; k++){
            if(tokenlist[a]->numeric[k]== -1){
              break;
            }
            else printf("%d ",tokenlist[a]->numeric[k]);
          }
          printf("\n");
        }
      }
  }

printf("%d hh\n",tokencount);


//tokenlist로 epilist에 있던 필요한 것들 중 중복된 것을 빼고 저장했다. 


int x=tokencount;
int y=mintermcount;
int to_darray[x][y];






for(int z=0; z<count;z++){
  printf("%d %d\n",z,list[z]->isdontcare);
}







  
  for(int a=0; a< count; a++){
    free(list[a]);
  }

  return 0;
}
