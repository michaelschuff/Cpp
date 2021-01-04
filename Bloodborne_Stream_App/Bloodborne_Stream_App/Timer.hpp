//
//  Timer.hpp
//  Bloodborne_Stream_App
//
//  Created by Michael Schuff on 1/3/21.
//  Copyright © 2021 Michael Schuff. All rights reserved.
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
    chrono::time_point<chrono::system_clock> m_StartTime;
    chrono::time_point<chrono::system_clock> m_EndTime;
    bool m_bRunning = false, started = false;
public:
    void start() {
        m_StartTime = chrono::system_clock::now();
        m_bRunning = true;
        started = true;
    }
    
    void stop() {
        m_EndTime = chrono::system_clock::now();
        m_bRunning = false;
    }
    
    long time_count() {
        if (started) {
            chrono::time_point<chrono::system_clock> endTime;
            if(m_bRunning) {
                endTime = chrono::system_clock::now();
            } else {
                endTime = m_EndTime;
            }
            return chrono::duration_cast<chrono::milliseconds>(endTime - m_StartTime).count();
        } else {
            return 0;
        }
        
    }
    
    int milliseconds() {
        return (time_count() % 1000) / 10;
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
            s += to_string(mins);
        }
        
        s += ":";
        
        if (secs < 10) {
            s += "0" + to_string(secs);
        } else {
            s += to_string(secs);
        }
        
        s += ".";
        
        if (mill < 10) {
            s += "0" + to_string(mill);
        } else {
            s += to_string(mill);
        }
        
        return s;
    }
};


#endif /* Timer_hpp */

