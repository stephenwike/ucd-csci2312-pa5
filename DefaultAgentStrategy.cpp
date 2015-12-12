//
// Created by Stephen on 12/10/2015.
//

#include <iostream>
#include "DefaultAgentStrategy.h"
#include "Game.h"

Gaming::DefaultAgentStrategy::DefaultAgentStrategy() : Strategy() {
    //TODO - Implement this
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

    std::cout << "DAS: FINAL ACT: " << act << " :: ";
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
