//
//  Timer.hpp
//  BloodborneStreamTextUpdater
//
//  Created by Michael Schuff on 1/3/21.
//

#ifndef Timer_hpp
#define Timer_hpp

#include <stdio.h>
#include <chrono>
#include <ctime>
#include <string>

using namespace std;

class Timer {
private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool m_bRunning = false;
public:
    void start() {
        m_StartTime = std::chrono::system_clock::now();
        m_bRunning = true;
    }
    
    void stop() {
        m_EndTime = std::chrono::system_clock::now();
        m_bRunning = false;
    }
    
    long time_count() {
        std::chrono::time_point<std::chrono::system_clock> endTime;
        if(m_bRunning) {
            endTime = std::chrono::system_clock::now();
        } else {
            endTime = m_EndTime;
        }
        return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
    }
    
    int milliseconds() {
        return time_count() % 100;
    }
    
    int seconds() {
        return (time_count() / 1000) % 60;
    }
    
    int minutes() {
        return (time_count() / (60 * 1000)) % 60;
    }
    
    int hours() {
        return time_count() / (60 * 60 * 1000);
    }
    
    string formattedTime() {
        string s = to_string(hours()) + ":";
        int mins = minutes(),
            secs = seconds(),
            mill = milliseconds();
        
        if (mins < 10) {
            s += "0" + to_string(mins);
        } else {
            s += mins;
        }
        
        s += ":";
        
        if (secs < 10) {
            s += "0" + to_string(secs);
        } else {
            s += secs;
        }
        
        s += ".";
        
        if (mill < 10) {
            s += "0" + to_string(mill);
        } else {
            s += mill;
        }
        
        return s;
    }
};


#endif /* Timer_hpp */
