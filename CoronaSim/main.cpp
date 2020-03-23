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
    
    // Set number of people
    const int Length = 5;
    const int Width = 5;
    srand(5); //time(NULL)
    
    // Create the 1D array of people
    Person Group[Length*Width];
    
    // Create the position vector and assign their indexes
    int positionReference[Length][Width];
    
    
    
    
    

    for (int i = 0; i < Length; i++) {
        for (int j = 0; j < Width; j++) {
            // Set initial positions
            positionReference[i][j] = 5*i + j;
        }
    }
    
//    // Test the indices of the positionReference
//    for (int i = 0; i < Length; i++) {
//        for (int j = 0; j < Width; j++) {
//            // Set initial positions
//            std::cout << positionReference[i][j] << "\n";
//        }
//    }
    
    
    
    int test1 = 0;
    test1 = spreadInfection((int*)positionReference, Group, Length, Width);
    std::cout << test1 << "\n";
    std::cout << positionReference[1][3] << "\n";
    
    
    // Infect a random person
    int vector = rand() % (Length*Width);
    //std::cout << vector << "\n";
    vector = 24;
    Group[vector].infect();

    

    for (int i = 0; i < Length; i++) {
        std::cout << Group[5*i].status << Group[5*i + 1].status << Group[5*i + 2].status << Group[5*i + 3].status << Group[5*i + 4].status << "\n";
    }
    std::cout << "\n";
    
    
    
    //Create temporary array to keep track of who to make sick
    int tempSick [Length][Width] = {0};
    
    // Loop through people and find out who to make sick
    for (int i = 0; i < Length; i++) {
        
        for (int j = 0; j < Width; j++) {
            
            // If the person associated with array point is sick then infect around
            if (Group[positionReference[i][j]].status == "S") {
                
                // Create the array of people to infect
                int target[4][2] = { {std::max(0, i - 1), j}, {std::min(Length, i + 1), j}, {i, std::max(0, j - 1)}, {i, std::min(Width, j + 1)} };
                
                // Assign 1 to the tempSick array that have to be infected
                for (int k = 0; k < 4; k++) {
                    //std::cout << target[k][0] << " " << target[k][1] << "\n"; // Visualize the points to change
                    tempSick[target[k][0]][target[k][1]] = 1;
                }
                
            }
            
        }
        
    }
    
    
    
//    // Visualize tempSick Matrix
//    for (int i = 0; i < Length; i++) {
//        std::cout << tempSick[i][0] << tempSick[i][1] << tempSick[i][2] << tempSick[i][3] << tempSick[i][4] << "\n";
//    }
    
    // Apply the tempSick array to the group
    for (int i = 0; i < Length; i++) {
        for (int j = 0; j < Width; j++) {
            // Make individual people sick
            if (tempSick[i][j] == 1) {
                Group[5*i + j].infect();
            }
        }
    }
    
    // Visualize the actual sick people
    for (int i = 0; i < Length; i++) {
        std::cout << Group[5*i].status << Group[5*i + 1].status << Group[5*i + 2].status << Group[5*i + 3].status << Group[5*i + 4].status << "\n";
    }
    
    
    return 0;
}


// Create temp array
// if person is sick then mark i,j as 1 on temp array
// Generate the proximity array to infect
// Apply the proximity array to the temp array
// Continue
// At end of whole loop, cycle through temp array and make i,j people sick


// Why are all of these random people getting sick????



