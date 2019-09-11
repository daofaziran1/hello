#include<bits/stdc++.h>
using namespace std;
int n,a;
vector<int> pre;
queue<int > in;
struct tree{
    int data;
    tree *l,*r;
    tree(){
        l=NULL;
        r=NULL;
        data=0;
    }
};
tree *sroot;
tree* rebuild(int l,int r){
    if(l==r){
        return NULL;
    }
    tree *root = new tree();
    int d=in.front();
    in.pop();
    for(int i=0;i<n;i++){
        if(pre[i]==d){
            root->data=d;
            root->l=rebuild(l,i);
            root->r=rebuild(i+1,r);
        }
    }
    return root;
}
void houxubianli(tree *root){{
    if(root==NULL){
        return;
    }
    houxubianli(root->l);
    houxubianli(root->r);
    printf("%d%c",root->data," \n"[root==sroot]);
}

}
void cengxubianli(tree *root)
{
    queue<tree *> t;
    t.push(root);
    while (!t.empty())
    {
        int temp=t.front()->data;
        if (t.front()->l != NULL)
            t.push(t.front()->l);
        if (t.front()->r != NULL)
            t.push(t.front()->r);
        t.pop();
        printf("%d%c",temp," \n"[t.empty()]);
    }
}
int main(){
    while(cin>>n){
        while(!pre.empty()){
            pre.pop_back();
        }
        for (int i = 0; i < n; i++){
          cin >> a;
           in.push(a);
        }
        for(int i=0;i<n;i++){
            cin>>a;
            pre.push_back(a);
        }
        sroot=rebuild(0,n);
        houxubianli(sroot);
    }
    return 0;
}