#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
using namespace std;
struct tree {
    int data;
    int high;
    struct tree *right, *left;
    tree() {
        right = NULL;
        left = NULL;
    }
    tree(int a) {
        data = a;
        right = NULL;
        left = NULL;
        high = 1;
    }
};
tree *newtree(int t) {
    tree *p = new tree();
    p->data = t;
    p->high = 1;
    return p;
}
int gethigh(tree *root) {
    if (root == NULL) return 0;
    return root->high;
}
int GetBanlanceNum(tree *root) {
    if (root == NULL) return 0;
    return gethigh(root->left) - gethigh(root->right);
}
void updatehigh(tree *root) {
    root->high = max(gethigh(root->left), gethigh(root->right)) + 1;
}
void L(tree* &root) {
    tree *temp = root->right;
    root->right = temp->left;
    temp->left = root;
    updatehigh(root);
    updatehigh(temp);
    root = temp;
}
void R(tree* &root) {
    tree *temp = root->left;
    root->left = temp->right;
    temp->right = root;
    updatehigh(root);
    updatehigh(temp);
    root = temp;
}
void insert(tree* &root, int t) {
    if (root == NULL) {
        root = new tree(t);
        return;
    }
    if (t < root->data) {
        insert(root->left, t);
        updatehigh(root);
        if (GetBanlanceNum(root) == 2) {
            if (GetBanlanceNum(root->left) == 1) {
                R(root);
            } else if (GetBanlanceNum(root->left) == -1) {
                L(root->left);
                R(root);
            }
        }
    } else {
        insert(root->right, t);
        updatehigh(root);
        if (GetBanlanceNum(root) == -2) {
            if (GetBanlanceNum(root->right) == -1) {
                L(root);
            } else if (GetBanlanceNum(root->right) == 1) {
                R(root->right);
                L(root);
            }
        }
    }
}
tree *create(int data[], int n) {
    tree *rot = new tree(data[0]);
    for (int i = 1; i < n; i++) {
        insert(rot, data[i]);
    }
    return rot;
}
int search(tree *root, int data) {
    if (root == NULL) {
        return 0;
    }
    if (root->data == data) {
        return 1;
    } else if (root->data > data) {
        return search(root->left, data);
    } else {
        return search(root->right, data);
    }
    return 0;
}
void zhongxubianli(tree *root) {
    if (root == NULL) return;
    zhongxubianli(root->left);
    printf("%d ", root->data);
    zhongxubianli(root->right);
}
int main() {
    tree *root = NULL;
    int n, a;
    cin >> n;
    while (n--) {
        cin >> a;
        insert(root, a);
    }
    zhongxubianli(root);
    return 0;
}