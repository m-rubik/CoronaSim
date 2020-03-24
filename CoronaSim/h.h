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
    std::string status = "H";
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
        if (status == "H") {x = 1;}
        
        status = "S";
        
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



// Shuffle a random group of people
void shuffle(int nunmberToShuffle) {
    // Shuffle the number of people inputted, the number inputted is the number of pairs
    // Have to make sure that all vectors are unique
    
    
}


void infection(int * tempSick, Person Group[], int Length, int Width) {
    // Take tempSick, Group[], Length and Width and make the people in tempSick sick
    
    for (int i = 0; i < Length; i++) {
        std::cout << *(tempSick + Length*i + 0) << *(tempSick + Length*i + 1) << *(tempSick + Length*i + 2) << *(tempSick + Length*i + 3) << *(tempSick + Length*i + 4) << "\n";
    }
    std::cout << "\n\n";
    
    for (int i = 0; i < Length; i++) {
        for (int j = 0; j < Width; j++) {
            // Make individual people sick
            if (*(tempSick + i*Length + j) == 1) {
                Group[Length*i + j].infect();
            }
        }
    }
}


// Spread the virus to the immediately adjacent people
void spreadInfection(int * positionReference, Person Group[], int Length, int Width) {
    // Have to parse through each person and if infected then infect adjacent
    // Then I can call the function to apply tempsick to the Group
    
    int tempSick [100][100] = {0};
    
    // Loop through people and find out who to make sick
    for (int i = 0; i < Length; i++) {
        
        for (int j = 0; j < Width; j++) {
            
            // If the person associated with array point is sick then infect around
            if (Group[*(positionReference + i*Length + j)].status == "S") {
                
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
    
    for (int i = 0; i < Length; i++) {
        std::cout << tempSick[i][0] << tempSick[i][1] << tempSick[i][2] << tempSick[i][3] << tempSick[i][4] << "\n";
    }
    std::cout << "\n\n";
    
    for (int i = 0; i < Length; i++) {
        for (int j = 0; j < Width; j++) {
            // Make individual people sick
            if (tempSick[i][j] == 1) {
                Group[Length*i + j].infect();
            }
        }
        
        
    }
    
    
    
    displayGroup(Group, Length, Width);
    
    //infection((int*)tempSick, Group, Length, Width);
    
}






// I can pass an array to the function and then change the original array
// int * positionReference in declaration and (int*)positionReference in call

// i can call the values of an array in the function
// *(positionReference + 2*Length + 3)

// Should I be using std::vector?








#endif /* h_h */
