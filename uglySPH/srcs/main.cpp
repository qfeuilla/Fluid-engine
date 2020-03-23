#include "../includes/sph.h"

void InitSPH(void)
{
    /*
    double x,y;

	std::ifstream datas("../scene/scene1.txt");
	std::string val;

	while (!datas.eof()) {
		for (int i = 0; i < 3; i++) {
			std::getline(datas, val, ' ');
			if (datas.eof())
				break;
			switch (i) {
				case 0:
					x = std::stof(val);
				case 1:
					y = std::stof(val);
			}
		}
		std::getline(datas, val);
        
		particles.push_back(Particle(x, y));
	}
	datas.close();*/
	cout << "initializing dam break with " << DAM_PARTICLES << " particles" << endl;
	for(float y = EPS; y < VIEW_HEIGHT-EPS*2.f; y += H)
		for(float x = VIEW_WIDTH/4; x <= VIEW_WIDTH/2; x += H)
			if(particles.size() < DAM_PARTICLES)
			{
				float jitter = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				particles.push_back(Particle(x+jitter,y));
			}
}

void Integrate(void)
{
	for(auto &p : particles)
	{
		// forward Euler integration
		p.v += p.f/p.rho * DT;
		p.x += p.v * DT;

		// enforce boundary conditions
		if(p.x.x -EPS < 0.0f)
		{
			p.v.x *= BOUND_DAMPING;
			p.x.x = EPS;
		}
		if(p.x.x+EPS > VIEW_WIDTH) 
		{
			p.v.x *= BOUND_DAMPING;
			p.x.x = VIEW_WIDTH-EPS;
		}
		if(p.x.y-EPS < 0.0f)
		{
			p.v.y *= BOUND_DAMPING;
			p.x.y = EPS;
		}
		if(p.x.y+EPS > VIEW_HEIGHT)
		{
			p.v.y *= BOUND_DAMPING;
			p.x.y = VIEW_HEIGHT-EPS;
		}
	}
}


void ComputeDensityPressure(void)
{
	for(auto &pi : particles)
	{
		pi.rho = 0.f;
		for(auto &pj : particles)
		{
			Vector2D rij = pj.x - pi.x;
			float r2 = rij.dot(rij);

			if(r2 < HSQ)
			{
				// this computation is symmetric
				pi.rho += MASS*POLY6*pow(HSQ-r2, 3.f);
			}
		}
		pi.p = GAS_CONST*(pi.rho - REST_DENS);
	}
}


void ComputeForces(void)
{
	for(auto &pi : particles)
	{
		Vector2D fpress(0.f, 0.f);
		Vector2D fvisc(0.f, 0.f);
		for(auto &pj : particles)
		{
			if(&pi == &pj)
				continue;

			Vector2D rij = pj.x - pi.x;
			float r = sqrt(rij.dot(rij));

			if(r < H)
			{
				// compute pressure force contribution
				fpress += rij.normalized()*MASS*(pi.p + pj.p)/(2.f * pj.rho) * SPIKY_GRAD*pow(H-r,2.f) * -1;
				// compute viscosity force contribution
				fvisc += (pj.v - pi.v)/pj.rho * VISC_LAP*(H-r)*MASS * VISC;
			}
		}
		Vector2D fgrav = G * pi.rho;
		pi.f = fpress + fvisc + fgrav;
	}
}


void saveActualState() {
	std::string dir = "../render/values/";
	std::string name = "frame#";
	std::string num;
	size_t n = particles.size();

	num = std::to_string(frameIndex);

	for (int i = 0; i < 4 - num.length(); ++i) {
		name += "0";
	}

	name += num;
	name += "_2d_fluid_animation.txt";

	//std::cout << dir + name << std::endl;

	std::ofstream file(dir + name);

	file << n << std::endl;

	for (int i = 0; i < n; ++i) {
		file << particles[i].x.x << "," << particles[i].x.y << std::endl;
	}
}

void Update(bool disp)
{ 
	ComputeDensityPressure();
 	ComputeForces();
 	Integrate();

    //std::cout << "ok" << std::endl;
    if (disp) {
        saveActualState();
        frameIndex++;
        std::cout << actualTime << std::endl;
    }
    actualTime += DT;
}

int main() {
    float fps = 60;
    float simTime = 3;
    float stepDuration = 1 / fps;
    bool disp;

    std::cout << "start" << std::endl;

    InitSPH();

    while (actualTime < simTime) {
        disp = fmod(actualTime, stepDuration) <= DT ? 1 : 0;
        Update(disp);
    }
}