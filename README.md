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
  * 먼저 merge sort 의 코드 부분입니다
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
  
  * 다음으로 linked list 를 사용한 insertion sort 의 코드입니다.
  ```c
  struct LNode *list_insertion_sort ( struct LNode *head )
{
  /* GJ: FILL */
  struct LNode *cur,*cur2,*tmp;

  tmp = head;
  cur = head->next;
  head->next = NULL;
  cur2 = cur;

  while(cur!=NULL)
    {
        cur2 = cur2->next;
        tmp = head;

        if(cur->key <= tmp->key)
        {
            tmp = insert_head(tmp,cur);
            head = tmp;
        }
        else
        {
            while(tmp!=NULL)
            {
                if(tmp->next == NULL)
                {
                    tmp = insert_next(tmp,cur);
                    tmp = tmp->next;
                    break;
                }
                else
                {
                    if(tmp->next->key >= cur->key)
                    {
                    tmp = insert_next(tmp,cur);
                    break;
                    }
                    else tmp = tmp->next;
                }
            }
        }
        if(cur2 == NULL) cur = NULL;
        else cur = cur2;
    }
    return head;
}
  ```
  새로운 node 의 포인터를 입력받아 그 노드가 추가된 linkedlist 의 node를 다시 반환하는 함수입니다. 큰 while 문에서 cur 포인터(노드를 차례대로 하나씩 가리킴)가 NULL 을 가리킬때 까지 반복이 진행됩니다. cur 포인터가 각 노드들을 순회하면서 tmp의 삽입 될 노드의 key 값을 비교하게 되고 삽입되는 tmp 노드는 가장 앞에 삽입될 경우, 헤드를 새로 삽입하는 노드로 바꾸어 주어야 하고, 아니라면 순서에 올바르게 그 다음노드와 비교하여 알맞은 위치에 그 link 를 연결해 주면 됩니다. 
  
  * 다음으로 linked list 를 사용한 merge sort 의 코드 일부분 입니다.
  ```c
  struct LNode *list_array_merge_sort( struct LNode **head_array, int N )
{
  /* GJ: FILL */
  int i,count;
  int mid,mid1;
  struct LNode *p1,*p2;

  while(head_array[1]!=NULL)
    {
        mid = (N-1)/2;
        mid1 = mid+1;

        for(i=0;i<mid1;i++) // main loop to get all thing together
        {
            if(mid1+i == N) break;
            else
            {
                p1 = head_array[i];
                p2 = head_array[mid1+i]->next;
                count = 0;

                 while(head_array[mid1+i]!=NULL)
                {
                    if(count == 0)
                    {
                        if(p1->key >= head_array[mid1+i]->key)
                        {
                            p1 = insert_head(p1,head_array[mid1+i]);
                            head_array[i] = p1;
                            head_array[mid1+i] = p2;
                            if(p2!=NULL) p2 = p2->next;
                        }
                        else
                        {
                            if(p1->next!=NULL)
                            {
                                if(p1->next->key > head_array[mid1+i]->key)
                                {
                                    p1 = insert_next(p1,head_array[mid1+i]);
                                    head_array[mid1+i] = p2;
                                    if(p2!=NULL) p2 = p2->next;
                                }
                                else
                                {
                                    p1 = p1->next;
                                }

                            }
                            else
                            {
                                p1->next = head_array[mid1+i];
                                head_array[mid1+i] = NULL;
                            }
                        }
                    }
  
  ```
  수업시간의 이야기를 토대로 recusrive 하게 merge를 수행하기보다는 iterative 하게 merge sort를 진행해보고자 하였습니다.
  linked list 로 merge sort 를 진행하기 위해 다음과 같은 알고리즘을 세웠습니다. 각 node 들을 최소단위(1개의 노드)로 분해하여 이중포인터를 사용한 포인터 배열을 통해 분리시켜 놓습니다. 그런다음 mid 와 mid1(mid+1) 값을 매 루프마다 계산하며 갱신합니다. 이때, 이중포인터 array 는 각 
노드들을 한번의 루프마다 merge 하게 됩니다. 이때, merge 가 일어나 그 head 가 존재하는곳은 이중포인터 array 의 start 부터 mid 까지의 부분입니다. 결과적으로 루프가 수행되면서 이 start와 mid 가 이중포인터의 0번째로 모두 합쳐지게 될 것이므로 총 loop 는 이중포인터의 1번째 배열이 NULL을 가리키면 종료할수 있습니다. 각 노드들이 병합될때, 두개의 array가 각각 key 값들을 비교하게 되고 이미 비교한 key 값들에 의해 그 뒤의 node 들은 sorting 되어 이미 연결되어있는 node 들과 다시한번 비교를 진행하지 않아도 됩니다. 이부분에서 수행시간에서의 이득이 발생합니다
마지막으로 정렬된 linkedlist 의 연결된 node 들은 모두 head_array[0] 을 헤드로 하는 linkedlist 형태로 존재하므로 이 head 를 반환해주는 함수로 linkedlist 를 사용한 mergesort 함수를 작성하였습니다.

* 마지막으로, heavy array sort 와 heavy list sort 의 설명입니다
 각 heavey sort 들은 앞서 작성된 merge 와 insertion sort 에서 부하가 추가된 새로운 struct를 node 로 하는 함수로 약간씩만 수정을 하였습니다.
 ```c
 struct LHNode *list_insertion_sort ( struct LHNode *head )
{
  /* GJ: FILL */
  struct LHNode *cur,*cur2,*tmp; 
 ```
 위의 코드와 같이 **struct LHNode**로  변경 되었습니다.
 코드 실행결과는, array 로 구현한 sorting 함수에서는 데이터의 크기가 커짐에 따라 sort 되는 시간이 오래 결렸습니다. 하지만 linkedlist 로 구현한 sorting 에서는 data를 직접 load 해오지 않고 포인터의 이동을 통해서만 sorting 이 이루어지므로 실행시간이 매우 단축되었습니다. 
  
