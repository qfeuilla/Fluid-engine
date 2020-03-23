
#include "../../includes/sph.h"

double spikyKernel(double r) {
	if(r >= h) {
		return (0);
	} else {
		double x = 1.0 - r / h;
		return (15.0 / (PI * (std::pow(h, 3))) * std::pow(x, 3));
	}
}

double firstDerivativeSpikyKernel(double r) {
	if(r >= h) {
		return (0);
	} else {
		double x = 1.0 - r / h;
		return (-45.0 / (PI * (std::pow(h, 4))) * x * x);
	}
}

double secondDerivativeSpikyKernel(double r) {
	if(r >= h) {
		return (0);
	} else {
		double x = 1.0 - r / h;
		return (90.0 / (PI * (std::pow(h, 5))) * x);
	}
}

Vector2D spikyKernelGradient(double r, const Vector2D directionToCenter) {
	return (directionToCenter * -firstDerivativeSpikyKernel(r));
}