
#include "../includes/sph.h"

void SPHSolver2D::advanceTimeStep(double advance_time) {
	beginAdvanceTimeStep(); // preprocess for the Algorithm

	accumulateForces(advance_time);
	//std::cout << particle_datas._densities[5] << std::endl;
	timeIntegration(advance_time);
	resolveCollision(advance_time);

	endAdvanceTimeStep(advance_time); // postprocess for the Algorithm
}

void SPHSolver2D::accumulateForces(double advance_time) {
	accumulateNonPressureForces(advance_time);
	accumulatePressureForce(advance_time);
}

void SPHSolver2D::accumulateNonPressureForces(double timeIntervalInSeconds) {
	accumulateExternalForces(timeIntervalInSeconds);
	accumulateViscosityForce();
}

void SPHSolver2D::accumulateViscosityForce() {
	size_t n = particle_datas.numberOfParticles();
	double pm2 = pm * pm;
	double d;

	for (int i = 0; i < n; i++) {
		for (int n: particle_datas._neighbors[i]) {
			if (particle_datas._densities[n]) {
				d = dist(particle_datas._positions[i], particle_datas._positions[n]);
				particle_datas._forces[i] += ((particle_datas._velocities[n] - particle_datas._velocities[i]) / particle_datas._densities[n])
											* secondDerivativeSpikyKernel(d)
											* viscosityCoefficient * pm2;
			}
		}
	}
}

void SPHSolver2D::accumulatePressureForce(double timeIntervalInSeconds) {
	computePressure();
	accumulatePressureForce();
}

double SPHSolver2D::computePressureFromEos(double density, double targetDensity, double eosScale, double eosExponent, double negativePressureScale) {
	double p = eosScale / eosExponent * (std::pow((density / targetDensity), eosExponent) - 1.0);
	p *= p < 0 ? negativePressureScale : 1;
	return (p);
}

void SPHSolver2D::computePressure() {
	size_t n = particle_datas.numberOfParticles();
	double eosScale = particle_datas.targetDensity * (std::pow(VSOUND, 2));
	for (int i = 0; i < n; i++) {
		particle_datas._pressure[i] = computePressureFromEos(particle_datas._densities[i], particle_datas.targetDensity, eosScale, eosExponent, negativePressureScale);
	}
}

void SPHSolver2D::accumulatePressureForce() {
	size_t n = particle_datas.numberOfParticles();
	Vector2D dir;	
	double pm2 = pm * pm;
	double d;

	for (int i = 0; i < n; i++) {
		for (int n: particle_datas._neighbors[i]) {
			d = dist(particle_datas._positions[i], particle_datas._positions[n]);
			if (d > 0) {
				//std::cout << particle_datas._pressure[i] << std::endl;
				if (particle_datas._densities[n]) {
					dir = (particle_datas._positions[n] - particle_datas._positions[i]) / d;
					particle_datas._forces[i] -= spikyKernelGradient(d, dir) * 
												(particle_datas._pressure[i] / (std::pow(particle_datas._densities[i] , 2))
												+ particle_datas._pressure[n] / (std::pow(particle_datas._densities[n] , 2)))
												* pm2;
				}
			}
		}
	}
}

void SPHSolver2D::accumulateExternalForces(double advance_time) {
	Vector2D force;
	Vector2D relativeVel;
	size_t n = particle_datas.numberOfParticles();

	for (int i = 0; i < n; i++) {
		force = _gravity * pm;
		relativeVel = particle_datas._velocities[i] - wind_dir;
		force +=  relativeVel * -_dragCoefficient;
		particle_datas._forces[i] += force;
	}
}

void SPHSolver2D::beginAdvanceTimeStep() {
	size_t n = particle_datas.numberOfParticles();
	_newPositions.resize(n);
	_newVelocities.resize(n);
	particle_datas._forces.clear();
	particle_datas._forces.resize(n, Vector2D(0, 0));

	onBeginAdvanceTimeStep();
}

void SPHSolver2D::onBeginAdvanceTimeStep() {
	particle_datas.comput_neighbors();
	particle_datas.compute_densities();
}

void SPHSolver2D::endAdvanceTimeStep(double timeStepInSeconds) {
	size_t n = particle_datas.numberOfParticles();

	for (int i = 0; i < n; i++) {
		particle_datas._velocities[i] = _newVelocities[i];
		particle_datas._positions[i] = _newPositions[i];
	}
	onEndAdvanceTimeStep(timeStepInSeconds);
}

