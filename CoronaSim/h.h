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
    // Has the person been infected and then healed
    
    
    // Unit time that the person has been infected
    int sicktime = 0;
    
    // Position of the person
    int position[2];
    
    // Which group is the person in
    int group;
    
    Person() {}
    
    
    bool infect() {
        // Set status of person to Sick
        bool x = 0;
        if (status == ".") {x = 1;}
        
        status = "+";
        
        return x;
    }
    
    void heal() {
        // Set status of person to Healed
        status = "Healed";
    }
    
    void Die() {
        //Set the status of person to Dead
        status = "Dead";
    }
    
    
    void changePosition(int x, int y) {
        // Set the position of the person to [x,y]
        position[0] = x;
        position[1] = y;
    }
    
};

// Display the current status of the group
void displayGroup (Person Group[], int Length, int Width, int flag) {
    // Display the current status of the group
    for (int i = 0; i < Length; i++) {
        for (int j = 0; j < Width; j++) {
            std::cout << Group[Length*i + j].status;
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    
    // Display the current Healthy and Sick Count
    int sickCount = 0;
    if (flag == 1) {
        for (int i = 0; i < Length; i++) {
            for (int j = 0; j < Width; j++) {
                if (Group[Length*i + j].status == "+") {sickCount++;}
            }
        }
        
    }
    std::cout << "Healthy: " << (Length*Width - sickCount) << "\n";
    std::cout << "Sick:    " << sickCount << "\n";
    
    
}



// Shuffle a random group of people
void shuffleGroup(int numberToShuffle, Person Group[], int Length, int Width) {
    
    //Initialization
    int switchVector[48][2];
    int poolSize = Length*Width;
    unsigned char is_used[1000] = {0}; // Flag
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
        
        tempStatus = Group[switchVector[i][0]].status;
        Group[switchVector[i][0]].status = Group[switchVector[i][1]].status;
        Group[switchVector[i][1]].status = tempStatus;
        
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
    
    // Display the status
    displayGroup(Group, Length, Width, 1);
}








#endif /* h_h */
