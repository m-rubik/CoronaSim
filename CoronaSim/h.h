//
//  h.h
//  CoronaSim
//
//  Created by Lucas Nieuwenhout on 2020-03-22.
//  Copyright © 2020 Lucas Nieuwenhout. All rights reserved.
//

#ifndef h_h
#define h_h

#include "VariadicTable.h"
#include <sstream>


struct person {
    int child_M = 0;
    int child_F = 0;
    int young_M = 0;
    int young_F = 0;
    int middle_M = 0;
    int middle_F = 0;
    int senior_M = 0;
    int senior_F = 0;
    int total = 0;
} population;

void prettyPrintPopulation(){
    std::cout << "Demographic information\n";
    // Construct an empty table
    VariadicTable<std::string, std::string, double> vt({"Age Range", "Gender", "Percentage (%)"});
    // Populate table with population information
    vt.addRow("0-17", "Male", float(population.child_M)/float(population.total) * 100);
    vt.addRow("0-17", "Female", float(population.child_F)/float(population.total) * 100);
    vt.addRow("18-44", "Male", float(population.young_M)/float(population.total) * 100);
    vt.addRow("18-44", "Female", float(population.young_F)/float(population.total) * 100);
    vt.addRow("45-64", "Male", float(population.middle_M)/float(population.total) * 100);
    vt.addRow("45-64", "Female", float(population.middle_F)/float(population.total) * 100);
    vt.addRow("65+", "Male", float(population.senior_M)/float(population.total) * 100);
    vt.addRow("65+", "Female", float(population.senior_F)/float(population.total) * 100);
    vt.print(std::cout);
    std::cout << std::endl;
}

// Utiliy function for generating a random double within a range fMin to fMax
double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

class Person {
private:
    int age, sickTime, position[2], group; 
    std::string status;
    bool immune, underlyingCondition;
    double deathRate;

public:
    Person(){ // Class constructor

        /*
        Looking at the 2019 census information for population age in Canada:
        https://www.statista.com/statistics/444858/canada-resident-population-by-gender-and-age-group/

        --- Statistics ---
        0-17 Male: 9.81%
        0-17 Female: 9.39%
        Total: 19.2 %

        18-44 Male: 18.41%
        18-44 Female: 17.8%
        Total: 36.21 %

        45-64 Male: 13.41%
        45-64 Female: 13.62%
        Total: 27.03 %

        65+ Male: 8.06%
        65+ Female: 9.5%
        Total: 17.56 %

        */
        double val = fRand(0, 100);
        if (0 <= val && val <= 9.81){
            age = (rand() % 17) + 0;
            std::string gender = "Male";
            population.child_M += 1;
            population.total += 1;
        }
        else if (9.81 < val && val <= 19.2){ // 9.81 + 9.39 = 19.2
            age = (rand() % 17) + 0;
            std::string gender = "Female";
            population.child_F += 1;
            population.total += 1;
        }
        else if (19.2 < val && val <= 37.61){ // 19.2 + 18.41 = 37.61
            age = (rand() % 44) + 18;
            std::string gender = "Male";
            population.young_M += 1;
            population.total += 1;
        }
        else if (37.61 < val && val <= 55.41){ // 37.61 + 17.8 = 55.41
            age = (rand() % 44) + 18;
            std::string gender = "Female";
            population.young_F += 1;
            population.total += 1;
        }
        else if (55.41 < val && val <= 68.82){ // 55.41 + 13.21 = 68.82
            age = (rand() % 64) + 45;
            std::string gender = "Male";
            population.middle_M += 1;
            population.total += 1;
        }
        else if (68.82 < val && val <= 82.44){ // 68.82 + 13.62 = 82.44
            age = (rand() % 64) + 45;
            std::string gender = "Female";
            population.middle_F += 1;
            population.total += 1;
        }
        else if (82.44 < val && val <= 90.5){ // 82.44 + 8.06 = 90.5
            age = (rand() % 100) + 65;
            std::string gender = "Male";
            population.senior_M += 1;
            population.total += 1;
        }
        else if (90.5 < val && val <= 100){ // 90.5 + 9.5 = 100
            age = (rand() % 100) + 65;
            std::string gender = "Female";
            population.senior_F += 1;
            population.total += 1;
        }

        /*
        Death rate is determined from the data provided from the NYC outbreak as of April 14th
        https://www.worldometers.info/coronavirus/coronavirus-age-sex-demographics/
        */
        if (underlyingCondition){
            if (0 <= age && age <= 17){
                deathRate = 0.0004;
            }
            else if (18 <= age && age <= 44){
                deathRate = 0.035;
            }
            else if (45 <= age && age <= 64){
                deathRate = 0.196;
            }
            else if (65 <= age && age <= 74){
                deathRate = 0.186;
            }
            else {
                deathRate = 0.335;
            }
        }
        else {
            if (0 <= age && age <= 17){
                deathRate = 0;
            }
            else if (18 <= age && age <= 44){
                deathRate = 0.01;
            }
            else if (45 <= age && age <= 64){
                deathRate = 0.035;
            }
            else if (65 <= age && age <= 74){
                deathRate = 0.06;
            }
            else {
                deathRate = 0.142;
            }
        }

        // Is the person infected
        status = ".";
        
        // Is the person immune
        immune = 0;
        
        // Unit time that the person has been infected
        sickTime = 0;
    }

