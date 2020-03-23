//
//  main.cpp
//  CoronaSim
//
//  Created by Lucas Nieuwenhout on 2020-03-22.
//  Copyright © 2020 Lucas Nieuwenhout. All rights reserved.
//

#include <iostream>
#include "h.h"



int main(int argc, const char * argv[]) {
    
    // Set number of people
    int Length = 5;
    int Width = 5;
    
    
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
    
    
    // Infect a random person
    Group[rand() % (Length*Width)].infect();
    
    
    return 0;
}





