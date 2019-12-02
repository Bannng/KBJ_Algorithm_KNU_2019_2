// Kim Byeong Ju
//Code for Knapsack HW4
// this is completely made by me

#include <stdio.h>
#include <stdlib.h>

struct item
{
    int index;
    int weight;
    int value;
};

//////////stack ADT/////////////
typedef struct node
{
    int key;
    struct node *link;
}Node;

typedef struct
{
    Node *head;
    Node *top;
}STACK;

STACK *createStack(void)
{
    STACK *stack;
    stack = (STACK*)malloc(sizeof(STACK));
    if(stack)
    {
        stack->head = NULL;
        stack->top = NULL;
    }
    return stack;
}

void pushStack(STACK *stack, int kkey)
{
    Node *n;
    n = (Node*)malloc(sizeof(Node));
    if(!n) return;
    n->key = kkey;
    n->link = stack->top;
    stack->top = n;
}

void popStack(STACK *stack)
{
    int dataOut;
    Node *temp;
    if(stack->top == NULL) return;
    else
    {
        temp = stack->top;
        dataOut = stack->top->key;
        stack->top = stack->top->link;
        free(temp);
    }
    printf(" %d",dataOut);
}
///////////Stack ADT end////////////////////////////

struct item **readkeys_textfile(char infile[]);
///////////////////////////////////////////////////

void checkary(int **ary, int n, int W) // this is for int
{
    for(int i=0;i<=W;i++)
    {
        for(int j=0;j<=n;j++)
        {
            printf("%d ",ary[i][j]);
        }
        printf("\n");
    }
}

void checkary2(double **ary, int n, int W) // this is for double
{
    for(int i=0;i<=W;i++)
    {
        for(int j=0;j<=n;j++)
        {
            printf("%.1f ",ary[i][j]);
        }
        printf("\n");
    }
}

//////////////////////1. 0-1 knapsack problem////////////////////////////
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
//////////////////////////////////////////////////////////////////////

///////////////////2. 0-1knapsack with one item split/////////////////
struct spitem
{
    int index;
    double weight;
    double value;
    //int oweight;
};

struct spitem *gethalfary(struct item *sary, int sarynum)
{
    struct spitem *halfary = (struct spitem*)malloc(sizeof(struct spitem)*sarynum);

    for(int i=0; i<sarynum;i++)
    {
        (halfary+i)->index = (sary+i)->index;
        (halfary+i)->weight = (double)(sary+i)->weight/2.0;
        (halfary+i)->value = (double)(sary+i)->value/2.0;
    }
    return halfary;
}

double **dp2(struct spitem *ssary, int n, int W)
{
    double **B;
    B = (double**)malloc((2*W+1)*sizeof(double*));
    for(int i=0; i<2*W+1; i++) B[i] = (double*)malloc((n+1)*sizeof(double));
    //int B[W+1][n+1];

    for(int i = 0; i<=2*W ; i++) B[i][0] = 0;
    for(int i = 1; i<=n;i++)
    {
        B[0][i] = 0;
        for(int w=1; w<=2*W ; w++)
        {
            int _w = (int)2*((ssary+i-1)->weight);
            double _b = (ssary+i-1)->value;
            if(_w <= w)
            {
                if(_b+B[w-_w][i-1]>B[w][i-1]) B[w][i] = _b + B[w-_w][i-1];
                else B[w][i] = B[w][i-1];
            }
            else B[w][i] = B[w][i-1];
        }
    }
    checkary2(B,n,2*W);
    printf("best benefit : %.1f\n", B[2*W][n]);

    return B;
}

struct spitem *getmixary(struct item *sary, int n, int j)
{
    struct spitem *halfary;
    struct spitem *mixary = (struct spitem*)malloc(sizeof(struct spitem)*n);
    for(int i=0;i<n;i++)
    {
        (mixary+i)->index = (sary+i)->index;
        (mixary+i)->weight = (sary+i)->weight;
        (mixary+i)->value = (sary+i)->value;
        //printf("mixary index is : %d   weight is : %.2f  value is : %.2f\n",(mixary+i)->index,(mixary+i)->weight,(mixary+i)->value);
    }
    halfary = gethalfary(sary,n);
    (mixary+j)->index = (halfary+j)->index;
    (mixary+j)->weight = (halfary+j)->weight;
    (mixary+j)->value = (halfary+j)->value;
    /*
    for(int i=0; i<n; i++)
    {
        printf("mixary index is : %d   weight is : %.2f  value is : %.2f\n",(mixary+i)->index,(mixary+i)->weight,(mixary+i)->value);
    }
    */
    return mixary;
}

