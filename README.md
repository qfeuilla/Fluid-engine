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

