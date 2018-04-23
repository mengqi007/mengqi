#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <algorithm>
using namespace std;

typedef struct node
{
    struct node *left;
    struct node *right;
    int data;
}*tree;

int i = 0;

/*void Create_tree(tree *tr)
{
    int x = 0;
    scanf("%d",&x);
    if(x == -1)
        *tr = NULL;
    else{
         printf("$$$\n");
        *tr = (tree)malloc(sizeof(struct node));
        (*tr)->data = x;
        Create_tree(&((*tr)->left));
        Create_tree(&((*tr)->right));
    }
}*/

tree Create_tree(tree tr,int x)
{
    if(tr == NULL){
        tr = (tree)malloc(sizeof(struct node));
        tr->left = NULL;
        tr->right = NULL;
        tr->data = x;
    }else if(x < tr->data){
        tr->left = Create_tree(tr->left,x);
    }else if(x > tr->data){
        tr->right = Create_tree(tr->right,x);
    }
    return tr;
}

void level_order(tree tr)
{
    queue<tree>q;
    if(!tr)
        return;
    q.push(tr);
    while(!q.empty()){
        tr = q.front();
        q.pop();
        printf("%d ",tr->data);
        if(tr->left) q.push(tr->left);
        if(tr->right) q.push(tr->right);
    }
}

int max(int x,int y)
{
    return x>y?x:y;
}

int tree_high(tree tr)
{
    if(!tr)
        return 0;
    int p = tree_high(tr->left);
    int q = tree_high(tr->right);
    return max(p,q)+1;
}

void leaves(tree tr)
{
    if(!tr->left && !tr->right) i++;
    leaves(tr->left);
    leaves(tr->right);
}

tree copy_tree(tree tr)
{
    tree st,s,t;
    if(tr){
        s = copy_tree(tr->left);
        t = copy_tree(tr->right);
        st = (tree)malloc(sizeof(struct node));
        st->left = s;
        st->right = t;
        st->data = tr->data;
    }else{
        return NULL;
    }
    return st;
}

bool Judge_equal_tree(tree tr1,tree tr2)
{
    if(tr1 && tr2){
        if(tr1->data == tr2->data){
            if(Judge_equal_tree(tr1->left,tr2->left) && Judge_equal_tree(tr1->right,tr2->right) ||Judge_equal_tree(tr1->left,tr2->right) && Judge_equal_tree(tr1->right,tr2->left))
                return 1;
        }
        else
            return 0;
    }
    if(!tr1 && !tr2)
        return 1;
    else
        return 0;
}

bool Judge_smiliar_tree(tree tr1,tree tr2)
{
    if(!tr1 && !tr2 || tr1 && tr2){
        if(Judge_equal_tree(tr1->left,tr2->left) && Judge_equal_tree(tr1->right,tr2->right) ||Judge_equal_tree(tr1->left,tr2->right) && Judge_equal_tree(tr1->right,tr2->left))
            return 1;
    }
    return 0;
}

/*bool Judge_smiliar_tree(tree tr1,tree tr2)
{
    if(!tr1 || !tr2)
        return (tr1==NULL) && (tr2==NULL)
    return Judge_smiliar_tree(tr1->left,tr2->left)&&Judge_smiliar_tree(tr1->right,tr2->right);
} */

tree exchange(tree tr)
{
    if(!tr) return NULL;
    tree p = exchange(tr->left);
    tree q = exchange(tr->right);
    tr->left = q;
    tr->right = p;
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

int main()
{
    tree tr = NULL,tr3=NULL;
    int x,n;
    //Create_tree(&tr);
    srand(time(NULL));
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        x = rand()%100+1;
        tr = Create_tree(tr,x);
    }
    Output(tr);
    printf("\n");
    level_order(tr);
    printf("\n%d\n",tree_high(tr));
    tr3 = copy_tree(tr);
    Output(tr3);
    if(Judge_equal_tree(tr,tr3))
        printf("\n1");
    if(Judge_smiliar_tree(tr,tr3))
        printf("\n1");
    printf("\n");
    tr = exchange(tr);
    Output(tr);
    return 0;
}
