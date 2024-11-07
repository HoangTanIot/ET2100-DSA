#include <stdio.h> // Thư viện chuẩn cho các hàm nhập/xuất như printf và scanf

#define MAX_TERMS 100 // Định nghĩa số lượng tối đa các hạng tử trong đa thức là 100

// Định nghĩa cấu trúc cho một hạng tử đa thức
typedef struct {
    int coeff;  // Hệ số của hạng tử
    int exp;    // Bậc của hạng tử
} Term;

// Định nghĩa cấu trúc cho một đa thức
typedef struct {
    Term terms[MAX_TERMS]; // Mảng chứa các hạng tử của đa thức
    int n; // Số lượng hạng tử trong đa thức
} Polynomial;

// Hàm nhập đa thức từ người dùng
void inputPolynomial(Polynomial *p) {
    printf("Nhập số lượng hạng tử: ");
    scanf("%d", &p->n); // Nhập vào số lượng hạng tử và lưu vào p->n
    
    // Vòng lặp để nhập từng hạng tử
    for (int i = 0; i < p->n; i++) {
        printf("Nhập hệ số và bậc của hạng tử %d: ", i + 1);
        // Nhập hệ số và bậc cho từng hạng tử và lưu vào mảng terms của p
        scanf("%d %d", &p->terms[i].coeff, &p->terms[i].exp);
    }
}

// Hàm in đa thức theo định dạng mong muốn
void printPolynomial(Polynomial p) {
    for (int i = 0; i < p.n; i++) { // Duyệt qua từng hạng tử của đa thức
        if (i > 0 && p.terms[i].coeff > 0) { 
            printf(" + "); // Thêm dấu "+" nếu hệ số dương và không phải hạng tử đầu tiên
        } else if (p.terms[i].coeff < 0) { 
            printf(" - "); // Nếu hệ số âm, in dấu "-" phía trước
            printf("%d.x^%d", -p.terms[i].coeff, p.terms[i].exp); // In hệ số và bậc của hạng tử âm
            continue; // Bỏ qua lệnh phía sau và chuyển sang hạng tử tiếp theo
        }
        printf("%d.x^%d", p.terms[i].coeff, p.terms[i].exp); // In hệ số và bậc của hạng tử
    }
    printf(";\n"); // Xuống dòng sau khi in đa thức
}

// Hàm cộng hai đa thức và trả về kết quả là một đa thức mới
Polynomial addPolynomials(Polynomial p1, Polynomial p2) {
    Polynomial result; // Đa thức kết quả
    result.n = 0; // Số lượng hạng tử ban đầu của kết quả là 0
    int i = 0, j = 0; // Khởi tạo chỉ số cho hai đa thức đầu vào
    
    // Vòng lặp để cộng hai đa thức theo bậc
    while (i < p1.n && j < p2.n) {
        if (p1.terms[i].exp > p2.terms[j].exp) { // Nếu bậc của p1 lớn hơn bậc của p2
            result.terms[result.n++] = p1.terms[i++]; // Thêm hạng tử của p1 vào kết quả
        } else if (p1.terms[i].exp < p2.terms[j].exp) { // Nếu bậc của p2 lớn hơn bậc của p1
            result.terms[result.n++] = p2.terms[j++]; // Thêm hạng tử của p2 vào kết quả
        } else { // Nếu bậc của hai hạng tử bằng nhau
            result.terms[result.n].exp = p1.terms[i].exp; // Bậc giữ nguyên
            result.terms[result.n].coeff = p1.terms[i].coeff + p2.terms[j].coeff; // Hệ số là tổng của hai hệ số
            result.n++; // Tăng số lượng hạng tử trong kết quả
            i++; j++; // Di chuyển đến hạng tử tiếp theo trong cả hai đa thức
        }
    }
    
    // Thêm các hạng tử còn lại của đa thức p1 vào kết quả
    while (i < p1.n) {
        result.terms[result.n++] = p1.terms[i++];
    }
    // Thêm các hạng tử còn lại của đa thức p2 vào kết quả
    while (j < p2.n) {
        result.terms[result.n++] = p2.terms[j++];
    }
    
    return result; // Trả về đa thức kết quả
}

int main() {
    Polynomial f, g, h; // Khai báo ba đa thức f, g và h (kết quả)

    printf("Nhập đa thức f(x):\n");
    inputPolynomial(&f); // Nhập đa thức f từ người dùng
    printf("Nhập đa thức g(x):\n");
    inputPolynomial(&g); // Nhập đa thức g từ người dùng
    
    printf("f(x) = ");
    printPolynomial(f); // In đa thức f theo định dạng
    printf("g(x) = ");
    printPolynomial(g); // In đa thức g theo định dạng
    
    h = addPolynomials(f, g); // Tính tổng của f và g, lưu vào h
    
    printf("Tổng của hai đa thức h(x) = f(x) + g(x) là:\n");
    printf("h(x) = ");
    printPolynomial(h); // In đa thức h là kết quả tổng của f và g
    
    return 0; // Kết thúc chương trình
}
