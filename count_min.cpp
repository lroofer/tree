#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct segtree{

    struct node{
        int min, cnt;
    };

    vector<node> tree;
    int size;
    void init(int n){
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size - 1, {0, 0});
    }

    node combine(node a, node b){
        if (a.min < b.min) return a;
        if (a.min > b.min) return b;
        return {a.min, a.cnt + b.cnt};
    }
    const node ZERO = {1000000000, 0};
    void build(vector<int> &a, int x, int lx, int rx){
        if(rx - lx == 1){
            if (lx < a.size())
                tree[x] = {a[lx], 1};
        } else{
            int m = (lx + rx) / 2;
            build(a, 2 * x + 1, lx, m);
            build(a, 2 * x + 2, m, rx);
            tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
        }
    }
    void build(vector<int> &a){
        init(a.size());
        build(a, 0, 0, size);
    }
    void set(int i, int v, int x, int lx, int rx){
        if (rx - lx == 1){
            tree[x] = {v, 1};
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m){
            set(i, v, 2 * x + 1, lx, m);
        } else{
            set(i, v, 2 * x + 2, m, rx);
        }
        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void set(int i, int v){
        set(i, v, 0, 0, size);
    }

    node min(int l, int r, int x, int lx, int rx){
        if (l >= rx || lx >= r){
            return ZERO;
        }
        if(lx >= l && rx <= r){
            return tree[x];
        }
        int m = (lx + rx) / 2;
        node s1 = min(l, r, 2 * x + 1, lx, m);
        node s2 = min(l, r, 2 * x + 2, m, rx);
        return combine(s1, s2);
    }
    node min(int l, int r){
        return min(l, r, 0, 0, size);
    }
};

int main() {
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    segtree st;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    st.build(a);
    for(int t = 0; t < m; t++){
        int c;
        cin >> c;
        if(c == 1){
            int i, v;
            cin >> i >> v;
            st.set(i, v);
        } else{
            int l, r;
            cin >> l >> r;
            segtree::node res = st.min(l, r);
            cout << res.min << " " << res.cnt << "\n";
        }
    }
    return 0;
}