    std::string getStatus() {
        return status;
    }

    void setStatus(std::string newStatus) {
        status = newStatus;
    }
    
    bool infect() {
        // Try to set status of person to Sick
        // If the person is healthy and not immune then infect and return that they were infected
        if (status == "." && immune == 0) {
            status = "+";
            return 1;
        }
        else {
            return 0;
        }
    }
    
    void unconditionalHeal(bool makeImmune) {
        // Set status of person to Healed unconditionally
        status = "-";
        if (makeImmune) {immune = 1;};
    }
    
    void Die() {
        //Set the status of person to Dead
        status = " ";
    }
    
    void changePosition(int x, int y) {
        // Set the position of the person to [x,y]
        position[0] = x;
        position[1] = y;
    }
    
    void cycle() {
        // Age the person and their sick period by a day if they are already sick
        if (status == "+") {
            sickTime++;
        }
    }
    
    void healTest(int incubationLifetime, bool makeImmune) {
        if (status != " "){ // Make sure the person is not already dead
            if ((sickTime > incubationLifetime) && (status == "+")){
                // Test if the person will be healed or die
                if ((((double) rand() / (RAND_MAX)) < (1 - deathRate))) {
                    status = "-"; // This person is healed
                    if (makeImmune) {immune = 1;}; // Conditionally make immune
                }
                else if ((sickTime > incubationLifetime) && (status == "+")) {
                    Die();
                }
            }
        }
    }
};

