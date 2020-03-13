# Fluid-engine

A fluide engine writting in C++ using the book Fluid Engine Development
https://fluidenginedevelopment.org/

# Journal

### 29/02/2020 :

Before continuing to the core of the engine I have to go deeper throught the Documentation and the existing process to render a fluid. Due to a lack of mathematical and physical knowing, the book don't suit my actual needing. I have to go deeper in the research about physical based rendering process.

### 01/03/2020 :

I have found a realy exciting ongoing project that i can use to render my fluid : https://rgl.epfl.ch/publications/NimierDavidVicini2019Mitsuba2 Sadly it is not avaible yet, but I think it's letting me time to research about how to construct my engine

After seeing this page

https://www.researchgate.net/figure/Visual-comparison-of-SPH-left-and-PIC-FLIP-right-flow-simulations-the-impact-of_fig1_321111273

I think I will implement a particule based simulation (SPH). The main reason is that if I want to reuse my fluid engine to create for example a complet rendring engine (for example to interact with object like in this video https://www.youtube.com/watch?v=OSMUzIhP14c) it will be much more easier to use than a grid base simulation.

But i found that there is a lot of different way to do particule based fluid simulation so now i have to found them all and compare them to choose the better one compared to my needings

### 02/03/2020

I have found this repo that is realy intresting
https://github.com/InteractiveComputerGraphics/SPlisHSPlasH

As far as this repo say, there is 5 diferent SPH solver : WCSPH, PCISPH, PBF, IISPH, DFSPH

- #### PBF (position base fluids) : 
	
	Pros : 
		
	-	design for realtime
	
	Cons :
		
	-	require  a  notion  of  incompressibility and to do so it uses a iterative aproch. "Iterative process suffers from low convergence rates when simulating large volumes with a large number of particles. In these cases, the required solver iterations have to be increased significantly, implying a huge impact on the runtime of the overall simulation." https://arxiv.org/ftp/arxiv/papers/1608/1608.04721.
	
	
I also learn that there is a branch in fluid simulation that simulate the interaction between solid and fluid object (dissolution for example) and it's called FSI (maybe later implementation)

- #### WCSPH (weakly compressible SPH) : 
	stiff equation of state
	
	Pros : 
		
	-	low cost / step
	
	Cons :
		
	-	only small time steps
	
- #### PCISPH (weakly compressible SPH) : 
	prediction-correction scheme
	
	Pros : 
		
	-	low cost / steps
	-	Handle large time steps
	-	77 time faster than WCSPH with multithread according to this paper https://people.inf.ethz.ch/~sobarbar/papers/Sol09b/Sol09b.pdf
	
- #### DFSPH (divergence free SPH) : 
	It is a prediction model a bit like PCISPH but that take into acount the numerical error.
	
	Pros : 
		
	-	much more faster than other SPH for "Big" time step according to the end of this paper https://animation.rwth-aachen.de/media/papers/2015-SCA-DFSPH.pdf

I have found a paper that seems interesting and i wait for the aproval of my account
 https://www.researchgate.net/publication/318294651_Comparison_between_Incompressible_SPH_Solvers

So after this searching process I think that for the moment i will use DFSPH solver that seem to suit my needing : fast simulator with low artifacts. the only negative point I see is that the fluid will be incompressible

### 03/03/2020

After reading some paper about the SPH I have seen a lot of terms that I don't understand so I will list theme and try to understand theme in a glossary that can be found in Glossary.md

### 06/03/2020

I am starting to understand the main lines of the solver now it is time for me to trying to find a good algoritm. My main goal is to have an algorithme that is the most optimized I can. I will focus on the display later. see DFSPH_algoritm.md

### 08/03/2020

Now that i have an aproximal algorithm I will build step by step. So from now I will focus on the neighbour searching.
From what I have read, it is the longest thing in the simulation so, I will try to do the state of the art algorithm, and to understand it.

### 11/03/2020

After a lot of research, I have build a custom algorithm. The idea is that I group the particle into cell and I test the distance between each particules in each cell to group theme by neighbour. Furthermore, if particle is near a edge, I put in one of the case and then i group the cells in function of the case .


### 13/03/2020

So I have finished to implement my temporary algorithm for neighbor search. it takes 10 seconds for 500 000 particules without GPU and multithreading. I will try to decrease it to 10 ms for each time step, but i need to learn to use CUDA for that so I will focus on optimization later on.
