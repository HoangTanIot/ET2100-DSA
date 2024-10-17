// Bài 2: Thiết kế giải thuật và cài đặt để tạo ra một mảng số nửa nguyên tố (Blum) nhỏ hơn một số N cho trước và thực hiện hai yêu cầu sau:
// - Tìm ra tất cả các cặp số Blum có tổng cũng là một số Blum nhỏ hơn N
// - Kiểm tra xem một số Blum M có tồn tại trong dãy số Blum được tạo ra hay không.

#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>

using namespace std;

// Hàm kiểm tra số nguyên tố
bool isPrime(int num) {
    if (num < 2) {
        return false;
    }
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

// Hàm tạo mảng số Blum
vector<int> generateBlumNumbers(int N) {
    vector<int> blumNumbers;
    vector<int> primes;

    // Tìm tất cả các số nguyên tố nhỏ hơn sqrt(N) và kiểm tra điều kiện p ≡ 3 mod 4
    for (int p = 2; p <= sqrt(N); p++) {
        if (isPrime(p) && p % 4 == 3) {
            primes.push_back(p);
        }
    }

    // Tạo số Blum bằng cách nhân các cặp số nguyên tố thỏa mãn điều kiện trên
    for (int i = 0; i < primes.size(); i++) {
        for (int j = i + 1; j < primes.size(); j++) {
            int blumNumber = primes[i] * primes[j];
            if (blumNumber < N) {
                blumNumbers.push_back(blumNumber);
            }
        }
    }

    return blumNumbers;
}

// Hàm tìm tất cả các cặp số Blum có tổng cũng là số Blum
vector<pair<int, int>> findBlumPairs(const vector<int>& blumNumbers) {
    vector<pair<int, int>> pairs;
    set<int> blumSet(blumNumbers.begin(), blumNumbers.end());

    for (int i = 0; i < blumNumbers.size(); i++) {
        for (int j = i; j < blumNumbers.size(); j++) {
            int total = blumNumbers[i] + blumNumbers[j];
            if (total < *max_element(blumNumbers.begin(), blumNumbers.end()) && blumSet.find(total) != blumSet.end()) {
                pairs.push_back(make_pair(blumNumbers[i], blumNumbers[j]));
            }
        }
    }

    return pairs;
}

// Hàm kiểm tra sự tồn tại của số Blum M
bool checkBlumExistence(const vector<int>& blumNumbers, int M) {
    return find(blumNumbers.begin(), blumNumbers.end(), M) != blumNumbers.end();
}

int main() {
    int N = 100;
    int M = 15;

    vector<int> blumNumbers = generateBlumNumbers(N);
    vector<pair<int, int>> blumPairs = findBlumPairs(blumNumbers);
    bool exists = checkBlumExistence(blumNumbers, M);

    cout << "Số Blum nhỏ hơn " << N << ": ";
    for (int num : blumNumbers) {
        cout << num << " ";
    }
    cout << endl;

    cout << "Các cặp số Blum có tổng cũng là số Blum nhỏ hơn " << N << ": ";
    for (const auto& pair : blumPairs) {
        cout << "(" << pair.first << ", " << pair.second << ") ";
    }
    cout << endl;

    cout << "Số " << M << " " << (exists ? "có" : "không có") << " trong dãy số Blum." << endl;

    return 0;
}
