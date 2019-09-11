#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-8;
const double inf = 1e20;
const double pi = acos(-1.0);
const int maxp = 1010;
int sgn(double x) {
    if (fabs(x) < eps) return 0;
    if (x < 0)
        return -1;
    else
        return 1;
}
struct Point {
    int x, y;
    Point() {}
    Point(int _x, int _y) {
        x = _x;
        y = _y;
    }
    void input() { scan_d(x),scan_d(y); }
    bool operator==(Point b) const {
        return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
    }
    bool operator < (Point b) const {
        return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x;
    }
}P[1010];

template <class T>
inline bool scan_d(T &ret) {
    char c;
    int sgn;
    if (c = getchar(), c == EOF) return 0;  // EOF
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9') ret = ret * 10 + (c - '0');
    ret *= sgn;
    return 1;
}

unordered_map<Point,int> mp;

int n,m;
int main() { 
    Point t;
    scan_d(n);
    for(int i=0;i<n;++i){
        P[i].input();
    }
    for(int i=0;i<n;++i){
        for(int j=i+1;j<n;++j){
            t.x=(P[i].x+P[j].x);
            t.y=(P[i].y+P[j].y);
            mp[t]+=1;
        }
    }
    int ans=0;
    for( auto x : mp){
        ans=max(ans,x.second);
    }
    printf("%d\n",ans);
    return 0; 
    
}