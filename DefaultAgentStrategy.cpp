//
// Created by Stephen on 12/10/2015.
//

#include <iostream>
#include "DefaultAgentStrategy.h"
#include "Game.h"

Gaming::DefaultAgentStrategy::DefaultAgentStrategy() : Strategy()
{
}

Gaming::DefaultAgentStrategy::~DefaultAgentStrategy() {
    //TODO - Implement this
}

Gaming::ActionType Gaming::DefaultAgentStrategy::operator()(const Gaming::Surroundings &s) const {

    std::size_t act = 4;
    for(std::size_t i = 0; i < 9; i++){
        if(s.array[i] == ADVANTAGE){
            act = i;
            break;
        }
    }
    if(act == 4) {
        for (std::size_t i = 0; i < 9; i++) {
            if(s.array[i] == FOOD){
                act = i;
                break;
            }
        }
    }
    if(act == 4) {
        for (std::size_t i = 0; i < 9; i++) {
            if(s.array[i] == EMPTY){
                act = i;
                break;
            }
        }
    }
    if(act == 4) {
        for (std::size_t i = 0; i < 9; i++) {
            if(s.array[i] == SIMPLE){
                act = i;
                break;
            }
        }
    }

    switch(act){
        case 0:
            return NW;
        case 1:
            return N;
        case 2:
            return NE;
        case 3:
            return W;
        case 4:
            return STAY;
        case 5:
            return E;
        case 6:
            return SW;
        case 7:
            return S;
        case 8:
            return SE;
        default:
            return STAY;
    }
}