// Display the current status of the group
void displayGroup (Person Group[], int Length, int Width) {
    for (int i = 0; i < Length; i++) {
        for (int j = 0; j < Width; j++) {
            std::cout << Group[Length*i + j].getStatus();
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// Save the current census of the group to census array
void census(int * census, Person Group[], int Length, int Width, int printFlag) {
    
    census[0] = 0;
    census[1] = 0;
    census[2] = 0;
    census[3] = 0;
    
    for (int i = 0; i < Length; i++) {
        for (int j = 0; j < Width; j++) {
            if (Group[Length*i + j].getStatus() == ".") {census[0]++;}
            if (Group[Length*i + j].getStatus() == "+") {census[1]++;}
            if (Group[Length*i + j].getStatus() == "-") {census[2]++;}
            if (Group[Length*i + j].getStatus() == " ") {census[3]++;}
        }
    }
    
    if (printFlag) {
        std::cout << "Healthy: " << census[0] << "\n";
        std::cout << "Sick:    " << census[1] << "\n";
        std::cout << "Healed:  " << census[2] << "\n";
        std::cout << "Dead:    " << census[3] << "\n\n";
    }
}

// Shuffle a random group of people
void shuffleGroup(int numberToShuffle, Person *Group, int Length, int Width) {
    
    //Initialization
    int **switchVector = new int*[numberToShuffle];
    for (int i = 0; i < numberToShuffle; i++) {
        switchVector[i] = new int[2];
    }
    unsigned char *is_used = new unsigned char[Length*Width]; // Flag
    int poolSize = Length*Width;
    int in;
    int im = 0;
    
    // Independent Random number generator, formatting into pairs
    // https://stackoverflow.com/questions/1608181/unique-random-numbers-in-an-integer-array-in-the-c-programming-language
    for(in = poolSize - 2*numberToShuffle; in < poolSize && im < 2*numberToShuffle; ++in) {
        int r = rand() % (in + 1);
        
        if(is_used[r])
            r = in;
        
        // Format into pairs
        switchVector[im/2][im % 2] = r + 1;
        // std::cout << switchVector[im/2][im % 2] << "\n";

        im++;
        is_used[r] = 1;
        
    }
    
    // Print the people to switch
    //    for (int i = 0; i < numberToShuffle; i++) {
    //        for (int j = 0; j < 2; j++) {
    //            std::cout << switchVector[i][j] << " ";
    //        }
    //        std::cout << "\n";
    //    }
    
    // for each row in switchVector, temp = group(first index).status, group(first index).status = group(second index).status, then group(second).status = temp
    std::string tempStatus;
    
    for (int i = 0; i < numberToShuffle-1; i++) {
        if ((Group[switchVector[i][0]].getStatus() != " ") && (Group[switchVector[i][1]].getStatus() != " ")) {
            tempStatus = Group[switchVector[i][0]].getStatus();
            Group[switchVector[i][0]].setStatus(Group[switchVector[i][1]].getStatus());
            Group[switchVector[i][1]].setStatus(tempStatus);
        }
    }
    
    // Clean up allocated memory
    for(int i = 0; i < numberToShuffle; ++i) {
        delete [] switchVector[i];
    }
    delete [] switchVector;
    
    delete [] is_used;
    
}



// Spread the virus to the immediately adjacent people
void spreadInfection(int ** positionReference, Person Group[], int Length, int Width, double contagionFactor) {
    
    // Create array to keep track of who to make sick
    int **tempSick = new int*[Length];
    for (int i = 0; i < Length; ++i) {
        tempSick[i] = new int[Width];
    }
    for (int i = 0; i < Length; i++) {
        for (int j = 0; j < Width; j++) {
            tempSick[i][j] = 0;
        }
    }
    
    //tempSick [Length][Width] = {0};
    
    // Loop through people and find out who to make sick
    for (int i = 0; i < Length; i++) {
        
        for (int j = 0; j < Width; j++) {

            // If the person associated with array point is sick then infect around
            if (Group[(**positionReference + i*Length + j)].getStatus() == "+") {

                // Create the array of people to infect
                int target[4][2] = { {std::max(0, i - 1), j}, {std::min(Length - 1, i + 1), j}, {i, std::max(0, j - 1)}, {i, std::min(Width - 1, j + 1)} };
                
                // Assign 1 to the tempSick array that have to be infected
                for (int k = 0; k < 4; k++) {
                    //std::cout << target[k][0] << " " << target[k][1] << "\n"; // Visualize the points to change
                    if (((double) rand() / (RAND_MAX)) < contagionFactor) {
                        tempSick[target[k][0]][target[k][1]] = 1;
                    }
                    
                }
                
            }
            
        }
        
    }

    // Take the tempSick array and apply to Group
    for (int i = 0; i < Length; i++) {
        for (int j = 0; j < Width; j++) {
            // Make individual people sick
            if (tempSick[i][j] == 1) {
                Group[Length*i + j].infect();
            }
        }
    }
    
    // Display the status each cycle
    //displayGroup(Group, Length, Width, 1);
    
    // Cleanup memory
    for(int i = 0; i < Length; ++i) {
        delete [] tempSick[i];
    }
    delete [] tempSick;
}

// Print the history of the simulation throughout the epochs using the VariadicTable library
void prettyPrintCensusHistory(int noCycles, int **censusHistory) {
    std::cout << "Census history\n";

    // Construct an empty table
    VariadicTable<int, int, int, int, int> vt({"Epoch", "Healthy", "Sick", "Healed", "Dead"});

    // For each census history entry, add a new row to the table
    for (int i = 0; i < noCycles; i++) {
        vt.addRow(i, censusHistory[i][0], censusHistory[i][1], censusHistory[i][2], censusHistory[i][3]);
    }
    vt.print(std::cout);
}

// Print the history of the simulation
void printCensusHistory(int noCycles, int **censusHistory) {
    std::cout << "Round\t\tH\t\t\tS\t\t\tH\t\t\tD\n";
    for (int i = 0; i < noCycles; i++) {
        std::cout << std::setw(3) << i << "\t\t";
        for (int j = 0; j < 4; j++) {
            std::cout << std::setw(5) <<  censusHistory[i][j] << "\t\t";
        }
        std::cout << "\n";
    } 
}

void cycleSickTimeline(Person Group[], int Length, int Width, bool makeImmune) {
    // Cycle the Timeline for person
    for (int i = 0; i < Length*Width; i++) {
        Group[i].cycle();
    }
}

void testSickTimeline(Person Group[], int Length, int Width, int incubationLifetime, bool makeImmune) {
    // Test if people have been sick long enough to become healed
    for (int i = 0; i < Length*Width; i++) {
        Group[i].healTest(incubationLifetime, makeImmune);
    }
    
}

#endif /* h_h */
