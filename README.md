# KBJ_Algorithm_KNU_2019_2

## 2019_2 Algorithm assignment's code
  > 2019년 2학기 알고리즘에서 작성한 코드들입니다.
  >> HW01,02,03 에 있는 코드들중, main함수와 파일입출력, 기본연산 함수들은 **professor Gil-Jin Jang** 의 template 코드입니다.
     HW04의 코드들은 저의 코드입니다.
     주석처리되어 __(/* GJ: FILL */)__ 라고 되어있는 함수부분에 작성한 코드는 저의 코드입니다.

### Table of Contents
  * [HW01](#hw01)
    - [개요1](#개요1)
    - [함수설명1](#함수설명1)
    
  * [HW02](#)
    - [개요2](#개요2)
    - [함수설명2](#함수설명2)
    
  * [HW03](#)
    - [개요3](#개요3)
    - [함수설명3](#함수설명3)
    
  * [HW04](#)
    - [개요4](#개요4)
    - [함수설명4](#함수설명4)
    
---------------------------------------------------------
# HW01    
## 개요1
  * 첫번째 과제로 binary search 를 하기 위해서 array 를 sort 하는 함수를 작성하였습니다. 제공된 template 코드에 맞춰
`int add_value_for_binsearch( int A[], int loc, int val )` 의 함수를 완성하였습니다. 
  
## 함수설명1
  * 작성한 add_value_for_binsearch 함수 코드입니다.
  ```c
  int add_value_for_binsearch( int A[], int loc, int val )
  // assumption: A[0]~A[loc-1] - sorted values
  // find the location of val in A including A[loc]
  // and re-order all the other values as well
{
  /* FILL */ // have trouble with after the same number comes out!
  int i,j;
  int tmp;
  int index;
  //int count = 0;
  //int samecount = 0;

  A[loc] = val;

  for(i=0; i<loc; i++){
    if(A[loc]<=A[i]){
        tmp = A[loc];
        A[loc] = A[i];
        A[i] = tmp;
        //count++;
    }
  }
  for(j=0; j<=loc;j++){
    if(val<A[j]) break;
  }
  index = j-1;
  //index = loc - count;

  return index;
}
  ```
  위 함수는 insertion sort 함수로 입력인자로 받은 배열 A[] 의 인덱스들을 차례로 접근하여 확인하게 됩니다. 먼저 A[loc] 에 집어넣을 val 값을 저장합니다
  그 다음, for 문을 통해 배열 A[] 에 있는 모든 인덱스들과 A[loc] 의 값을 비교해줍니다.
  만약 A[loc] 이 A[i] 보다 작다면, 앞서 선언한 임의의 저장공간인 tmp을 사용하여 A[loc] 과 A[i]의 자리를 바꾸어 줍니다.
  다음의 j를 이용한 for 문은 index를 반환하는데, 여기서 index 는 val 이 삽입된 배열의 index 가 됩니다.
  이를 반복해서 수행한다면 새로들어오는 값 val 이 A[] 에 적절한 위치에 삽입되어 A[] 는 정렬된 배열을 가지게 됩니다. 
  
-------------------------------------------------------  
# HW02    
## 개요2
  HW02 는 listosrt 를 이용한 과제입니다. 구현해야할 것들은 먼저 
  
 
## 함수설명2
  *
  
-------------------------------------------------------  
# HW03    
## 개요3
  * 


## 함수설명3
  *
  
-------------------------------------------------------  
# HW04    
## 개요4
  * 


## 함수설명4
  *
  
-------------------------------------------------------  
  
