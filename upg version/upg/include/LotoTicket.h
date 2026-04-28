#ifndef LOTOTICKET_H
#define LOTOTICKET_H

#include <iostream>
#include <vector>
#include <set>
#include <string>

class LotoTicket {
private:
    int id;
    std::string name;
    int board[9][9];
    std::set<int> checkedNumbers;
    int winCount;
    std::set<int> danhSachSoTrongVe; // Chuyển vào đây

public:
    // THÊM DÒNG NÀY: Lưu 45 số cố định của tờ vé

    LotoTicket(int _id, std::string _name, int data[9][5]);
    void reset();
    bool checkNumber(int drawnNumber);
    bool kiemTraKinh();
    void hienThi();

    int getId() const { return id; }
    std::string getName() const { return name; }
    int getWinCount() const { return winCount; }
    void incrementWinCount() { winCount++; }
    // Thêm vào mục public
    int soSoConThieuDeKinh(); // Trả về số lượng số còn thiếu của hàng "gần Kinh" nhất
    const std::set<int>& getDanhSachSo() const { return danhSachSoTrongVe; }
};

#endif
