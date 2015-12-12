//
// Created by Stephen on 12/10/2015.
//

#include "Game.h"
#include "Piece.h"
#include "Agent.h"
#include "Resource.h"

const double Gaming::Agent::AGENT_FATIGUE_RATE = 0.3;

Gaming::Agent::Agent(const Gaming::Game &g, const Gaming::Position &p, double energy) : Piece(g,p), __energy(energy)
{
}

Gaming::Agent::~Agent() {
    //TODO - Implement this
}

void Gaming::Agent::age() {
    __energy -= AGENT_FATIGUE_RATE;
    if(!isViable()){
        finish();
    }
}

Gaming::Piece &Gaming::Agent::operator*(Gaming::Piece &other) {
    return other.interact(this);
}

Gaming::Piece &Gaming::Agent::interact(Gaming::Agent *agent) {
    return *this;
}

Gaming::Piece &Gaming::Agent::interact(Gaming::Resource *resource) {
    return *this;
}
