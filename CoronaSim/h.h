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
    std::string status = "Healthy";
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
        if (status == "Healthy") {x = 1;}
        
        status = "Sick";
        
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



// Shuffle a random group of people
void shuffle(int nunmberToShuffle) {
    // Shuffle the number of people inputted, the number inputted is the number of pairs
    // Have to make sure that all vectors are unique
    
    
}



// Spread the virus to the immediately adjacent people
void spread() {
    // Have to parse through each person and if infected then infect adjacent
    
    
}










#endif /* h_h */