-------------------------------------------------------  
# HW03    
## 개요3
  * HW03 는 binary search tree 를 구현하는 과제입니다.
  이번 과제에선 모두 재귀함수를 사용하여 트리를 구성하였습니다. 데이터 구조는 노드안에 bulksize 만큼의 char array 가 있고 교수님께서
  미리 만들어주신 template 에 있는 함수연산을 통해서만 값들을 비교, 출력할 수 있습니다.
  bst 를 완성하기 위해 작성한 함수들은 아래와 같습니다.
  1. struct BTNode *insert_to_BST_leaf(struct BTNode *bst, struct BTNode *newPtr)
  2. struct BTNode *generate_BST_by_insertion(struct BTNode *lhbt)
   위의 두가지 함수가 bst 를 만드는 함수로 1번 함수는 노드 1개를 기존의 bst에 삽입하는 알고리즘입니다. 2번 함수는 fileio 를 통해 txt 파일을    통해 읽어들인 숫자들이 lhbt 즉 왼쪽 링크로만 이어진 트리형태로 반환되게 되고, 이를 인자로 받아 bst 를 완성하는 함수입니다.
   
   * 다음으로 bst 를 출력하는것에 대한 함수도 작성하였습니다.
   1.int print_LHBT(FILE *fp, struct BTNode *lhbt)
   2.int print_BST_sortedorder(FILE *fp, struct BTNode *bst, int level)
   3.int print_BST_right_center_left(FILE *fp, struct BTNode *bst, int level)
   4.int print_BST_1(FILE *fp, struct BTNode *bst, int level)
   5.int print_BST_2(FILE *fp, struct BTNode *bst, int level, struct Node *head, struct Node *top)
   
   * 다음으로 bst를 complete bst 로 변환하는 함수도 작성하였습니다
   
     struct BTNode *BST_to_completeBST(struct BTNode *bst, int numNodes)
   
   * 또한, bst 를 insertion 으로 생성하는 것이 아닌 quicksort 알고리즘을 통해서 생성하는 함수도 작성하였습니다.
   
     struct BTNode *generate_BST_quicksort_basic(struct BTNode *lhbt)
   
   * 마지막으로 bst를 quicksort 로 생성할때 , 그 root 를 어떤것으로 잡는지에 따라 height 가 차이가 나게 되는데, 최소한의 height 를
   가지기 위한 advanced 된 알고리즘을 작성하였습니다.
   
     struct BTNode *generate_BST_quicksort_advanced(struct BTNode *lhbt)

## 함수설명3
  * struct BTNode *insert_to_BST_leaf(struct BTNode *bst, struct BTNode *newPtr)
  ```c
  if ( comparekey(bst, newPtr) < 0 ) {
      /* FILL */
      bst->right = insert_to_BST_leaf(bst->right, newPtr);
    }
    else {
      /* FILL */
      bst->left = insert_to_BST_leaf(bst->left,newPtr);
    }
  }  
  ```
  와 같이 key 값들을 비교하여 작다면 left link 로, 크다면 ,right 의 link로 node 를 보내주면 된다.
  
  * struct BTNode *generate_BST_by_insertion(struct BTNode *lhbt)
  ```c
  while(lhbt!=NULL)
  {
      newroot = insert_to_BST_leaf(newroot,lhbt);
      lhbt->left = NULL;
      lhbt = cur;
      if(cur!=NULL) cur = cur->left;
  }
  return newroot;  
  ```
  while 문을 사용하여 모든 lhbt 의 노드들을 순회하여 계속하여 insert_to_bst_leaf 함수를 실행한다면, 가장 첫번째 lhbt node를 root 로 하는 bst 가 완성된다.
  
  * int print_LHBT(FILE *fp, struct BTNode *lhbt)
  계속하여 포인터의 next 를 left 로 update 하며 모든 노드를 순회하여 출력할수 있다.
  
  * int print_BST_sortedorder(FILE *fp, struct BTNode *bst, int level)
  ```c
  int count;	// to count the number of nodes

  count = 0;
  if ( bst != NULL ) {
    level++;	// root node of the current subtree exists

    /* FILL: print left subtree */
    if(bst->left!=NULL) count = print_BST_sortedorder(fp,bst->left,level);

    // center node
    fprintf(fp, "%s ",getkey(bst));
    count++;

    /* FILL: print right subtree */
    if(bst->right!=NULL) count = count + print_BST_sortedorder(fp,bst->right,level);
  }
  //ount++;

  // change the line once - only at the bst node
  if ( level <= 1 ) fprintf(fp, "\n");

  return count;
  ```
  재귀적으로 함수를 사용하여 bst root의 left 를 다시 새로운 함수의 root 로 하는 함수를 먼저 호출하게되고, left node 를 출력하게 되면 반환되어 그다음 본인 root 의 값을 출력, 마지막으로 다시금 right leaf 의 print 함수가 출력되어 마지막 leaf 에서 left,right node 가 모두 NULL 일때 함수가 더 이상 호출되지 않고 본인의 key값을 출력하도록 하는 재귀함수를 구현하였다. 간단히 말하면 left->root->right 순으로 출력하게 된다.
  
  * int print_BST_right_center_left(FILE *fp, struct BTNode *bst, int level)
  
  
  
-------------------------------------------------------  
# HW04    
## 개요4
  * 


## 함수설명4
  *
  
-------------------------------------------------------  
  
