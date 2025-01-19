#include <iostream>
#define MAX_SIZE 1000

/*
  BÀI TOÁN "TÌM ĐỘ DÀI LỌN NHẤT CỦA DÃY CON LIÊN TIẾP CÓ TỔNG BẾNG GIÁ TRỊ CHO TRƯỜC"

  Mô tả bài toán:
  ---------------
  - Cho một mảng số nguyên và một số nguyên mục tiêu `target`.
  - Tìm độ dài lớn nhất của dãy con liên tiếp trong mảng mà tổng của nó bằng `target`.
*/

// Tìm độ dài lớn nhất của dãy con
int findMaxLengthSubarray(int arr[], int n, int target) {
    int prefix_sum[MAX_SIZE] = {0}; // Lưu trữ tổng tích lũy
    int prefix_index[MAX_SIZE];     // Lưu trữ chỉ số đầu tiên của prefix_sum
    for (int i = 0; i < MAX_SIZE; i++) {
        prefix_index[i] = -1; // Khởi tạo mỗi chỉ số là -1
    }

    int prefix_sum_value = 0;
    int max_length = 0;

    for (int i = 0; i < n; i++) {
        prefix_sum_value += arr[i];

        // Nếu tổng tới vị trí i bằng target
        if (prefix_sum_value == target) {
            max_length = i + 1;
        }

        // Nếu prefix_sum_value - target đã tồn tại
        int diff = prefix_sum_value - target;
        for (int j = 0; j < MAX_SIZE; j++) {
            if (prefix_index[j] != -1 && prefix_sum[j] == diff) {
                int length = i - prefix_index[j];
                if (length > max_length) {
                    max_length = length;
                }
            }
        }

        // Nếu prefix_sum_value chưa được thêm vào mảng
        bool exists = false;
        for (int j = 0; j < MAX_SIZE; j++) {
            if (prefix_sum[j] == prefix_sum_value && prefix_index[j] != -1) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            for (int j = 0; j < MAX_SIZE; j++) {
                if (prefix_index[j] == -1) {
                    prefix_sum[j] = prefix_sum_value;
                    prefix_index[j] = i;
                    break;
                }
            }
        }
    }

    return max_length;
}

// In chi tiết dãy con
void printSubarrayDetails(int arr[], int n, int target) {
    int prefix_sum[MAX_SIZE] = {0};
    int prefix_index[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++) {
        prefix_index[i] = -1;
    }

    int prefix_sum_value = 0;
    int max_length = 0;
    int start_index = -1;
    int end_index = -1;

    for (int i = 0; i < n; i++) {
        prefix_sum_value += arr[i];

        if (prefix_sum_value == target) {
            max_length = i + 1;
            start_index = 0;
            end_index = i;
        }

        int diff = prefix_sum_value - target;
        for (int j = 0; j < MAX_SIZE; j++) {
            if (prefix_index[j] != -1 && prefix_sum[j] == diff) {
                int length = i - prefix_index[j];
                if (length > max_length) {
                    max_length = length;
                    start_index = prefix_index[j] + 1;
                    end_index = i;
                }
            }
        }

        bool exists = false;
        for (int j = 0; j < MAX_SIZE; j++) {
            if (prefix_sum[j] == prefix_sum_value && prefix_index[j] != -1) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            for (int j = 0; j < MAX_SIZE; j++) {
                if (prefix_index[j] == -1) {
                    prefix_sum[j] = prefix_sum_value;
                    prefix_index[j] = i;
                    break;
                }
            }
        }
    }

    if (start_index != -1 && end_index != -1) {
        std::cout << "Dãy con có tổng bằng " << target << " là: [";
        for (int i = start_index; i <= end_index; i++) {
            std::cout << arr[i];
            if (i < end_index) {
                std::cout << ", ";
            }
        }
        std::cout << "]\n";
    } else {
        std::cout << "Không tìm thấy dãy con nào có tổng bằng " << target << ".\n";
    }
}

int main() {
    int n;
    int arr[MAX_SIZE];

    std::cout << "Nhập số phần tử của mảng: ";
    std::cin >> n;

    std::cout << "Nhập các phần tử của mảng: ";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    int target;
    std::cout << "Nhập tổng mục tiêu (target): ";
    std::cin >> target;

    int max_length = findMaxLengthSubarray(arr, n, target);
    std::cout << "\u0110ộ dài lớn nhất của dãy con có tổng bằng " << target << ": " << max_length << "\n";

    printSubarrayDetails(arr, n, target);

    return 0;
}
