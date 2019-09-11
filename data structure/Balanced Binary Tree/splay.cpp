#include <bits/stdc++.h>
#define N 100005
#define inf 1000000005
using namespace std;
inline int read() {
    register int x = 0, f = 1;
    register char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x * f;
}
inline void write(register int x) {
    if (!x) putchar('0');
    if (x < 0) x = -x, putchar('-');
    static int sta[36];
    int tot = 0;
    while (x) sta[tot++] = x % 10, x /= 10;
    while (tot) putchar(sta[--tot] + 48);
}
struct node {
    int v;
    int fa;
    int ch[2];
    int rec;
    int sum;
} tree[N];
int tot;
inline void update(register int x) {
    tree[x].sum =
        tree[tree[x].ch[0]].sum + tree[tree[x].ch[1]].sum + tree[x].rec;
}
inline bool findd(register int x) {
    return tree[tree[x].fa].ch[0] == x ? 0 : 1;
}
inline void connect(
    register int x, register int fa,
    register int son)  //把x转为fa的son(son是0/1，表示左孩子或右孩子)
{
    tree[x].fa = fa;
    tree[fa].ch[son] = x;
}
inline void rotate(register int x) {
    int Y = tree[x].fa;
    int R = tree[Y].fa;
    int Yson = findd(x);
    int Rson = findd(Y);
    int B = tree[x].ch[Yson ^ 1];
    connect(B, Y, Yson);
    connect(Y, x, Yson ^ 1);
    connect(x, R, Rson);
    update(Y), update(x);
}
inline void splay(register int x, register int to) {
    to = tree[to].fa;
    while (tree[x].fa != to) {
        int y = tree[x].fa;
        if (tree[y].fa == to)
            rotate(x);
        else if (findd(x) == findd(y))
            rotate(y), rotate(x);
        else
            rotate(x), rotate(x);
    }
}
inline int newpoint(register int v, register int fa) {
    tree[++tot].fa = fa;
    tree[tot].v = v;
    tree[tot].sum = tree[tot].rec = 1;
    return tot;
}
inline void Insert(register int x) {
    int now = tree[0].ch[1];
    if (tree[0].ch[1] == 0) {
        newpoint(x, 0);
        tree[0].ch[1] = tot;
    } else {
        while (19260817) {
            ++tree[now].sum;
            if (tree[now].v == x) {
                ++tree[now].rec;
                splay(now, tree[0].ch[1]);
                return;
            }
            int nxt = x < tree[now].v ? 0 : 1;
            if (!tree[now].ch[nxt]) {
                int p = newpoint(x, now);
                tree[now].ch[nxt] = p;
                splay(p, tree[0].ch[1]);
                return;
            }
            now = tree[now].ch[nxt];
        }
    }
}
inline int find(register int v) {
    int now = tree[0].ch[1];
    while (19260817) {
        if (tree[now].v == v) {
            splay(now, tree[0].ch[1]);
            return now;
        }
        int nxt = v < tree[now].v ? 0 : 1;
        if (!tree[now].ch[nxt]) return 0;
        now = tree[now].ch[nxt];
    }
}
inline void delet(register int x) {
    int pos = find(x);
    if (!pos) return;
    if (tree[pos].rec > 1) {
        --tree[pos].rec;
        --tree[pos].sum;
    } else {
        if (!tree[pos].ch[0] && !tree[pos].ch[1])
            tree[0].ch[1] = 0;
        else if (!tree[pos].ch[0]) {
            tree[0].ch[1] = tree[pos].ch[1];
            tree[tree[0].ch[1]].fa = 0;
        } else {
            int left = tree[pos].ch[0];
            while (tree[left].ch[1]) left = tree[left].ch[1];
            splay(left, tree[pos].ch[0]);
            connect(tree[pos].ch[1], left, 1);
            connect(left, 0, 1);
            update(left);
        }
    }
}
inline int rank(register int v) {
    int pos = find(v);
    return tree[tree[pos].ch[0]].sum + 1;
}
inline int arank(register int x) {
    int now = tree[0].ch[1];
    while (19260817) {
        int used = tree[now].sum - tree[tree[now].ch[1]].sum;
        if (x > tree[tree[now].ch[0]].sum && x <= used) {
            splay(now, tree[0].ch[1]);
            return tree[now].v;
        }
        if (x < used)
            now = tree[now].ch[0];
        else
            x -= used, now = tree[now].ch[1];
    }
}
inline int lower(register int v) {
    int now = tree[0].ch[1];
    int ans = -inf;
    while (now) {
        if (tree[now].v < v && tree[now].v > ans) ans = tree[now].v;
        if (v > tree[now].v)
            now = tree[now].ch[1];
        else
            now = tree[now].ch[0];
    }
    return ans;
}
inline int upper(register int v) {
    int now = tree[0].ch[1];
    int ans = inf;
    while (now) {
        if (tree[now].v > v && tree[now].v < ans) ans = tree[now].v;
        if (v < tree[now].v)
            now = tree[now].ch[0];
        else
            now = tree[now].ch[1];
    }
    return ans;
}
int main() {
    int m = read();
    while (m--) {
        int opt = read(), x = read();
        if (opt == 1)
            Insert(x);
        else if (opt == 2)
            delet(x);
        else if (opt == 3) {
            write(rank(x));
            printf("\n");
        } else if (opt == 4) {
            write(arank(x));
            printf("\n");
        } else if (opt == 5) {
            write(lower(x));
            printf("\n");
        } else {
            write(upper(x));
            printf("\n");
        }
    }
    return 0;
}