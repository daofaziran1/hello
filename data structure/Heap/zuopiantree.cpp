#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000;

int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while ((ch < '0') || (ch > '9')) {
        if (ch == '-') {
            f = -f;
        }
        ch = getchar();
    }
    while ((ch >= '0') && (ch <= '9')) {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

struct node {
    node* son[2];
    node* fa;
    int val, dist, pos;
};

node tnode[maxn + 10];
node* p[maxn + 10];
int n, m;

inline int upd_dist(node* now) {
    if (now->son[1] != NULL) {
        now->dist = now->son[1]->dist + 1;
    } else {
        now->dist = 0;
    }
    return 0;
}

node* merge(node* a, node* b) {
    if (a == NULL) {
        return b;
    }
    if (b == NULL) {
        return a;
    }
    if ((a->val > b->val) || ((a->val == b->val) && (a->pos > b->pos))) {
        std::swap(a, b);
    }
    a->son[1] = merge(a->son[1], b);
    a->son[1]->fa = a;
    if ((a->son[0] != NULL) && (a->son[1] != NULL) &&
        (a->son[0]->dist < a->son[1]->dist)) {
        std::swap(a->son[0], a->son[1]);
    } else if ((a->son[0] == NULL) && (a->son[1] != NULL)) {
        a->son[0] = a->son[1];
        a->son[1] = NULL;
    }
    upd_dist(a);
    return a;
}

node* getf(node* x) {
    if (x->fa == NULL) {
        return x;
    }
    return getf(x->fa);
}

int getmin_pop(node* x) {
    node* f = getf(x);
    int v = f->val;
    node* s = merge(f->son[0], f->son[1]);
    if (s != NULL) {
        s->fa = NULL;
    }
    f->pos = -1;
    return v;
}

int main() {
    n = read();
    m = read();
    for (int i = 1; i <= n; ++i) {
        p[i] = &tnode[i];
        p[i]->son[0] = p[i]->son[1] = p[i]->fa = NULL;
        p[i]->val = read();
        p[i]->dist = 0;
        p[i]->pos = i;
    }
    while (m--) {
        int op = read(), a = read();
        if (op == 1) {
            int b = read();
            if ((p[a]->pos == -1) || (p[b]->pos == -1)) {
                continue;
            }
            node* fa = getf(p[a]);
            node* fb = getf(p[b]);
            if (fa == fb) {
                continue;
            }
            merge(fa, fb);
        } else {
            if (p[a]->pos == -1) {
                puts("-1");
            } else {
                printf("%d\n", getmin_pop(p[a]));
            }
        }
    }
    return 0;
}