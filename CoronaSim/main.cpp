//
//  main.cpp
//  CoronaSim
//
//  Created by Lucas Nieuwenhout on 2020-03-22.
//  Copyright © 2020 Lucas Nieuwenhout. All rights reserved.
//

#include <iostream>
#include <vector>
#include "h.h"



int main(int argc, const char * argv[]) {
    
    // Set number of people, limited to 100x100 for now, can change in spreadInfection
    const int Length = 30;
    const int Width = 30;
    double contagionFactor = 0.25;
    int noSwitches = 4;
    const int noCycles = 40;
    
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
        
        census((int*) censusHistory[i], Group, Length, Width, 1);
        
        
        // Test print of censusHistory
        std::cout << censusHistory[i][0] << " " << censusHistory[i][1] << " " << censusHistory[i][2] << " " << censusHistory[i][3] << "\n";
        
        shuffleGroup(noSwitches, Group, Length, Width);
    }
    
    
    
    
    return 0;
}


