#include <bits/stdc++.h>
using namespace std;

const int maxn = 100005;
struct node {
    node *ch[2];
    int key, fix, size, cnt;
    void maintain() { size = ch[0]->size + ch[1]->size + cnt; }
};
typedef node *P_node;
int max(int x, int y) { return x > y ? x : y; }
int min(int x, int y) { return x < y ? x : y; }
struct Treap {
    node base[maxn], nil;
    P_node root, null, len;
    Treap() {
        root = null = &nil;
        null->key = null->fix = 1e+9;
        null->size = null->cnt = 0;
        null->ch[0] = null->ch[1] = null;
        len = base;
    }
    P_node newnode(int tkey) {
        len->key = tkey;
        len->fix = rand();
        len->ch[0] = len->ch[1] = null;
        len->size = len->cnt = 1;
        return len++;
    }
    void rot(P_node &p, int d) {
        P_node k = p->ch[d ^ 1];
        p->ch[d ^ 1] = k->ch[d];
        k->ch[d] = p;
        p->maintain();
        k->maintain();
        p = k;
    }
    void _Insert(P_node &p, int tkey) {
        if (p == null)
            p = newnode(tkey);
        else if (p->key == tkey)
            p->cnt++;
        else {
            int d = tkey > p->key;
            _Insert(p->ch[d], tkey);
            if (p->ch[d]->fix > p->fix) rot(p, d ^ 1);
        }
        p->maintain();
    }
    void _Erase(P_node &p, int tkey) {
        if (p->key == tkey) {
            if (p->cnt > 1)
                p->cnt--;
            else if (p->ch[0] == null)
                p = p->ch[1];
            else if (p->ch[1] == null)
                p = p->ch[0];
            else {
                int d = p->ch[0]->fix > p->ch[1]->fix;
                rot(p, d);
                _Erase(p->ch[d], tkey);
            }
        } else
            _Erase(p->ch[tkey > p->key], tkey);
        p->maintain();
    }
    int _Kth(P_node p, int k) {
        if (p == null || k < 1 || k > p->size) return 0;
        if (k < p->ch[0]->size + 1) return _Kth(p->ch[0], k);
        if (k > p->ch[0]->size + p->cnt)
            return _Kth(p->ch[1], k - p->ch[0]->size - p->cnt);
        return p->key;
    }
    int _Rank(P_node p, int tkey, int res) {
        if (p->key == tkey) return p->ch[0]->size + res + 1;
        if (tkey < p->key) return _Rank(p->ch[0], tkey, res);
        return _Rank(p->ch[1], tkey, res + p->ch[0]->size + p->cnt);
    }
    int _Pred(P_node p, int tkey) {
        if (p == null) return -1e+9;
        if (tkey <= p->key) return _Pred(p->ch[0], tkey);
        return max(p->key, _Pred(p->ch[1], tkey));
    }
    int _Succ(P_node p, int tkey) {
        if (p == null) return 1e+9;
        if (tkey >= p->key) return _Succ(p->ch[1], tkey);
        return min(p->key, _Succ(p->ch[0], tkey));
    }
    void _Print(P_node p) {
        if (p == null) return;
        _Print(p->ch[0]);
        for (int i = 1; i <= p->cnt; i++) printf("%d ", p->key);
        _Print(p->ch[1]);
    }
    void Insert(int tkey) { _Insert(root, tkey); }
    void Erase(int tkey) { _Erase(root, tkey); }
    int Kth(int k) { return _Kth(root, k); }
    int Rank(int tkey) { return _Rank(root, tkey, 0); }
    int Pred(int tkey) { return _Pred(root, tkey); }
    int Succ(int tkey) { return _Succ(root, tkey); }
    void Print() {
        _Print(root);
        printf("\n");
    }
} T;
int n;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int pd, x;
        scanf("%d%d", &pd, &x);
        if (pd == 1) T.Insert(x);
        if (pd == 2) T.Erase(x);
        if (pd == 3) printf("%d\n", T.Rank(x));
        if (pd == 4) printf("%d\n", T.Kth(x));
        if (pd == 5) printf("%d\n", T.Pred(x));
        if (pd == 6) printf("%d\n", T.Succ(x));
    }
    return 0;
}
