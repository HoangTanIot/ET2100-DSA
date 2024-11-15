#include <stdio.h>
#include <stdlib.h>

// Định nghĩa cấu trúc thanh gỗ
typedef struct ThanhGo {
    char loaiGo[20];
    int chieuDai;
    int tuoiGo;
    struct ThanhGo* tiepTheo;
} ThanhGo;

// Định nghĩa cấu trúc ngăn xếp cho từng loại gỗ
typedef struct NganXepGo {
    char loaiGo[20];
    ThanhGo* dinh;
} NganXepGo;

// Hàm sao chép chuỗi
void saoChepChuoi(char* dich, const char* nguon) {
    while ((*dich++ = *nguon++));
}

// Khởi tạo một ngăn xếp gỗ
NganXepGo* khoiTaoNganXep(const char* loaiGo) {
    NganXepGo* nganXep = (NganXepGo*)malloc(sizeof(NganXepGo));
    saoChepChuoi(nganXep->loaiGo, loaiGo);
    nganXep->dinh = NULL;
    return nganXep;
}

// Thêm gỗ vào ngăn xếp
void themGo(NganXepGo* nganXep, int chieuDai, int tuoiGo) {
    ThanhGo* thanhMoi = (ThanhGo*)malloc(sizeof(ThanhGo));
    saoChepChuoi(thanhMoi->loaiGo, nganXep->loaiGo);
    thanhMoi->chieuDai = chieuDai;
    thanhMoi->tuoiGo = tuoiGo;
    thanhMoi->tiepTheo = nganXep->dinh;
    nganXep->dinh = thanhMoi;
}

// Lấy gỗ ra khỏi ngăn xếp
ThanhGo* layGo(NganXepGo* nganXep) {
    if (nganXep->dinh == NULL) {
        printf("Ngăn xếp rỗng!\n");
        return NULL;
    }
    ThanhGo* thanhLayRa = nganXep->dinh;
    nganXep->dinh = nganXep->dinh->tiepTheo;
    return thanhLayRa;
}

// Đếm số lượng gỗ có cùng độ tuổi
int demGoTheoTuoi(NganXepGo* nganXep, int tuoi) {
    int soLuong = 0;
    ThanhGo* hienTai = nganXep->dinh;
    while (hienTai != NULL) {
        if (hienTai->tuoiGo == tuoi) {
            soLuong++;
        }
        hienTai = hienTai->tiepTheo;
    }
    return soLuong;
}

// Hiển thị nội dung ngăn xếp
void hienThiNganXep(NganXepGo* nganXep) {
    printf("Loại gỗ: %s\n", nganXep->loaiGo);
    ThanhGo* hienTai = nganXep->dinh;
    while (hienTai != NULL) {
        printf("  Chiều dài: %d, Tuổi: %d\n", hienTai->chieuDai, hienTai->tuoiGo);
        hienTai = hienTai->tiepTheo;
    }
    printf("\n");
}

int main() {
    // Tạo ngăn xếp cho các loại gỗ
    NganXepGo* goThong = khoiTaoNganXep("Gỗ Thông");
    NganXepGo* goLim = khoiTaoNganXep("Gỗ Lim");

    // Thêm gỗ vào ngăn xếp
    themGo(goThong, 5, 10);
    themGo(goThong, 7, 15);
    themGo(goLim, 4, 8);
    themGo(goThong, 6, 10);

    // Hiển thị nội dung ngăn xếp
    printf("Nội dung trong ngăn xếp:\n");
    hienThiNganXep(goThong);
    hienThiNganXep(goLim);

    // Đếm số gỗ có độ tuổi nhất định
    printf("Số lượng gỗ có tuổi là 10: %d\n", demGoTheoTuoi(goThong, 10));

    // Lấy gỗ ra khỏi ngăn xếp
    ThanhGo* thanhLayRa = layGo(goThong);
    if (thanhLayRa) {
        printf("Gỗ được lấy ra: Loại: %s, Chiều dài: %d, Tuổi: %d\n", thanhLayRa->loaiGo, thanhLayRa->chieuDai, thanhLayRa->tuoiGo);
        free(thanhLayRa);
    }

    // Hiển thị ngăn xếp sau khi lấy gỗ
    printf("\nNgăn xếp sau khi lấy gỗ:\n");
    hienThiNganXep(goThong);
    hienThiNganXep(goLim);

    // Giải phóng bộ nhớ
    free(goThong);
    free(goLim);

    return 0;
}
