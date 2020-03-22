//
//  main.cpp
//  CoronaSim
//
//  Created by Lucas Nieuwenhout on 2020-03-22.
//  Copyright © 2020 Lucas Nieuwenhout. All rights reserved.
//

#include <iostream>

class person {
public:
    // Is the person infected
    std::string status = "Healthy";
    // Has the person been infected and then healed
    
    
    // Unit time that the person has been infected
    int sicktime;
    
    // Position of the person
    int position[2];
    
    // Which group is the person in
    int group;
    
    
    void infect() {
        status = "Sick";
    };
    
    void heal() {
        status = "Healed";
    }
    
    
    
    
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    person Lucas;
    
    std::cout << Lucas.status << "\n";
    
    Lucas.infect();
    
    std::cout << Lucas.status << "\n";
    
    
    
    
    return 0;
}
