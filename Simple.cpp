//
// Created by Stephen on 12/10/2015.
//
#include "Game.h"
#include "Agent.h"
#include "Simple.h"

const char Gaming::Simple::SIMPLE_ID = 'S';

Gaming::Simple::Simple(const Gaming::Game &g, const Gaming::Position &p, double energy) : Agent(g,p,energy)
{
}

Gaming::Simple::~Simple() {
    //TODO - Implement this
}

void Gaming::Simple::print(std::ostream &os) const {
    os << SIMPLE_ID;
}

Gaming::ActionType Gaming::Simple::takeTurn(const Gaming::Surroundings &s) const {

    std::size_t act = 4;
    for(std::size_t i = 0; i < 9; i++){
        if(s.array[i] == FOOD || s.array[i] == ADVANTAGE){
            act = i;
            break;
        }else if(act == 4){
            if(s.array[i] == EMPTY){
                act = i;
            }
        }
    }

    switch(act){
        case 0:
            return NW;
        case 1:
            return W;
        case 2:
            return SW;
        case 3:
            return N;
        case 4:
            return STAY;
        case 5:
            return S;
        case 6:
            return NE;
        case 7:
            return E;
        case 8:
            return SE;
        default:
            return STAY;
    }
}


