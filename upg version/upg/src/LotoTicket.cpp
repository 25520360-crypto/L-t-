#include "../include/LotoTicket.h"
#include <iomanip>

// Constructor: Chuyển dữ liệu từ mảng 9x5 vào ma trận 9x9 đúng cột hàng chục
LotoTicket::LotoTicket(int _id, std::string _name, int data[9][5])
    : id(_id), name(_name), winCount(0) {

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            board[i][j] = 0;
        }
    }

    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 5; ++c) {
            int val = data[r][c];

            // THÊM DÒNG NÀY: Để lưu số vào danh sách phục vụ phân tích chiến thuật
            danhSachSoTrongVe.insert(val);

            int col = (val == 90) ? 8 : (val / 10);
            board[r][col] = val;
        }
    }
}

void LotoTicket::reset() {
    checkedNumbers.clear(); // Xóa sạch các số đã đánh dấu cho ván mới
}

bool LotoTicket::checkNumber(int drawnNumber) {
    // Tìm trong bảng 9x9 xem có số vừa bốc không
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (board[r][c] == drawnNumber) {
                checkedNumbers.insert(drawnNumber); // Đánh dấu số trúng
                return true;
            }
        }
    }
    return false;
}

bool LotoTicket::kiemTraKinh() {
    for (int r = 0; r < 9; ++r) {
        int hitInRow = 0;
        for (int c = 0; c < 9; ++c) {
            if (board[r][c] != 0 && checkedNumbers.count(board[r][c])) {
                hitInRow++;
            }
        }
        if (hitInRow == 5) return true;
    }
    return false;
}

void LotoTicket::hienThi() {
    std::cout << "\n--- VE " << name << " (#" << id << ") ---" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    for (int i = 0; i < 9; ++i) {
        std::cout << "|";
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] == 0) {
                std::cout << "    |"; // Ô trống màu hồng trong ảnh
            } else {
                if (checkedNumbers.count(board[i][j])) {
                    // Hiển thị số kèm dấu * nếu đã trúng
                    std::cout << std::setw(2) << board[i][j] << "* |";
                } else {
                    std::cout << std::setw(3) << board[i][j] << " |";
                }
            }
        }
        std::cout << std::endl;
        // Kẻ dòng ngăn cách mỗi 3 hàng (cho giống tờ sớ Tân Tân)
        if ((i + 1) % 3 == 0) {
            std::cout << "---------------------------------------------" << std::endl;
        }
    }
}

int LotoTicket::soSoConThieuDeKinh() {
    int minMissing = 5;
    for (int r = 0; r < 9; ++r) {
        int hitCount = 0;
        for (int c = 0; c < 9; ++c) {
            if (board[r][c] != 0 && checkedNumbers.count(board[r][c])) hitCount++;
        }
        int missing = 5 - hitCount;
        if (missing < minMissing) minMissing = missing;
    }
    return minMissing;
}
