#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

#define MAX 100
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

#define C_NORMAL "Binh thuong"
#define C_WEAK "Benh"
#define C_PREGNANT "Co thai"

struct date {
	int d, m, y;
};
struct parents {
	char mid[MAX], did[MAX];
};
struct creature {
	char type[MAX], name[MAX] = { "\0" }, id[MAX], barn[MAX], note[MAX * 10] = { "\0" };
	int age, carn_herbivore = 0, sex, condition = 1;
	float weight;
	date entry;
};
void setColor(int n) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
}
void deleteEndLine(char x[]) {
	size_t len = strlen(x);
	if (x[len - 1] == '\n') {
		x[len - 1] = '\0';
	}
}
void exportToFile(creature list[], int n) {
	char nameFile[100];
	printf("\nNhap vao duong dan va name file: ");
	fflush(stdin);
	fgets(nameFile, sizeof(nameFile), stdin);
	deleteEndLine(nameFile);
	FILE* f;
	f = fopen(nameFile, "wb");
	if (f == NULL) {
		setColor(RED);
		printf("\nLoi mo file de ghi!");
		setColor(LIGHTGRAY);
		return;
	}
	fwrite(&n, sizeof(n), 1, f);
	for (int i = 0; i < n; i++) {
		fwrite(&list[i], sizeof(creature), 1, f);
	}
	fclose(f);

}
void importFromFile(creature list[], int& n) {
	char nameFile[100];
	printf("\nNhap vao duong dan va name file: ");
	fflush(stdin);
	fgets(nameFile, sizeof(nameFile), stdin);
	deleteEndLine(nameFile);
	FILE* f;
	f = fopen(nameFile, "rb");
	if (f == NULL) {
		setColor(RED);
		printf("\nLoi mo file de doc!");
		setColor(LIGHTGRAY);
		return;
	}
	fread(&n, sizeof(n), 1, f);
	for (int i = 0; i < n; i++) {
		fread(&list[i], sizeof(creature), 1, f);
	}
	fclose(f);
}
void ghiChu(creature& cr) {
	if (cr.note != "*")
		printf("%s", cr.note);
}
void capNhatThongTin(creature& cr) {
	ghiChu(cr);
}
void nhapThongTin(creature& cr) {
	printf("\nID: ");
	scanf("%d", &cr.id);

	printf("\nTen: ");
	fflush(stdin);
	fgets(cr.name, sizeof(cr.name), stdin);
	deleteEndLine(cr.name);

	printf("\nLoai: ");
	fflush(stdin);
	fgets(cr.type, sizeof(cr.type), stdin);
	deleteEndLine(cr.type);

	printf("\nTuoi: ");
	scanf("%d", &cr.age);

	printf("\nMa chuong: ");
	fflush(stdin);
	fgets(cr.barn, sizeof(cr.barn), stdin);
	deleteEndLine(cr.barn);

	printf("\nGioi tinh (1 - Duc, 2 - Cai): ");
	scanf("%d", &cr.sex);

	printf("\nNgay nhap (d-m-y): ");
	scanf("%d%d%d", &cr.entry.d, &cr.entry.m, &cr.entry.y);

	printf("\nAn co/An thit (0/1): ");
	scanf("%d", &cr.carn_herbivore);

	printf("\nTinh trang suc khoe (1 - Binh thuong, 2 - Benh, 3 - Co thai): ");
	scanf("%d", &cr.condition);

	printf("\nGhi chu (Neu khong co thi nhap '*'): ");
	fflush(stdin);
	fgets(cr.note, sizeof(cr.note), stdin);
	deleteEndLine(cr.note);
	capNhatThongTin(cr);
}
void nhapDanhSachCacConVat(creature list[], int& n) {
	do {
		printf("\nNhap vao n:");
		scanf("%d", &n);
	} while (n <= 0);
	for (int i = 0; i < n; i++) {
		printf("\nNhap vao con vat thu %d: ", i);
		nhapThongTin(list[i]);
	}
}
void xuatThongTin(creature cr) {
	printf("%5s \t %15s \t %15s \t %5d \t %5s \t %5s \t %2d/%d/%d \t %8s \t %12s \t %s\n", cr.id, cr.name, cr.type, cr.age, cr.barn, cr.sex, cr.entry.d, cr.entry.m, cr.entry.y, carn_herbivore(), condition(), cr.note);
}
void xuatDanhSachCacConVat(creature list[], int n) {
	printf("%5s \t %15s \t %15s \t %5s \t %5s \t %5s \t %11s \t %8s \t %12s \t %s\n", "ID", "Ten", "Loai", "Tuoi", "Ma chuong", "Gioi tinh", "Ngay nhap", "An co/An thit", "Tinh trang suc khoe", "Ghi chu");
	printf("\n");
	for (int i = 0; i < n; i++) {
		xuatThongTin(list[i]);
	}
}

void nhapPhimBatKy() {
	printf("\nNhap phim bat ky de tiep tuc!");
	getch();
}
void menu() {
	int chon;
	do {
		printf("\nMENU:");
		printf("\n1 - Nhap danh sach cac con vat");
		printf("\n2 - Xuat danh sach cac con vat");
		printf("\n3 - Tim max can nang");
		printf("\n4 - Tim min can nang");
		printf("\n5 - Xuat danh sach con vat theo loai");
		printf("\n6 - Xuat danh sach con vat theo chuong");
		printf("\n6 - Xuat danh sach con vat theo tinh trang suc khoe");
		printf("\n7 - Sap xep con vat theo tuoi");
		printf("\n8 - Sap xep con vat theo name");
		printf("\n8 - Sap xep con vat theo ngay nhap");
		printf("\n8 - Sap xep con vat theo can nang");
		printf("\n8 - Xuat thong tin cac con con cua con vat");
		printf("\n8 - Tim thong tin ba me cua con vat");
		printf("\n9 - Them thong tin con vat moi");
		printf("\n9 - Tim thong tin con vat theo ID");
		printf("\n9 - Cap nhat thong tin con vat theo ID");
		printf("\n10 - Xoa thong tin con vat theo ID");
		printf("\n11 - Nhap danh sach cac con vat tu file");
		printf("\n12 - Xuat danh sach cac con vat vao file");
		printf("\n0 - Thoat");
		scanf("%d", &chon);

		switch (chon) {
		case 1:
			//nhapDanhSachSinhVien(ds, n);
			nhapPhimBatKy();
			break;
		case 2:
			//xuatDanhSachSinhVien(ds, n);
			nhapPhimBatKy();
			break;
		case 5:
			char lop[20];
			printf("\nNhap Ma Lop can hien thi: ");
			fflush(stdin);
			fgets(lop, sizeof(lop), stdin);
			deleteEndLine(lop);
			//xuatDanhSachSinhVienTheoLop(ds, n, lop);
			nhapPhimBatKy();
			break;
		default:
			setColor(RED);
			printf("\nKhong co lua chon ban vua nhap!");
			setColor(LIGHTGRAY);
			nhapPhimBatKy();
		}
	} while (chon != 0);
}
void main() {
	printf("skakjnckajcn");
	setColor(2);
	printf("\nskakjnckajcn");
	setColor(7);

}