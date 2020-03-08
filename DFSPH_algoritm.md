## Algorithm

```python
class Particle;
int time_of_simulation;
Particle particles;
Particle neighbors; # list of particle for each particles
rho; # list of density around each particle

def runSimulation:
  for p in particles:
    neighbors = findNeighbors(particles) # using compact hashing (to research)
  for i, p in enumerate(particles):
    rho = findDensity(neighbors[i], p)
    
```
## αi = 
![alt text](https://raw.githubusercontent.com/qfeuilla/Fluid-engine/master/ai.PNG)

## Wij :
![alt text](https://raw.githubusercontent.com/qfeuilla/Fluid-engine/master/Wij.PNG)
