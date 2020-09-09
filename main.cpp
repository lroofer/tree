#include <iostream>
using namespace std;
struct Node{
    Node *l, *r;
    int key, prior;
    Node() : l(nullptr), r(nullptr){}
    Node(int key) : key(key), prior((rand() << 15) + rand()), l(nullptr), r(nullptr){}
};
Node *tmp1, *tmp2, *tmp3;
void split(Node *root, Node *&l, Node *&r, int k){ // node, left child, right child, split for what
    if (!root){
        l = nullptr;
        r = nullptr;
        return;
    }
    if (root->key < k){
        split(root->r, root->r, r, k);
        l = root;
    }
    else{
        split(root->l, l, root->l, k);
        r = root;
    }
}
void merg(Node *&root, Node *l, Node *r){
    if (!l || !r){
        return void(root=l?l:r);
    }
    if (l->prior > r->prior){
        merg(l->r, l->r, r);
        root = l;
    }
    else{
        merg(r->l, l, r->l);
        root = r;
    }
}
void inset(Node *&root, int x){
    Node *ins = new Node(x);
    split(root, tmp1, tmp2, x);
    merg(root, tmp1, ins);
    merg(root, root, tmp2);
}
void eras(Node *&root, int x){
    split(root, tmp1, tmp2, x);
    split(tmp2, tmp2, tmp3, x+1);
    merg(root, tmp1, tmp3);
}
bool fin(Node *&root, int x){
    if(!root){
        return false;
    }
    if (root->key == x){
        return true;
    }
    if (root->key > x){
        return fin(root->l, x);
    }
    else{
        return fin(root->r, x);
    }
}

