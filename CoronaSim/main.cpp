//
//  main.cpp
//  CoronaSim
//
//  Created by Lucas Nieuwenhout on 2020-03-22.
//  Copyright © 2020 Lucas Nieuwenhout. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "h.h"



int main(int argc, const char * argv[]) {
    
    // Set number of people, limited to 100x100 for now, can change in spreadInfection
    const int Length = 30;
    const int Width = 30;
    double contagionFactor = 0.25;     // How contagious it is, higher is more contagious
    int noSwitches = 10;               // How many pairs to switch
    const int noCycles = 100;          // Number of simulation cycles
    int incubationLifetime = 3;        // How long people are sick and contagious
    double deathRate = 0.2;            // How deadly it is, higher is deadlier
    
    // Create the 1D array of people
    Person Group[Length*Width];
    
    // Create the position vector
    int positionReference[Length][Width];

    // Assign Indices to the positionReference array
    for (int i = 0; i < Length; i++) {
        for (int j = 0; j < Width; j++) {
            // Set initial positions
            positionReference[i][j] = Length*i + j;
        }
    }
    
    // Create history of Healthy, Sick, Healed and Dead people
    int censusHistory[noCycles][4] = {0};
    // int censusHistory[4][noCycles] = {0};  //This could be more helpful for plotting
    
    
    // Infect a random person
    srand((unsigned int) time(NULL)); //time(NULL)
    int vector = rand() % (Length*Width);
    Group[vector].infect();
    
    // Display first infected person
    displayGroup(Group, Length, Width);
    census((int*) censusHistory[0], Group, Length, Width, 1);
    
    // Infect surrounding people
    for (int i = 0; i < noCycles; i++) {
        spreadInfection((int*)positionReference, Group, Length, Width, contagionFactor);
        
        displayGroup(Group, Length, Width);
        
        census((int*) censusHistory[i], Group, Length, Width, 1); // Set 0 for no print
        
        shuffleGroup(noSwitches, Group, Length, Width);
        
        cycleSickTimeline(Group, Length, Width, 1);
        testSickTimeline(Group, Length, Width, incubationLifetime, deathRate, 1);
    }
    
    //printCensusHistory((int *)censusHistory, Length, Width);
    std::cout << "Round\tH\t\tS\t\tH\t\tD\n";
    
    for (int i = 0; i < noCycles; i++) {
        std::cout << i << "\t\t";
        for (int j = 0; j < 4; j++) {
            std::cout << censusHistory[i][j] << "\t\t";
            
        }
        
        std::cout << "\n";
    }
    
    
    
    
    
    return 0;
}


