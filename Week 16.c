#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TITLE_LENGTH 100
#define MAX_CHILDREN 50

// Định nghĩa kiểu enum cho loại node
typedef enum {
    BOOK,
    CHAPTER,
    SECTION,
    SUBSECTION
} NodeType;

// Cấu trúc node trong cây
typedef struct BookNode {
    char title[MAX_TITLE_LENGTH];
    NodeType node_type;
    int pages;
    struct BookNode* children[MAX_CHILDREN];
    int children_count;
} BookNode;

// Nguyên mẫu các hàm
BookNode* create_node(const char* title, NodeType type, int pages);
void add_child(BookNode* parent, BookNode* child);
void remove_child(BookNode* parent, const char* child_title);
int count_chapters(BookNode* root);
BookNode* find_longest_chapter(BookNode* root);
BookNode* find_and_remove_section(BookNode* root, const char* section_title);
void update_page_count(BookNode* node, int total_pages);
void free_book_tree(BookNode* root);

// Tạo node mới
BookNode* create_node(const char* title, NodeType type, int pages) {
    BookNode* node = (BookNode*)malloc(sizeof(BookNode));
    strcpy(node->title, title);
    node->node_type = type;
    node->pages = pages;
    node->children_count = 0;
    return node;
}

// Thêm node con
void add_child(BookNode* parent, BookNode* child) {
    if (parent->children_count < MAX_CHILDREN) {
        parent->children[parent->children_count++] = child;
    }
}

// Xóa node con
void remove_child(BookNode* parent, const char* child_title) {
    for (int i = 0; i < parent->children_count; i++) {
        if (strcmp(parent->children[i]->title, child_title) == 0) {
            // Giải phóng bộ nhớ của node bị xóa
            free_book_tree(parent->children[i]);
            
            // Dịch chuyển các node còn lại
            for (int j = i; j < parent->children_count - 1; j++) {
                parent->children[j] = parent->children[j + 1];
            }
            parent->children_count--;
            break;
        }
    }
}

// Đếm số chương
int count_chapters(BookNode* root) {
    int count = 0;
    for (int i = 0; i < root->children_count; i++) {
        if (root->children[i]->node_type == CHAPTER) {
            count++;
        }
    }
    return count;
}

// Tìm chương dài nhất
BookNode* find_longest_chapter(BookNode* root) {
    BookNode* longest_chapter = NULL;
    int max_pages = 0;
    
    for (int i = 0; i < root->children_count; i++) {
        if (root->children[i]->node_type == CHAPTER && 
            root->children[i]->pages > max_pages) {
            longest_chapter = root->children[i];
            max_pages = root->children[i]->pages;
        }
    }
    
    return longest_chapter;
}

// Tìm và xóa mục
BookNode* find_and_remove_section(BookNode* root, const char* section_title) {
    for (int i = 0; i < root->children_count; i++) {
        // Kiểm tra trực tiếp ở node con
        if (strcmp(root->children[i]->title, section_title) == 0) {
            BookNode* found = root->children[i];
            remove_child(root, section_title);
            return found;
        }
        
        // Kiểm tra đệ quy ở các node cháu
        for (int j = 0; j < root->children[i]->children_count; j++) {
            if (strcmp(root->children[i]->children[j]->title, section_title) == 0) {
                BookNode* found = root->children[i]->children[j];
                remove_child(root->children[i], section_title);
                return found;
            }
        }
    }
    
    return NULL;
}

// Cập nhật số trang
void update_page_count(BookNode* node, int total_pages) {
    if (node->children_count == 0) {
        node->pages = total_pages;
        return;
    }
    
    // Phân bổ trang theo số lượng node con
    int remaining_pages = total_pages;
    for (int i = 0; i < node->children_count - 1; i++) {
        // Tạm thời phân bổ đều
        int child_pages = total_pages / node->children_count;
        update_page_count(node->children[i], child_pages);
        remaining_pages -= child_pages;
    }
    
    // Phần trang còn lại cho node con cuối
    update_page_count(node->children[node->children_count - 1], remaining_pages);
}

// Giải phóng bộ nhớ
void free_book_tree(BookNode* root) {
    if (root == NULL) return;
    
    // Giải phóng các node con
    for (int i = 0; i < root->children_count; i++) {
        free_book_tree(root->children[i]);
    }
    
    // Giải phóng node gốc
    free(root);
}

// Hàm main minh họa
int main() {
    // Tạo sách
    BookNode* book = create_node("Giáo Trình Khoa Học", BOOK, 300);
    
    // Tạo chương 1
    BookNode* chapter1 = create_node("Nhập Môn", CHAPTER, 0);
    BookNode* section1_1 = create_node("Khái Niệm Cơ Bản", SECTION, 0);
    BookNode* section1_2 = create_node("Phương Pháp Nghiên Cứu", SECTION, 0);
    add_child(chapter1, section1_1);
    add_child(chapter1, section1_2);
    
    // Tạo chương 2
    BookNode* chapter2 = create_node("Phân Tích Dữ Liệu", CHAPTER, 0);
    BookNode* section2_1 = create_node("Thống Kê", SECTION, 0);
    BookNode* subsection2_1_1 = create_node("Xác Suất", SUBSECTION, 0);
    add_child(section2_1, subsection2_1_1);
    BookNode* section2_2 = create_node("Phương Pháp Mô Hình Hóa", SECTION, 0);
    add_child(chapter2, section2_1);
    add_child(chapter2, section2_2);
    
    // Thêm chương vào sách
    add_child(book, chapter1);
    add_child(book, chapter2);
    
    // Cập nhật số trang
    update_page_count(book, 300);
    
    // Kiểm tra chức năng
    printf("Số chương trong sách: %d\n", count_chapters(book));
    
    // Tìm chương dài nhất
    BookNode* longest_chapter = find_longest_chapter(book);
    if (longest_chapter) {
        printf("Chương dài nhất: %s, Số trang: %d\n", 
               longest_chapter->title, longest_chapter->pages);
    }
    
    // Tìm và xóa mục
    BookNode* removed_section = find_and_remove_section(book, "Thống Kê");
    if (removed_section) {
        printf("Đã xóa mục: %s\n", removed_section->title);
    }
    
    // Giải phóng bộ nhớ
    free_book_tree(book);
    
    return 0;
}