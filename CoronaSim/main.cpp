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
#include <time.h>



int main(int argc, const char * argv[]) {
    
    // Set number of people, limited to 100x100 in spreadInfection and 10000 in shuffleGroup, can change in spreadInfection
    const int Length = 40;
    const int Width = 40;
    double contagionFactor = 0.15;     // How contagious it is, higher is more contagious
    int noSwitches = 50;               // How many pairs to switch
    const int noCycles = 100;          // Number of simulation cycles
    int incubationLifetime = 5;        // How long people are sick and contagious
    double deathRate = 0.3;            // How deadly it is, higher is deadlier
    
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
    std::cout << "Round\t\tH\t\t\tS\t\t\tH\t\t\tD\n";
    //std::cout << std::setw(6);
    for (int i = 0; i < noCycles; i++) {
        std::cout << std::setw(3) << i << "\t\t";
        for (int j = 0; j < 4; j++) {
            std::cout << std::setw(5) <<  censusHistory[i][j] << "\t\t";
            
        }
        
        std::cout << "\n";
    }
    
    // Print data to file for plotting in Matlab
    time_t curtime;
    time(&curtime);
    std::fstream outfile("coronaResults.txt", std::fstream::out);
    outfile << "Data File for Simulation Results" << std::endl;
    outfile << "Test Time: " << ctime(&curtime);
    outfile << "---Parameters---" << std::endl << Length*Width << "\n"  << noCycles << "\n"  << noSwitches << "\n"  << incubationLifetime << "\n"  << contagionFactor << "\n"  << deathRate << std::endl << std::endl;
    outfile << "Round Healthy Sick Healed Dead" << std::endl;
    for (int i = 0; i < noCycles; i++) {
        outfile << i << " ";
        for (int j = 0; j < 4; j++) {
            outfile << censusHistory[i][j] << " ";
        }
        outfile << "\n";
    }
    outfile.close();
    
    
    return 0;
}


