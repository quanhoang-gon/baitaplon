#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// === Cấu trúc Sinh viên ===
typedef struct {
    char msv[20];
    char hoTen[50];
    int namSinh;
    char lop[20];
    float dtb;
    char diaChi[100];
} SinhVien;

// === Cấu trúc danh sách liên kết để ghi chú thao tác ===
typedef struct Node {
    char ghiChu[100];
    struct Node *next;
} Node;

// ==== Hàm menu ====
void menu() {
    printf("\n====== MENU ======\n");
    printf("1. Nhập danh sách sinh viên\n");
    printf("2. Hiển thị danh sách sinh viên\n");
    printf("3. Ghi danh sách vào file\n");
    printf("4. Sắp xếp theo họ tên (A-Z)\n");
    printf("5. Sắp xếp theo điểm TB (giảm dần)\n");
    printf("6. Hiển thị ghi chú thao tác\n");
    printf("0. Thoát\n");
    printf("==================\n");
}

// ==== Hàm thêm ghi chú vào danh sách liên kết ====
void themGhiChu(Node **head, const char *noiDung) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->ghiChu, noiDung);
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *p = *head;
        while (p->next != NULL) p = p->next;
        p->next = newNode;
    }
}

// ==== Hiển thị ghi chú thao tác ====
void hienThiGhiChu(Node *head) {
    printf("\n--- Ghi chú thao tác ---\n");
    int i = 1;
    while (head != NULL) {
        printf("%d. %s\n", i++, head->ghiChu);
        head = head->next;
    }
}

// ==== Nhập danh sách sinh viên ====
void nhapDanhSach(SinhVien **ds, int *n) {
    printf("Nhập số lượng sinh viên: ");
    scanf("%d", n);
    getchar();

    *ds = (SinhVien*)malloc((*n) * sizeof(SinhVien));
    if (*ds == NULL) {
        printf("Lỗi cấp phát bộ nhớ!\n");
        exit(1);
    }

    for (int i = 0; i < *n; i++) {
        printf("\n--- Sinh viên %d ---\n", i + 1);

        printf("Mã SV: "); fgets((*ds)[i].msv, 20, stdin); (*ds)[i].msv[strcspn((*ds)[i].msv, "\n")] = '\0';
        printf("Họ tên: "); fgets((*ds)[i].hoTen, 50, stdin); (*ds)[i].hoTen[strcspn((*ds)[i].hoTen, "\n")] = '\0';
        printf("Năm sinh: "); scanf("%d", &(*ds)[i].namSinh); getchar();
        printf("Lớp: "); fgets((*ds)[i].lop, 20, stdin); (*ds)[i].lop[strcspn((*ds)[i].lop, "\n")] = '\0';
        printf("Điểm TB: "); scanf("%f", &(*ds)[i].dtb); getchar();
        printf("Địa chỉ: "); fgets((*ds)[i].diaChi, 100, stdin); (*ds)[i].diaChi[strcspn((*ds)[i].diaChi, "\n")] = '\0';
    }
}

// ==== Hiển thị danh sách sinh viên ====
void hienThiDanhSach(SinhVien *ds, int n) {
    printf("\n--- Danh sách sinh viên ---\n");
    for (int i = 0; i < n; i++) {
        printf("STT %d\n", i + 1);
        printf("MSV    : %s\n", ds[i].msv);
        printf("Họ tên : %s\n", ds[i].hoTen);
        printf("Năm sinh: %d\n", ds[i].namSinh);
        printf("Lớp    : %s\n", ds[i].lop);
        printf("Điểm TB: %.2f\n", ds[i].dtb);
        printf("Địa chỉ: %s\n", ds[i].diaChi);
        printf("---------------------------\n");
    }
}

// ==== Ghi danh sách ra file ====
void ghiFile(SinhVien *ds, int n, const char *tenTep) {
    FILE *f = fopen(tenTep, "w");
    if (f == NULL) {
        printf("Không thể mở file để ghi!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(f, "STT %d\n", i + 1);
        fprintf(f, "%s\n", ds[i].msv);
        fprintf(f, "%s\n", ds[i].hoTen);
        fprintf(f, "%d\n", ds[i].namSinh);
        fprintf(f, "%s\n", ds[i].lop);
        fprintf(f, "%.2f\n", ds[i].dtb);
        fprintf(f, "%s\n", ds[i].diaChi);
    }

    fclose(f);
    printf("Đã ghi danh sách vào file '%s'\n", tenTep);
}

// ==== Hàm so sánh theo tên dùng cho con trỏ hàm ====
int soSanhTen(SinhVien a, SinhVien b) {
    return strcmp(a.hoTen, b.hoTen);
}

// ==== Hàm so sánh theo điểm TB ====
int soSanhDTB(SinhVien a, SinhVien b) {
    return b.dtb > a.dtb ? 1 : -1;
}

// ==== Hàm sắp xếp dùng con trỏ hàm ====
void sapXep(SinhVien *ds, int n, int (*cmp)(SinhVien, SinhVien)) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (cmp(ds[i], ds[j]) > 0) {
                SinhVien tmp = ds[i];
                ds[i] = ds[j];
                ds[j] = tmp;
            }
        }
    }
}

int main() {
    SinhVien *ds = NULL;
    int n = 0;
    Node *ghiChu = NULL;
    int luaChon;

    do {
        menu();
        printf("Chọn: ");
        scanf("%d", &luaChon);
        getchar();

        switch (luaChon) {
            case 1:
                nhapDanhSach(&ds, &n);
                themGhiChu(&ghiChu, "Đã nhập danh sách sinh viên.");
                break;
            case 2:
                hienThiDanhSach(ds, n);
                break;
            case 3:
                ghiFile(ds, n, "sinhvien.txt");
                themGhiChu(&ghiChu, "Đã ghi danh sách ra file.");
                break;
            case 4:
                sapXep(ds, n, soSanhTen);
                hienThiDanhSach(ds, n);
                themGhiChu(&ghiChu, "Đã sắp xếp theo họ tên.");
                break;
            case 5:
                sapXep(ds, n, soSanhDTB);
                hienThiDanhSach(ds, n);
                themGhiChu(&ghiChu, "Đã sắp xếp theo điểm trung bình.");
                break;
            case 6:
                hienThiGhiChu(ghiChu);
                break;
            case 0:
                printf("Kết thúc chương trình.\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ!\n");
        }
    } while (luaChon != 0);

    // Giải phóng bộ nhớ
    free(ds);
    while (ghiChu != NULL) {
        Node *tmp = ghiChu;
        ghiChu = ghiChu->next;
        free(tmp);
    }

    return 0;
}