void backtrack2(double **B, int n, int W, struct spitem *mixary, int j)
{
    STACK *stack;
    stack = createStack();
    W = 2*W;
    while(B[W][n]!=0)
    {
        if(B[W][n]==B[W][n-1])
        {
            n=n-1;
        }
        else
        {
            W = W-2*((mixary+n-1)->weight);
            n = n-1;
            //printf("%d \n",n+1);
            pushStack(stack,n+1);
        }
    }
    printf("item index :");
    while(stack->top!=NULL)
    {
        if(stack->top->key == j+1)
        {
            popStack(stack);
            printf("x0.5");
        }
        else popStack(stack);
    }
    free(stack);
}

int argmax(double ***a, int n, int W)
{
    int max = a[0][2*W][n];
    int maxIndex = 0;
    for(int i=1; i<=n;i++)
    {
        if(a[i][2*W][n]>max)
        {
            max = a[i][2*W][n];
            maxIndex = i;
        }
    }
    return maxIndex;
}

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
//////////////////////////////////////////////////////////////////////

/////////////////3. 0-1knapsack with one duplicate item///////////////
int getmax(int ***a, int n, int W)
{
    int max = a[0][W][n+1];
    int maxIndex = 0;
    for(int i=1; i<=n;i++)
    {
        if(a[i][W][n+1]>max)
        {
            max = a[i][W][n+1];
            maxIndex = i;
        }
    }
    return max;
}

struct item *getplusary(struct item *sary, int n, int j)
{
    struct item *plusary;
    plusary = (struct item*)malloc(sizeof(struct item)*(n+1));
    for(int i=0; i<n; i++)
    {
        (plusary+i)->index = (sary+i)->index;
        (plusary+i)->weight = (sary+i)->weight;
        (plusary+i)->value = (sary+i)->value;
    }
    if(n != j)
    {
        (plusary+n)->index = (sary+j)->index;
        (plusary+n)->weight = (sary+j)->weight;
        (plusary+n)->value = (sary+j)->value;
    }
    else
    {
        (plusary+n)->index = 0;
        (plusary+n)->weight = 0;
        (plusary+n)->value = 0;
    }
    /*
    for(int i=0; i<=n; i++)
    {
        printf("plusary index is : %d   weight is : %d  value is : %d\n",(plusary+i)->index,(plusary+i)->weight,(plusary+i)->value);
    }
    */
    return plusary;
}

void backtrack3(int **B, int n, int W, struct item *plusary, int j)
{
    STACK *stack;
    stack = createStack();
    int N = n;
    int checkstack = 0;

    while(B[W][n]!=0)
    {
        if(B[W][n]==B[W][n-1])
        {
            n=n-1;
        }
        else
        {
            W = W-((plusary+n-1)->weight);
            n = n-1;
            //printf("%d \n",n+1);
            if(n+1 == N) checkstack = 1;
            else pushStack(stack,n+1);
        }
    }
    //printf("check stack : %d\n",checkstack);
    printf("item index :");
    while(stack->top!=NULL)
    {
        if(checkstack==1)
        {
            if(stack->top->key == j+1)
            {
                popStack(stack);
                printf("x2");
            }
            else popStack(stack);
        }
        else popStack(stack);
    }
    free(stack);
}

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
//////////////////////////////////////////////////////////////////////


/////////////4. 0-1knapsack with two identical knapsacks//////////////
struct spitem* bubblesort(struct spitem *oneary, int sarynum)
{
    struct spitem tmp;
    for(int i=0;i<sarynum;i++)
    {
        for(int j=1;j<sarynum-i;j++)
        {
            if((oneary+j-1)->value < (oneary+j)->value)
            {
                tmp = *(oneary+j-1);
                *(oneary+j-1) = *(oneary+j);
                *(oneary+j) = tmp;
            }
        }
    }
    return oneary;
}

struct spitem *getrankedary(struct item *sary, int sarynum)
{
    struct spitem *oneary = (struct spitem*)malloc(sizeof(struct spitem)*sarynum);

    for(int i=0;i<sarynum;i++)
    {
        (oneary+i)->index = (sary+i)->index;
        (oneary+i)->weight = 1;
        (oneary+i)->value = (double)(sary+i)->value/(sary+i)->weight;
        //(oneary+i)->oweight = (sary+i)->weight;
    }
    oneary = bubblesort(oneary,sarynum);
    for(int i=0; i<sarynum;i++)
    {
        printf("ranked ary's index : %d , weight : %.1f , value : %.1f\n",(oneary+i)->index,(oneary+i)->weight,(oneary+i)->value);
    }
    return oneary;
}

struct bag
{
    int bagweight;
    int bagvalue;
    int bagindex;
};

struct bag *minptr(struct bag *bagary)
{
    struct bag *lowptr;
    if((bagary+0)->bagweight > (bagary+1)->bagweight)
    {
        lowptr = (bagary+1);
        return lowptr;
    }
    else
    {
        lowptr = bagary;
        return lowptr;
    }
}

