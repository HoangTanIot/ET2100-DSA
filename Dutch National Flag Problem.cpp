#include <iostream>
#define MAX_SIZE 1000  // Giới hạn kích thước mảng

/*
  Giải Thích Bài Toán:
  --------------------
  - Ta có một mảng chỉ chứa các phần tử 0, 1 và 2.
  - Yêu cầu: Sắp xếp mảng theo thứ tự tăng dần sao cho tất cả các 0 ở đầu, tiếp theo là các 1 và cuối cùng là các 2.
  - Yêu cầu tối ưu về thời gian: $O(n)$ và không sử dụng bộ nhớ phụ.

  Ý tưởng thuật toán:
  -------------------
  - Sử dụng thuật toán "Dutch National Flag Problem" với ba con trỏ:
      + `low`: Vị trí kết thúc của vùng chứa toàn 0.
      + `mid`: Vị trí hiện tại đang xử lý.
      + `high`: Vị trí bắt đầu của vùng chứa toàn 2.
  - Khi `mid` vượt qua `high`, quá trình sắp xếp hoàn tất.

  Các bước thuật toán:
  ---------------------
  1. Nếu phần tử tại `mid` là 0: Đổi chỗ với `low` và tăng cả `low` và `mid`.
  2. Nếu phần tử tại `mid` là 1: Chỉ tăng `mid`.
  3. Nếu phần tử tại `mid` là 2: Đổi chỗ với `high` và giảm `high`.
*/

// Hàm in mảng
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// Thuật toán Dutch National Flag để sắp xếp mảng
void sortArray(int arr[], int n) {
    int low = 0, mid = 0;
    int high = n - 1;

    while (mid <= high) {
        if (arr[mid] == 0) {
            // Đổi chỗ arr[mid] với arr[low]
            int temp = arr[low];
            arr[low] = arr[mid];
            arr[mid] = temp;
            low++;
            mid++;
        } else if (arr[mid] == 1) {
            mid++;
        } else { // arr[mid] == 2
            // Đổi chỗ arr[mid] với arr[high]
            int temp = arr[mid];
            arr[mid] = arr[high];
            arr[high] = temp;
            high--;
        }
    }
}

// Hàm chính "driver": khởi tạo, gọi thuật toán và in kết quả
int main() {
    // Nhập số phần tử của mảng
    int n;
    int arr[MAX_SIZE];  // Khai báo mảng với kích thước tối đa

    std::cout << "Nhập số phần tử của mảng: ";
    std::cin >> n;

    if (n > MAX_SIZE) {
        std::cout << "Số phần tử vượt quá giới hạn!" << std::endl;
        return 1;
    }

    std::cout << "Nhập các phần tử của mảng (chỉ gồm 0, 1, 2): ";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
        if (arr[i] < 0 || arr[i] > 2) {
            std::cout << "Phần tử không hợp lệ! Vui lòng nhập lại." << std::endl;
            return 1;
        }
    }

    // In mảng trước khi sắp xếp
    std::cout << "Mảng trước khi sắp xếp: ";
    printArray(arr, n);

    // Gọi hàm sắp xếp
    sortArray(arr, n);

    // In mảng sau khi sắp xếp
    std::cout << "Mảng sau khi sắp xếp: ";
    printArray(arr, n);

    return 0;
}
