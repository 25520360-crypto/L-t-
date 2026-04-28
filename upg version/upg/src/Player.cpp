#include "../include/Player.h"
#include <iostream>
#include <algorithm>

Player::Player() {}

void Player::analyzeEconomics(long giaVe, long giaiThuong, int totalGamesSimulation, const TicketManager& manager) {
    auto pool = manager.getPool();
    std::cout << "\n--- PHAN TICH CHIEN LUOC KINH TE (Dua tren mo phong) ---" << std::endl;
    std::cout << "Gia ve: " << giaVe << " VND | Giai thuong: " << giaiThuong << " VND" << std::endl;

    int bestIdx = 0, worstIdx = 0;
    for (size_t i = 1; i < pool.size(); ++i) {
        if (pool[i].getWinCount() > pool[bestIdx].getWinCount()) bestIdx = i;
        if (pool[i].getWinCount() < pool[worstIdx].getWinCount()) worstIdx = i;
    }

    double pBest = (double)pool[bestIdx].getWinCount() / totalGamesSimulation;
    double pWorst = (double)pool[worstIdx].getWinCount() / totalGamesSimulation;

    double evBest = (pBest * giaiThuong) - giaVe;
    double evWorst = (pWorst * giaiThuong) - giaVe;

    std::cout << "1. Mua to VIP (#" << pool[bestIdx].getId() << "): EV = " << evBest << " VND/van" << std::endl;
    std::cout << "2. Mua to te nhat (#" << pool[worstIdx].getId() << "): EV = " << evWorst << " VND/van" << std::endl;

    if (evBest > 0) std::cout << "=> KET LUAN: Ban CO THE KIEM LOI neu chon duoc ve tot!" << std::endl;
    else std::cout << "=> KET LUAN: Ky vong am. NHA CAI LUON THANG, KHONG NEN CHOI!" << std::endl;
}

// ĐÃ SỬA LẠI HÀM NÀY
void Player::findBestSet(const TicketManager& manager, int soLuongVe, long giaVe, long giaiThuong, int totalGamesSimulation) {
    auto pool = manager.getPool();
    if (soLuongVe <= 0 || soLuongVe > (int)pool.size()) {
        std::cout << "[!] So luong ve khong hop le!" << std::endl;
        return;
    }

    std::vector<int> selectedTickets;
    std::set<int> coveredNumbers;

    // Tìm vé tốt nhất làm gốc
    int bestIdx = 0;
    for (size_t i = 1; i < pool.size(); ++i) {
        if (pool[i].getWinCount() > pool[bestIdx].getWinCount()) bestIdx = i;
    }

    selectedTickets.push_back(bestIdx);
    coveredNumbers.insert(pool[bestIdx].getDanhSachSo().begin(), pool[bestIdx].getDanhSachSo().end());

    // Thuật toán Greedy tìm các vé tiếp theo
    for (int step = 1; step < soLuongVe; ++step) {
        int bestNextIdx = -1;
        int maxNewNumbers = -1;

        for (size_t i = 0; i < pool.size(); ++i) {
            if (std::find(selectedTickets.begin(), selectedTickets.end(), i) != selectedTickets.end())
                continue;

            int newNumbersCount = 0;
            for (int so : pool[i].getDanhSachSo()) {
                if (coveredNumbers.find(so) == coveredNumbers.end()) newNumbersCount++;
            }

            if (newNumbersCount > maxNewNumbers) {
                maxNewNumbers = newNumbersCount;
                bestNextIdx = i;
            }
        }

        selectedTickets.push_back(bestNextIdx);
        for (int so : pool[bestNextIdx].getDanhSachSo()) coveredNumbers.insert(so);
    }

    // In kết quả các vé
    std::cout << "\n=> BO " << soLuongVe << " VE TOI UU NHAT (Thuat toan Tham Lam):" << std::endl;
    std::cout << "Gom cac ve ID: ";

    // TÍNH TOÁN LỢI NHUẬN TỔNG
    int totalWinCountOfSet = 0;
    for (int idx : selectedTickets) {
        std::cout << "#" << pool[idx].getId() << " ";
        totalWinCountOfSet += pool[idx].getWinCount(); // Cộng dồn số trận thắng
    }

    std::cout << "\nTong do phu: " << coveredNumbers.size() << "/90 so." << std::endl;

    double pWinSet = (double)totalWinCountOfSet / totalGamesSimulation;
    double expectedValue = (pWinSet * giaiThuong) - (soLuongVe * giaVe); // Lợi nhuận = (Tỉ lệ thắng * Giải thưởng) - Tiền mua N vé

    std::cout << "---------------------------------" << std::endl;
    std::cout << "Xac suat thang cua bo ve  : " << pWinSet * 100 << "%" << std::endl;
    std::cout << "Loi nhuan ky vong (EV) bo : " << expectedValue << " VND/van" << std::endl;

    if (expectedValue > 0) {
        std::cout << "=> CHIEN LUOC: MUA BO NAY CO LAI THUE!" << std::endl;
    } else {
        std::cout << "=> CHIEN LUOC: MUA BO NAY SE LO VON TONG THE!" << std::endl;
    }
}
