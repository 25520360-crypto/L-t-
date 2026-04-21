#include "LotoTicket.h"

LotoTicket::LotoTicket(int _id) : id(_id) {}

void LotoTicket::reset() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 9; ++j)
            board[i][j].daDanhDau = false;
}

bool LotoTicket::checkVaDanhDau(int soRa) {
    if (danhSachSoTrongVe.find(soRa) != danhSachSoTrongVe.end()) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j].giaTri == soRa) {
                    board[i][j].daDanhDau = true;
                    return true;
                }
            }
        }
    }
    return false;
}

int LotoTicket::kiemTraKinh() {
    for (int i = 0; i < 3; ++i) {
        int dem = 0;
        for (int j = 0; j < 9; ++j) {
            if (board[i][j].giaTri != 0 && board[i][j].daDanhDau) dem++;
        }
        if (dem == 5) return i;
    }
    return -1;
}

void LotoTicket::hienThiVe() {
    std::cout << " VE SO: #" << std::setw(2) << std::left << id << " [TRUNG SO!] -----------------------" << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << "|";
        for (int j = 0; j < 9; ++j) {
            if (board[i][j].giaTri == 0) std::cout << "    |";
            else {
                if (board[i][j].daDanhDau) std::cout << std::setw(2) << board[i][j].giaTri << "* |";
                else std::cout << std::setw(3) << board[i][j].giaTri << " |";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "------------------------------------------" << std::endl;
}
