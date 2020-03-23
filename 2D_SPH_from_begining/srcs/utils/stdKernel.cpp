
#include "../../includes/sph.h"

double stdKernel(double r) {
	if(r*r >= h*h) {
		return (0);
	} else {
		double x = 1.0 - (r * r) / (h * h);
		return (315.0 / (64.0 * PI * (std::pow(h, 3))) * std::pow(x, 3));
	}
}

double firstDerivativeStdKernel(double r) {
	if(r >= h) {
		return (0);
	} else {
		double x = 1.0 - (r * r) / (h * h);
		return (-945.0 / (32.0 * PI * (std::pow(h, 5))) * r * x * x);
	}
}

double secondDerivativeStdKernel(double r) {
	if(r*r >= h*h) {
		return (0);
	} else {
		double x = (r * r) / (h * h);
		return (945.0 / (32.0 * PI * (std::pow(h, 5))) * (1 - x) * (3 * x - 1));
	}
}

Vector2D stdKernelGradient(double r, const Vector2D directionToCenter) {
	return (directionToCenter * -firstDerivativeStdKernel(r));
}