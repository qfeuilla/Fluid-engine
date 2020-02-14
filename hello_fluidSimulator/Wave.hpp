
#ifndef WAVE_HPP
#define WAVE_HPP

#include <iostream>

class Wave {
public:
	Wave(double pos, double speed, double height, double width);
	Wave();
	~Wave();
	
	double getPos() const;
	double getSpeed() const;
	const double getHeight() const;
	const double getWidth() const;

	void setPos(double pos);
	void setSpeed(double speed);

private:
	double      	pos;
	double      	speed;
	const double    height;
	const double    width;
};

#endif