//
//  main.cpp
//  CoronaSim
//
//  Created by Lucas Nieuwenhout on 2020-03-22.
//  Copyright © 2020 Lucas Nieuwenhout. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <string>
#include <string.h>
#include "h.h"

// Declare all defaults. These will get overriden by the command line arguments
int Length = 40;                  // Population grid length
int Width = 40;                   // Population grid width
int noCycles = 60;                // Number of simulation cycles
double contagionFactor = 0.4;     // How contagious it is, higher is more contagious
int noSwitches = 10;              // How many pairs to switch
int incubationLifetime = 5;       // How long people are sick and contagious
bool visualize = false;           // Display a visualization of the simulation
bool printCensus = false;         // Display census updates throughout simulation


static void show_usage(std::string name) {
    std::cerr << "Usage:\n"
              << "\t-h,--help\t\tShow this help message\n"
              << "\t-l,--length\tPopulation grid length\n"
              << "\t-w,--width\tPopulation grid width\n"
              << "\t-e,--noCycles\tNumber of time cycles (epochs) to run\n"
              << "\t-c,--contagionFactor\tHow contagious it is, higher is more contagious\n"
              << "\t-s,--noSwitches\tHow many pairs to switch\n"
              << "\t-i,--incubationLifetime\tHow long people are sick and contagious\n"
              << "\t-v,--visualize\tDisplay a visualization of the simulation\n"
              << "\t-p,--printCensus\tDisplay census updates throughout simulation\n"
              << std::endl;
}

static int runSimulation() {
    std::cout << "Running with parameters:\n"
              << "length: " << Length << std::endl
              << "width: " << Width << std::endl
              << "number of cycles: " << noCycles << std::endl
              << "number of switches: " << noSwitches << std::endl
              << "contagion factor: " << contagionFactor << std::endl
              << "incubation lifetime: " << incubationLifetime << std::endl << "\n";

    // Dynamically create the 1D array of people
    Person *Group{new Person[Length*Width]{} };
    
    // Dynamically create the position vector
    int **positionReference = new int*[Length];
    for(int i = 0; i < Length; ++i) {
        positionReference[i] = new int[Width];
    }
    // Assign Indices to the positionReference array
    for (int i = 0; i < Length; i++) {
        for (int j = 0; j < Width; j++) {
            // Set initial positions
            positionReference[i][j] = Length*i + j;
        }
    }
    
    // Create history of Healthy, Sick, Healed and Dead people
    int **censusHistory = new int*[noCycles];
    for(int i = 0; i < noCycles; ++i) {
        censusHistory[i] = new int[4];
    }
    // Assign Indices to the censusHistory array
    for (int i = 0; i < noCycles; i++) {
        for (int j = 0; j < 4; j++) {
            // Set initial positions
            censusHistory[i][j] = noCycles*i + j;
        }
    }
    
    // Infect a random person
    srand((unsigned int) time(NULL)); //time(NULL)
    int vector = rand() % (Length*Width);
    Group[vector].infect();
    
    // Display first infected person
    if (visualize) {
        displayGroup(Group, Length, Width);
    }
    census((int*) censusHistory[0], Group, Length, Width, printCensus);
    
    // Infect surrounding people
    for (int i = 0; i < noCycles; i++) {
        std::cout << "Running epoch " << i << "..." << std::endl;
        spreadInfection(positionReference, Group, Length, Width, contagionFactor);
        
        if (visualize) {
            displayGroup(Group, Length, Width);
        }
        
        census((int*) censusHistory[i], Group, Length, Width, printCensus);
        shuffleGroup(noSwitches, Group, Length, Width);
        cycleSickTimeline(Group, Length, Width, 1);
        testSickTimeline(Group, Length, Width, incubationLifetime, 1);
    }
    std::cout << "All epochs finished. Simulation complete.\n\n";

    prettyPrintCensusHistory(noCycles, censusHistory);
    // printCensusHistory(noCycles, censusHistory); // NOTE: Use if you don't want to add the VariadicTable library
    
    // Print data to file for plotting in Matlab
    time_t curtime;
    time(&curtime);
    std::fstream outfile("coronaResults.txt", std::fstream::out);
    outfile << "Data File for Simulation Results" << std::endl;
    outfile << "Test Time: " << ctime(&curtime);
    outfile << "---Parameters---" << std::endl << Length*Width << "\n"  << noCycles << "\n"  << noSwitches << "\n"  << incubationLifetime << "\n"  << contagionFactor << std::endl << std::endl;
    outfile << "Round Healthy Sick Healed Dead" << std::endl;
    for (int i = 0; i < noCycles; i++) {
        outfile << i << " ";
        for (int j = 0; j < 4; j++) {
            outfile << censusHistory[i][j] << " ";
        }
        outfile << "\n";
    }
    outfile.close();

    // Cleanup memory allocated for arrays
    delete[] Group;

    for(int i = 0; i < Length; ++i) {
        delete [] positionReference[i];
    }
    delete [] positionReference;

    for(int i = 0; i < noCycles; ++i) {
        delete [] censusHistory[i];
    }
    delete [] censusHistory;
    
    return 0;
}

int main(int argc, const char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help")) {
            show_usage(argv[0]);
            return 0;
        }
        else if ((arg == "-l") || (arg == "--length")) {
            if (i + 1 < argc) {
                Length = std::stoi(argv[++i]);
            } else {
                  std::cerr << "--length option requires one argument." << std::endl;
                return 1;
            }  
        }
        else if ((arg == "-w") || (arg == "--width")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                Width = std::stoi(argv[++i]);   
            } else {
                  std::cerr << "--width option requires one argument." << std::endl;
                return 1;
            }  
        }
        else if ((arg == "-e") || (arg == "--noCycles")) {
            if (i + 1 < argc) {
                noCycles = std::stoi(argv[++i]);
            } else {
                  std::cerr << "--noCycles option requires one argument." << std::endl;
                return 1;
            }  
        } 
        else if ((arg == "-c") || (arg == "--contagionFactor")) {
            if (i + 1 < argc) {
                contagionFactor = atof(argv[++i]);
            } else {
                  std::cerr << "--contagionFactor option requires one argument." << std::endl;
                return 1;
            }  
        }
        else if ((arg == "-s") || (arg == "--noSwitches")) {
            if (i + 1 < argc) {
                noSwitches = std::stoi(argv[++i]);
            } else {
                  std::cerr << "--noSwitches option requires one argument." << std::endl;
                return 1;
            }  
        }
        else if ((arg == "-i") || (arg == "--incubationLifetime")) {
            if (i + 1 < argc) {
                incubationLifetime = std::stoi(argv[++i]);
            } else {
                  std::cerr << "--incubationLifetime option requires one argument." << std::endl;
                return 1;
            }  
        }
        else if ((arg == "-v") || (arg == "--visualize")) {
            visualize = true;
        }
        else if ((arg == "-p") || (arg == "--printCensus")) {
            printCensus = true;
        }
        else {
            std::cerr << "Unrecognized argument " << arg << std::endl;
            show_usage(argv[0]);
            return 0;
        }
    }

    int result = runSimulation();

    return result;
}

