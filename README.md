# minimization

2020-05-08 

변수를 입력하고 2의 자리수로 나타내는 것

비교해서 다른 거 2로 바꾸기까지 완료

필요한  prime implicants를 빼오기까지

epilist에서 epi가 0인 것만 tokenlist로 빼오는데 중복된 것은 제외하고 빼옴


마지막 free를 할 때 최초 list만 free를 해주면 되는데 그 이유는 거기에서부터 시작되었기 때문에 다른 것들 중에서는 list를 free 해주면 다 free가 된다.

2200 즉 --00이면 0 4 8 12 를 출력하고 1012 즉 101-이면 10 11을 출력한다

처음 list를 추가할 때 있을 epi 즉 3, 5, 12가 들어갔을 때는 최종적으로 하지 저장이 되지 않았는데 되도록 해두었다.

해볼 것들 (추가)

-don't care를 입력해서 care와 don't care를 나누는 것. don't care 로 들어온 숫자들도 고려해야하지만 나중에 계산할 때는 쓰면 안된다.

-2020-05-17

don't care 추가하는 것은 마무리가 됐다. 하지만 아직 어느 것이 minterm이고 어느 것이 don't care인지 구분을 안 지어놨다 struct에 관련해서 추가해야할 것 같다

-2020-05-18

doncare인지 minterm인지 구분해놨고, 이걸 이용해서 2차원 배열을 만들어야한다.

-2020-05-19

간단하게 int to_d_array 로 만들면 될 것 같다

-2020-05-21

to_d_array에 집어 넣었다. 만약 minterm 중에 0 2 5 6 7 8 9 13이 있고 계산 결과 나온 것 중에 0020 이라는 pi가 나오면 0과 2에 해당하는 것이 1이 되도록 만들었다. 만약 아무것도 없다면 그것은 0이다.

변수가 4개가 아니라 5개, 6개이더라도 가능하도록 고쳤다. 4개 기준으로 samecount가 3일 때로 계산했지만 samecount가 varcount -1 일 때로 바꿔놨다.

-2020-05-22

원래 있던 to_d_array를 int **twod_array로 바꾸면서 함수를 만들 때 조금더 편리하게 만들었다.

또 맨 처음에 꼭 필요한 pi가 있으면 그것을 finallist에 집어 넣고 해당하는 가로 세로 모두 0으로 

-2020-05-24

세로를 기준으로 더 많은 영역을 차지 하고 있으면 그 영역을 지운다.(0으로 바꾼다)

만약 5를 p5와 p7로 만들 수 있고, 13을 p5,p6,p7 로 만들 수 있다고 하면 13에 해당하는 열을 모두 0으로 만들어 주는 

-2020-05-25

위와 비슷한 논리로 가로줄을 비교하는 것이다. 만약 p4가 0과 8을 커버하는데 p6이 8을 커버하고 있다면 p6을 필요가 없다.

따라서 p6을 지워주는 것이다. 다음에는 모두가 0일 때까지 반복하는 것을 추가하면 될 것 같다.

-2020-05-26

최종적으로 어떤 minimum cost expression에 필요한 finallist가 필요한지 뽑아냈다

하지만 나중에 변수가 4보다 커지게 되면 소거법으로 했을 때 문제점이 생길 수 도 있다.

그래서 소거 할 때는 어디하나에 속한게 아니고 같은 colcount, onecount, onecountnext 라면 해당하는 numericcount가 더 큰 것으로 흡수 하는 것을 코딩 해야한다.

더해서 x로 표현하는 것도 만들어내야 한다. 2라면 아무것도 없고, 1이면 x, 0이면 x'가 나와야 한다.

-2020-05-28

변수 개수가 6, minterm 36, dont care 0 minterm 0 4 6 8 9 11 12 13 15 16 20 22 24 25 27 28 29 31 32 34 36 38 40 41 42 43 45 47 48 49 54 56 57 59 61 63

위를 입력하였을 때 작동하지 않는다.

일단은 반복 구문이 너무 많아서 만약 변수가 6개 정도 되면 처리해야 하는 프로세스가 너무 복잡해지기 때문에 못하는 것으로 생각이 되기 때문에 정리를 할 수 있는 함수를 만들고 있다. 사실 함수가 만들어진다고 한들 논리가 잘못된 것이 아닌가 생각이 된다.

if else 로 되어있는 것들은 switch로 바꾸는 것이 좋을 것 같다.

-2020-05-30

점점 라인이 길어지면서 그냥 쓰다보면 너무 헷갈리는게 많아진다. 따라서 .h 파일을 만들어서 readable 하게 만들어주는 작업을 하고 있다.

-2020-05-31

4개, 5개의 변수로 하면 모든 것이 잘 나온다. 하지만 6개로 한다면 될 때도 있고 안 될 때도 있다.

-2020-06-02

지금은 조금 포인터로 하던 것을 그냥 array로만 해보려고 한다.

포인터에서 배열로 바꾸고 struct 안의 크기를 줄였더니 돌아간다. 아마 포인터로 했어도 돌아가지 않았을까 생각해본다.

