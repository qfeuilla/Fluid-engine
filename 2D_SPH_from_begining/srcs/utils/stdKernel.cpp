
#include "../../includes/sph.h"

double stdKernel(double r) {
    if(r >= h) {
        return (0);
    } else if (r >= 0) {
        double x = 1.0 - (r * r) / (h * h);
        return (315.0 / (64.0 * PI * (h * h * h)) * x * x * x);
    }
    return(0);
}