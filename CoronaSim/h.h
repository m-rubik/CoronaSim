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


// Shuffle a random group of people
void shuffle(int nunmberToShuffle) {
    // Shuffle the number of people inputted, the number inputted is the number of pairs
    // Have to make sure that all vectors are unique
    
    
}



// Spread the virus to the immediately adjacent people
int spreadInfection(int * positionReference, Person Group[], int Length, int Width) {
    // Have to parse through each person and if infected then infect adjacent
    
    
    Group[0].infect();
    
    *(positionReference + 4) = 15;
    
    
    
    return *(positionReference + 1*Length + 2);
}

// I can pass an array to the function and then change the original array
// int * positionReference in declaration and (int*)positionReference in call

// i can call the values of an array in the function
// *(positionReference + 2*Length + 3)

// Should I be using std::vector?








#endif /* h_h */
