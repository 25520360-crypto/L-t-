#ifndef PLAYER_H
#define PLAYER_H
#include "TicketManager.h"

class Player {
public:
    Player();
    void analyzeEconomics(long giaVe, long giaiThuong, int totalGamesSimulation, const TicketManager& manager);

    // Đã thêm các tham số mới vào hàm này:
    void findBestSet(const TicketManager& manager, int soLuongVe, long giaVe, long giaiThuong, int totalGamesSimulation);
};
#endif
