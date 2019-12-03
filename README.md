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
  * HW02 는 listosrt 를 이용한 과제입니다. 구현해야할 것들은 먼저 
  1. merge sort 를 array를 이용하여 구현
      (이 코드는 arraysort_kbj.c 파일에 있습니다)
  2. insertion sort를 linked list 를 이용하여 구현
  3.  merge sort 를 linked list를 이용하여 구현
      (이 코드는 listsort_kbj.c 파일에 있습니다)
  4. time challenge 로 구조체에 heavy load 를 붙여 정렬될때의 부하를 주었습니다.
      (이 코드는 heavy_arraysort , heavy_listsort.c 파일에 있습니다)
 이번 과제에서는 array를 사용한 sorting 과 linked list를 사용한 sorting 을 직접 구현하고 특정 조건에서 그 둘의 차이를 비교 하는
 과제 입니다.
 
## 함수설명2
  * 먼저 merge sort 의 코드입니다
  ```c
  void merge_sort( long A[], long Tmp[], int left, int right )
{
  /* GJ: FILL */
  if(left<right)
  {
      int mid = (left+right)/2;
      merge_sort(A,Tmp,left,mid);
      merge_sort(A,Tmp,mid+1,right);
  ```
  위의 코드는 array를 사용한 mergesort 의 부분입니다. mergesort 는 recusrive 하게 구현될수 있으므로 최소 단위까지 가장 먼저 호출되는
  mergesort(left,mid) 가 최소단위까지 실행된다면, 그다음의 merge_sort(mid+1,right) 가 최소단위 까지 호출되고 그 다음 실제 merge를 하는 코드 라인들이 실행이 됩니다. 최소단위에서 merge된 가장 최소단위 함수는 그 배열을 차례대로 반환하여 가장 처음 호출된 함수로 반환되었을때는 처음 배열에서 2부분으로 나뉘어져 왼쪽,오른쪽이 각각 정렬된 부분 배열로 존재하게 됩니다. 마지막으로 이 함수가 merge 하면서 결과적으로 sorting 된 ary 가 반환되게 됩니다.
 
  
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
  
