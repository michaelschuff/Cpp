//
//  main.cpp
//  BloodborneStreamTextUpdater
//
//  Created by Michael Schuff on 1/3/21.
//

#include <iostream>
#include <fstream>
#include <string.h>
#include "Timer.hpp"

using namespace std;

int main() {
    const int num_bosses = 22;
    string bosses[num_bosses] = {
        "Cleric Beast",
        "Father Gascoigne",
        "Blood-Starved Beast",
        "Vicar Amelia",
        "The Witch of Hemwick",
        "Shadow of Yharman",
        "Rom, the Vacuous Spider",
        "Martyr Logarius",
        "Darkbeast Paarl",
        "The One Reborn",
        "Celestial Emissary",
        "Ebrietas, Daughter of the Cosmos",
        "Amygdala",
        "Micolash, Host of the Nightmare",
        "Mergo's Wet Nurse",
        "Gherman, the First Hunter",
        "Moon Presence",
        "Ludwig, The Holy Blade",
        "Orphan of Kos",
        "Lady Maria of the Astral Clocktower",
        "Living Failures",
        "Laurance, the First Vicar",
    };
    
    string hits[num_bosses];
    
    
    fstream current("/Users/michael/ComputerScience/C++/"
                        "BloodborneStreamTextUpdater/"
                        "BloodborneStreamTextUpdater/"
                        "bloodborne_current.txt");
    fstream best("/Users/michael/ComputerScience/C++/"
                    "BloodborneStreamTextUpdater/"
                    "BloodborneStreamTextUpdater/"
                    "bloodborne_best.txt");
    
    for (int i = 0; i < num_bosses; i++) {
        best >> hits[i];
    }
    
    
    current.close();
    best.close();
}
