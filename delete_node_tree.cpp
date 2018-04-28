#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
    struct node *left;
    struct node *right;
    int data;
}*tree;

tree Create_tree(tree tr,int x)
{
    if(!tr){
        tr = (tree)malloc(sizeof(struct node));
        tr->data = x;
        tr->left = NULL;
        tr->right = NULL;
    }else if(x < tr->data){
        tr->left = Create_tree(tr->left,x);
    }else if(x > tr->data){
        tr->right = Create_tree(tr->right,x);
    }
    return tr;
}

void Output(tree tr)
{
    if(tr){
        Output(tr->left);
        printf("%d ",tr->data);
        Output(tr->right);
    }
}

tree Find_min(tree tr)
{
    while(tr->left){
        tr=tr->left;
    }
    return tr;
}

tree Delete_tree(tree tr,int x)
{
    if(!tr){
        return NULL;
    }else if(x < tr->data){
        tr->left = Delete_tree(tr->left,x);
    }else if(x > tr->data){
        tr->right = Delete_tree(tr->right,x);
    }else{
        tree st = tr;
        if(tr->left && tr->right){
            tree tmp = Find_min(tr->right);
            tr->data = tmp->data;
            tr = Delete_tree(tr->right,tr->data);
        }else if(tr->right == NULL){
            tr = tr->left;
        }else if(tr->left == NULL){
            tr = tr->right;
        }
        free(st);
        st = NULL;
    }
    return tr;
}

int main()
{
    int x,n;
    tree tr = NULL;
    srand(time(NULL));
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        x = rand()%100+1;
        tr = Create_tree(tr,x);
        printf("%d ",x);
    }
    printf("\n");
    Output(tr);
    tr = Delete_tree(tr,x);
    printf("\n");
    Output(tr);
    return 0;
}
