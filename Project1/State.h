#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "EnemyGOAP.h"

using namespace std;

class State {
public:
    bool isPatrolling = false; 
    bool isHunting = false;    
    bool isSearching = false;  
    bool shouldFlee = false;    

    bool getPatrolling() const { return isPatrolling; }
    bool getHunting() const { return isHunting; }
    bool getSearching() const { return isSearching; }
    bool getShouldFlee() const { return shouldFlee; }


    void setPatrolling(bool p) { isPatrolling = p; }
    void setHunting(bool h) { isHunting = h; }
    void setSearching(bool s) { isSearching = s; }
    void setShouldFlee(bool f) { shouldFlee = f; }
};


