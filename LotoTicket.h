#ifndef LOTOTICKET_H
#define LOTOTICKET_H

#include <iostream>
#include <vector>
#include <set>
#include <iomanip>

struct OSo {
    int giaTri = 0;
    bool daDanhDau = false;
};

class LotoTicket {
public:
    OSo board[3][9];
    int id;
    std::set<int> danhSachSoTrongVe;

    LotoTicket(int _id);
    void reset();
    bool checkVaDanhDau(int soRa);
    int kiemTraKinh();
    void hienThiVe();
};

#endif
