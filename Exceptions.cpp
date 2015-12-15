//
// Created by Stephen on 12/10/2015.
//
#include <string>
#include "Exceptions.h"

void Gaming::GamingException::setName(std::string name) {
    __name = name;
}

Gaming::DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height) : GamingException(), __exp_width(expWidth), __exp_height(expHeight), __width(width), __height(height)
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
    setName("InsufficientDimensionsEx");
}

void Gaming::InsufficientDimensionsEx::__print_args(std::ostream &os) const {
}

void Gaming::OutOfBoundsEx::__print_args(std::ostream &os) const {
    //TODO - Implement this
}

Gaming::OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height) : DimensionEx(maxWidth,maxHeight,width,height)
{
    setName("OutOfBoundsEx");
}

namespace Gaming {
    std::ostream &operator<<(std::ostream &os, const GamingException &ex) {
        return os;
    }
}
