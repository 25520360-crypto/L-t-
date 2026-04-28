#include "include/TicketManager.h"
#include "include/Host.h"
#include "include/Player.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

using namespace std;

void printSeparator() { cout << "\n==================================================================" << endl; }
void printHeader(string title) {
    printSeparator();
    cout << "          " << title << endl;
    printSeparator();
}

int main() {
    TicketManager manager;
    Host host;
    Player player;

    long ticketPrice = 10000;
    long prizeMoney = 120000;
    int nSimulations;

    printHeader("CHUONG TRINH PHAN TICH CHIEN LUOC LO TO(16 VE)");

    cout << "[?] Nhap so lan muon mo phong: ";
    cin >> nSimulations;

    cout << "\n[*] He thong dang bat dau tinh toan..." << endl;
    manager.runGlobalSimulation(nSimulations);

    // PHẦN 1: HOST
    int bestId = host.pickBestTicket(manager); // Dùng Host để pick

    printHeader("CHIEN LUOC TOI UU CHO QUAN TRO (HOST)");
    cout << "=> KET QUA: To ve VIP nhat la #" << bestId << " (ti le ra som cao nhat)." << endl;
    cout << "   - Host nen giu lai to #" << bestId << " de co xac suat thang chu dong." << endl;

    manager.showWinStatistics(nSimulations);

    // PHẦN 2: PLAYER
    printHeader("CHIEN LUOC TOI UU CHO NGUOI CHOI (PLAYER)");

    // ĐOẠN ĐƯỢC FIX LỖI (Thêm vòng lặp while)
    int loopPlayer = 1;
    while (loopPlayer == 1) {
        cout << "Nhap gia ve thuc te (VND): "; cin >> ticketPrice;
        cout << "Nhap gia tri giai thuong (VND): "; cin >> prizeMoney;

        player.analyzeEconomics(ticketPrice, prizeMoney, nSimulations, manager); // Dùng Player để phân tích

        int soVe;
        cout << "\n[?] Ban muon mua may to ve de he thong tim bo toi uu? ";
        cin >> soVe;
        player.findBestSet(manager, soVe, ticketPrice, prizeMoney, nSimulations);

        // Hỏi xem có muốn lặp lại không
        cout << "\n------------------------------------------------------------------";
        cout << "\n[?] Ban co muon thu lai voi muc gia/giai thuong khac khong? (1: Co, 0: Tiep tuc Demo): ";
        cin >> loopPlayer;
        if (loopPlayer == 1) {
            cout << "\n[*] TIEN HANH PHAN TICH LAI...\n";
        }
    }

    // PHẦN 3: DEMO VAN DAU LIVE
    printSeparator();
    int choice;
    cout << "Ban co muon xem mot van dau LIVE de kiem chung khong? (1: Co, 0: Thoat): ";
    cin >> choice;

    if (choice == 1) {
        printHeader("DEMO VAN DAU LIVE - PHAN TICH TRUC TIEP");
        host.analyzeHouseEdge(ticketPrice, prizeMoney); // Host phân tích lợi thế

        cin.ignore();
        cout << "\nNhan Enter de bat dau boc so..."; cin.get();

        LotoTicket& hostVe = manager.getTicket(bestId);
        int guestId = (bestId == 1) ? 2 : 1;
        LotoTicket& guestVe = manager.getTicket(guestId);

        cout << "\n[Host] Giu ve VIP: #" << hostVe.getId() << endl;
        cout << "[Ban]  Giu ve: #" << guestVe.getId() << endl;

        vector<int> longCau;
        for(int i=1; i<=90; i++) longCau.push_back(i);

        // Sử dụng random device chuẩn
        random_device rd;
        mt19937 g(rd());
        shuffle(longCau.begin(), longCau.end(), g);

        hostVe.reset(); guestVe.reset();
        bool finish = false; int turn = 0;

        while(!finish && turn < 90) {
            int soRa = longCau[turn++];
            cout << "\n------------------------------------------" << endl;
            cout << "LUOT " << turn << " -> [ CON SO " << soRa << " ]" << endl;

            bool hTrung = hostVe.checkNumber(soRa);
            bool gTrung = guestVe.checkNumber(soRa);

            if(hTrung) { cout << "[!] Host trung so " << soRa << endl; hostVe.hienThi(); }
            if(gTrung) { cout << "[*] Ban trung so " << soRa << endl; guestVe.hienThi(); }

            if (!hostVe.kiemTraKinh() && hostVe.soSoConThieuDeKinh() == 1) cout << ">>> CANH BAO: Host chi con thieu 1 so!" << endl;
            if (!guestVe.kiemTraKinh() && guestVe.soSoConThieuDeKinh() == 1) cout << ">>> TIN VUI: Ban chi con thieu 1 so!" << endl;

            if(hostVe.kiemTraKinh() || guestVe.kiemTraKinh()) {
                cout << "\n==========================================" << endl;
                if(hostVe.kiemTraKinh()) cout << "   QUAN TRO (HOST) DA KINH ROI! (VIP #" << hostVe.getId() << ")" << endl;
                if(guestVe.kiemTraKinh()) cout << "   NGUOI CHOI DA KINH ROI! (Ve #" << guestVe.getId() << ")" << endl;
                cout << "==========================================" << endl;
                finish = true;
            } else {
                if(hTrung || gTrung) {
                    cout << "Nhan Enter de tiep tuc..."; cin.get();
                }
            }
        }
    }

    printHeader("KET THUC GIA LAP");
    return 0;
}
