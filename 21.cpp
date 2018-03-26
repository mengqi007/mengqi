#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node
{
    int data;
    int high;
    struct node *left;
    struct node *right;
};

typedef struct node *position;
typedef struct node *tree;

int get_high(position p)
{
    if(p==NULL){
        return -1;
    }else{
        return p->high;
    }
}

int max(int a,int b)
{
    return a>b?a:b;
}

position singleft(position p)
{
    position q=p->right;
    p->right=q->left;
    q->left=p;

    p->high=1+max(get_high(p->left),get_high(p->right));
    q->high=1+max(get_high(q->right),get_high(p));

    return q;
}

position singright(position p)
{
    position q=p->left;
    p->left=q->right;
    q->right=p;

    p->high=1+max(get_high(p->left),get_high(p->right));
    q->high=1+max(get_high(q->left),get_high(p));

    return q;
}

int fabs(int x)
{
    return x>=0? x:-x;
}

position fix(position p)
{
    p->high=1+max(get_high(p->left),get_high(p->right));

    if(fabs(get_high(p->left)-get_high(p->right))>1){
        if(get_high(p->left)>get_high(p->right)){
            if(get_high(p->left->left)>get_high(p->left->right)){
                p=singright(p);
            }else{
                p->left=singleft(p->left);
                p=singright(p);
            }
        }else{
            if(get_high(p->right->right)>get_high(p->right->left)){
                p=singleft(p);
            }else{
                p->right=singright(p->right);
                p=singleft(p);
            }
        }
        p->high=1+max(get_high(p->left),get_high(p->right));
    }

    return p;
}

tree insert(tree t,int x)
{
    if(t==NULL){
        t=malloc(sizeof(struct node));
        t->data=x;
        t->left=t->right=NULL;
        t->high=0;
    }else if(x<t->data){
        t->left=insert(t->left,x);
    }else if(x>t->data){
        t->right=insert(t->right,x);
    }

    if(t!=NULL){
        t=fix(t);
    }

    return t;
}

void dfs(tree t)
{
    if(t==NULL){
        return ;
    }

    printf("%d %d\n",t->data,t->high);
    dfs(t->left);
    dfs(t->right);
}

void dfs_2(tree t)
{
    if(t==NULL){
        return ;
    }

    dfs_2(t->left);
    printf("%d %d\n",t->data,t->high);
    dfs_2(t->right);
}

void tree_destory(tree t)
{
    if(t==NULL){
        return ;
    }

    tree_destory(t->left);
    tree_destory(t->right);
    free(t);
    t=NULL;
}

position find_min(tree t)
{
    if(t==NULL){
        return t;
    }
    if(t->left){
        return find_min(t->left);
    }else{
        return t;
    }
}

tree tree_remove(tree t,int x)
{
    if(t==NULL){
        return t;
    }

    if(x<t->data){
        t->left=tree_remove(t->left,x);
    }else if(x>t->data){
        t->right=tree_remove(t->right,x);
    }else if(t->left&&t->right){
        position p=find_min(t->right);
        t->data=p->data;
        t->right=tree_remove(t->right,t->data);
    }else{
        position p=t;
        if(t->left==NULL){
            t=t->right;
        }else if(t->right==NULL){
            t=t->left;
        }

        free(p);
        p=NULL;
    }

    if(t){
        t=fix(t);
    }

    return t;
}

int main()
{
    tree t=NULL;
    int n;
    int x;

    srand(time(NULL));

    scanf("%d",&n);
    for(int i=0;i<n;i++){
        x=rand()%100;
        printf("%d ",x);
        //scanf("%d",&x);
        t=insert(t,x);
    }
    printf("\n");

    dfs(t);
    printf("\n");
    dfs_2(t);

    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&x);
        t=tree_remove(t,x);
        dfs(t);
        printf("\n");
        dfs_2(t);
        printf("\n");
    }

    tree_destory(t);

    return 0;
}
