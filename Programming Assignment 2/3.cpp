#include <iostream>
using namespace std;

struct node{
    int val;
    struct node* left;
    struct node* right;
};

struct node* create_new_node(int m);
void insert(struct node** T, int m);
struct node* Find(struct node* T, int m);
int Search(struct node* T, int m);
void Traversal(struct node* T);
struct node* parent(struct node *T, struct node *q);
void swap_with_pred_and_delete(struct node**T, struct node* q);
void Delete(struct node** T, int m);
void Delete_root(struct node** T);

int main(){
    int d;
    cin>>d;
    struct node* T = NULL;
    while(d--){
        char ch;
        int m;
        cin>>ch>>m;
        if(ch == 'B'){//Insert
            insert(&T,m);
        }
        else if (ch == 'S'){//Delete
            Delete(&T,m);
        }
        else if (ch == 'R'){//Search;
            if(Search(T,m)) cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
        }
        
    }
    // Traversal(T);
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct node* create_new_node(int m){
    struct node* temp = new struct node;
    temp->left = NULL;
    temp->right = NULL;
    temp->val = m;
    return temp;
}

void insert(struct node** T, int m){
    if(Search(*T, m)) return;
    if(*T==NULL){
        *T = create_new_node(m);
        return;
    }
    struct node* temp = create_new_node(m);
    struct node* p = *T;

    while(true){
        if(m < p->val){//Insert in left
             if(p->left != NULL) p = p->left;
            else{
                p->left = temp;
                break;
            }         
        }
        else if(m > p->val){//Insert in right
            if(p->right != NULL) p = p->right;
            else{
                p->right = temp;
                break;
            }
        }
    }
}

struct node* Find(struct node* T, int m){//Returns pointer to the node m.
    struct node *p = T;
    while(p != NULL){
        if(m == p->val){
            return p;
        }
        else if(m < p->val){
            p = p->left;
        }
        else{
            p = p->right;
        }
    }
    return NULL;
}

int Search(struct node* T, int m){// Checks whether m is in T or not.
    if(Find(T,m) != NULL) return 1;
    else return 0;
}

void Traversal(struct node* T){
    struct node* p = T;
    if(p == NULL) return;
    else{
        if(p->left != NULL) Traversal(p->left);
        cout<<p->val<<" ";
        if(p->right != NULL) Traversal(p->right);
    }
}

struct node* parent(struct node *T, struct node *q){
    struct node* p = T;
    if(q == T) return NULL; // If q is the root node
    while(true){
        if(q->val < p->val){
            if(p->left == q) return p;
            else p = p->left;
        }
        else if(q->val > p->val){
            if(p->right == q) return p;
            else p = p->right;
        }
    }
}

void swap_with_pred_and_delete(struct node**T, struct node* q){
    struct node* p = q;
    p = p->left;
    while(p->right != NULL){
        p = p->right;
    }
    int pred = p->val;
    Delete(T,pred);
    q->val = pred;
}

void Delete(struct node** T, int m){
    struct node* p = Find(*T,m);
    if(p == NULL) return;
    struct node* par = parent(*T,p);
    if(par == NULL){
        Delete_root(T);
        return;
    }
    if(p->left == NULL){
        if(par->left == p){
            par->left = p->right;
        }
        else if(par->right == p){
            par->right = p->right;
        }
    }
    else if(p->right == NULL){
        if(par->left == p){
            par->left = p->left;
        }
        else if(par->right == p){
            par->right = p->left;
        }
    }
    else{
        swap_with_pred_and_delete(T,p);
    }
}

void Delete_root(struct node** T){
    struct node* p = *T;
    if(p->left == NULL){
        (*T) = p->right;
    }
    else if(p->right == NULL){
        (*T) = p->left;
    }
    else{
        swap_with_pred_and_delete(T,p);
    }
}