//
// Created by Stephen on 12/10/2015.
//

#include "Game.h"
#include "Food.h"

const char Gaming::Food::FOOD_ID = 'F';

Gaming::Food::Food(const Gaming::Game &g, const Gaming::Position &p, double capacity) : Resource(g,p,capacity)
{
}

Gaming::Food::~Food() {
    //TODO - Implement this
}

void Gaming::Food::print(std::ostream &os) const {
    //std::cout << FOOD_ID;
    os << FOOD_ID;
    //TODO - Implement this
}
