// Bài 2: Thiết kế giải thuật và cài đặt để tạo ra một mảng số nửa nguyên tố (Blum) nhỏ hơn một số N cho trước và thực hiện hai yêu cầu sau:
// - Tìm ra tất cả các cặp số Blum có tổng cũng là một số Blum nhỏ hơn N
// - Kiểm tra xem một số Blum M có tồn tại trong dãy số Blum được tạo ra hay không.
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Ham kiem tra so nguyen to
bool Prime(int n){
    if (n<2)
        return 0;
    else {
        for(int i=2; i < sqrt(n); i++){
            if(n % i == 0)
                return 0;
        }
    } 
    return 1;
}

// Ham kiem tra so nua nguyen to (blum)
bool blumPrime(int p){
    return Prime(p) && (p % 4 == 3);
}

// mang dong chua cac so nua nguyen to
vector<int> blumNumbers(int N){
    vector<int> vectorBlum;
    for(int m=2; m<N; m++){
        if(blumPrime(m)){
            for(int n=m+1; n<N; n++){
                if(blumPrime(n)){
                    vectorBlum.push_back(m*n);
                }
            }
        }
    }
    return vectorBlum;
}

// Ham kiem tra 1 so co phai so Blum hay khong
bool isBlumNumber(int n, const vector<int>& vectorBlum) {
    for (int blum : vectorBlum) {
        if (blum == n) 
            return 1;
    }
    return 0;
}

// Tim cac tong trong mang la so Blum nho hon N
void findBlum(vector<int>& vectorBlum, int N){
    for (int i = 0; i < vectorBlum.size(); i++) {
        for (int j = i + 1; j < vectorBlum.size(); j++){
            int sum = vectorBlum[i] + vectorBlum[j];
            if (sum < N && isBlumNumber(sum, vectorBlum)) {
                cout << vectorBlum[i] << " + " << vectorBlum[j] << " = " << sum << endl;
            }
        } 
    }
}
int main(){
    int N, M;
    cout << "Nhap N: ";
    cin >> N;
    vector<int> vectorBlum = blumNumbers(N);

    cout << "Day so Blum nho hon N la: ";
    for(int num : vectorBlum){
        cout << num << " ";
    }
    cout << endl;

    cout << "Cac cap so Blum co tong cung la mot so Blum nho hon " << N << ": ";
    findBlum(vectorBlum, N);
    cout << endl;

    cout << "Nhap M: ";
    cin >> M;
    if(isBlumNumber(M, vectorBlum))
        cout << M << " ton tai trong day so Blum";
    else
        cout << M << " khong ton tai trong day so Blum";
    return 0;
}
