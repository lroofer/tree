#include <iostream>
#include <vector>
using namespace std;
struct Node {
    long int sumic; // the sum of children and key
    Node* l, * r;
    long int key, prior;
    Node() : l(nullptr), r(nullptr), sumic(0) {}
    Node(long int key) : key(key), prior((rand() << 15) + rand()), l(nullptr), r(nullptr), sumic(key) {}
};
Node* tmp1, * tmp2, * tmp3;
long int sum(Node* v) { return v ? v->sumic : 0; }
void upd(Node* v) {
    long int answer = v->key;
    if (v->l != nullptr)
        answer += sum(v->l);
    if (v->r != nullptr)
        answer += sum(v->r);
    v->sumic = answer;
}

void split(Node* root, Node*& l, Node*& r, long int k) { // node, left child, right child, split for what
    if (!root) {
        l = nullptr;
        r = nullptr;
        return;
    }
    if (root->key < k) {
        split(root->r, root->r, r, k);
        l = root;
        upd(l);
    }
    else {
        split(root->l, l, root->l, k);
        r = root;
        upd(r);
    }
}
void merg(Node*& root, Node* l, Node* r) {
    if (!l || !r) {
        return void(root = l ? l : r);
    }
    if (l->prior > r->prior) {
        merg(l->r, l->r, r);
        root = l;
        upd(root);
    }
    else {
        merg(r->l, l, r->l);
        root = r;
        upd(root);
    }
}
bool fin(Node*& root, long int x) {
    if (!root) {
        return false;
    }
    if (root->key == x) {
        return true;
    }
    if (root->key > x) {
        return fin(root->l, x);
    }
    else {
        return fin(root->r, x);
    }
}
void inset(Node*& root, long int x) {
    Node* ins = new Node(x);
    if (!fin(root, ins->key)) {
        split(root, tmp1, tmp2, x);
        merg(root, tmp1, ins);
        merg(root, root, tmp2);

    }
    upd(root);
}
typedef pair<Node*, Node*> Pair;
long int sum_p(Node* root, long int l, long int r) {
    Pair rq;
    split(root, rq.first, rq.second, r);
    Pair lq;
    split(rq.first, lq.first, lq.second, l);
    long int res = sum(lq.second);
    merg(rq.first, lq.first, lq.second);
    merg(root, rq.first, rq.second);
    // merge
    return res;
}
int main() {
    vector<long int> ans;
    long int n;
    Node* S = new Node();
    cin >> n;
    long int prev_y = NULL;
    for (long int i = 0; i < n; ++i) {
        char com;
        cin >> com;
        if (com == '+') {
            long int num;
            cin >> num;
            if (prev_y != NULL) {
                long int input = (prev_y + num) % 1000000000;
                inset(S, input);
                prev_y = NULL;
        
            }
            else {
                inset(S, num);
                
            }
        }
        else {
            long int l, r;
            cin >> l >> r;
            r++;
            prev_y = sum_p(S, l, r);
            ans.push_back(prev_y);
        }
        
    }
    for (long int i : ans) {
        cout << i << endl;
    }

    return 0;
}
