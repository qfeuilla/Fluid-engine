 ## Algorithm

```python
class Particle;  # -> attribute position, and all constants like mass
class vec3;
int time_of_simulation;
int actual_time = 0;
Particle particles;
Particle neighbors; # list of particle for each particles
rho; # list of density around each particle
alpha; # list of constant alpha for each particles
forces; # list of forces for each particles
actual_veloc; # list of velocitie of each particle
prev_veloc = [vec(0) for _ in range(len(particles))];

def runSimulation:
	for i, p in enumerate(particles):
		neighbors[i] = findNeighbors(p, particles) # using compact hashing (to research)
	for i, p in enumerate(particles):
		rho[i] = findDensity(neighbors[i], p)
		alpha[i] = findAlpha(neighbors[i], p)
	while actual_time < time_simulation:
		for i, p in enumerate(particles):
			forces[i] = calculateExtForces(p)  #  gravity,  surface  tension  and  viscosity
        ∆t = CFL condition # i don't cleary understand how to compute and the meaning of this, adding to gloassary
		for i, p in enumerate(particles):
			actual_veloc[i] = prev_veloc[i] +  ∆t * (forces[i] / m[i])
		correctDensityError(alpha, actual_veloc)
		for i, p in enumerate(particles):
			p.pos = p.pos + ∆t * actual_veloc[i]
		for i, p in enumerate(particles):
			neighbors[i] = findNeighbors(p, particles)
		for i, p in enumerate(particles):
			rho[i] = findDensity(neighbors[i], p)
			alpha[i] = findAlpha(neighbors[i], p)
		correctDivergenceError(alpha, actual_veloc)
		for i, p in enumerate(particles):
			prev_veloc = actual_veloc
		actual_time = actual_time + ∆t
```
## alpha[i] = 
![alt text](https://raw.githubusercontent.com/qfeuilla/Fluid-engine/master/ai.PNG)                                 
I don't know what ∇ mean adding to Gloassary.

## Wij :
![alt text](https://raw.githubusercontent.com/qfeuilla/Fluid-engine/master/Wij.PNG)
Gaussian like kernel function with the support radius h (I don't know what it is, adding to Gloassary)

