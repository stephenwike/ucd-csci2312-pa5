//
// Created by Stephen on 12/10/2015.
//
#include <string>
#include "Exceptions.h"

void Gaming::GamingException::setName(std::string name) {
    std::cout << "ERROR: " << name << ": Something went wrong.  Elaboration needed!" << std::endl;
}

Gaming::DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height) : __exp_width(expWidth), __exp_height(expHeight), __width(width), __height(height)
{
}

unsigned Gaming::DimensionEx::getExpWidth() const {
    return __exp_width;
}

unsigned Gaming::DimensionEx::getExpHeight() const {
    return __exp_width;
}

unsigned Gaming::DimensionEx::getWidth() const {
    return __width;
}

unsigned Gaming::DimensionEx::getHeight() const {
    return __height;
}

Gaming::InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight, unsigned width, unsigned height) : DimensionEx(minWidth,minHeight,width,height)
{
}

void Gaming::InsufficientDimensionsEx::__print_args(std::ostream &os) const {
    //TODO - Implement this
}

void Gaming::OutOfBoundsEx::__print_args(std::ostream &os) const {
    //TODO - Implement this
}

Gaming::OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height) : DimensionEx(maxWidth,maxHeight,width,height)
{
}

namespace Gaming {
    std::ostream &operator<<(std::ostream &os, const GamingException &ex) {
        return os;
    }
}
