# CoronaSim

This is a short program to simulate the spread of an illness through a community.

Length, Width - Insert the dimensions of the simulation population, limit is 100x100
contagionFactor - This is how contagious the virus is, higher is more contagious, range: [0,1]
noSwitches - This is the number of pairs in the population that will be switched each round, limit is 50, over that and it just crashes
noCycles - This is the number of simulation cycles, no real limit, just a higher chance of crashing, < 100 is usually good
incubationLifetime - How many cycles people are sick and contagious before they either die or get better and become immune
deathRate - How deadly the virus is, higher is deadlier, range: [0,1]
