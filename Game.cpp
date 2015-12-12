//
// Created by Stephen on 12/10/2015.
//

#include "Game.h"
#include "Simple.h"
#include "Strategic.h"
#include "Food.h"
#include "Advantage.h"

const unsigned int Gaming::Game::NUM_INIT_AGENT_FACTOR = 4;
const unsigned int Gaming::Game::NUM_INIT_RESOURCE_FACTOR = 2;
const unsigned Gaming::Game::MIN_WIDTH = 3;
const unsigned Gaming::Game::MIN_HEIGHT = 3;
const double Gaming::Game::STARTING_AGENT_ENERGY = 20;
const double Gaming::Game::STARTING_RESOURCE_CAPACITY = 10;

void Gaming::Game::populate() {
    //TODO - Implement this
}

Gaming::Game::Game() : __numInitAgents(0), __numInitResources(0), __width(MIN_WIDTH), __height(MIN_HEIGHT), __round(0), __status(NOT_STARTED), __verbose(false) //TODO:0th- __posRandomizer() 5th- __grid()
{
    std::vector<Piece *>* grid = new std::vector<Piece *>(9, nullptr);
    __grid = *grid;
}

Gaming::Game::Game(unsigned width, unsigned height, bool manual) : __width(width), __height(height), __round(0), __status(NOT_STARTED), __verbose(false)
{
    __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
    __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
    std::vector<Piece *>* grid = new std::vector<Piece *>(width*height, nullptr);
    __grid = *grid;
    populate();
    //TODO - Implement this
}

Gaming::Game::Game(const Gaming::Game &another) {
    __posRandomizer = another.__posRandomizer;
    __numInitAgents = another.__numInitAgents;
    __numInitResources = another.__numInitResources;
    __width = another.__width;
    __height = another.__height;
    __grid = another.__grid;
    __round = another.__round;
    __status = another.__status;
    __verbose = another.__verbose;
}

Gaming::Game::~Game() {
    //TODO - Implement this
}

unsigned int Gaming::Game::getNumPieces() const {
    return __numInitAgents + __numInitResources;
}

unsigned int Gaming::Game::getNumAgents() const {
    return __numInitAgents;
}

unsigned int Gaming::Game::getNumSimple() const {
    return 0;    //TODO - Implement this
}

unsigned int Gaming::Game::getNumStrategic() const {
    return 0;    //TODO - Implement this
}

unsigned int Gaming::Game::getNumResources() {
    return __numInitResources;
}

bool Gaming::Game::addSimple(const Gaming::Position &position) {
    Gaming:Simple* si = new Simple(*this,position,STARTING_AGENT_ENERGY);
    __grid[position.y * __width + position.x] = si;
    return true;  //TODO: Implement false condition
}

bool Gaming::Game::addSimple(unsigned x, unsigned y) {
    Position pos(x,y);
    Gaming::Simple* si = new Simple(*this,pos,STARTING_AGENT_ENERGY);
    __grid[pos.y * __width + pos.x] = si;
    return true;  //TODO: Implement false condition
}

bool Gaming::Game::addStrategic(const Gaming::Position &position, Gaming::Strategy *s) {
    //TODO: Make starting energy decided by type of strategy
    Gaming:Strategic* st = new Strategic(*this,position,STARTING_AGENT_ENERGY);
    __grid[position.y * __width + position.x] = st;
    return true;  //TODO: Implement false condition
}

bool Gaming::Game::addStrategic(unsigned x, unsigned y, Gaming::Strategy *s) {
    Position pos(x,y);
    //TODO: Make starting energy decided by type of strategy
    Gaming:Strategic* st = new Strategic(*this,pos,STARTING_AGENT_ENERGY);
    __grid[pos.y * __width + pos.x] = st;
    return true;  //TODO: Implement false condition
}

bool Gaming::Game::addFood(const Gaming::Position &position) {
    Gaming::Food* fo = new Food(*this,position,STARTING_RESOURCE_CAPACITY);
    __grid[position.y * __width + position.x] = fo;
    return true;  //TODO: Implement false condition
}

bool Gaming::Game::addFood(unsigned x, unsigned y) {
    Position pos(x,y);
    Gaming::Food* fo = new Food(*this,pos,STARTING_RESOURCE_CAPACITY);
    __grid[pos.y * __width + pos.x] = fo;
    return true;  //TODO: Implement false condition
}

bool Gaming::Game::addAdvantage(const Gaming::Position &position) {
    Gaming::Advantage* ad = new Advantage(*this,position,STARTING_RESOURCE_CAPACITY);
    __grid[position.y * __width + position.x] = ad;
    return true;    //TODO: Implement false condition
}

bool Gaming::Game::addAdvantage(unsigned x, unsigned y) {
    Position pos(x,y);
    Gaming::Advantage* ad = new Advantage(*this,pos,STARTING_RESOURCE_CAPACITY);
    __grid[pos.y * __width + pos.x] = ad;
    return true;    //TODO: Implement false condition
}

const Gaming::Surroundings Gaming::Game::getSurroundings(const Gaming::Position &pos) const {
    int x = pos.x-1;
    int y = pos.y-1;
    Surroundings s;

    int posCount = 0;
    int boardPos = y*__width + x;
    for(int i = -1; i < 2; i++) {
        for(int j = -1; j < 2; j++) {
            if (boardPos > __width*__height - 1 || (pos.x + j) < 0 || (pos.x + j) > __width || (pos.y + i) < 0 || (pos.y + i) > __height) {
                s.array[posCount] = INACCESSIBLE;
            } else if (i == 0 && j == 0) {
                s.array[posCount] = SELF;
            } else if (__grid[boardPos] != nullptr) {
                s.array[posCount] = __grid[boardPos]->getType();
            } else {
                s.array[posCount] = EMPTY;
            }
            posCount++;
            boardPos++;
        }
    }

    for(std::size_t i = 0; i < 9; i++){
        std::cout << "-" << s.array[i];
    }
    std::cout << "-";
    return s;
}

const Gaming::ActionType Gaming::Game::reachSurroundings(const Gaming::Position &from, const Gaming::Position &to) {
    return S;    //TODO - Implement this
}

bool Gaming::Game::isLegal(const Gaming::ActionType &ac, const Gaming::Position &pos) const {
    return false;    //TODO - Implement this
}

const Gaming::Position Gaming::Game::move(const Gaming::Position &pos, const Gaming::ActionType &ac) const {
    return Gaming::Position();    //TODO - Implement this
}

void Gaming::Game::round() {
    //TODO - Implement this
}

void Gaming::Game::play(bool verbose) {
    //TODO - Implement this
}

namespace Gaming {
    std::ostream &operator<<(std::ostream &os, const Game &game) {
        return os;
    }
}
