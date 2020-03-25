#include "../includes/sph.h"


void computeNeighbors() {
	std::map<int, std::deque<int>> buckets;
	std::map<int, std::map<int, std::deque<int>>> types;
	std::deque<int> group;
	int indice, type, part_index = 0;
	double x, y;

	// first step, fill buckets and underBuckets
	for (Particle p: particles) {
		indice = vecToIndex(p.x);
		x = std::round(std::fmod(p.x.x / H, 1) * 2);
		y = std::round(std::fmod(p.x.y / H, 1) * 2);
		type = static_cast<long int>(x + y * 3);
		//std::cout << x << " " << p.x.x / H << " " << p.x.x << " " << p.x.y << " " << y << " " << type << std::endl;
		buckets[indice].push_back(part_index);
		types[indice][type].push_back(part_index++);
	}

	neighbors.clear();
	neighbors.resize(particles.size());
	for (std::pair<int, std::deque<int>> cell: buckets) {
		for (std::pair<int, std::deque<int>> groups: types[cell.first]) {
			group = getCellGroup(groups.first, cell.first);
			for (int particle: groups.second) {
				for (int g: group) {
					for (int possible: buckets[g]) {
						auto pj = particles[possible];
						auto pi = particles[particle];
						Vector2D rij = pj.x - pi.x;
						if (rij.dot(rij) < HSQ) {
							neighbors[particle].push_back(possible);
						}
					}
				}
			}
		}
	}
	/*
	neighbors.clear();
	neighbors.resize(particles.size());
	for (int i = 0; i < particles.size(); i++) {
		auto pi = particles[i];
		for (int j = 0; j < particles.size(); j++) {
			auto pj = particles[j];
			Vector2D rij = pj.x - pi.x;
			if (rij.dot(rij) < HSQ) {
				neighbors[i].push_back(j);
			}
		}
	}*/
}

void InitSPH(void)
{
    double x,y;

	cout << "initializing particles" << endl;

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
	datas.close();
}

void Integrate(void)
{
	for(auto &p : particles)
	{
		// forward Euler integration
		p.v += p.f/p.rho* DT;
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
	for(int i = 0; i < particles.size(); i++)
	{
		auto& pi = particles[i];
		bool ok = false;
		pi.rho = 0.f;
		for(int j: neighbors[i])
		{
			auto& pj = particles[j];
			Vector2D rij = pj.x - pi.x;
			float r2 = rij.dot(rij);

			ok = true;
			// this computation is symmetric
			pi.rho += MASS*POLY6*pow(HSQ-r2, 3.f) ;
		}
		if (!ok) 
			pi.rho = 0.1;
		pi.p = GAS_CONST*(pi.rho - REST_DENS) * 1.5;
		//std::cout << pi.rho << std::endl;
	}
}


void ComputeForces(void)
{
	for(int i = 0; i < particles.size(); i++)
	{
		auto& pi = particles[i];
		Vector2D fpress(0.f, 0.f);
		Vector2D fvisc(0.f, 0.f);
		for(int j: neighbors[i])
		{
			if (i == j)
				continue ;
			auto& pj = particles[j];
			Vector2D rij = pj.x - pi.x;
			float r = sqrt(rij.dot(rij));
			// compute pressure force contribution
			fpress += rij.normalized()*MASS*(pi.p + pj.p)/(2.f * pj.rho) * SPIKY_GRAD*pow(H-r,2.f) * -1;
			// compute viscosity force contribution
			fvisc += (pj.v - pi.v)/pj.rho * VISC_LAP*(H-r)*MASS * VISC;
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
	computeNeighbors();
	ComputeDensityPressure();
 	ComputeForces();
 	Integrate();

    //std::cout << "ok" << std::endl;
    if (disp) {
        saveActualState();
        frameIndex++;
		if (!movingMax && VIEW_WIDTH - 10 > 600)
			VIEW_WIDTH -= 30;
		else if (!movingMax)
			movingMax = true;
		else if (VIEW_WIDTH + 10 < 1000)
			VIEW_WIDTH += 30;
		else
			movingMax = false;
		std::cout << actualTime << std::endl;
    }
    actualTime += DT;
}

int main() {
    float fps = 60;
    float simTime = 10;
    float stepDuration = 1 / fps;
    bool disp;

    std::cout << "start" << std::endl;

    InitSPH();

    while (actualTime < simTime) {
        disp = fmod(actualTime, stepDuration) <= DT ? 1 : 0;
        Update(disp);
    }
}