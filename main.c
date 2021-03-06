
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "minh.h"

int main(){
  char all[2048]="";
  char dontcare[2048]="";
  Variable* list[2048] ; 
  Variable* Epilist[4096];
  Variable* tokenlist[2048];
  Variable* finallist[2048]; 
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

    printf("acount: %d \n",count);
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
    int qcount=0;
    for(int j=0; j< varcount; j++){
       qcount++;
      printf("%d ",list[a]->binary[j]);
      if(qcount%varcount==0)printf("\n");
    }
  }//변환이 잘 됐는지 확인 나중에 삭제
  
  printf("dkr\n");

  for(int a=0; a< count; a++){
    int samecount=0; //같은 자리수의 값이 같은 개수 확인용
    int confirmsamecount=count; //모든 값에 대해 samecount가 3이하이면 그것도 추가
      //printf("a: %d\n",a);
    for(int A=a+1; A<count; A++){
      //printf("A: %d\n",A);
      samecount = countsame(varcount, *list[a], *list[A]);
      /*
      for(int b=0; b<varcount; b++){
        if(list[a]->binary[b] == list[A]->binary[b]) samecount++;
        //printf("same: %d\n",samecount);
      }
      */
      if(samecount==(varcount-1)){
        Epilist[epicount]=(Variable*)malloc(sizeof(Variable));
        
        
        Epilist[epicount]->numeric[Epilist[epicount]->numericcount]= list[a]->numeric[0];
        Epilist[epicount]->numericcount++;
        Epilist[epicount]->numeric[Epilist[epicount]->numericcount]= list[A]->numeric[0];
         Epilist[epicount]->numericcount++;
        Epilist[epicount]->numeric[(Epilist[epicount]->numericcount)]= -1;
         
        //converttotwo(varcount, epicount, Epilist[epicount], list[a], a , A);
        
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
      printf("%d dkr\n",a);
      printf("%d dkr\n",epicount);
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
        if(samecount==(varcount-1)){
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

  printBinary(epicount, varcount, Epilist);


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
          if(samecount == varcount){
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
            /*if(tokenlist[a]->numeric[k]== -1){
              break;
            }
            */
            //else 
            printf("%d ",tokenlist[a]->numeric[k]);
          }
          printf("\n");
        }
      }
  }

printf("%d hh\n",tokencount);


//tokenlist로 epilist에 있던 필요한 것들 중 중복된 것을 빼고 저장했다. 


int col=tokencount;
int row=mintermcount;
int to_darray[col][row];

int **twod_array;
twod_array=(int **)malloc(tokencount * sizeof(int*));

for(int z=0; z<tokencount ; z++){
  for(int y=0; y<mintermcount; y++){
    twod_array[z]=(int *)malloc(mintermcount * sizeof(int));
    }
  }


for(int z=0; z<mintermcount ; z++){
  for(int y=0; y<tokencount; y++){
    for(int k=0; k<tokenlist[y]->numericcount; k++){
      if(tokenlist[y]->numeric[k]== list[z]->num ) twod_array[y][z]= 1;
    }
  }
}


for(int z=0; z<mintermcount; z++){
  for(int y=0; y<tokencount; y++){
    if(twod_array[y][z]!= 1) twod_array[y][z]=0;
  }
  printf("\n");
}


for(int z=0; z<mintermcount; z++){
  printf("%d",list[z]->num);
}


printf("\n");
printf("-------------------\n");
print2darray(tokencount, mintermcount, twod_array);
printf("\n");
printf("-------------------\n");

int finalcount=0; //finallist에 들어갈 minterm이 몇 개인지 확인

while(1){
  for(int y=0; y<mintermcount; y++){
    int onecount=0;
    for(int z=0; z<tokencount; z++){
      if(twod_array[z][y] == 1) onecount++;
    }
    if(onecount==1){
      finallist[finalcount]=(Variable*)malloc(sizeof(Variable)); //minimum cost expression을 저장할 list
      for(int z=0; z<tokencount; z++){
        if(twod_array[z][y] == 1){
          finallist[finalcount]=tokenlist[z];
          finalcount++;
          for(int Y=0; Y<mintermcount; Y++){
            if(twod_array[z][Y]==1){
              for(int Z=0; Z<tokencount; Z++){
                twod_array[Z][Y]=0;
              }
            }
            twod_array[z][Y]=0;
          }
        } 
        twod_array[z][y] = 0; 
      } 
    }
  }

  printf("Step 1: \n");
  print2darray(tokencount, mintermcount, twod_array);


  for(int y=0; y<mintermcount-1; y++){//'-1'을 하는 이유: 마지막에 있는 것은 비교할게 없으니 마지막에서 두번째와 마지막을 비교하는 것이 맞다.
    
    
    for(int Y=y+1; Y<mintermcount;Y++){
      int colcount=0; // 세로 줄 비교
      int onecount=0; //y줄에 1이 있는지 확인
      int onecountnext=0;//y+1 에 1이 있는지 확인
      for(int z=0; z<tokencount; z++){
        
          if(twod_array[z][y] == 1 && twod_array[z][Y] == 1) colcount++;
          if(twod_array[z][y] == 1) onecount++;
          if(twod_array[z][Y] == 1) onecountnext++;
      }
        
        
        if(colcount > 0 && onecount == colcount) {
          for(int z=0; z<tokencount; z++){
            twod_array[z][Y]= 0;
          } 
        }
        else if(colcount > 0 && onecountnext == colcount) {
          for(int z=0; z<tokencount; z++){
            twod_array[z][y]= 0;
          } 
        }
        printf("y: %d colcount: %d onecount: %d onecountnext: %d\n", y,colcount,onecount,onecountnext);
      
    }
    
  }


  printf("Step 2: \n");
  print2darray(tokencount, mintermcount, twod_array);

  for(int y=0; y<tokencount-1; y++){//'-1'을 하는 이유: 마지막에 있는 것은 비교할게 없으니 마지막에서 두번째와 마지막을 비교하는 것이 맞다.
    
    
    for(int Y=y+1; Y<tokencount;Y++){
      int rowcount=0; // 가로 줄 비교
      int onecount=0; //y줄에 1이 있는지 확인
      int onecountnext=0;//y+1 에 1이 있는지 확인
      for(int z=0; z<mintermcount; z++){
        
          if(twod_array[y][z] == 1 && twod_array[Y][z] == 1) rowcount++;
          if(twod_array[y][z] == 1) onecount++;
          if(twod_array[Y][z] == 1) onecountnext++;
      }
        if(rowcount > 0 && onecount == rowcount && onecountnext == rowcount) {
          if(tokenlist[y]->numericcount >= tokenlist[Y]->numericcount){
            for(int z=0; z<mintermcount; z++){
              twod_array[Y][z]= 0;
            }
          }
          else {
            for(int z=0; z<mintermcount; z++){
              twod_array[y][z]= 0;
            }
          } 
          rowcount=0;
        }
        if(rowcount > 0 && onecount == rowcount) {
          for(int z=0; z<mintermcount; z++){
            twod_array[y][z]= 0;
          } 
        }
        else if(rowcount > 0 && onecountnext == rowcount) {
          for(int z=0; z<mintermcount; z++){
            twod_array[Y][z]= 0;
          } 
        }
        printf("y: %d rowcount: %d onecount: %d onecountnext: %d\n", y,rowcount,onecount,onecountnext);
      
    }
    
  }

  printf("Step 3: \n");
  print2darray(tokencount, mintermcount, twod_array);

  for(int a=0; a<finalcount; a++){ //finallist에 들어갔으면 보여주는 것
      int count=0;
      for(int j=0; j< varcount; j++){
      count++;
      printf("%d ",finallist[a]->binary[j]);
      if(count%varcount==0) printf("\n");
      }
    }

  int zerocount =0;
  for(int z=0; z<tokencount; z++){
    for(int y=0; y<mintermcount; y++){
      if(twod_array[z][y] == 0) zerocount++; 
    }
  }
 
  if(zerocount == (tokencount*mintermcount)) break;
}


for(int z=0; z<count;z++){
  printf("%d %d\n",z,list[z]->isdontcare);
}







  
  for(int a=0; a< count; a++){
    free(list[a]);
  }

  return 0;
}
