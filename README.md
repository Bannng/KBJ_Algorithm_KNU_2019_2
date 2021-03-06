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
   1. int print_LHBT(FILE *fp, struct BTNode *lhbt)
   2. int print_BST_sortedorder(FILE *fp, struct BTNode *bst, int level)
   3. int print_BST_right_center_left(FILE *fp, struct BTNode *bst, int level)
   4. int print_BST_1(FILE *fp, struct BTNode *bst, int level)
   5. int print_BST_2(FILE *fp, struct BTNode *bst, int level, struct Node *head, struct Node *top)
   
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
   ```c
    if(bst->right!=NULL) rlevel = print_BST_right_center_left(fp,bst->right,level);
    // center node
    for(int i=0; i<level-1;i++)
    {
       if(level!=1) fprintf(fp, "    ");
    }
    fprintf(fp, "%s ",getkey(bst));
    fprintf(fp, "%\n ");

    /* FILL: print right subtree */
    if(bst->left!=NULL) llevel = print_BST_right_center_left(fp,bst->left,level);
   ```
   이 함수도 위의 sorted print 함수처럼 bst 를 출력하지만, 이는 root를 270 도 회전한 모양의 bst 를 출력한다. 위와 달리, right node 부터 출력하게 되어, 재귀함수의 실행 순서가 right -> root -> left 의 순으로 실행되게 되고 각 노드들이 출력될때 마다 줄바꿈이 일어나게 하여 더욱 트리모양에 가깝게 출력할수 있게 하였다.
   
   * int print_BST_1(FILE *fp, struct BTNode *bst, int level)
   ```c
    if(bst->right!=NULL)
    {
        fprintf(fp,"/");
        rlevel = print_BST_1(fp,bst->right,level);
    }

    /* FILL: print right subtree */
    if(bst->left!=NULL)
    {
        fprintf(fp,"\n");
        for(int i=0; i<level;i++)
        {
            if(i==level-1) fprintf(fp,"   +");
            else fprintf(fp, "    ");
        }
        llevel = print_BST_1(fp,bst->left,level);
    }
    if(level == 1) fprintf(fp,"\n");
    return rlevel>llevel?rlevel:llevel;
   ```
위의 right center left 와 코드실행순서는 크게 다르지않지만, right node 들을 출력할때 줄바꿈이 일어나지 않고 / 를 통해서 right node 들을 구분지었다. 또한 left node 들도 + 모양과 공백으로 그 출력을 나타내었다. 위의 재귀함수 실행순서에, left 가 출력될때마다 각 level 에 알맞는 공백을 출력하고 마지막에 left node 를 출력할땐 + 를 출력하게 하였다. 반환값은 level 값들을 return 값으로 받아 그 level 값이 가장 깊을때의 수를 계속 반환하게 하여 이 트리의 최종 level을 반환하게 하였다
    
   * int print_BST_2(FILE *fp, struct BTNode *bst, int level, struct Node *head, struct Node *top)
```c
    struct Node *subandprintblank(FILE *fp,struct Node *head)
    {
    struct Node *cur;
    struct Node *ccur;
    for(cur=head ; cur!=NULL ; cur= cur->next)
    {
        if(cur->key == 0) fprintf(fp,"    ");
        else if(cur->key == 1) fprintf(fp,"   +");
        else fprintf(fp,"   |");
    }
    for(ccur=head ; ccur!=NULL ; ccur=ccur->next)
    {
        if(ccur->key != 0 ) ccur->key = ccur->key - 1;
    }
    return head;
```    
    
