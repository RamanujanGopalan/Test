#include <bits/stdc++.h>
using namespace std;

int max(int a, int b){
    return (a>b)? a:b;
}

struct Node {
    int data;
    Node* lchild;
    Node* rchild;
    int height;

    Node(int value): data(value), lchild(nullptr), rchild(nullptr), height(0) {}
};

int node_height(Node* node) {
    return (node == nullptr) ? -1 : node->height;
}

int node_balance(Node* node) {
    if (node == nullptr){return 0;}
    return node_height(node->lchild) - node_height(node->rchild);
}

Node* rotate_right(Node* &x) {
    Node* y = x->lchild;
    Node* temp = y->rchild;

    y->rchild = x;
    x->lchild = temp;

    x->height = 1 + max(node_height(x->lchild), node_height(x->rchild));
    y->height = 1 + max(node_height(y->lchild), node_height(y->rchild));

    return y;
}

Node* rotate_left(Node* &x) {
    Node* y = x->rchild;
    Node* temp = y->lchild;

    y->lchild = x;
    x->rchild = temp;

    x->height = 1 + max(node_height(x->lchild), node_height(x->rchild));
    y->height = 1 + max(node_height(y->lchild), node_height(y->rchild));

    return y;
}

class AVL {
public:
    Node* root;

    AVL(): root(nullptr) {}

    Node* insert(Node* &root, int val) {
        if (root == nullptr) {
            root = new Node(val);
            return root;
        }
        if (val < root->data) {
            root->lchild = insert(root->lchild, val);
        }
        else if (val > root->data) {
            root->rchild = insert(root->rchild, val);
        }
        else {
            cout << "DUPLICATE" << endl;
            return root;
        }

        root->height = 1 + max(node_height(root->lchild), node_height(root->rchild));

        int bf = node_balance(root);
        // cout<<bf<<endl;

        // LL
        if (bf > 1 && val < root->lchild->data)
            return rotate_right(root);

        // RR
        if (bf < -1 && val > root->rchild->data)
            return rotate_left(root);

        // LR
        if (bf > 1 && val > root->lchild->data) {
            root->lchild = rotate_left(root->lchild);
            return rotate_right(root);
        }

        // RL
        if (bf < -1 && val < root->rchild->data) {
            root->rchild = rotate_right(root->rchild);
            return rotate_left(root);
        }

        return root;
    }

    Node* deletion(Node* &root, int val) {
        if (root == nullptr)
            return root;

        if (val < root->data)
            root->lchild = deletion(root->lchild, val);
        else if (val > root->data)
            root->rchild = deletion(root->rchild, val);
        else {
            if (root->lchild == nullptr || root->rchild == nullptr) {
                Node* temp = root->lchild ? root->lchild : root->rchild;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                Node* temp = root->lchild;
                while (temp->rchild != nullptr)
                    temp = temp->rchild;
                root->data = temp->data;
                root->lchild = deletion(root->lchild, temp->data);
            }
        }

        if (root == nullptr)
            return root;

        root->height = 1 + max(node_height(root->lchild), node_height(root->rchild));

        int bf = node_balance(root);

        // LL
        if (bf > 1 && node_balance(root->lchild) >= 0)
            return rotate_right(root);

        // RR
        if (bf < -1 && node_balance(root->rchild) <= 0)
            return rotate_left(root);

        // LR
        if (bf > 1 && node_balance(root->lchild) < 0) {
            root->lchild = rotate_left(root->lchild);
            return rotate_right(root);
        }

        // RL
        if (bf < -1 && node_balance(root->rchild) > 0) {
            root->rchild = rotate_right(root->rchild);
            return rotate_left(root);
        }

        return root;
    }

    // TRAVERSAL
    void preorder(Node* root) {
        if (root == nullptr) return;
        cout << root->data << " ";
        preorder(root->lchild);
        preorder(root->rchild);
    }

    Node* search(Node* root, int val){
        if (root == nullptr){
            cout<<"NOT FOUND"<<endl;
            return root;
        }
        if (val<root->data){
            return search(root->lchild, val);
        }
        if (val>root->data){
            return search(root->rchild, val);
        }
        if (root->data = val){
            cout<<"FOUND"<<endl;
            return root;
        }
        return root;
    }
};

int main() {
    AVL tree;
    cout << "n: ";
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int temp; cin >> temp;
        tree.root = tree.insert(tree.root, temp);
    }

    cout << "PRE: ";
    tree.preorder(tree.root);
    cout<<endl;

    Node* test = tree.search(tree.root, 4);
}