struct bag *maxptr(struct bag *bagary)
{
    struct bag *bigptr;
    if((bagary+0)->bagweight > (bagary+1)->bagweight)
    {
        bigptr = (bagary+0);
        return bigptr;
    }
    else
    {
        bigptr = (bagary+1);
        return bigptr;
    }
}

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
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
/////////////           M A I N     C O D E             //////////////
//////////////////////////////////////////////////////////////////////
int main(void)
{
    struct item **datatable;
    struct item *sary;
    int n;
    int W;
    int W2;

    char infile[1024], outfile[1024];

    printf("Input file name? : ");
    scanf("%s",infile);
    //printf("Output file name? : ");
    //scanf("%s",outfile);

    datatable = readkeys_textfile(infile);
    sary = *datatable;
    n = (*(datatable+1))->index;
    W = (*(datatable+1))->weight;
    W2 = (*(datatable+1))->value;

    printf("n : %d , W : %d\n",n,W);
    for(int i=0;i<n;i++)
    {
        printf("input data = index is : %d   weight is : %d  value is : %d\n",(sary+i)->index,(sary+i)->weight,(sary+i)->value);
    }

    //////////////////          P1          //////////////////
    printf("\n\n--------P1. 0-1 Knapsack problem ----------\n\n");
    int **B;
    B = dp(sary,n,W);
    backtrack(B,n,W,sary);
    printf("\n\n");
    ///////////////////////////////////////////////////////////

    //////////////////          P2          //////////////////
    double ***P_2;
    P_2 = P2(sary,n,W);
    //////////////////////////////////////////////////////////


    //////////////////          P3          //////////////////
    int ***P_3;
    P_3 = P3(sary,n,W);
    //////////////////////////////////////////////////////////


    //////////////////          P3          //////////////////
    printf("\n\n---P4. 0-1 Knapsack with two identical knapsacks---\n\n");
    if(W2 == 0)
    {
        printf("There is no Bag 2 !!\n");
        printf("if you want to see Problem4, make input as <i2.txt>\n");
        printf("---------------------------------------------------\n");
    }
    else
    {
        printf("We have bag2 , Problem4 is here!\n\n");
        struct bag *P_4;
        P_4 = P4(sary,n,W,W2);
        free(P_4);
    }
    //////////////////////////////////////////////////////////

    free(B);
    free(P_2);
    free(P_3);
    free(datatable);

    return 0;
}


//////////////////////////////////////////////////////////////////////
/////////////          Detail for file input            //////////////
//////////////////////////////////////////////////////////////////////

struct item **readkeys_textfile(char infile[])
  // returns an array of long integers, with its size stored in
  // the memory indicated by integer pointer variable pN
  // the retured memory should freed by the caller
{
    struct item **wary = (struct item**)malloc(sizeof(struct item*)*2);
    int tmp[20];
    int *ptr = tmp;
    int *nptr = tmp;
    int count =0;
    int *W;
    struct item *sary;
    struct item *nWitem;
    int sarynum = 0;

    FILE *fp;

  // check for input file name
    if ( infile == NULL )
    {
    fprintf(stderr, "NULL file name\n");
    return NULL;
    }

  // check for file existence
    fp = fopen(infile,"r");
    if ( !fp )
    {
        fprintf(stderr, "cannot open file %s\n",infile);
        return NULL;
    }
    else
    {
        while(1)
        {
            fscanf(fp,"%d",ptr);
            if(*ptr == -1) break;
            else
            {
                ptr++;
                count++;
            }
        }
        for(int i=0; i<count;i++)
        {
            //printf("%d ",tmp[i]);
        }
        //printf("\ncount : %d\n",count);

        if(count%2==1)
        {
            W = (int*)malloc(sizeof(int));
            *W = tmp[count-1];
            //printf("total weight is : %d\n",*W);

        }
        else
        {
            W = (int*)malloc(sizeof(int)*2);
            *W = tmp[count-2];
            *(W+1) = tmp[count-1];
            //printf("total weight is : %d, %d\n",*W,*(W+1));
        }

        if(count%2==1)
        {
            sarynum = (count-1)/2;
            sary = (struct item*)malloc(sizeof(struct item)*sarynum);
        }
        else
        {
            sarynum = (count-2)/2;
            sary = (struct item*)malloc(sizeof(struct item)*sarynum);
        }
        //printf("sarynum(n)  = %d\n",sarynum);

        nWitem = (struct item*)malloc(sizeof(struct item));
        if(count%2==1)
        {
            nWitem->index = sarynum;
            nWitem->weight = *W;
            nWitem->value = 0;
        }
        else
        {
            nWitem->index = sarynum;
            nWitem->weight = *W;
            nWitem->value = *(W+1);
        }
        *wary = sary;
        *(wary+1) = nWitem;

        for(int i=0;i<sarynum;i++)
        {
            (sary+i)->index = i+1;
            (sary+i)->weight = tmp[2*i];
            (sary+i)->value = tmp[2*i+1];
            //printf("index is : %d   weight is : %d  value is : %d\n",(sary+i)->index,(sary+i)->weight,(sary+i)->value);
        }
    }
    fclose(fp);
    return wary;
  }