이 함수와 linked list 를 이용하여 bst print 1에서 left를 출력할때 공백대신 앞선 left node 가 존재한다면 , 그정보를 기억해 | 를 연달아 출력하게 하는 print 함수를 구현하였다. 함수를 재귀적으로 호출할때 마다 생성된 linked list 의 값들이 변화하여 만약 left node 가 존재한다면 list 에 1의 값을 가지는 노드가 추가되고 기존의 노드들은 모두 1증가한다. 만약 left node 가 없다면 , 0의 노드가 추가되고 아무 연산도 이루어지지 않는다. 이를 통해 각 left 노드가 얼마만큼의 line 수를 기다렸다가 출력되는지 linkedlist 에 그 정보가 저장되는 것이고, 0인 노드들은 아무 연산도 이루어지지 않으므로 left node 의 | 를 표시하지 않게 된다. 재귀적으로 호출된 함수가 반환되면서 이 linkedlist 의 값들도 소비 되는데, 위의 subandprintblank 함수를 통해 각 list 에 알맞는 출력이 행해지게 되고 결과적으로 left node를 | 로 연결한 270도 회전 bst 의 출력을 확인할 수 있다.
   
   * struct BTNode *BST_to_completeBST(struct BTNode *bst, int numNodes)
   ```c
  struct BTNode **aryhead = (struct BTNode**)malloc(sizeof(struct BTNode*)*numNodes);
  struct BTNode *comroot;

  aryhead = sorttoary(bst,aryhead);

  comroot = makecompbst(0,numNodes-1,aryhead);

  return comroot; 
  ```
  
  ```c
  struct BTNode *makecompbst(int start, int end, struct BTNode **aryhead)
{
    int rootindex;
    int numnode = end-start+1;
    struct BTNode *comproot;

    rootindex = start+getroot(numnode);

    comproot = *(aryhead+rootindex);
    //printf("%s ",getkey(comproot));

    if(start == end) return comproot;
    else
    {
        if(start<=rootindex-1) comproot->left = makecompbst(start,rootindex-1,aryhead);
        if(rootindex+1<=end)   comproot->right = makecompbst(rootindex+1,end,aryhead);
        return comproot;
    }
}
  ```
   
   bst 를 complete bst 로 변형하는 함수이다. bst 의 node 들을 하나씩 때와 이중포인터로 늘여 놓은다음, 그 이중포인터 array 에서 complete bst 를 만들수 있는 root 노드를 계속하여 선정하게되고, 이를 재귀적으로 호출하게 하여 complete bst 를 완성한다.
   root 를 고를때에는 , 먼저 노드의 개수를 파악하여야하고 , 이 노드의 개수가 가장 마지막 level/2 보다 큰지, 작은지 판단해 주어야 한다. 이를 각 level 마다 수행해 주면 최종적으로 complete bst 를 만들수 있는 root 들을 계속 pick 하여 bst 를 변형 할 수 있다.
   
  * struct BTNode *generate_BST_quicksort_basic(struct BTNode *lhbt)
  ```c
  if(lhbt != NULL && lhbt->left != NULL)
  {
      //struct BTNode *root;
      //root = lhbt;
      lhbt = partition(lhbt);//root = partition(root);
      lhbt->left = generate_BST_quicksort_basic(lhbt->left);
      lhbt->right = generate_BST_quicksort_basic(lhbt->right);
  }
  return lhbt;
  ```
  quicksort 를 활용하여 bst 를 만드는 함수는, 가장 첫번째 node 를 root 로 삼아 그것보다 작은 node 들은 left, 큰 노드들은 right 에 lhbt 형식으로 link 해준다. 이를 recusrive 하게 수행하면, 가장 마지막 leaf 까지 sort 되므로 bst 가 완성된다.
  
  * struct BTNode *generate_BST_quicksort_advanced(struct BTNode *lhbt)
  ```c
   if(lhbt != NULL)
  {
      lhbt = getmidroot(lhbt);
      lhbt = partition(lhbt);
      lhbt->left = generate_BST_quicksort_advanced(lhbt->left);
      lhbt->right = generate_BST_quicksort_advanced(lhbt->right);
  }
  return lhbt;  
  ``` 
  
  ```c
  struct BTNode *getmidroot(struct BTNode *bst)
{
    if(bst != NULL)
    {
      if(bst->left == NULL || bst->left->left == NULL) return bst;
      else
      {
        struct BTNode *midroot, *cur;
        cur = bst;
        if(comparekey(cur,cur->left)+comparekey(cur,cur->left->left)>=-1
           && comparekey(cur,cur->left)+comparekey(cur,cur->left->left)<=1)
        {
            midroot = cur;
            //printf("%s ",getkey(midroot));
        }
        else if(comparekey(cur->left,cur)+comparekey(cur->left,cur->left->left)>=-1
           && comparekey(cur->left,cur)+comparekey(cur->left,cur->left->left)<=1)
        {
            midroot = cur->left;
            //printf("%s ",getkey(midroot));
            cur->left = cur->left->left;
            midroot->left = cur;
        }
        else
        {
            midroot = cur->left->left;
            //printf("%s  ",getkey(midroot));
            cur->left->left = cur->left->left->left;
            midroot->left = cur;
        }
        return midroot;
      }
    }
}
  ```
  위의 quicksort basic 은 가장 첫번째 노드를 root 로 하여 bst 의 높이가 최적이 아니다. 이를 최적의 높이를 가지는 bst 로 만들기 위해 처음 3노드의 key 값들을 비교하고, 그중 중간값을 가지는 node를 root 로 삼아 bst 를 만들게 되면, 앞선 basic quicksort 보다 높이가 줄어든 bst를 얻을수 있다. 마지 compelete bst 를 만드는것 처럼 매 순간 greedy 하게 중간값들의 노드를 찾아 root 로 삼는다면 optimal 한 결과가 나오지 않을까 생각 해 보았다.
  
