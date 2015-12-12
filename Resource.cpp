//
// Created by Stephen on 12/10/2015.
//

#include "Game.h"
#include "Gaming.h"
#include "Agent.h"
#include "Resource.h"

const double Gaming::Resource::RESOURCE_SPOIL_FACTOR = 1.2;

Gaming::Resource::Resource(const Gaming::Game &g, const Gaming::Position &p, double __capacity) : Piece(g,p), __capacity(__capacity)
{
}

Gaming::Resource::~Resource() {
    //TODO - Implement this
}

double Gaming::Resource::consume() {
    return 0;    //TODO - Implement this
}

void Gaming::Resource::age() {
    //__capacity /= RESOURCE_SPOIL_FACTOR;
    __capacity = (int)__capacity / RESOURCE_SPOIL_FACTOR;
    if(!isViable()){
        finish();
    }
}

Gaming::ActionType Gaming::Resource::takeTurn(const Gaming::Surroundings &s) const {
    return STAY;
}

Gaming::Piece &Gaming::Resource::operator*(Gaming::Piece &other) {
    return other.interact(this);    //TODO - Implement this
}

Gaming::Piece &Gaming::Resource::interact(Gaming::Agent *agent) {
    return *this;    //TODO - Implement this
}

Gaming::Piece &Gaming::Resource::interact(Gaming::Resource *resource) {
    return *this;    //TODO - Implement this
}
