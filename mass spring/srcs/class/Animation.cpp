#include "Animation.hpp"

Frame::Frame() {
}

Frame::Frame(int newIndex, double newTimeIntervalInSecond) : index(newIndex), timeIntervalInSeconds(newTimeIntervalInSecond) {
}

double Frame::timeInSeconds() const {
    return index * timeIntervalInSeconds;
}

void Frame::advance() {
    ++index;
}

void Frame::advance(int delta) {
    index += delta;
}

Frame &Frame::operator++() {
    advance();
    return *this;
}

Frame Frame::operator++(int i) {
    (void)i;

    Frame result = *this;
    advance();
    return result;
}

Animation::Animation() {
}

Animation::~Animation() {
}

void Animation::update(const Frame& frame) {
    onUpdate(frame);
}