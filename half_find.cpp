#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool half1_find(int *a,int begin,int end,int x)
{
    int mid = (begin+end)/2;
    while(begin<=end){
        if(a[mid]==x) return 1;
        if(a[mid]<x) begin = ++mid;
        if(a[mid]>x) end = --mid;
        mid = (begin+end)/2;
    }
    return 0;
}

bool half2_find(int *a,int begin,int end,int x)
{
    int mid = (begin+end)/2;
    if(begin > end)
        return 0;
    if(a[mid] == x){
        return 1;
    }else if(a[mid] < x){
        begin = ++mid;
        half2_find(a,begin,end,x);
    }else if(a[mid] > x){
        end = --mid;
        half2_find(a,begin,end,x);
    }
}

void swap(int *a,int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void quicksort(int *a,int left,int right)
{

    int p = left, q = right;
    if(left > right)
        return;
    while(p < q){
        while(a[q] >= a[left] && p < q) q--;
        while(a[p] <= a[left] && p < q) p++;
        swap(&a[p],&a[q]);
    }
    swap(&a[left],&a[p]);
    quicksort(a,left,p-1);
    quicksort(a,p+1,right);
}

int main()
{
    int a[100],n,x,m;
    srand(time(NULL));
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        x = rand()%100+1;
        a[i] = x;
    }
    quicksort(a,1,n);
    for(int i = 1;i<=n;i++)
        printf("%d ",a[i]);
    if(half1_find(a,1,n,x))
        printf("1");
    if(half2_find(a,1,n,x))
        printf("\n1");
    return 0;
}
