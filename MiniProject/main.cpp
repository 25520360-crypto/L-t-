#include "TicketGenerator.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

// Hàm vẽ thanh Loading ngang
void hienThiThanhLoading(int hienTai, int tongSo) {
    int doRongThanh = 40;
    float phanTram = (float)hienTai / tongSo;
    int viTri = doRongThanh * phanTram;

    cout << "\r[";
    for (int i = 0; i < doRongThanh; ++i) {
        if (i < viTri) cout << "=";
        else if (i == viTri) cout << ">";
        else cout << " ";
    }
    cout << "] " << int(phanTram * 100.0) << " %";
    cout.flush();
}

int runOneGame(vector<LotoTicket>& tuiVe, bool fastMode) {
    for (auto& ve : tuiVe) ve.reset();
    vector<int> longCau;
    for (int i = 1; i <= 90; ++i) longCau.push_back(i);
    static mt19937 rng_game(time(0));
    shuffle(longCau.begin(), longCau.end(), rng_game);

    bool coNguoiKinh = false;
    int luot = 0;

    while (!coNguoiKinh && luot < 90) {
        int soHienTai = longCau[luot];
        luot++;

        vector<int> winIDs;
        bool coVeNaoTrung = false;
        for (int i = 0; i < (int)tuiVe.size(); ++i) {
            bool trung = tuiVe[i].checkVaDanhDau(soHienTai);
            if (!fastMode && trung) {
                if (!coVeNaoTrung) cout << "\nLUOT " << luot << " -> [ CON SO: " << soHienTai << " ]" << endl;
                tuiVe[i].hienThiVe();
                coVeNaoTrung = true;
            }
            if (tuiVe[i].kiemTraKinh() != -1) { winIDs.push_back(tuiVe[i].id); coNguoiKinh = true; }
        }

        if (!fastMode) {
            if (coNguoiKinh) {
                cout << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
                cout << "   PHAT HIEN KINH DONG THOI TAI LUOT " << luot << "!" << endl;
                cout << "   Cac ve thang cuoc: ";
                for (int id : winIDs) cout << "#" << id << " ";
                cout << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
            } else if (coVeNaoTrung) {
                cout << "Nhan Enter de tiep tuc...";
                cin.get();
            }
        }
    }
    return luot;
}

int main() {
    int soLuongVe, luaChon;
    long giaVe;
    TicketGenerator gen;

    cout << "--- HE THONG QUAN LY & MO PHONG LO TO ---" << endl;
    cout << "Nhap gia tien moi to ve (VND): "; cin >> giaVe;
    cout << "Ban muon mua bao nhieu ve: "; cin >> soLuongVe;

    vector<LotoTicket> tuiVe;
    for (int i = 0; i < soLuongVe; ++i) {
        if (i > 0 && i % 2 != 0) tuiVe.push_back(gen.generateRandomTicket(i+1, tuiVe.back().danhSachSoTrongVe));
        else tuiVe.push_back(gen.generateRandomTicket(i+1));
    }

    cout << "\nCHON CHE DO:" << endl;
    cout << "1. Live (Xem tung luot trung)" << endl;
    cout << "2. Mo phong nhanh (Simulate)" << endl;
    cout << "Lua chon: "; cin >> luaChon;
    cin.ignore();

    double ketQuaThongKe = 0;
    int tongTranThucTe = 1;

    if (luaChon == 1) {
        ketQuaThongKe = runOneGame(tuiVe, false);
    } else {
        int soTran;
        cout << "Nhap so tran muon mo phong: "; cin >> soTran;
        tongTranThucTe = soTran;

        long long tongLuot = 0;
        cout << "\nDang chay mo phong...\n" << endl;

        for (int t = 1; t <= soTran; ++t) {
            tongLuot += runOneGame(tuiVe, true);
            if (t % (soTran / 100 + 1) == 0 || t == soTran) {
                hienThiThanhLoading(t, soTran);
            }
        }
        cout << "\n\nHOAN TAT MO PHONG!" << endl;
        ketQuaThongKe = (double)tongLuot / soTran;
    }

    // --- PHẦN TỔNG KẾT ĐÃ CHỈNH SỬA ---
    cout << "\n==========================================" << endl;
    cout << "      KET QUA TONG KET CHIEN THUAT" << endl;
    cout << "==========================================" << endl;
    cout << "=> SO LUONG VE SO HUU  : " << soLuongVe << endl;
    cout << "=> TONG SO TRAN DA XET : " << tongTranThucTe << endl;

    // Tách biệt hiển thị cho Live và Mô phỏng
    if (luaChon == 1) {
        cout << "=> SO LUOT TRAN NAY    : " << (int)ketQuaThongKe << " luot" << endl;
    } else {
        cout << "=> TRUNG BINH DE KINH  : " << fixed << setprecision(2) << ketQuaThongKe << " luot" << endl;
    }

    cout << "=> TONG CHI PHI DAU TU : " << (long long)soLuongVe * giaVe << " VND" << endl;
    cout << "=> TY LE BAO PHU SO    : " << fixed << setprecision(2) << (double)soLuongVe * 15 * 100 / 90 << "%" << endl;
    cout << "==========================================" << endl;

    cout << "\nNhan Enter de thoat chuong trinh...";
    cin.ignore(); cin.get();
    return 0;
}
