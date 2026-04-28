#include "../include/TicketManager.h"
#include <algorithm>
#include <random>
#include <ctime>
#include <iomanip>

TicketManager::TicketManager() {
    // Nhóm hãy nhập dữ liệu 16 tờ vé từ ảnh vào đây
    int d1[9][5] = {{19,28,46,68,75},{5,26,39,58,78},{14,37,50,69,84},{3,25,57,60,86},{16,31,49,77,89},{8,17,48,59,79},{15,20,44,52,70},{4,33,41,61,83},{9,29,30,62,88}};
    pool.push_back(LotoTicket(1, "Mot", d1));

    int d2[9][5] = {{18,22,55,76,87},{12,38,40,66,82},{1,27,42,73,85},{10,34,56,63,80},{6,35,43,64,71},{13,21,54,74,90},{7,24,32,53,67},{2,36,47,65,72},{11,23,45,51,81}};
    pool.push_back(LotoTicket(2, "Hai", d2));

    // Tờ số 3 (Ba) - Đã sửa lỗi thiếu dấu ngoặc nhọn
    int d3[9][5] = {
        {19, 32, 58, 64, 84},
        {13, 20, 48, 55, 77},
        {2, 21, 46, 75, 82},
        {6, 18, 39, 62, 70},
        {25, 41, 59, 74, 83},
        {17, 38, 44, 60, 86},
        {8, 22, 47, 66, 72},
        {9, 12, 37, 42, 88},
        {15, 36, 51, 68, 90}
    };
    pool.push_back(LotoTicket(3, "Ba", d3));

    // Tờ số 4 (Bon)
    int d4[9][5] = {
        {5, 29, 30, 56, 80},
        {10, 35, 54, 63, 81},
        {4, 26, 45, 61, 79},
        {3, 14, 43, 50, 71},
        {7, 23, 31, 52, 73},
        {11, 28, 49, 69, 89},
        {24, 34, 53, 67, 85},
        {27, 40, 57, 76, 87},
        {1, 16, 33, 65, 78}
    };
    pool.push_back(LotoTicket(4, "Bon", d4));

    // Tờ số 5 (Nam)
    int d5[9][5] = {
        {15, 24, 44, 64, 79},
        {4, 29, 30, 51, 76},
        {17, 32, 53, 63, 80},
        {7, 23, 56, 61, 85},
        {11, 34, 42, 72, 87},
        {3, 13, 45, 54, 74},
        {16, 21, 43, 58, 78},
        {6, 37, 40, 65, 82},
        {2, 22, 39, 67, 83}
    };
    pool.push_back(LotoTicket(5, "Nam", d5));

    // Tờ số 6 (Sau)
    int d6[9][5] = {
        {15, 24, 44, 64, 79},
        {4, 29, 30, 51, 76},
        {17, 32, 53, 63, 80},
        {7, 23, 56, 61, 85},
        {11, 34, 42, 72, 87},
        {3, 13, 45, 54, 74},
        {16, 21, 43, 58, 78},
        {6, 37, 40, 65, 82},
        {2, 22, 39, 67, 83}
    };
    pool.push_back(LotoTicket(6, "Sau", d6));

    // Tờ số 7 (Bay)
    int d7[9][5] = {
        {12, 34, 40, 75, 89},
        {8, 16, 42, 55, 77},
        {5, 24, 33, 67, 83},
        {14, 27, 51, 78, 84},
        {18, 38, 46, 63, 81},
        {9, 47, 66, 79, 86},
        {4, 28, 31, 57, 72},
        {17, 36, 52, 64, 80},
        {19, 23, 45, 62, 74}
    };
    pool.push_back(LotoTicket(7, "Bay", d7));

    // Tờ số 8 (Tam)
    int d8[9][5] = {
        {3, 15, 32, 60, 71},
        {10, 20, 43, 54, 85},
        {2, 26, 35, 59, 76},
        {6, 39, 49, 68, 73},
        {13, 29, 48, 50, 88},
        {22, 30, 53, 65, 82},
        {1, 25, 58, 69, 90},
        {7, 21, 41, 56, 87},
        {11, 37, 44, 61, 70}
    };
    pool.push_back(LotoTicket(8, "Tam", d8));

    // --- Tiếp tục nạp dữ liệu từ tờ 9 đến tờ 16 vào TicketManager Constructor ---

    // Tờ số 9 (Chin)
    int d9[9][5] = {
        {7, 16, 32, 66, 73}, {18, 29, 46, 55, 88}, {2, 23, 34, 50, 75},
        {4, 30, 40, 61, 78}, {10, 27, 41, 56, 86}, {20, 39, 59, 60, 83},
        {9, 24, 51, 64, 81}, {3, 28, 48, 53, 80}, {17, 37, 45, 63, 77}
    };
    pool.push_back(LotoTicket(9, "Chin", d9));

    // Tờ số 10 (Muoi)
    int d10[9][5] = {
        {19, 35, 49, 71, 85}, {8, 14, 47, 54, 74}, {6, 25, 36, 62, 84},
        {15, 22, 58, 70, 89}, {12, 31, 43, 68, 90}, {1, 42, 65, 72, 87},
        {5, 21, 38, 52, 76}, {13, 33, 57, 67, 82}, {11, 26, 44, 69, 79}
    };
    pool.push_back(LotoTicket(10, "Muoi", d10));

    // Tờ số 11 (Muoi Mot)
    int d11[9][5] = {
        {16, 28, 45, 68, 87}, {4, 29, 35, 55, 73}, {9, 30, 54, 62, 88},
        {1, 21, 33, 52, 76}, {8, 40, 50, 79, 81}, {11, 20, 46, 63, 83},
        {27, 49, 59, 72, 80}, {2, 19, 32, 48, 67}, {14, 22, 57, 78, 90}
    };
    pool.push_back(LotoTicket(11, "Muoi Mot", d11));

    // Tờ số 12 (Muoi Hai) - Đã sửa lỗi khai báo mảng
    int d12[9][5] = {
        {6, 18, 47, 69, 86}, {13, 31, 44, 61, 70}, {7, 24, 34, 56, 71},
        {5, 23, 41, 65, 74}, {10, 37, 53, 60, 89}, {17, 38, 42, 75, 84},
        {15, 25, 51, 77, 85}, {12, 36, 43, 64, 82}, {3, 26, 39, 58, 66}
    };
    pool.push_back(LotoTicket(12, "Muoi Hai", d12));

    // Tờ số 13 (Muoi Ba)
    int d13[9][5] = {
        {13, 22, 41, 61, 86}, {3, 24, 34, 52, 71}, {1, 35, 56, 64, 83},
        {7, 23, 36, 53, 75}, {5, 48, 59, 72, 84}, {14, 28, 42, 60, 87},
        {26, 47, 50, 79, 89}, {4, 10, 30, 49, 66}, {15, 25, 51, 76, 81}
    };
    pool.push_back(LotoTicket(13, "Muoi Ba", d13));

    // Tờ số 14 (Muoi Bon)
    int d14[9][5] = {
        {9, 16, 46, 65, 80}, {11, 32, 45, 68, 78}, {8, 21, 33, 57, 73},
        {6, 20, 43, 63, 77}, {12, 31, 54, 62, 85}, {19, 39, 40, 70, 82},
        {18, 29, 58, 74, 90}, {17, 38, 44, 69, 88}, {2, 27, 37, 55, 67}
    };
    pool.push_back(LotoTicket(14, "Muoi Bon", d14));

    // Tờ số 15 (Muoi Lam)
    int d15[9][5] = {
        {11, 35, 59, 68, 80}, {17, 24, 42, 57, 76}, {1, 27, 48, 79, 81},
        {7, 16, 31, 65, 77}, {23, 44, 50, 71, 85}, {14, 37, 49, 63, 88},
        {3, 20, 46, 67, 73}, {8, 12, 34, 45, 87}, {19, 39, 55, 60, 89}
    };
    pool.push_back(LotoTicket(15, "Muoi Lam", d15));

    // Tờ số 16 (Muoi Sau) - Đã sửa lỗi thiếu dấu ngoặc nhọn từng hàng
    int d16[9][5] = {
        {9, 25, 38, 53, 86}, {15, 36, 51, 64, 90}, {2, 28, 47, 66, 78},
        {5, 10, 41, 56, 72}, {4, 22, 33, 54, 74}, {13, 26, 40, 61, 82},
        {29, 30, 58, 62, 83}, {21, 43, 52, 75, 84}, {6, 18, 32, 69, 70}
    };
    pool.push_back(LotoTicket(16, "Muoi Sau", d16));

// --- Cứ thế tiếp tục cho đến d16 ---

    // ... (Nhóm tiếp tục nạp cho đến tờ thứ 16 tương tự như trên) ...
}

