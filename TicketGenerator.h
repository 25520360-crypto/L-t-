#ifndef TICKETGENERATOR_H
#define TICKETGENERATOR_H

#include "LotoTicket.h"
#include <random>
#include <algorithm>

class TicketGenerator {
private:
    std::mt19937 rng;
public:
    TicketGenerator();
    LotoTicket generateRandomTicket(int id, std::set<int> excludeNumbers = {});
};

#endif
