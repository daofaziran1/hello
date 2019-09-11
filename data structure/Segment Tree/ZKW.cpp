#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include<algorithm>
using namespace std;
const int N = 1e5;

struct node {
    int sum, d, v;
    int l, r;
    void init() {
        d = 0;
        v = -1;
    }
    void cb(node ls, node rs) {
        sum = ls.sum + rs.sum;
        l = ls.l, r = rs.r;
    }
    int len() { return r - l + 1; }
    void V(int x) {
        sum = len() * x;
        d = 0;
        v = x;
    }
    void D(int x) {
        sum += len() * x;
        d += x;
    }
};

struct tree {
    int m, h;
    node g[N << 2];
    void build(int n) {
        for (m = h = 1; m < n + 2; m <<= 1, h++);
        int i = 0;
        for (; i <= m; i++) {
            g[i].init();
            g[i].sum = 0;
        }
        for (; i <= m + n; i++) {
            g[i].init();
            scanf("%d", &g[i].sum);
            g[i].l = g[i].r = i - m;
        }
        for (; i < m + m; i++) {
            g[i].init();
            g[i].sum = 0;
            g[i].l = g[i].r = i - m;
        }
        for (i = m - 1; i > 0; i--) g[i].cb(g[i << 1], g[i << 1 | 1]);
    }
    void dn(int x) {
        for (int i = h - 1; i > 0; i--) {
            int f = x >> i;
            if (g[f].v != -1) {
                g[f << 1].V(g[f].v);
                g[f << 1 | 1].V(g[f].v);
            }
            if (g[f].d) {
                g[f << 1].D(g[f].d);
                g[f << 1 | 1].D(g[f].d);
            }
            g[f].v = -1;
            g[f].d = 0;
        }
    }
    void up(int x) {
        for (x >>= 1; x; x >>= 1) {
            if (g[x].v != -1) continue;
            int d = g[x].d;
            g[x].d = 0;
            g[x].cb(g[x << 1], g[x << 1 | 1]);
            g[x].D(d);
        }
    }
    void update(int l, int r, int x, int o) {
        l += m - 1, r += m + 1;
        dn(l), dn(r);
        for (int s = l, t = r; s ^ t ^ 1; s >>= 1, t >>= 1) {
            if (~s & 1) {
                if (o)
                    g[s ^ 1].V(x);
                else
                    g[s ^ 1].D(x);
            }
            if (t & 1) {
                if (o)
                    g[t ^ 1].V(x);
                else
                    g[t ^ 1].D(x);
            }
        }
        up(l), up(r);
    }
    int Q(int l, int r) {
        int ans = 0;
        l += m - 1, r += m + 1;
        dn(l), dn(r);
        for (int s = l, t = r; s ^ t ^ 1; s >>= 1, t >>= 1) {
            if (~s & 1) ans += g[s ^ 1].sum;
            if (t & 1) ans += g[t ^ 1].sum;
        }
        return ans;
    }
};
