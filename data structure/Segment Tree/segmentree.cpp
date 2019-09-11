//动态
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

struct node {
    node *ls, *rs;
    LL l, r;
    LL sum, minn, maxx;
    LL set_lazy, add_lazy;
    node(int ll, int rr) {
        l = ll, r = rr;
        if (ll == rr) {
            scanf("%lld", &sum);
            ls = NULL, rs = NULL;
        } else {
            int mid = (ll + rr) >> 1;
            ls = &node(ll, mid);
            rs = &node(mid + 1, rr);
        }
    }
    void push_down() {
        if (set_lazy) {
            ls->set_lazy = set_lazy;
            rs->set_lazy = set_lazy;
            ls->sum = (ls->r - ls->l + 1) * (set_lazy);
            ls->maxx = set_lazy;
            ls->minn = set_lazy;
            rs->sum = (rs->r - rs->l + 1) * (set_lazy);
            rs->maxx = set_lazy;
            rs->minn = set_lazy;
            add_lazy = 0, rs->add_lazy = 0, ls->add_lazy = 0;
            set_lazy = 0;
        } else if (add_lazy) {
            ls->add_lazy = add_lazy, rs->add_lazy = add_lazy;
            rs->sum += (rs->r - rs->l + 1) * (add_lazy);
            ls->sum += (ls->r - ls->l + 1) * (add_lazy);
            ls->maxx += add_lazy, rs->maxx += add_lazy;
            rs->minn += add_lazy, ls->minn += add_lazy;
            add_lazy = 0;
        }
    }
    inline void push_up() {
        if (l == r) return;
        sum = ls->sum + rs->sum;
        maxx = max(ls->maxx, rs->maxx);
        minn = min(ls->minn, rs->minn);
    }
    void set_(int ll, int rr, LL data) {
        push_down();
        if (l == ll && r == rr) {
            set_lazy = data;
            return;
        } else {
            int mid = (l + r) >> 1;
            if (r <= mid) {
                ls->set_(l, r, data);
            } else if (l > mid) {
                rs->set_(l, r, data);
            } else {
                ls->set_(l, mid, data);
                rs->set_(mid + 1, r, data);
            }
        }
        push_up();
    }
    void add_(int ll, int rr, int data) {
        push_down();
        if (l == ll && r == rr) {
            add_lazy = data;
            sum += (r - l + 1) * data;
            maxx += data;
            minn += data;
            return;
        }
        int mid = (l + r) >> 1;
        if (r <= mid) {
            ls->add_(l, r, data);
        } else if (l > mid) {
            rs->add_(l, r, data);
        } else {
            ls->add_(l, mid, data);
            rs->add_(mid + 1, r, data);
        }
    }
    LL QS(int ll, int rr) {
        push_down();
        if (l == ll && r == rr) {
            return sum;
        } else {
            int mid = (l + r) >> 1;
            if (r <= mid) {
                return ls->QS(l, r);
            } else if (l > mid) {
                return rs->QS(l, r);
            } else {
                return ls->QS(l, mid) + rs->QS(mid + 1, r);
            }
        }
    }
    LL QMX(int ll,int rr){
        push_down();
        if (l == ll && r == rr) {
            return maxx;
        } else {
            int mid = (l + r) >> 1;
            if (r <= mid) {
                return ls->QMX(l, r);
            } else if (l > mid) {
                return rs->QMX(l, r);
            } else {
                return max(ls->QMX(l, mid) ,rs->QMX(mid + 1, r));
            }
        }
    }
    LL QMN(int ll,int rr){
        push_down();
        if (l == ll && r == rr) {
            return minn;
        } else {
            int mid = (l + r) >> 1;
            if (r <= mid) {
                return ls->QMN(l, r);
            } else if (l > mid) {
                return rs->QMN(l, r);
            } else {
                return min(ls->QMN(l, mid) ,rs->QMN(mid + 1, r));
            }
        }
    }
};

node *root = NULL;

int main() {
    int n;

    return 0;
}