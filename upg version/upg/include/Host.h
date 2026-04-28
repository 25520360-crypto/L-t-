#ifndef HOST_H
#define HOST_H

#include "TicketManager.h"

class Host {
public:
    Host();

    // Tìm tờ vé có tỉ lệ thắng cao nhất từ kết quả mô phỏng
    int pickBestTicket(const TicketManager& manager);

    // Phân tích lợi nhuận của nhà cái
    void analyzeHouseEdge(long ticketPrice, long prizeMoney);
};

#endif
