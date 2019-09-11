#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ls t[x].ch[0]
#define rs t[x].ch[1]
using namespace std;
const int inf=2147483647;
const int maxn=5e4+1000;
int n,m;
int p[maxn];
struct node{
	int val,key,cnt,size;
	int ch[2];
};
node t[maxn*40];
int tot;
struct Treap{
	int root;
	void update(int x){
		t[x].size=t[ls].size+t[rs].size+t[x].cnt;
	}
	void rotate(int &x,int d){
		int son=t[x].ch[d];
		t[x].ch[d]=t[son].ch[d^1];
		t[son].ch[d^1]=x;update(x);update(x=son);
	}
	void insert(int &x,int val){
		if(!x){
			x=++tot;
			t[x].cnt=t[x].size=1;
			t[x].key=rand(),t[x].val=val;
			return ;
		}
		t[x].size++;
		if(t[x].val==val){t[x].cnt++;return;}
		int d=val>t[x].val;insert(t[x].ch[d],val);
		if(t[x].key>t[t[x].ch[d]].key) rotate(x,d);
	}
	void delet(int &x,int val){
		if(!x) return ;
		if(t[x].val==val){
			if(t[x].cnt>1){t[x].cnt--,t[x].size--;return ;}
			bool d=t[ls].key>t[rs].key;
			if(ls==0||rs==0) x=ls+rs;
			else rotate(x,d),delet(x,val);
		}
		else t[x].size--,delet(t[x].ch[t[x].val<val],val);
	}
	int rank(int x,int val){
		if(!x)return 0;
		if(t[x].val==val) return t[ls].size;
		if(t[x].val>val) return rank(ls,val);
		else return t[ls].size+t[x].cnt+rank(rs,val);
	}
	int kth(int x,int k){
		while(1){
			if(k<=t[ls].size)x=ls;
			else if(k>t[ls].size+t[x].cnt) k-=t[ls].size+t[x].cnt,x=rs;
			else return t[x].val;
		}
	}
	int pre(int x,int val){
		if(!x) return -inf;
		if(t[x].val>=val) return pre(ls,val);
		else return max(t[x].val,pre(rs,val));
	}
	int nxt(int x,int val){
		if(!x) return inf;
		if(t[x].val<=val) return nxt(rs,val);
		else return min(t[x].val,nxt(ls,val));
	}
}a[maxn<<2];
inline void read(int &x){
	x=0;char tmp=getchar();
	while(tmp<'0'||tmp>'9') tmp=getchar();
	while(tmp>='0'&&tmp<='9') x=(x<<1)+(x<<3)+tmp-'0',tmp=getchar();
}
inline void read(int &x,int &y){read(x),read(y);}
inline void read(int &x,int &y,int &z){read(x),read(y),read(z);}

void build(int x,int l,int r){
	for(int i=l;i<=r;i++)
		a[x].insert(a[x].root,p[i]);
	if(l==r) return ;
	build(x<<1,l,l+r>>1);
	build(x<<1|1,(l+r>>1)+1,r);
}
int queryrank(int x,int l,int r,int ql,int qr,int num){
	if(l>qr||r<ql) return 0;
	if(ql<=l&&r<=qr)
		return a[x].rank(a[x].root,num);
	int ret=0;
	ret+=queryrank(x<<1,l,l+r>>1,ql,qr,num);
	ret+=queryrank(x<<1|1,(l+r>>1)+1,r,ql,qr,num);
	return ret;
}
int queryval(int ql,int qr,int k){
	int l=0,r=1e8,mid,ans=-1;
	while(l<=r){
		mid=l+r>>1;
		if(queryrank(1,1,n,ql,qr,mid)+1<=k)ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}
void modify(int x,int l,int r,int pos,int k){
	if(pos<l||r<pos) return ;
	a[x].delet(a[x].root,p[pos]);
	a[x].insert(a[x].root,k);
	if(l==r) return ;
	modify(x<<1,l,l+r>>1,pos,k);
	modify(x<<1|1,(l+r>>1)+1,r,pos,k);
}
int querypre(int x,int l,int r,int ql,int qr,int k){
	if(l>qr||r<ql) return -inf;
	if(ql<=l&&r<=qr) return a[x].pre(a[x].root,k);
	int ret=querypre(x<<1,l,l+r>>1,ql,qr,k);
	ret=max(ret,querypre(x<<1|1,(l+r>>1)+1,r,ql,qr,k));
	return ret;
}
int querynxt(int x,int l,int r,int ql,int qr,int k){
	if(l>qr||r<ql) return inf;
	if(ql<=l&&r<=qr) return a[x].nxt(a[x].root,k);
	int ret=querynxt(x<<1,l,l+r>>1,ql,qr,k);
	ret=min(ret,querynxt(x<<1|1,(l+r>>1)+1,r,ql,qr,k));
	return ret;
}
int main(){
	srand(19260817);
	cin>>n>>m;
	for(int i=1;i<=n;i++)read(p[i]);
	build(1,1,n);
	int op;
	for(int i=1;i<=m;i++){
		int l,r,k,pos;
		read(op);
		if(op==1){
			read(l,r,k);
			printf("%d\n",queryrank(1,1,n,l,r,k)+1);
		}
		else if(op==2){
			read(l,r,k);
			printf("%d\n",queryval(l,r,k));
		}
		else if(op==3){
			read(pos,k);
			modify(1,1,n,pos,k);p[pos]=k;
		}
		else if(op==4){
			read(l,r,k);
			printf("%d\n",querypre(1,1,n,l,r,k));
		}
		else{
			read(l,r,k);
			printf("%d\n",querynxt(1,1,n,l,r,k));
		}
	}
	return 0;
}
