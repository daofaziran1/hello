#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+15;
const int inf=1e9+7;
int n,m,tot,root;
struct TREAP
{
    int l,r;
    int val,dat;
    int cnt,size;
}a[maxn];
inline void read(int &x)
{
    char ch=getchar();
    int s=0,f=1;
    while (!(ch>='0'&&ch<='9')) {if (ch=='-') f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9') {s=(s<<3)+(s<<1)+ch-'0';ch=getchar();}
    x=s*f;
}
int New(int val){
    a[++tot].val=val;
    a[tot].cnt=a[tot].size=1;
    a[tot].dat=rand();
    return tot;
}
void update(int p){
    a[p].size=a[a[p].l].size+a[p].cnt+a[a[p].r].size;
}
void build()
{
    New(-inf);New(inf);
    root=1;a[1].r=2;
    update(root);
}
int get_rank_by_val(int p,int val)
{
    if (!p) return 0;
    if (val==a[p].val) return a[a[p].l].size+1;
    if (val<a[p].val) return get_rank_by_val(a[p].l,val);
    return a[a[p].l].size+a[p].cnt+get_rank_by_val(a[p].r,val);
}
int get_val_by_rank(int p,int rank)
{
    if (!p) return inf;
    if (a[a[p].l].size>=rank) return get_val_by_rank(a[p].l,rank);
    if (a[a[p].l].size+a[p].cnt>=rank) return a[p].val;
    return get_val_by_rank(a[p].r,rank-a[a[p].l].size-a[p].cnt);
}
void zig(int &p)
{
    int q=a[p].l;
    a[p].l=a[q].r;a[q].r=p;p=q;
    update(a[p].r);update(p);
}
void zag(int &p)
{
    int q=a[p].r;
    a[p].r=a[q].l;a[q].l=p;p=q;
    update(a[p].l);update(p);
}
void insert(int &p,int val)
{
    if (!p){
         p=New(val);
         return;
    }
    if (val==a[p].val){
        a[p].cnt++;update(p);
        return;
    }
    if (val<a[p].val){
        insert(a[p].l,val);
        if (a[p].dat<a[a[p].l].dat) zig(p);
    }
    else {
        insert(a[p].r,val);
        if (a[p].dat<a[a[p].r].dat) zag(p);
    }
    update(p);
}
int getpre(int val)
{
    int ans=1;
    int p=root;
    while (p){
        if (val==a[p].val){
            if (a[p].l>0) {
            p=a[p].l;
            while (a[p].r>0) p=a[p].r;
            ans=p;
            }
            break;
        }
        if (a[p].val<val&&a[p].val>a[ans].val) ans=p;
        if (val<a[p].val) p=a[p].l;else p=a[p].r;
    }
    return a[ans].val;
}
int getnext(int val)
{
    int ans=2;
    int p=root;
    while (p){
        if (val==a[p].val){
            if (a[p].r>0){
            p=a[p].r;
            while (a[p].l>0) p=a[p].l;
            ans=p;
            }
            break;
        }
        if (a[p].val>val&&a[p].val<a[ans].val) ans=p;
        if (val<a[p].val) p=a[p].l;else p=a[p].r;
    }
    return a[ans].val;
}
void remove(int &p,int val)
{
    if (!p) return;
    if (val==a[p].val){
        if (a[p].cnt>1) {
            a[p].cnt--;update(p);
            return;
        }
        if (a[p].l||a[p].r){
            if (a[p].r==0||a[a[p].l].dat>a[a[p].r].dat){
                zig(p);remove(a[p].r,val);
            }
            else {
                zag(p);remove(a[p].l,val);
            }
            update(p);
        }
        else p=0;
        return;
    }
    if (val<a[p].val) remove(a[p].l,val);else remove(a[p].r,val);
    update(p);
}
int main()
{
    int opt;
    build();
    read(n);
    while (n--)
    {
        read(opt);int x;
        read(x);
        if (opt==1) insert(root,x); 
        if (opt==2) remove(root,x);
        if (opt==3) printf("%d\n",get_rank_by_val(root,x)-1);
        if (opt==4) printf("%d\n",get_val_by_rank(root,x+1));
        if (opt==5) printf("%d\n",getpre(x));
        if (opt==6) printf("%d\n",getnext(x));
    }
    return 0;
}