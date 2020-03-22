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
    // insert code here...
    std::cout << "Hello, World!\n";
    
    Person Lucas;
    
    std::cout << Lucas.status << "\n";
    
    Lucas.infect();
    
    std::cout << Lucas.status << "\n";
    
    Lucas.changePosition(2, 3);
    
    std::cout << Lucas.position[0] << Lucas.position[1] << "\n";
    
    
    return 0;
}





