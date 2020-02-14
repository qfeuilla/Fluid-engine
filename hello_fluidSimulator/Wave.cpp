
#include "Wave.hpp"

Wave::Wave(double p, double s, double h, double w) : pos(p), speed(s), height(h), width(w) {}
Wave::Wave() : pos(0.0), speed(0.0), height(0.0), width(0.0) {}
Wave::~Wave() {}

double 			Wave::getPos() const {
	return(this->pos);
}

double 			Wave::getSpeed() const {
	return(this->speed);
}

const double 	Wave::getHeight() const {
	return(this->height);
}

const double 	Wave::getWidth() const {
	return(this->width);
}

void			Wave::setPos(double pos) {
	this->pos = pos;
}

void			Wave::setSpeed(double speed) {
	this->speed = speed;
}