void hienThiProgressBar(int current, int total) {
    int width = 40;
    float progress = (float)current / total;
    int pos = width * progress;

    std::cout << "\r[*] Dang mo phong: [";
    for (int i = 0; i < width; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << "%";
    std::cout.flush();
}

void TicketManager::runGlobalSimulation(int totalGames) {
    std::vector<int> longCau;
    for (int i = 1; i <= 90; ++i) longCau.push_back(i);
    std::mt19937 rng(time(0));

    for (int g = 0; g < totalGames; ++g) {
        if (g % (totalGames / 100 + 1) == 0 || g == totalGames - 1) {
            hienThiProgressBar(g + 1, totalGames);
        }

        for (auto& ve : pool) ve.reset();
        std::shuffle(longCau.begin(), longCau.end(), rng);

        bool finished = false;
        for (int so : longCau) {
            for (auto& ve : pool) {
                ve.checkNumber(so);
                if (ve.kiemTraKinh()) {
                    ve.incrementWinCount();
                    finished = true;
                }
            }
            if (finished) break;
        }
    }
    std::cout << "\n[!] Hoan tat mo phong du lieu!" << std::endl;
}

void TicketManager::showWinStatistics(int totalGames) {
    std::cout << "\n--- BANG XEP HANG TI LE THANG (Xac suat thuc te) ---" << std::endl;
    std::cout << std::left << std::setw(10) << "ID Ve"
              << std::setw(15) << "Ten Ve"
              << std::setw(20) << "So lan Kinh"
              << "Ti le thang (%)" << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;

    for (const auto& ve : pool) {
        double winRate = (double)ve.getWinCount() * 100.0 / totalGames;
        std::cout << std::left << std::setw(10) << ve.getId()
                  << std::setw(15) << ve.getName()
                  << std::setw(20) << ve.getWinCount()
                  << std::fixed << std::setprecision(2) << winRate << "%" << std::endl;
    }
    std::cout << "------------------------------------------------------------------" << std::endl;
}

LotoTicket& TicketManager::getTicket(int id) {
    return pool[id - 1];
}
