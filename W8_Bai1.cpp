#include <stdio.h> // Thư viện chuẩn C để sử dụng printf và scanf

// Cấu trúc lưu trữ thông tin về ngày sinh
struct Ngay {
    int ngay;
    int thang;
    int nam;
};

// Cấu trúc lưu trữ thông tin về sinh viên
struct SinhVien {
    char maSV[8];       // Mã sinh viên (7 ký tự + 1 ký tự kết thúc chuỗi)
    char hoTen[50];     // Họ tên sinh viên (49 ký tự + 1 ký tự kết thúc chuỗi)
    int gioiTinh;       // Giới tính (0: Nữ, 1: Nam)
    Ngay ngaySinh;      // Ngày sinh
    char diaChi[100];   // Địa chỉ sinh viên
    char lop[12];       // Lớp sinh viên
    char khoa[7];       // Khoa sinh viên
};

// Cấu trúc nút trong danh sách liên kết để lưu trữ sinh viên
struct Node {
    SinhVien data;      // Dữ liệu sinh viên
    Node* link;         // Con trỏ đến nút tiếp theo trong danh sách
};

// Cấu trúc danh sách liên kết chứa các sinh viên
struct List {
    Node* first;        // Con trỏ đến nút đầu tiên của danh sách
    Node* last;         // Con trỏ đến nút cuối cùng của danh sách
};

// Hàm khởi tạo danh sách sinh viên rỗng
void initList(List &list) {
    list.first = NULL;
    list.last = NULL;
}

// Hàm so sánh mã sinh viên (so sánh từng ký tự của chuỗi)
int compareMaSV(char maSV1[], char maSV2[]) {
    for (int i = 0; i < 7; i++) {
        if (maSV1[i] < maSV2[i]) return -1;  // Trả về -1 nếu maSV1 nhỏ hơn maSV2
        if (maSV1[i] > maSV2[i]) return 1;   // Trả về 1 nếu maSV1 lớn hơn maSV2
    }
    return 0; // Trả về 0 nếu hai mã sinh viên bằng nhau
}

// Hàm thêm sinh viên vào danh sách đã sắp xếp theo mã sinh viên
void insertSorted(List &list, SinhVien sv) {
    Node* newNode = new Node;   // Tạo nút mới
    newNode->data = sv;         // Gán dữ liệu sinh viên vào nút mới
    newNode->link = NULL;       // Khởi tạo con trỏ link là NULL

    if (list.first == NULL || compareMaSV(sv.maSV, list.first->data.maSV) < 0) {
        // Thêm vào đầu danh sách nếu danh sách rỗng hoặc mã sinh viên là nhỏ nhất
        newNode->link = list.first;
        list.first = newNode;
        if (list.last == NULL) list.last = newNode; // Nếu danh sách rỗng, cập nhật last
    } else {
        // Tìm vị trí phù hợp để chèn vào danh sách
        Node* current = list.first;
        while (current->link != NULL && compareMaSV(current->link->data.maSV, sv.maSV) < 0) {
            current = current->link;
        }
        newNode->link = current->link; // Liên kết nút mới vào danh sách
        current->link = newNode;
        if (newNode->link == NULL) list.last = newNode; // Cập nhật last nếu là nút cuối
    }
}

// Hàm in danh sách sinh viên
void printList(const List &list) {
    Node* current = list.first;
    while (current != NULL) {
        printf("Ma SV: %s - Ho ten: %s\n", current->data.maSV, current->data.hoTen);
        current = current->link;
    }
}

// Hàm kiểm tra ngày sinh có giống nhau không
int sameBirthday(Ngay ngay1, Ngay ngay2) {
    return (ngay1.ngay == ngay2.ngay && ngay1.thang == ngay2.thang && ngay1.nam == ngay2.nam);
}

// Hàm in các sinh viên có cùng ngày sinh
void printStudentsWithSameBirthday(const List &list, Ngay ngaySinh) {
    Node* current = list.first;
    int found = 0; // Biến để kiểm tra xem có sinh viên nào cùng ngày sinh không

    while (current != NULL) {
        if (sameBirthday(current->data.ngaySinh, ngaySinh)) {
            printf("Ma SV: %s - Ho ten: %s\n", current->data.maSV, current->data.hoTen);
            found = 1;
        }
        current = current->link;
    }

    if (!found) {
        printf("Khong tim thay sinh vien cung ngay sinh\n");
    }
}

// Hàm xóa sinh viên có cùng ngày sinh
void removeStudentsWithSameBirthday(List &list, Ngay ngaySinh) {
    Node* current = list.first;
    Node* prev = NULL; // Con trỏ trỏ đến nút trước đó trong danh sách

    while (current != NULL) {
        if (sameBirthday(current->data.ngaySinh, ngaySinh)) {
            // Nếu tìm thấy sinh viên có cùng ngày sinh
            if (prev == NULL) {
                // Xóa sinh viên đầu danh sách
                list.first = current->link;
            } else {
                // Xóa sinh viên ở giữa hoặc cuối danh sách
                prev->link = current->link;
            }

            if (current->link == NULL) {
                list.last = prev; // Cập nhật nếu là nút cuối
            }

            Node* temp = current;
            current = current->link;
            delete temp; // Giải phóng bộ nhớ của nút đã xóa
        } else {
            prev = current;
            current = current->link;
        }
    }
}

int main() {
    List list; // Khởi tạo danh sách sinh viên
    initList(list); // Gọi hàm khởi tạo danh sách rỗng

    // Ví dụ thêm sinh viên
    SinhVien sv1 = {"001", "TaThiKimHue", 1, {1, 1, 1999}, "HaNoi", "CNTT", "IT"};
    SinhVien sv2 = {"002", "TranThiKimThoa", 1, {5, 7, 1999}, "HaiPhong", "DTVT", "ET"};
    SinhVien sv3 = {"003", "TranQuangAnh", 0, {6, 5, 2004}, "HaNoi", "DTVT", "ET-E9"};
    SinhVien sv4 = {"004", "TruongQuocAnh", 0, {6, 5, 2004}, "HaNoi", "DTVT", "ET-E9"};

    insertSorted(list, sv1); // Thêm sv1 vào danh sách
    insertSorted(list, sv2); // Thêm sv2 vào danh sách
    insertSorted(list, sv3); // Thêm sv3 vào danh sách
    insertSorted(list, sv4); // Thêm sv4 vào danh sách

    // In danh sách sinh viên
    printf("Danh sach sinh vien:\n");
    printList(list);

    // In sinh viên có cùng ngày sinh
    printf("\nSinh vien co cung ngay sinh 6/5/2004:\n");
    printStudentsWithSameBirthday(list, (Ngay){6, 5, 2004});

    // Xóa sinh viên có cùng ngày sinh
    removeStudentsWithSameBirthday(list, (Ngay){6, 5, 2004});

    // In lại danh sách sau khi xóa
    printf("\nDanh sach sinh vien sau khi xoa:\n");
    printList(list);

    return 0;
}
