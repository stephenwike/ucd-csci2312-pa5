//
// Created by Stephen on 12/10/2015.
//

#include "Game.h"
#include "Gaming.h"
#include "Agent.h"
#include "Resource.h"
#include "Advantage.h"

const double Gaming::Resource::RESOURCE_SPOIL_FACTOR = 1.2;

Gaming::Resource::Resource(const Gaming::Game &g, const Gaming::Position &p, double __capacity) : Piece(g,p), __capacity(__capacity)
{
}

Gaming::Resource::~Resource() {
    //TODO - Implement this
}

double Gaming::Resource::consume() {
    return 0;
}

void Gaming::Resource::age() {
    __capacity = (int)__capacity / RESOURCE_SPOIL_FACTOR;
    if(!isViable()){
        finish();
    }
}

Gaming::ActionType Gaming::Resource::takeTurn(const Gaming::Surroundings &s) const {
    return STAY;
}

Gaming::Piece &Gaming::Resource::operator*(Gaming::Piece &other) {
    return other.interact(this);
}

Gaming::Piece &Gaming::Resource::interact(Gaming::Agent *agent) {
    if(getType() == FOOD){
        agent->addEnergy(__capacity);
    }if(getType() == ADVANTAGE){
        agent->addEnergy(__capacity * Advantage::ADVANTAGE_MULT_FACTOR);
    }
    finish();
    return *this;
}

Gaming::Piece &Gaming::Resource::interact(Gaming::Resource *resource) {
    return *this;
}
