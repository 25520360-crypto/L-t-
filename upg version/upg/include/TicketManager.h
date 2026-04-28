#ifndef TICKETMANAGER_H
#define TICKETMANAGER_H

#include "LotoTicket.h"
#include <vector>

class TicketManager {
private:
    std::vector<LotoTicket> pool;

public:
    TicketManager();
    void runGlobalSimulation(int totalGames);
    void showWinStatistics(int totalGames);

    LotoTicket& getTicket(int id);

    // THÊM HÀM NÀY ĐỂ HOST VÀ PLAYER TRUY CẬP DỮ LIỆU
    const std::vector<LotoTicket>& getPool() const { return pool; }
};

#endif
