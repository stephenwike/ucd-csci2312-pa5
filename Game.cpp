//
// Created by Stephen on 12/10/2015.
//

#include <iomanip>
#include <typeinfo>
#include "Game.h"
#include "Simple.h"
#include "Strategic.h"
#include "Food.h"
#include "Advantage.h"
#include "Exceptions.h"
#include "AggressiveAgentStrategy.h"

const unsigned int Gaming::Game::NUM_INIT_AGENT_FACTOR = 4;
const unsigned int Gaming::Game::NUM_INIT_RESOURCE_FACTOR = 2;
const unsigned Gaming::Game::MIN_WIDTH = 3;
const unsigned Gaming::Game::MIN_HEIGHT = 3;
const double Gaming::Game::STARTING_AGENT_ENERGY = 20;
const double Gaming::Game::STARTING_RESOURCE_CAPACITY = 10;

void Gaming::Game::populate() {
    unsigned int numStrategic = __numInitAgents / 2;
    unsigned int numSimple = __numInitAgents - numStrategic;
    unsigned int numAdvantages = __numInitResources / 4;
    unsigned int numFoods = __numInitResources - numAdvantages;

    std::default_random_engine gen;
    std::uniform_int_distribution<int> d(0, __width * __height - 1);

    while (numStrategic > 0) {
        int i = d(gen); // random index in the grid vector
        if (__grid[i] == nullptr) { // is position empty
            Position pos(i / __width, i % __width);
            __grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
            numStrategic --;
        }
    }
    while (numSimple > 0) {
        int i = d(gen); // random index in the grid vector
        if (__grid[i] == nullptr) { // is position empty
            Position pos(i / __width, i % __width);
            __grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
            numSimple --;
        }
    }
    while (numAdvantages > 0) {
        int i = d(gen); // random index in the grid vector
        if (__grid[i] == nullptr) { // is position empty
            Position pos(i / __width, i % __width);
            __grid[i] = new Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
            numAdvantages --;
        }
    }
    while (numFoods > 0) {
        int i = d(gen); // random index in the grid vector
        if (__grid[i] == nullptr) { // is position empty
            Position pos(i / __width, i % __width);
            __grid[i] = new Food(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
            numFoods --;
        }
    }
}

Gaming::Game::Game() : __numInitAgents(0), __numInitResources(0), __width(MIN_WIDTH), __height(MIN_HEIGHT), __round(0), __status(NOT_STARTED), __verbose(false) //TODO:0th- __posRandomizer()
{
    std::vector<Piece *>* grid = new std::vector<Piece *>(9, nullptr);
    __grid = *grid;
}

Gaming::Game::Game(unsigned width, unsigned height, bool manual) : __width(width), __height(height), __round(0), __status(NOT_STARTED), __verbose(false)
{
    if(width < MIN_WIDTH || height < MIN_HEIGHT){
        InsufficientDimensionsEx ex(MIN_WIDTH,MIN_HEIGHT,width,height);
        throw ex;
    }
    std::vector<Piece *>* grid = new std::vector<Piece *>(width*height, nullptr);
    __grid = *grid;
    if(manual){
        __numInitResources = 0; __numInitAgents = 0;
    }
    else{
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
        populate();
    }
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
    unsigned int numRes = 0;
    for (auto it = __grid.begin(); it != __grid.end(); ++it) {
        Resource *res = dynamic_cast<Food*>(*it);
        if (res) numRes ++;
    }
    for (auto it = __grid.begin(); it != __grid.end(); ++it) {
        Resource *res = dynamic_cast<Advantage*>(*it);
        if (res) numRes ++;
    }
    return (getNumAgents() + numRes);
}

unsigned int Gaming::Game::getNumAgents() const {
    return (getNumSimple() + getNumStrategic());
}

unsigned int Gaming::Game::getNumSimple() const {
    unsigned int numAgents = 0;
    for (auto it = __grid.begin(); it != __grid.end(); ++it) {
        Agent *agent = dynamic_cast<Simple*>(*it);
        if (agent) numAgents ++;
    }
    return numAgents;
}

unsigned int Gaming::Game::getNumStrategic() const {
    unsigned int numAgents = 0;
    for (auto it = __grid.begin(); it != __grid.end(); ++it) {
        Agent *agent = dynamic_cast<Strategic*>(*it);
        if (agent) numAgents ++;
    }
    return numAgents;
}

unsigned int Gaming::Game::getNumResources() {
    unsigned int numRes = 0;
    for (auto it = __grid.begin(); it != __grid.end(); ++it) {
        Resource *res = dynamic_cast<Food*>(*it);
        if (res) numRes ++;
    }
    for (auto it = __grid.begin(); it != __grid.end(); ++it) {
        Resource *res = dynamic_cast<Advantage*>(*it);
        if (res) numRes ++;
    }
    return numRes;
}

bool Gaming::Game::addSimple(const Gaming::Position &position) {
    if(position.x >= __height || position.y >= __width){
        OutOfBoundsEx ex(__width,__height,position.x,position.y);
        throw ex;
    }
    if(__grid[position.x*__width + position.y] != nullptr){
        return false;
    }
    Gaming:Simple* si = new Simple(*this,position,STARTING_AGENT_ENERGY);
    __grid[position.x * __width + position.y] = si;
    return true;
}

bool Gaming::Game::addSimple(unsigned x, unsigned y) {
    if(x >= __height || y >= __width){
        OutOfBoundsEx ex(__width,__height,x,y);
        throw ex;
    }
    if(__grid[x*__width + y] != nullptr){
        return false;
    }
    Position pos(x,y);
    Gaming::Simple* si = new Simple(*this,pos,STARTING_AGENT_ENERGY);
    __grid[pos.x * __width + pos.y] = si;
    return true;
}

bool Gaming::Game::addStrategic(const Gaming::Position &position, Gaming::Strategy *s) {
    if(position.x >= __height || position.y >= __width){
        OutOfBoundsEx ex(__width,__height,position.x,position.y);
        throw ex;
    }
    if(__grid[position.x*__width + position.y] != nullptr){
        return false;
    }
    Gaming:Strategic* st = new Strategic(*this,position,STARTING_AGENT_ENERGY,s);
    __grid[position.x * __width + position.y] = st;
    return true;
}

bool Gaming::Game::addStrategic(unsigned x, unsigned y, Gaming::Strategy *s) {
    if(x >= __height || y >= __width){
        OutOfBoundsEx ex(__width,__height,x,y);
        throw ex;
    }
    if(__grid[x*__width + y] != nullptr){
        return false;
    }
    Position pos(x,y);
    Gaming:Strategic* st = new Strategic(*this,pos,STARTING_AGENT_ENERGY,s);
    __grid[pos.x * __width + pos.y] = st;
    return true;
}

bool Gaming::Game::addFood(const Gaming::Position &position) {
    if(position.x >= __height || position.y >= __width){
        OutOfBoundsEx ex(__width,__height,position.x,position.y);
        throw ex;
    }
    if(__grid[position.x*__width + position.y] != nullptr){
        return false;
    }
    Gaming::Food* fo = new Food(*this,position,STARTING_RESOURCE_CAPACITY);
    __grid[position.x * __width + position.y] = fo;
    return true;
}

bool Gaming::Game::addFood(unsigned x, unsigned y) {
    if(x >= __height || y >= __width){
        OutOfBoundsEx ex(__width,__height,x,y);
        throw ex;
    }
    if(__grid[x*__width + y] != nullptr){
        return false;
    }
    Position pos(x,y);
    Gaming::Food* fo = new Food(*this,pos,STARTING_RESOURCE_CAPACITY);
    __grid[pos.x * __width + pos.y] = fo;
    return true;
}

bool Gaming::Game::addAdvantage(const Gaming::Position &position) {
    if(position.x >= __height || position.y >= __width){
        OutOfBoundsEx ex(__width,__height,position.x,position.y);
        throw ex;
    }
    if(__grid[position.x*__width + position.y] != nullptr){
        return false;
    }
    Gaming::Advantage* ad = new Advantage(*this,position,STARTING_RESOURCE_CAPACITY);
    __grid[position.x * __width + position.y] = ad;
    return true;
}

bool Gaming::Game::addAdvantage(unsigned x, unsigned y) {
    if(x >= __height || y >= __width){
        OutOfBoundsEx ex(__width,__height,x,y);
        throw ex;
    }
    if(__grid[x*__width + y] != nullptr){
        return false;
    }
    Position pos(x,y);
    Gaming::Advantage* ad = new Advantage(*this,pos,STARTING_RESOURCE_CAPACITY);
    __grid[pos.x * __width + pos.y] = ad;
    return true;
}

const Gaming::Surroundings Gaming::Game::getSurroundings(const Gaming::Position &pos) const {
    Surroundings s;

    int posCount = 0;
    for(int i = -1; i < 2; i++) {
        for(int j = -1; j < 2; j++) {
            int board = ((pos.x + i)*__width + (pos.y + j));
            if (board < 0 || board >= __width*__height || (pos.x + i) < 0 || (pos.x + i) >= __height || (pos.y + j) < 0 || (pos.y + j) >= __width) { //boardPos < 0 || boardPos >= __width*__height ||
                s.array[posCount] = INACCESSIBLE;
            } else if (i == 0 && j == 0) {
                s.array[posCount] = SELF;
            } else if (__grid[board] != nullptr) {
                s.array[posCount] = __grid[board]->getType();
            } else {
                s.array[posCount] = EMPTY;
            }
            posCount++;
        }
    }

//    for(std::size_t i = 0; i < 9; i++){
//        std::cout << "-" << s.array[i];
//    }
//    std::cout << "- : ";
    return s;
}

const Gaming::ActionType Gaming::Game::reachSurroundings(const Gaming::Position &from, const Gaming::Position &to) {
    if(from.x > to.x && from.y > to.y){
        return NW;
    }
    if(from.x > to.x && from.y == to.y){
        return N;
    }
    if(from.x > to.x && from.y < to.y){
        return NE;
    }
    if(from.x == to.x && from.y > to.y){
        return W;
    }
    if(from.x == to.x && from.y == to.y){
        return STAY;
    }
    if(from.x == to.x && from.y < to.y){
        return E;
    }
    if(from.x < to.x && from.y > to.y){
        return SW;
    }
    if(from.x < to.x && from.y == to.y){
        return S;
    }
    if(from.x < to.x && from.y < to.y){
        return SE;
    }
}

bool Gaming::Game::isLegal(const Gaming::ActionType &ac, const Gaming::Position &pos) const {
    Surroundings s = getSurroundings(pos);

    int num = 0;
    switch(ac){
        case NW:
            num = 0;
            break;
        case N:
            num = 1;
            break;
        case NE:
            num = 2;
            break;
        case W:
            num = 3;
            break;
        case STAY:
            num = 4;
            break;
        case E:
            num = 5;
            break;
        case SW:
            num = 6;
            break;
        case S:
            num = 7;
            break;
        case SE:
            num = 8;
            break;
        default:
            num = 4;
    }

    return s.array[num] != INACCESSIBLE;
}

const Gaming::Position Gaming::Game::move(const Gaming::Position &pos, const Gaming::ActionType &ac) const {
    Position p;
    int x = 0, y = 0;
    if(isLegal(ac,pos)){
        switch(ac){
            case NW: { x = -1; y = -1; }
                break;
            case N: { x = -1; y = 0; }
                break;
            case NE: { x = -1; y = 1; }
                break;
            case W: { x = 0; y = -1; }
                break;
            case STAY: { x = 0; y = 0; }
                break;
            case E: { x = 0; y = 1; }
                break;
            case SW: { x = 1; y = -1; }
                break;
            case S: { x = 1; y = 0; }
                break;
            case SE: { x = 1; y = 1; }
                break;
            default: { x = 0; y = 0; }
                break;
        }
    }
    p.x = pos.x + x; p.y = pos.y + y;

    return p;
}

void Gaming::Game::round() {
    for(unsigned int i = 0; i < __height; i++){
        for(unsigned int j = 0; j < __width; j++) {
            if (__grid[i * __width + j] != nullptr) {
                if (__grid[i * __width + j]->getType() == SIMPLE || __grid[i * __width + j]->getType() == STRATEGIC) {
                    if(!__grid[i * __width + j]->getTurned()) {
                        __grid[i * __width + j]->setTurned(true);
                        Position pos(i, j);
                        Surroundings surr = getSurroundings(pos);
                        std::cout << "- ";
                        Position newPos = move(__grid[i * __width + j]->getPosition(), __grid[i * __width + j]->takeTurn(surr));
                        if(pos.x != newPos.x || newPos.y != pos.y) {
                            Piece *s1 = __grid[i * __width + j], *s2 = __grid[newPos.x * __width + newPos.y];
                            if (s2 != nullptr) {  //In
                                *s1 * *s2;
                            }
                            for (unsigned int k = 0; k < __width * __height; k++) {
                                if (__grid[k] != nullptr) {
                                    if (!__grid[k]->isViable()) {
                                        delete __grid[k];
                                        __grid[k] = nullptr;
                                    }
                                }
                            }
                            if(__grid[i * __width + j] != nullptr) {
                                __grid[newPos.x * __width + newPos.y] = s1;
                                s1->setPosition(newPos);
                                __grid[i * __width + j] = nullptr;
                            }
                        }
                    }
                }
            }
        }
    }
    for(unsigned int i = 0; i < __height*__width; i++){  //Clears finished pieces
        if (__grid[i] != nullptr) {
            if(__grid[i]->getType() == SIMPLE || __grid[i]->getType() == STRATEGIC || __grid[i]->getType() == FOOD || __grid[i]->getType() == ADVANTAGE){
                if(!__grid[i]->isViable()){
                    delete __grid[i];
                    __grid[i] = nullptr;
                }
            }
            if (__grid[i]->getType() == SIMPLE || __grid[i]->getType() == STRATEGIC) {
                __grid[i]->setTurned(false);
            }
        }
    }
    __round++;
    //Age everything
    for(unsigned int i = 0; i < __width*__height; i++) {
        if(__grid[i] != nullptr){
            __grid[i]->age();
        }
    }
    if(getNumResources() == 0){
        __status = OVER;
    }
    //TODO - Implement this
}

void Gaming::Game::play(bool verbose) {
    __status = PLAYING;

    while(__status != OVER) {
        if(!__verbose){
            std::cout << *this;
        }
        round();
    }
    std::cout << *this;
}

namespace Gaming {
    std::ostream &operator<<(std::ostream &os, const Game &game) {
        os << "Round " << game.__round << std::endl;
        for(std::size_t i = 0; i < game.__height; i++){
            for(std::size_t j = 0; j < game.__width; j++) {
                if(game.__grid[i * game.__width + j] != nullptr){
                    os << "[" << *(game.__grid[i * game.__width + j]) << " ]";
                }else{
                    os << "[" << std::setw(6) << "]";
                }
            }
            os << std::endl;
        }
        os << "Status: " << game.__status << std::endl;
        return os;
    }
}