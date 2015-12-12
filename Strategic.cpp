//
// Created by Stephen on 12/10/2015.
//
#include "Game.h"
#include "Strategy.h"
#include "Strategic.h"

const char Gaming::Strategic::STRATEGIC_ID = 'T';

Gaming::Strategic::Strategic(const Gaming::Game &g, const Gaming::Position &p, double energy, Gaming::Strategy *s) : Agent(g,p,energy), __strategy(s)
{
}

Gaming::Strategic::~Strategic() {
    //TODO - Implement this
}

void Gaming::Strategic::print(std::ostream &os) const {
    os << STRATEGIC_ID;
}

Gaming::ActionType Gaming::Strategic::takeTurn(const Gaming::Surroundings &s) const {
    return (*__strategy)(s);
}
