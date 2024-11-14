#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char word[20];
    struct Node* next;
} Node;

// Hàm khởi tạo node mới
Node* createNode(const char* word) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->word, word);
    newNode->next = NULL;
    return newNode;
}

// Hàm thêm node vào danh sách liên kết
void addNode(Node** head, const char* word) {
    Node* newNode = createNode(word);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Hàm tìm từ xuất hiện nhiều nhất
char* findMostFrequentWord(Node* head) {
    Node* temp = head;
    Node* inner;
    int maxCount = 0;
    static char mostFrequentWord[20];

    while (temp != NULL) {
        int count = 1;
        inner = temp->next;
        while (inner != NULL) {
            if (strcmp(temp->word, inner->word) == 0) {
                count++;
            }
            inner = inner->next;
        }
        if (count > maxCount) {
            maxCount = count;
            strcpy(mostFrequentWord, temp->word);
        }
        temp = temp->next;
    }
    return mostFrequentWord;
}

// Hàm loại bỏ từ láy
void removeRedundantWords(Node** head) {
    Node* current = *head;
    Node* prev = NULL;

    while (current != NULL && current->next != NULL) {
        if (strcmp(current->word, current->next->word) == 0) {
            Node* temp = current->next;
            current->next = temp->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
}

// Hàm đếm số từ duy nhất trong danh sách
int countUniqueWords(Node* head) {
    Node* temp = head;
    Node* inner;
    int uniqueCount = 0;

    while (temp != NULL) {
        int isUnique = 1;
        inner = head;
        while (inner != temp) {
            if (strcmp(temp->word, inner->word) == 0) {
                isUnique = 0;
                break;
            }
            inner = inner->next;
        }
        if (isUnique) {
            uniqueCount++;
        }
        temp = temp->next;
    }
    return uniqueCount;
}

// Hàm xử lý câu và thêm vào danh sách liên kết
void processSentence(Node** head, const char* sentence) {
    char tempSentence[100];
    strcpy(tempSentence, sentence);
    char* word = strtok(tempSentence, " ");
    
    while (word != NULL) {
        addNode(head, word);
        word = strtok(NULL, " ");
    }
}

// Hàm giải phóng bộ nhớ của danh sách
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Hàm chính
int main() {
    char sentence[100];
    printf("Nhập câu: ");
    fgets(sentence, sizeof(sentence), stdin);
    sentence[strcspn(sentence, "\n")] = 0; // Loại bỏ ký tự xuống dòng

    Node* head = NULL;
    
    // Xử lý câu để lưu vào danh sách liên kết
    processSentence(&head, sentence);
    
    // Tìm từ xuất hiện nhiều nhất
    char* mostFrequent = findMostFrequentWord(head);
    printf("Từ xuất hiện nhiều nhất: %s\n", mostFrequent);
    
    // Loại bỏ từ láy
    removeRedundantWords(&head);
    
    // Đếm số từ vựng
    int uniqueWordCount = countUniqueWords(head);
    printf("Số lượng từ vựng: %d\n", uniqueWordCount);
    
    // Giải phóng bộ nhớ
    freeList(head);
    
    return 0;
}
