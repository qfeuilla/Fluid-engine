 ## Algorithm

```python
class Particle;
int time_of_simulation;
Particle particles;
Particle neighbors; # list of particle for each particles
rho; # list of density around each particle
alpha; # list of constant alpha for each particles
def runSimulation:
  for p in particles:
    neighbors = findNeighbors(particles) # using compact hashing (to research)
  for i, p in enumerate(particles):
    rho = findDensity(neighbors[i], p)
    alpha = findAlpha(rho
    
```
## alpha[i] = 
![alt text](https://raw.githubusercontent.com/qfeuilla/Fluid-engine/master/ai.PNG)                                 
I don't know what ∇ mean adding to Gloassary.

## Wij :
![alt text](https://raw.githubusercontent.com/qfeuilla/Fluid-engine/master/Wij.PNG)
Gaussian like kernel function with the support radius h (I don't know what it adding to Gloassary)
