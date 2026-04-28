#include "../include/Host.h"
#include <iostream>
#include <iomanip>

Host::Host() {}

int Host::pickBestTicket(const TicketManager& manager) {
    auto pool = manager.getPool();
    int bestIdx = 0;
    for (size_t i = 1; i < pool.size(); ++i) {
        if (pool[i].getWinCount() > pool[bestIdx].getWinCount()) {
            bestIdx = i;
        }
    }
    return pool[bestIdx].getId();
}

void Host::analyzeHouseEdge(long ticketPrice, long prizeMoney) {
    long totalRevenue = ticketPrice * 16;
    double edge = (double)(totalRevenue - prizeMoney) * 100.0 / totalRevenue;

    std::cout << "\n--- PHAN TICH QUAN LY CHO CHU TRO (HOST) ---" << std::endl;
    std::cout << "=> Tong doanh thu (16 ve): " << totalRevenue << " VND" << std::endl;
    std::cout << "=> Loi nhuan du kien    : " << totalRevenue - prizeMoney << " VND" << std::endl;
    std::cout << "=> House Edge (Loi the): " << std::fixed << std::setprecision(2) << edge << "%" << std::endl;

    if (edge > 20) std::cout << ">> Loi khuyen: Loi nhuan cao, nhung hay can than khach hang bo cuoc!" << std::endl;
    else if (edge < 0) std::cout << ">> Canh bao: Giai thuong qua cao, ban dang lam tu thien!" << std::endl;
}
