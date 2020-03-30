//
//  h.h
//  CoronaSim
//
//  Created by Lucas Nieuwenhout on 2020-03-22.
//  Copyright © 2020 Lucas Nieuwenhout. All rights reserved.
//

#ifndef h_h
#define h_h

class Person {
public:
    // Is the person infected
    std::string status = ".";
    
    // Is the person immune
    bool immune = 0;
    
    // Unit time that the person has been infected
    int sickTime = 0;
    
    // Position of the person, this is not currently being used
    int position[2];
    
    // Which group is the person in
    int group;
    
    
    
    bool infect() {
        // Set status of person to Sick
        bool x = 0;
        // If the person is healthy and not immune then infect and return that they were infected
        if (status == "." && immune == 0) {
            x = 1;
            status = "+";
        }
        
        return x;
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
    
    
    void healTest(int incubationLifetime, double deathRate, bool makeImmune) {
        // Check if the person has gone through the whole incubation period
        if ((sickTime > incubationLifetime) && (status == "+") && (((double) rand() / (RAND_MAX)) < (1 - deathRate))) {
            status = "-";
            if (makeImmune) {immune = 1;}; // Conditionally make immune
        } else if ((sickTime > incubationLifetime) && (status == "+")) {
            status = " ";
        }
        
    }
    
    
};

// Display the current status of the group
void displayGroup (Person Group[], int Length, int Width) {
    // Display the current status of the group
    for (int i = 0; i < Length; i++) {
        for (int j = 0; j < Width; j++) {
            std::cout << Group[Length*i + j].status;
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
            if (Group[Length*i + j].status == ".") {census[0]++;}
            if (Group[Length*i + j].status == "+") {census[1]++;}
            if (Group[Length*i + j].status == "-") {census[2]++;}
            if (Group[Length*i + j].status == " ") {census[3]++;}
        }
    }
    
    if (printFlag == 1) {
        std::cout << "Healthy: " << census[0] << "\n";
        std::cout << "Sick:    " << census[1] << "\n";
        std::cout << "Healed:  " << census[2] << "\n";
        std::cout << "Dead:    " << census[3] << "\n\n";
    }
    
}



// Shuffle a random group of people
void shuffleGroup(int numberToShuffle, Person Group[], int Length, int Width) {
    
    //Initialization
    int switchVector[100][2];
    int poolSize = Length*Width;
    unsigned char is_used[10001] = {0}; // Flag
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
        //std::cout << switchVector[im/2][im % 2] << "\n";

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
    
    for (int i = 0; i < numberToShuffle; i++) {
        
        if ((Group[switchVector[i][0]].status != " ") && (Group[switchVector[i][1]].status != " ")) {
            tempStatus = Group[switchVector[i][0]].status;
            Group[switchVector[i][0]].status = Group[switchVector[i][1]].status;
            Group[switchVector[i][1]].status = tempStatus;
        }
    }
}



// Spread the virus to the immediately adjacent people
void spreadInfection(int * positionReference, Person Group[], int Length, int Width, double contagionFactor) {
    
    // Create array to keep track of who to make sick
    int tempSick [100][100] = {0};
    
    // Loop through people and find out who to make sick
    for (int i = 0; i < Length; i++) {
        
        for (int j = 0; j < Width; j++) {
            
            // If the person associated with array point is sick then infect around
            if (Group[*(positionReference + i*Length + j)].status == "+") {
                
                // Create the array of people to infect
                int target[4][2] = { {std::max(0, i - 1), j}, {std::min(Length, i + 1), j}, {i, std::max(0, j - 1)}, {i, std::min(Width, j + 1)} };
                
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
}


// Print the History of the simulations
// This does not work
void printCensusHistory(int * censusHistory, int Length, int Width) {
    
    std::cout << "Round\tH\tS\tD\tH\n";
    
    for (int i = 0; i < Length*Width; i++) {
        for (int j = 0; j < 1; j++) {
            std::cout << censusHistory[i];
            
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

void testSickTimeline(Person Group[], int Length, int Width, int incubationLifetime, double deathRate, bool makeImmune) {
    // Test if people have been long enough to become healed
    for (int i = 0; i < Length*Width; i++) {
        Group[i].healTest(incubationLifetime, deathRate, makeImmune);
    }
    
}




#endif /* h_h */
