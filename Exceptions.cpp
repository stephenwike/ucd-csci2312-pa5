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
    os << "Minimum Height: " << __exp_height << ", Minimum Width: " << __exp_width << ", Current Height: " << __height << ", Current Width: " << __width;
}

void Gaming::OutOfBoundsEx::__print_args(std::ostream &os) const {
    os << "Maximum Height: " << __exp_height << ", Maximum Width: " << __exp_width << ", Current Height: " << __height << ", Current Width: " << __width;
}

Gaming::OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height) : DimensionEx(maxWidth,maxHeight,width,height)
{
    setName("OutOfBoundsEx");
}

namespace Gaming {
    std::ostream &operator<<(std::ostream &os, const GamingException &ex) {
        os << ex.__name << ": ";
        ex.__print_args(os);
        return os;
    }
}