void SPHSolver2D::onEndAdvanceTimeStep(double timeStepInSeconds) {
	computePseudoViscosity(timeStepInSeconds);
}

void SPHSolver2D::computePseudoViscosity(double timeStepInSeconds) {
	size_t n = particle_datas.numberOfParticles();
	ParticleSystemData2::VectorArray smoothedVelocities;
	smoothedVelocities.resize(n);

	for (int i = 0; i < n; i++) {
        double weightSum = 0.0;
		Vector2D smoothedVelocity = Vector2D(0);
		if (particle_datas._densities[i]) {
			for (int n: particle_datas._neighbors[i]) {
				if (particle_datas._densities[n]) {
					double distance = dist(particle_datas._positions[i], particle_datas._positions[n]);
					double wj = pm / particle_datas._densities[n] * spikyKernel(distance);
					weightSum += wj;
					smoothedVelocity += particle_datas._velocities[n] * wj;
				}
			}
			double wi = pm / particle_datas._densities[i];
			weightSum += wi;
			smoothedVelocity += particle_datas._velocities[i] * wi;

			if (weightSum > 0.0) {
				smoothedVelocity = smoothedVelocity / weightSum;
			}

			//std::cout << smoothedVelocity.y << std::endl;
			smoothedVelocities[i] = smoothedVelocity;
		}
	}
	double factor = timeStepInSeconds * _pseudoViscosityCoefficient;
	factor = clamp(factor, 0.0, 1.0);

	for (int i = 0; i < n; i++) {
		if (particle_datas._densities[i]) {
			particle_datas._velocities[i] = lerp(particle_datas._velocities[i], smoothedVelocities[i], factor);
		}
	}
}

void SPHSolver2D::timeIntegration(double timeIntervalInSeconds) {
	size_t n = particle_datas.numberOfParticles();
	auto forces = particle_datas._forces;
	auto velocities = particle_datas._velocities;
	auto positions = particle_datas._positions;

	for (int i = 0; i < n; i++) {
		_newVelocities[i] = velocities[i] + (forces[i] / pm) * timeIntervalInSeconds;
		_newPositions[i] = positions[i] + _newVelocities[i] * timeIntervalInSeconds;
	}
}

void SPHSolver2D::resolveCollision(double timeIntervalInSeconds) {
	//resolve border Collision for the moment
	size_t n = particle_datas.numberOfParticles();
	
	for (int i = 0; i < n; i++) {
		if (_newPositions[i].y < floorPositionY) {
			//std::cout << i << " " << particle_datas._positions[i].y << std::endl;
			_newPositions[i].y = floorPositionY;
			_newVelocities[i].y = 0;
			//std::cout << particle_datas._positions[i].y << std::endl;
		}
		if (_newPositions[i].x < wallPositionXl) {
			_newPositions[i].x = wallPositionXl;
			_newVelocities[i].x = 0;
		}
		if (_newPositions[i].x > wallPositionXr) {
			_newPositions[i].x = wallPositionXr;
			_newVelocities[i].x = 0;
		}
		if (_newPositions[i].y > topPositionY) {
			_newPositions[i].y = topPositionY;
			_newVelocities[i].y = 0;
		}
	}
}

void SPHSolver2D::saveActualState() {
	std::string dir = "../render/values/";
	std::string name = "frame#";
	std::string num;
	size_t n = particle_datas.numberOfParticles();

	num = std::to_string(frameIndex);

	for (int i = 0; i < 4 - num.length(); ++i) {
		name += "0";
	}

	name += num;
	name += "2d_fluid_animation.txt";

	//std::cout << dir + name << std::endl;

	std::ofstream file(dir + name);

	file << n << std::endl;

	for (int i = 0; i < n; ++i) {
		file << particle_datas._positions[i].x << "," << particle_datas._positions[i].y << std::endl;
	}
}

void SPHSolver2D::runSimulation(double timeOfSimulation) {
	double timeToAdvance = 1 / (fps * 5);
	
	while (actual_time_seconds < timeOfSimulation) {
		advanceTimeStep(timeToAdvance);
		actual_time_seconds += timeToAdvance;
		advanceTimeStep(timeToAdvance);
		actual_time_seconds += timeToAdvance;
		advanceTimeStep(timeToAdvance);
		actual_time_seconds += timeToAdvance;
		advanceTimeStep(timeToAdvance);
		actual_time_seconds += timeToAdvance;
		advanceTimeStep(timeToAdvance);
		actual_time_seconds += timeToAdvance;
		saveActualState();
		frameIndex++;
		std::cout << actual_time_seconds << std::endl;
	}
}