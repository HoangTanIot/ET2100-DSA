#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cấu trúc của một node trong cây biểu thức
typedef struct Node {
    char* value;         // Giá trị node (toán tử/toán hạng)
    struct Node* left;   // Con trái
    struct Node* right;  // Con phải
} Node;

// Hàm tạo node mới
Node* createNode(const char* value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = strdup(value);  // Sao chép chuỗi giá trị
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Hàm duyệt cây theo thứ tự trước (Pre-order)
void preOrderTraversal(Node* root) {
    if (root == NULL) return;
    printf("%s ", root->value);      // In giá trị tại node
    preOrderTraversal(root->left);  // Duyệt cây con trái
    preOrderTraversal(root->right); // Duyệt cây con phải
}

// Hàm duyệt cây theo thứ tự giữa (In-order)
void inOrderTraversal(Node* root) {
    if (root == NULL) return;
    inOrderTraversal(root->left);   // Duyệt cây con trái
    printf("%s ", root->value);     // In giá trị tại node
    inOrderTraversal(root->right);  // Duyệt cây con phải
}

// Hàm duyệt cây theo thứ tự sau (Post-order)
void postOrderTraversal(Node* root) {
    if (root == NULL) return;
    postOrderTraversal(root->left);  // Duyệt cây con trái
    postOrderTraversal(root->right); // Duyệt cây con phải
    printf("%s ", root->value);      // In giá trị tại node
}

// Hàm dựng cây biểu thức
Node* buildExpressionTree() {
    // Tạo các node nhỏ (lá hoặc nhánh con)
    Node* a = createNode("a");
    Node* five = createNode("5");
    Node* b = createNode("b");
    Node* c1 = createNode("c");
    Node* c2 = createNode("c");
    Node* eight = createNode("8");
    Node* d = createNode("d");
    Node* e = createNode("e");
    Node* half = createNode("1/2");

    // Tạo các toán tử
    Node* mulBC = createNode("*");  // 5 * b
    mulBC->left = five;
    mulBC->right = b;

    Node* divBC = createNode("/");  // (5 * b) / c
    divBC->left = mulBC;
    divBC->right = c1;

    Node* expC8 = createNode("^");  // c^8
    expC8->left = c2;
    expC8->right = eight;

    Node* expE = createNode("^");   // e^(1/2)
    expE->left = e;
    expE->right = half;

    Node* mulDE = createNode("*");  // d * e^(1/2)
    mulDE->left = d;
    mulDE->right = expE;

    // Gộp thành biểu thức lớn
    Node* add1 = createNode("+");   // a + (5 * b / c)
    add1->left = a;
    add1->right = divBC;

    Node* sub = createNode("-");    // (a + 5*b/c) - c^8
    sub->left = add1;
    sub->right = expC8;

    Node* finalAdd = createNode("+"); // ((a + 5*b/c) - c^8) + d*e^(1/2)
    finalAdd->left = sub;
    finalAdd->right = mulDE;

    return finalAdd; // Trả về cây biểu thức
}

int main() {
    // Dựng cây biểu thức
    Node* expressionTree = buildExpressionTree();

    // In cây theo ba cách duyệt
    printf("Duyet truoc (Pre-order): ");
    preOrderTraversal(expressionTree);
    printf("\n");

    printf("Duyet giua (In-order): ");
    inOrderTraversal(expressionTree);
    printf("\n");

    printf("Duyet sau (Post-order): ");
    postOrderTraversal(expressionTree);
    printf("\n");

    return 0;
}
