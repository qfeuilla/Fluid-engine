#ifndef SPH_H
#define SPH_H

#include "../classes/particles_stuff.hpp"
#include <algorithm>

#define PI 355/113
#define VSOUND 1482

static double xm = 200, ym = 200; // max pos
static double s = 5; // size of the edge of the square
static int xms = xm / s, yms = ym / s; // max pos in grid size index
static double doi =  1; // distance of interaction
static double h = 1.9; // len for kernel

Vector2D	lerp(Vector2D a, Vector2D b, double t);
double	lerp(double a, double b, double t);
double	clamp(double a, double b, double c);

class SPHSolver2D {
public:
	ParticleSystemData2	particle_datas;
	double				actual_time_seconds;
	double				fps;
	double				_dragCoefficient = 1e-4;
	Vector2D			wind_dir = Vector2D(0.0, 0.0);
	Vector2D			_gravity = Vector2D(0.0, -9.8);
	ParticleSystemData2::VectorArray _newPositions;
	ParticleSystemData2::VectorArray _newVelocities;
	int					frameIndex;
	double				floorPositionY = 0;
	double				topPositionY = 140;
	double				wallPositionXl = 0;
	double				wallPositionXr = 140;
	double				eosExponent; 
	double              restitusionCoefficient = 0.2;
	double				negativePressureScale;
	double				viscosityCoefficient;
	double				_pseudoViscosityCoefficient = 10.0;

	SPHSolver2D() {}
	SPHSolver2D(const ParticleSystemData2 & datas, double fps = 60, double eosExponent = 7, 
				double negativePressureScale = -0.3 , double viscosityCoefficient = 0.1) : negativePressureScale(negativePressureScale), 
													eosExponent(eosExponent), particle_datas(datas), 
													fps(fps), 
													frameIndex(0), 
													actual_time_seconds(0),
													viscosityCoefficient(viscosityCoefficient) {}

	void accumulateForces(double advance_time);
	void accumulateExternalForces(double advance_time);
	void accumulateNonPressureForces(double timeIntervalInSeconds);
	void accumulatePressureForce(double timeIntervalInSeconds);
	void accumulatePressureForce();
	void computePressure();
	double computePressureFromEos(double density,double targetDensity,double eosScale,double eosExponent, double negativePressureScale);
	void accumulateViscosityForce();
	void computePseudoViscosity(double timeStepInSeconds);

	void advanceTimeStep(double advance_time);
	void beginAdvanceTimeStep();
	void endAdvanceTimeStep(double timeStepInSeconds);
	void onBeginAdvanceTimeStep();
	void onEndAdvanceTimeStep(double timeStepInSeconds);

	void timeIntegration(double timeIntervalInSeconds);

	void resolveCollision(double timeIntervalInSeconds);

	void saveActualState();

	void runSimulation(double timeOfSimulation);

};

#endif