-------------------------------------------------------  
# HW04    
## 개요4
  * HW04 는 0-1 knapsack problem 에 관한 과제로, 총 4가지의 문제가 있다.
  1. 기본적인 0-1 knapsack problem
  2. 0-1knapsack with one item split
  3. 0-1knapsack with one duplicate item
  4. 0-1knapsack with two identical knapsacks
  의 문제를 해결하기 위한 코드를 작성하였다.
  이번 코드는 모두 작성자에 의해 작성되었다.

## 함수설명4
  * 1. 0-1 knapsack problem
  ```c
  int **dp(struct item *sary, int n, int W)
{
    int **B;
    B = (int**)malloc((W+1)*sizeof(int*));
    for(int i=0; i<W+1; i++) B[i] = (int*)malloc((n+1)*sizeof(int));
    //int B[W+1][n+1];

    for(int i = 0; i<=W ; i++) B[i][0] = 0;
    for(int i = 1; i<=n;i++)
    {
        B[0][i] = 0;
        for(int w=1; w<=W ; w++)
        {
            int _w = (sary+i-1)->weight;
            int _b = (sary+i-1)->value;
            if(_w <= w)
            {
                if(_b+B[w-_w][i-1]>B[w][i-1]) B[w][i] = _b + B[w-_w][i-1];
                else B[w][i] = B[w][i-1];
            }
            else B[w][i] = B[w][i-1];
        }
    }
    checkary(B,n,W);
    printf("best benefit : %d\n", B[W][n]);
    return B;
}
  ```
  dp table 을 작성하는 함수이다. malloc 함수를 통해 이차원 배열을 할당받고 각 아이템의 weight 와 value 에 의해 dp table 을 채워나간다. 이때, 가장 마지막 요소(B[W][n]) 에 있는 값이 best 한 value 가 된다.
  dp table 을 작성하여 best final benefit 을 구하였으면, dp tabel 을 통하여 무슨 아이템을 골랐는지 backtrack 할 수 있다.
  ```c
  void backtrack(int **B, int n, int W, struct item* sary)
{
    STACK *stack;
    stack = createStack();
    while(B[W][n]!=0)
    {
        if(B[W][n]==B[W][n-1])
        {
            n=n-1;
        }
        else
        {
            W = W-(sary+n-1)->weight;
            n = n-1;
            //printf("%d \n",n+1);
            pushStack(stack,n+1);
        }
    }
    printf("item index :");
    while(stack->top!=NULL)
    {
        popStack(stack);
    }
    free(stack);
}
  ```
  backtrack 의 알고리즘은, 2차원배열의 가장마지막요소 B[W][n] 에서 시작해, 만약 왼쪽에 같은 값이 있다면 왼쪽으로 한칸이동, 없다면 바로 왼쪽열의 내가가진 weight 만큼 뺀 행으로 이동한다. 이를 통해 best final benefit 에서부터 무슨 아이템을 마지막으로 넣었는지 찾아낼 수 있으며, 이 찾아낸 값들을 stack 에 push 하여 가장 먼저 넣은 item 이 stack 의 top에 저장되게 된다. item 을 확인, 출력하기 위해선 단지 stack 에 저장된 item 의 인덱스 값들을 pop 해주기만 하면 된다.
  
  * 2. 0-1knapsack with one item split
  ```c
  double **dp2(struct spitem *ssary, int n, int W)
{
    double **B;
    B = (double**)malloc((2*W+1)*sizeof(double*));
    for(int i=0; i<2*W+1; i++) B[i] = (double*)malloc((n+1)*sizeof(double));
    //int B[W+1][n+1];
  ```
  2번 문제에서 dp table 은 value 값이 double 형을 가진다는것, split 된 아이템의 value 가 0.5 단위가 되므로 0에서8까지의 weight 에서 0부터16 까지의 weight 로 표현하였다. 실제 0~16까지인것이 아니라, 0,0.5,1,1.5 로 눈금이 0.5 로 변경됨에 따라 배열의 행 index 에는 소숫점으로 접근할수 없으므로 16개의 정수로 표현하였다. best 한 benefit 은 B[2W][n]에 저장된다.

