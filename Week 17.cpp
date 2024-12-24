//Cài đặt cây AVL với các hàm theo yêu cầu sau:
//* Khai báo cấu trúc cây AVL
//* Cài đặt hàm thực hiện các phép xoay đơn, xoay kép để cân bằng cây 
//* Cài đặt hàm bổ sung thêm một node mới trên cây AVL 
//* Sử dụng mảng cho trên lớp để làm bộ kiểm tra đầu vào, in ra cây AVL theo từng bước bổ sung thêm phân tử theo các phép duyệt cây 
//* Chú ý nộp bài đúng hạn
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
};

class AVLTree {
private:
    Node* root;
    
    // Hàm lấy chiều cao của node
    int getHeight(Node* node) {
        if (node == nullptr) return 0;
        return node->height;
    }
    
    // Hàm lấy độ cân bằng
    int getBalance(Node* node) {
        if (node == nullptr) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }
    
    // Cập nhật chiều cao
    void updateHeight(Node* node) {
        if (node == nullptr) return;
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }
    
    // Xoay phải
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        updateHeight(y);
        updateHeight(x);
        
        return x;
    }
    
    // Xoay trái 
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        updateHeight(x);
        updateHeight(y);
        
        return y;
    }
    
    // Chèn node mới
    Node* insert(Node* node, int data) {
        if (node == nullptr) {
            Node* newNode = new Node();
            newNode->data = data;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->height = 1;
            return newNode;
        }
        
        if (data < node->data)
            node->left = insert(node->left, data);
        else if (data > node->data)
            node->right = insert(node->right, data);
        else
            return node;
            
        updateHeight(node);
        
        int balance = getBalance(node);
        
        // Trường hợp Left Left
        if (balance > 1 && data < node->left->data)
            return rightRotate(node);
            
        // Trường hợp Right Right    
        if (balance < -1 && data > node->right->data)
            return leftRotate(node);
            
        // Trường hợp Left Right
        if (balance > 1 && data > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        
        // Trường hợp Right Left
        if (balance < -1 && data < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        return node;
    }
    
    // In theo thứ tự trước
    void preOrder(Node* node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }
    
    // In theo thứ tự giữa
    void inOrder(Node* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }
    
    // In theo thứ tự sau
    void postOrder(Node* node) {
        if (node == nullptr) return;
        postOrder(node->left);
        postOrder(node->right);
        cout << node->data << " ";
    }

public:
    AVLTree() {
        root = nullptr;
    }
    
    void insert(int data) {
        root = insert(root, data);
        cout << "\nSau khi chèn " << data << ":\n";
        cout << "Duyệt trước: "; preOrder(root); cout << endl;
        cout << "Duyệt giữa: "; inOrder(root); cout << endl;
        cout << "Duyệt sau: "; postOrder(root); cout << endl;
    }
};

int main() {
    AVLTree tree;
    
    // Mảng test
    int arr[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    for(int i = 0; i < n; i++) {
        tree.insert(arr[i]);
    }
    
    return 0;
}