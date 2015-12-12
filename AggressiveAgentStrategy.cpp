//
// Created by Stephen on 12/10/2015.
//

#include "Game.h"
#include "AggressiveAgentStrategy.h"

const double Gaming::AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Gaming::Game::STARTING_AGENT_ENERGY * 0.75;

Gaming::AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) : Strategy(){
    __agentEnergy = agentEnergy;
}

Gaming::AggressiveAgentStrategy::~AggressiveAgentStrategy() {
    //TODO - Implement this
}

Gaming::ActionType Gaming::AggressiveAgentStrategy::operator()(const Gaming::Surroundings &s) const {
    std::size_t act = 4;
    if(__agentEnergy >= DEFAULT_AGGRESSION_THRESHOLD) {
        for (std::size_t i = 0; i < 9; i++) {
            if (s.array[i] == SIMPLE || s.array[i] == STRATEGIC) {
                act = i;
                break;
            }
        }
    }
    if(act == 4) {
        for (std::size_t i = 0; i < 9; i++) {
            if(s.array[i] == ADVANTAGE){
                act = i;
                break;
            }
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

    std::cout << "AAS: FINAL ACT: " << act << " :: ";
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