2번 문제를 해결하기 위해서, 총 5개의 case 를 실행하였다. 1번아이템을 두개로 나눌경우, 2번아이템,3번,4번 을 2개로 나눌경우의 4가지
그리고 아무 아이템도 나누지 않을 경우의 총 5가지 경우를 비교하여 가장 큰 final value 를 가지는 경우를 선택하는 방식으로 하였다. backtrack 함수는 1번과 크게 다르지 않으며, 
```c
double ***P2(struct item *sary, int n, int W)
{
    printf("\n\n----P2. 0-1 Knapsack with one item split------\n\n");
    double **B;
    double ***A = (double***)malloc(sizeof(double**)*(n+1));
    struct spitem *mixary;
    for(int i=0; i<=n;i++)
    {
        printf("for case : %d\n",i+1);
        mixary = getmixary(sary,n,i);
        B = dp2(mixary,n,W);
        *(A+i) = B;
        backtrack2(B,n,W,mixary,i);
        printf("\n\n");
    }
    printf("list of benefit :");
    for(int i=0; i<=n ; i++) printf("%.1f ",A[i][2*W][n]);
    int maxindex = argmax(A,n,W);
    printf("\nargmax is : %d\n\n",maxindex);

    mixary = getmixary(sary,n,maxindex);
    printf("-------------------------------\n");
    printf("the best benefit is : %.1f\n",A[maxindex][2*W][n]);
    backtrack2(A[maxindex],n,W,mixary,maxindex);
    printf("\n-------------------------------\n");
    return A;
}
```
와 같이 모든 case 를 수행한 dp table 을 3차원 cube로 쌓아 A[maxindex][2W][n] 와 같이 최종 value 를 비교하기 용이하게 하였다. 이 array를 search 하여 최고의 값을 가지는 index 를 반환하는 argmax 함수를 사용하여 해당 dptable 에 대해 backtrack 을 진행하게 하였다.

 * 3. 0-1knapsack with one duplicate item
 3번 문제도 2번문제와 접근방식이 같다. 다만, 2번문제에선 item 을 split 하였기때문에 weight 의 범위가 2배가 되었지만(실제로는 아니다)
 3번 문제에선 1개의 아이템이 추가된것과 마찬가지 이므로, i의 값이 1늘어난 경우의 dptable 을 작성하는것으로 생각하였다.
 ```c
 int ***P3(struct item *sary, int n, int W)
{
    printf("\n\n---P3. 0-1 Knapsack with one duplicate item---\n\n");
    int ***C = (int***)malloc(sizeof(int**)*(n+1));
    int **D;
    struct item *plusary;
    for(int i=0;i<=n;i++)
    {
        printf("for case : %d\n",i+1);
        plusary = getplusary(sary,n,i);
        D = dp(plusary,n+1,W);
        *(C+i) = D;
        backtrack3(D,n+1,W,plusary,i);
        printf("\n\n");
    }
    printf("list of benefit : ");
    for(int i=0 ; i<=n ; i++) printf("%d ",C[i][W][n+1]);
    int mmax = getmax(C,n,W);
    printf("\nmax benefit : %d\n\n",mmax);

    printf("====Show every possible ways====\n");
    printf("the best benefit is : %d\n",mmax);
    for(int i=0; i<=n ;i++)
    {
        if(mmax == C[i][W][n+1])
        {
            printf("-------------------------------\n");
            plusary = getplusary(sary,n,i);
            backtrack3(C[i],n+1,W,plusary,i);
            printf("\n-------------------------------\n");
        }
    }
    return C;
}
 ```
 참조하는 item array 를 확장한 plusary 함수를 통해 i를 증가시키고 이 데이터를 기반으로 dptable 을 작성한다, dptable은 2번에서와 마찬가지로 총 5개의 경우에 대해 작성을 하게 되는데, 1번,2,3,4번을 2번씩 사용할 경우와 아무것도 2번씩 사용하지 않을 경우에 대해 dptable 을 구성한다.
 2번과 마찬가지로 3중포인터를 통해 dptable 을 쌓아올리고,  C[i][W][n+1] 의 배열을 뒤지면서 가장 best 한 값을 찾는다. 다만 이경우에서, best 한 결과를 나타내는 방법이 여러가지가 될수 있으므로, for문을 사용하여 최대 value  를 가지는 dptable 을 모두 선택하여 backtrack 을 진행하도록 하여 가능한 모든 경우의수를 나타내게 하였다.
 
 * 4. 0-1knapsack with two identical knapsacks
 해당 문제는 두개의 knapsack 에 아이템을 집어넣는 문제로, 처음에는 dp로 문제를 풀려고 하였으나 모든경우의수를 찾기는 힘들다는 판단하에
 greedy 알고리즘을 사용하여 문제를 해결해 보았다.
 
 ```c
 struct bag *P4(struct item *sary, int n, int W, int W2)
{
    struct spitem *rankedary;
    struct bag *bagary = (struct bag*)malloc(sizeof(struct bag)*2);
    int rankedlist[n];
    struct bag *lowptr,*bigptr;
    int j=0;

    rankedary = getrankedary(sary,n);
    printf("\n");

    for(int i=0; i<n;i++)
    {
        rankedlist[i] = (rankedary+i)->index-1;
        //printf("rankedlist[%d] = %d\n",i,rankedlist[i]);
    }

    (bagary+0)->bagweight = W;
    (bagary+0)->bagvalue = 0;
    (bagary+0)->bagindex = 1;
    (bagary+1)->bagweight = W2;
    (bagary+1)->bagvalue = 0;
    (bagary+1)->bagindex = 2;
    /*
    for(int i=0; i<2;i++)
    {
        printf("bagary's weight = %d value : %d\n",(bagary+i)->bagweight,(bagary+i)->bagvalue);
    }
    */

    lowptr = minptr(bagary);
    bigptr = maxptr(bagary);

    while((lowptr)->bagweight > 0)
    {
        lowptr->bagweight = lowptr->bagweight - (sary+rankedlist[j])->weight;
        if(lowptr->bagweight < 0 )
        {
            lowptr->bagweight = lowptr->bagweight + (sary+rankedlist[j])->weight;
            break;
        }
        lowptr->bagvalue = lowptr->bagvalue + (sary+rankedlist[j])->value;
        //printf("bag1's weight : %d , bagvalue : %d and plusvalue : %d and j :%d\n",lowptr->bagweight,lowptr->bagvalue,(sary+rankedlist[j])->value,j);
        printf("you should put item <index : %d> into the <bag : %d>\n",(sary+rankedlist[j])->index,lowptr->bagindex);
        j++;
    }

    while((bigptr)->bagweight > 0)
    {
        bigptr->bagweight = bigptr->bagweight - (sary+rankedlist[j])->weight;
        if(bigptr->bagweight < 0 )
        {
            bigptr->bagweight = bigptr->bagweight + (sary+rankedlist[j])->weight;
            break;
        }
        bigptr->bagvalue = bigptr->bagvalue + (sary+rankedlist[j])->value;
        //printf("bag2's weight : %d , bagvalue : %d and plusvalue : %d and j :%d\n",bigptr->bagweight,bigptr->bagvalue,(sary+rankedlist[j])->value,j);
        printf("you should put item <index : %d> into the <bag : %d>\n",(sary+rankedlist[j])->index,bigptr->bagindex);
        j++;
    }
    printf("Sum of Bag1 and Bag2's value is : %d\n",(bagary+0)->bagvalue+(bagary+1)->bagvalue);
    printf("---------------------------------------------------\n");
    return bagary;
}
 ```
 4번 문제해결의 아이디어는, 단위 weight 당 value 가 가장 높은 item 부터 정렬하여, 가장 높은 아이템들이 bag의 수용범위가 작은 bag 부터 먼저 채워나가는 방식으로 접근하였다. 그 이유는 단위 weight 당 value 가 낮다면, 비슷한 value 에서 weight 도 그만큼 클것이고, 이를 모두 포용하려면 이러한 단위 weight 당 value 가 낮은 item 들이 더 큰 knapsack 에 들어가야 한다고 생각했기 때문이다.
 고로, 실제 위의 코드에도 아이템들을 단위무게당 value 순으로 정렬하였고, 이를 두 냅색중 weight 가 더 작은 knapsack 부터 채워넣는 식으로 코드를 작성하였다.  
  
-------------------------------------------------------  
  
