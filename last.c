#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arraymin.h"

int main(){
    char all[50]="";
  char dontcare[50]="";
  Variable list[40] ;
  Variable Epilist[2048];
  Variable tokenlist[30];
  Variable finallist[20];
  printf("array");
  int count=0; //minterm 개수
  int varcount=0; //변수 개수
  int i= 0;
  int a=0;
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
    list[i].num = atoi(token);
    if(ipisdontcare < mintermcount){
      list[i].isdontcare =1;
      ipisdontcare++;
    }
    else list[i].isdontcare =0;

    list[i].numeric[0]=list[i].num;
    list[i].numericcount++;
    //printf("%d\n",atoi(token));
    printf("%d \n",list[i].num);
    i++;
    token=strtok( NULL," ");
    count++;
  }

    printf("\n Debug 1\n"); //입력받은 것을 doncare 인지 minterm으로 받은건지 구분이 끝났다.


    while(a<count){
    int tok=list[a].num;
    //printf("%d \n",tok);
    for(int j = (varcount-1); j> -1 ; j--){
        if(tok == 0) list[a].binary[j]=0;
        else list[a].binary[j]=tok%2;
        tok=tok/2;
    }
    a++;
    } // 이진수로 변환
    a=0;

    printf("\n Debug 2\n"); // 이진수로 바꿔서 binary에 집어 넣는다.


    for(int a=0; a<count; a++){
        int count=0;
        for(int j=0; j< varcount; j++){
        count++;
        printf("%d ",list[a].binary[j]);
        if(count%varcount==0)printf("  %d\n",list[a].epi);
        }
    }


    while(a< count){
        int samecount=0; //같은 자리수의 값이 같은 개수 확인용
        int confirmsamecount=count; //모든 값에 대해 samecount가 3이하이면 그것도 추가
        for(int A=a+1; A<count; A++){
            samecount = countsame(varcount, list[a], list[A]);
            if(samecount==(varcount-1)){
                Epilist[epicount].numeric[Epilist[epicount].numericcount]= list[a].numeric[0];
                Epilist[epicount].numericcount++;
                Epilist[epicount].numeric[Epilist[epicount].numericcount]= list[A].numeric[0];
                Epilist[epicount].numericcount++;
                for(int b=0; b<varcount; b++){
                    if(list[a].binary[b] == list[A].binary[b]){
                        Epilist[epicount].binary[b] = list[a].binary[b]; //원래는 '-'를 넣어서 표현했지만 0,1 이 아닌 수 를 집어 넣어준 것
                    }
                    else Epilist[epicount].binary[b]= 2;
                }
                confirmsamecount--;
                epicount++;
                list[a].epi=1;
            }
        }
        if(confirmsamecount == count){
            Epilist[epicount]=list[a];
            epicount++;
            list[a].epi=0;
        }
        a++;
    }


    a=0;

    printf("\n Debug 3\n"); //각 자리수를 한 번씩 다 비교. 만약 같은 것이 없다면 그것도 epilist로 들어간다

    printBinary(epicount, varcount, Epilist);
    printNumeric(epicount, varcount, Epilist);

    int epilistcount=0;
    int nextepicount=0;


    while(epilistcount!=epicount){
        printf("epicount: %d\n",epicount);
        epilistcount=epicount;
        int bconfirm=0;
        for(int a=nextepicount; a< epilistcount-1; a++){
            int samecount=0; //같은 자리수의 값이 같은 개수 확인용
            for(int A=a+1; A<epilistcount; A++){
                for(int b=0; b<varcount; b++){
                    if(Epilist[a].binary[b] == Epilist[A].binary[b]) samecount++;
                    bconfirm=b;
                }
                if(samecount==(varcount-1)){
                    for(int b=0; b<varcount; b++){
                        if(Epilist[a].binary[b] == Epilist[A].binary[b]){
                            Epilist[epicount].binary[b] = Epilist[a].binary[b]; //원래는 '-'를 넣어서 표현했지만 0,1 이 아닌 수 를 집어 넣어준 것
                        }
                        else Epilist[epicount].binary[b]= 2;
                    }
                    int episamecount=0; // epi에서 새로운거 추가할 때 그 전에 같은 것이 있으면 1로 바뀐다.

                    for(int x=0; x<epilistcount; x++){
                        samecount=0;
                        if(Epilist[x].epi==0){
                            for(int b=0; b<varcount; b++){
                                if(Epilist[epicount].binary[b] == Epilist[x].binary[b]) samecount++;     
                            }
                            if(samecount == varcount){
                                epicount--;
                                //continue;
                                episamecount=1;
                                break;
                            }
                        }
                        samecount=0;
                    }
                    //
                    if(episamecount==0){
                        for(int nucount = 0; nucount<Epilist[a].numericcount;nucount++){
                            int kcount=0;
                            for( int k=0; k< Epilist[epicount].numericcount; k++){
                                if(Epilist[epicount].numeric[k] == Epilist[a].numeric[nucount]) kcount++;
                            }
                            if(kcount==0){
                                Epilist[epicount].numeric[Epilist[epicount].numericcount]= Epilist[a].numeric[nucount];
                                Epilist[epicount].numericcount++;
                            }
                        }

                        for(int nucount = 0; nucount<Epilist[A].numericcount;nucount++){
                            int kcount=0;
                            for( int k=0; k< Epilist[epicount].numericcount; k++){
                                if(Epilist[epicount].numeric[k] == Epilist[A].numeric[nucount]) kcount++;
                            }
                            if(kcount==0){
                                Epilist[epicount].numeric[Epilist[epicount].numericcount]= Epilist[A].numeric[nucount];
                                Epilist[epicount].numericcount++;
                            }
                        }
                        /*
                        for(int nucount = 0; nucount<Epilist[A]->numericcount;nucount++){

                            Epilist[epicount]->numeric[Epilist[epicount]->numericcount]= Epilist[A]->numeric[nucount];
                            Epilist[epicount]->numericcount++;
                        }
                        */

                        //Epilist[epicount]->numeric[(Epilist[epicount]->numericcount)]= -1;
                        epicount++;
                        Epilist[a].epi=1;
                        Epilist[A].epi=1;
                    }
                    episamecount=0;
                }
                samecount=0;
            }
        }
        nextepicount=epilistcount;
    }


    printf("\n Debug 4\n"); //각 자리수를 한 번씩 다 비교. 만약 같은 것이 없다면 그것도 epilist로 들어간다

    printBinary(epicount, varcount, Epilist);
    printNumeric(epicount, varcount, Epilist);



    int tokencount=0;
    for(int a=epicount-1; a>-1 ; a--){
        int samecount=0; //같은 자리수의 값이 같은 개수 확인용
        if(Epilist[a].epi == 0){
            tokenlist[tokencount]=Epilist[a];///////
            tokencount++;
        }
        for(int x=0; x<tokencount-1; x++){
            for(int b=0; b<varcount; b++){
                if(tokenlist[tokencount-1].binary[b] == tokenlist[x].binary[b]) samecount++;
            }
            if(samecount == varcount){
                tokencount--;
                //continue;
                break;
            }
            samecount=0;
        }
    }


    printf("\n Debug 5\n"); //epi가 0인 것만 tokenlist에 집어 넣는다.

    printBinary(tokencount, varcount, tokenlist);
    printNumeric(tokencount, varcount, tokenlist);



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
            for(int k=0; k<tokenlist[y].numericcount; k++){
                if(tokenlist[y].numeric[k]== list[z].num ) twod_array[y][z]= 1;
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
        printf("%d",list[z].num);
    }


    printf("\n");
    printf("-------------------\n");
    print2darray(tokencount, mintermcount, twod_array);
    printf("\n");
    printf("-------------------\n");

    int finalcount=0; //finallist에 들어갈 minterm이 몇 개인지 확인
    int exitcount=0;
    while(1){
        exitcount++;
        if(exitcount>5) break;
        for(int y=0; y<mintermcount; y++){
            int onecount=0;
            for(int z=0; z<tokencount; z++){
                if(twod_array[z][y] == 1) onecount++;
            }
            if(onecount==1){
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
                if(tokenlist[y].numericcount >= tokenlist[Y].numericcount){
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



    printf("Step 2: \n");
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


    printf("Step 3: \n");
    print2darray(tokencount, mintermcount, twod_array);

    for(int a=0; a<finalcount; a++){ //finallist에 들어갔으면 보여주는 것
        int count=0;
        for(int j=0; j< varcount; j++){
            count++;
            printf("%d ",finallist[a].binary[j]);
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
  printf("%d %d\n",z,list[z].isdontcare);
}


for(int a=0; a<finalcount; a++){
    for(int b=0; b< varcount; b++){

        switch(finallist[a].binary[b]){
            case 0 :
                printf("x%d'",b+1);
                break;
            case 1 :
                printf("x%d",b+1);
                break;
            default :
                break;

        }

    }
    if(a != finalcount -1) printf(" + ");
}



    return 0;

}
