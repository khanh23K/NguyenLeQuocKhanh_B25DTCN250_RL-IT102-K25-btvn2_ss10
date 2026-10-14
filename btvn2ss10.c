
#include <stdio.h>
#include <string.h>

#define MAX_VE 50

struct VeSuKien {
    int maVe;
    char tenSuKien[50];
    char loaiVe[20];
    float giaGoc;
    int isEarlyBird;
    int daCheckIn;
};

float tinhGiaVe(struct VeSuKien ve);

int timVeTheoMa(const struct VeSuKien dsVe[],
                int soLuongVe, int maVe);

int phatHanhVe(struct VeSuKien dsVe[],
               int soLuongVe, struct VeSuKien veMoi);

void hienThiDanhSachVe(const struct VeSuKien dsVe[],
                       int soLuongVe);

int checkInVe(struct VeSuKien dsVe[],
              int soLuongVe, int maVe);

int huyVe(struct VeSuKien dsVe[],
          int soLuongVe, int maVe);


float tinhGiaVe(struct VeSuKien ve) {
    if (ve.isEarlyBird == 1) {
        return ve.giaGoc * 0.85f;
    }

    return ve.giaGoc;
}


int timVeTheoMa(const struct VeSuKien dsVe[],
                int soLuongVe, int maVe) {
    int i;

    for (i = 0; i < soLuongVe; i++) {
        if (dsVe[i].maVe == maVe) {
            return i;
        }
    }

    return -1;
}


int phatHanhVe(struct VeSuKien dsVe[],
               int soLuongVe, struct VeSuKien veMoi) {

    if (soLuongVe >= MAX_VE) {
        printf("[LOI] Danh sach da day, khong the phat hanh ve!\n");
        return soLuongVe;
    }

    if (timVeTheoMa(dsVe, soLuongVe, veMoi.maVe) != -1) {
        printf("[LOI] Ma ve %d da ton tai!\n", veMoi.maVe);
        return soLuongVe;
    }

    veMoi.daCheckIn = 0;

    dsVe[soLuongVe] = veMoi;
    soLuongVe++;

    printf("[THANH CONG] Da phat hanh ve %d.\n", veMoi.maVe);

    return soLuongVe;
}


void hienThiDanhSachVe(const struct VeSuKien dsVe[],
                       int soLuongVe) {
    int i;

    if (soLuongVe == 0) {
        printf("[THONG BAO] Danh sach ve dang rong!\n");
        return;
    }

    printf("\n===== DANH SACH VE (%d VE) =====\n", soLuongVe);

    for (i = 0; i < soLuongVe; i++) {
        printf("Ma ve: %d\n", dsVe[i].maVe);
        printf("Su kien: %s\n", dsVe[i].tenSuKien);
        printf("Loai ve: %s\n", dsVe[i].loaiVe);
        printf("Gia goc: %.0f VND\n", dsVe[i].giaGoc);
        printf("Gia thanh toan: %.0f VND\n",
               tinhGiaVe(dsVe[i]));

        if (dsVe[i].daCheckIn == 1) {
            printf("Trang thai: Da check-in\n");
        } else {
            printf("Trang thai: Chua check-in\n");
        }

        printf("-----------------------------\n");
    }
}

int checkInVe(struct VeSuKien dsVe[],
              int soLuongVe, int maVe) {
    int viTri;

    if (soLuongVe == 0) {
        printf("[LOI] Khong co ve nao trong he thong!\n");
        return 0;
    }

    viTri = timVeTheoMa(dsVe, soLuongVe, maVe);

    if (viTri == -1) {
        printf("[LOI] Ma ve %d khong ton tai!\n", maVe);
        return 0;
    }

    if (dsVe[viTri].daCheckIn == 1) {
        printf("[CANH BAO] Ve %d da check-in truoc do!\n", maVe);
        printf("[CANH BAO] Tu choi quet QR trung lap!\n");
        return 0;
    }

    dsVe[viTri].daCheckIn = 1;

    printf("[THANH CONG] Check-in ve %d thanh cong!\n", maVe);

    return 1;
}


int huyVe(struct VeSuKien dsVe[],
          int soLuongVe, int maVe) {
    int viTri;
    int i;

    if (soLuongVe == 0) {
        printf("[LOI] Danh sach rong, khong co ve de huy!\n");
        return soLuongVe;
    }

    viTri = timVeTheoMa(dsVe, soLuongVe, maVe);

    if (viTri == -1) {
        printf("[LOI] Khong tim thay ve %d de huy!\n", maVe);
        return soLuongVe;
    }

    for (i = viTri; i < soLuongVe - 1; i++) {
        dsVe[i] = dsVe[i + 1];
    }

    soLuongVe--;

    printf("[THANH CONG] Da huy ve %d.\n", maVe);

    return soLuongVe;
}


int main() {
    struct VeSuKien dsVe[MAX_VE];
    int soLuongVe = 3;

    struct VeSuKien ve1 = {
        1001, "Live Concert VIBE 2025",
        "VIP", 2000000.0f, 1, 0
    };

    struct VeSuKien ve2 = {
        1002, "Live Concert VIBE 2025",
        "GA", 800000.0f, 0, 0
    };

    struct VeSuKien ve3 = {
        1003, "Live Concert VIBE 2025",
        "Zone A", 1200000.0f, 1, 0
    };

    dsVe[0] = ve1;
    dsVe[1] = ve2;
    dsVe[2] = ve3;

    printf("=== TICKETBOX - LIVE CONCERT VIBE 2025 ===\n");

    printf("\n1. DANH SACH VE BAN DAU");
    hienThiDanhSachVe(dsVe, soLuongVe);

    printf("\n2. PHAT HANH VE MOI");

    struct VeSuKien ve4 = {
        1004, "Live Concert VIBE 2025",
        "VIP", 2500000.0f, 0, 0
    };

    soLuongVe = phatHanhVe(dsVe, soLuongVe, ve4);

    printf("\n3. CHECK-IN VE 1001");
    checkInVe(dsVe, soLuongVe, 1001);

    printf("\n4. THU QUET LAI VE 1001");
    checkInVe(dsVe, soLuongVe, 1001);

    printf("\n5. HUY VE 1002");
    soLuongVe = huyVe(dsVe, soLuongVe, 1002);

    printf("\n6. CHECK-IN VE KHONG TON TAI 9999");
    checkInVe(dsVe, soLuongVe, 9999);

    printf("\n7. DANH SACH VE SAU CAC THAO TAC");
    hienThiDanhSachVe(dsVe, soLuongVe);

    return 0;
}

