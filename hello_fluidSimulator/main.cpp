#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <string>
#include <iostream>
#include <thread>
#include "Wave.hpp"

using namespace std;
using namespace chrono;

const size_t	kBufferSize = 80;
const char		*kGrayScaleTable = " .:-=+*#%@";
const size_t 	kGrayScaleTableSize = sizeof(kGrayScaleTable) / sizeof(char);

void	updateWave(const double time_interval, Wave *w) {
	(*w).setPos((*w).getPos() + time_interval * (*w).getSpeed());
	if ((*w).getPos() > 1.0) {
		(*w).setSpeed((*w).getSpeed() * -1.0);
		(*w).setPos(1.0 + time_interval * (*w).getSpeed());
	} else if ((*w).getPos() < 0.0) {
		(*w).setSpeed((*w).getSpeed() * -1.0);
		(*w).setPos(time_interval * (*w).getSpeed());
	}
}

void	accumulateWaveToHeightField(Wave w, array<double, kBufferSize> *heightField) {
	const double quarterWaveLength = 0.25 * w.getWidth();
	const int start =static_cast<int>((w.getPos() - quarterWaveLength) * kBufferSize);
	const int end =static_cast<int>((w.getPos() + quarterWaveLength) * kBufferSize);

	for (int i=start; i < end; i++) {
		int iN = i;
		if (i < 0) {
			iN = -i - 1;
		} else if (i >= static_cast<int>(kBufferSize)) {
			iN = 2 * kBufferSize - i - 1;
		}
		double distance = fabs((i + 0.5) / kBufferSize - w.getPos());
		double height = w.getHeight() * 0.5 * (cos(min(distance * M_PI / quarterWaveLength, M_PI)) + 1.0);
		(*heightField)[iN] += height;
	}
}

void draw(const array<double, kBufferSize> &heightField) {
	string buffer(kBufferSize, ' ');

	// Convert height field to grayscale
	for(size_t i = 0; i < kBufferSize; ++i) {
		double height = heightField[i];
		size_t tableIndex = min(
			static_cast<size_t>(floor(kGrayScaleTableSize * height)),
			kGrayScaleTableSize - 1);
		buffer[i] = kGrayScaleTable[tableIndex];
	}

	// Clear old prints
	for(size_t i = 0; i < kBufferSize; ++i) {
		printf("\b");
	}

	printf("%s", buffer.c_str());
	fflush(stdout);
}

int		main () {
    Wave 						x(0.0, 1.0, 0.5, 0.8);
    Wave 						y(1.0, -0.5, 0.4, 1.2);
	Wave 						z(0.5, 0.25, 0.45, 1.0);

    const int 					fps = 100;
    const double 				time_interval = 1.0 / fps;
    
	array<double, kBufferSize> 	heightField;
    
	for (int i = 0; i < 1000; i++) {
		updateWave(time_interval, &x);
		updateWave(time_interval, &y);
		updateWave(time_interval, &z);

		for(double &height : heightField) {
			height = 0.0;
		}

		accumulateWaveToHeightField(x, &heightField);
		accumulateWaveToHeightField(y, &heightField);
		accumulateWaveToHeightField(z, &heightField);

		draw(heightField);

		this_thread::sleep_for(milliseconds(1000 / fps));
	}

	printf("\n");
	fflush(stdout);
	return (0);
}