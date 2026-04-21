#include "TicketGenerator.h"
#include <ctime>

TicketGenerator::TicketGenerator() {
    rng.seed(time(0));
}

LotoTicket TicketGenerator::generateRandomTicket(int id, std::set<int> excludeNumbers) {
    LotoTicket ticket(id);
    for (int r = 0; r < 3; ++r) {
        std::vector<int> cols = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        std::shuffle(cols.begin(), cols.end(), rng);
        for (int i = 0; i < 5; ++i) {
            int c = cols[i];
            int minVal = (c == 0) ? 1 : c * 10;
            int maxVal = (c == 8) ? 90 : c * 10 + 9;
            std::vector<int> validNums;
            for (int v = minVal; v <= maxVal; ++v) {
                if (excludeNumbers.find(v) == excludeNumbers.end()) validNums.push_back(v);
            }
            if (validNums.empty()) { for (int v = minVal; v <= maxVal; ++v) validNums.push_back(v); }
            std::shuffle(validNums.begin(), validNums.end(), rng);
            int picked = validNums[0];
            while(ticket.danhSachSoTrongVe.count(picked)) {
                std::shuffle(validNums.begin(), validNums.end(), rng);
                picked = validNums[0];
            }
            ticket.board[r][c].giaTri = picked;
            ticket.danhSachSoTrongVe.insert(picked);
        }
    }
    return ticket;
}
