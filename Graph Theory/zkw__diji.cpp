#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef long long LL;
typedef long long int;
namespace IO {

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
}  // namespace IO

template <typename T>
struct ZkwHeapNode {
    T value;
    size_t mark;
    ZkwHeapNode() {}
    ZkwHeapNode(const T &_value) : value(_value) {}
};

template <typename T, typename Comp>
class ZkwHeap {
   private:
    typedef ZkwHeapNode<T> Node;
    typedef ZkwHeap<T, Comp> Heap;

    Comp cmp;
    Node *NodeList;
    size_t n;
    int init_value;

    void fix(size_t _pos) {
        if (cmp(NodeList[_pos << 1].value, NodeList[(_pos << 1) + 1].value))
            NodeList[_pos] = NodeList[(_pos << 1) + 1];
        else
            NodeList[_pos] = NodeList[_pos << 1];
    }

   public:
    ZkwHeap(const size_t &_MaxN, const T &_init_value)
        : init_value(_init_value) {
        n = 1 << (1 + (size_t)(log(_MaxN) / log(2.0)));
        NodeList = new Node[n << 1];
        for (size_t i = 1; i <= n + n - 1; i++) NodeList[i].value = init_value;
        for (size_t i = n; i <= n + n - 1; i++) NodeList[i].mark = i - n + 1;
    }

    ~ZkwHeap() { delete[] NodeList; }

    T top() { return NodeList[1].value; }

    T top_pos() { return NodeList[1].mark; }

    void modify(size_t _position, const T &_new_value) {
        int _pos = _position + n - 1;
        NodeList[_pos].value = _new_value;
        while (_pos) fix(_pos >>= 1);
    }

    T pop() {
        T return_value = NodeList[1].value;
        modify(NodeList[1].mark, init_value);
        return return_value;
    }
};
const int maxPoint = 100010;
const int maxEdge = 200010;

struct p {
    int to, dis, next;
} graph[maxEdge];
int  head[maxPoint];
int pointer = 0;
int dis[maxPoint];

int n, m, S, T;
int zkn;
ZkwHeap<int, greater<int>> tree(maxPoint, 100000000);

void init() {
    memset(head, 0, sizeof(head));
    memset(dis, 127 / 3, sizeof(head));
}

void push_edge(int from, int to, int dis) {
    graph[++pointer].to = to;
    graph[pointer].dis = dis;
    graph[pointer].next = head[from];
    head[from] = pointer;
}

void dijkstra(int from) {
    memset(dis, 127 / 3, sizeof(dis));
    dis[from] = 0;
    tree.modify(from, 0);
    for (int i = 2; i <= n; i++) {
        int kn = tree.top_pos();
        dis[kn] = tree.pop();
        // if (kn == T) {
        //     cout << dis[T] << endl;
        //     return;
        // }
        for (int k = head[kn]; k; k = graph[k].next) {
            if (dis[graph[k].to] > dis[kn] + graph[k].dis) {
                dis[graph[k].to] = dis[kn] + graph[k].dis;
                tree.modify(graph[k].to, dis[graph[k].to]);
            }
        }
    }
    // cout << dis[T] << endl;
}

signed main() {
    IO::scan_d(n), IO::scan_d(m), IO::scan_d(S);
    init();
    zkn = (1 << (int)((int)log(n) / log(2) + 1));
    int from, to, diss;
    for (int i = 1; i <= m; i++) {
        IO::scan_d(from), IO::scan_d(to), IO::scan_d(diss);
        push_edge(from, to, diss);
        push_edge(to, from, diss);
    }
    dijkstra(S);
    for (int i = 1; i <= n; ++i) {
        printf("%d ", dis[i]);
    }
    puts("");

return 0;
}