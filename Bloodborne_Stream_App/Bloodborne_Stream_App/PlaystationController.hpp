//
//  PlaystationGamepad.hpp
//  Bloodborne_Stream_App
//
//  Created by Michael Schuff on 1/3/21.
//  Copyright © 2021 Michael Schuff. All rights reserved.
//

#ifndef PlaystationGamepad_hpp
#define PlaystationGamepad_hpp
#include <SFML/Graphics.hpp>


class PlaystationController {
private:
    int sf_Joystick_index;
    bool squareDown = false,
         crossDown = false,
         circleDown = false,
         triangleDown = false,
         lBumperDown = false,
         rBumperDown = false,
         lTriggerDown = false,
         rTriggerDown = false,
         shareDown = false,
         optionsDown = false,
         LStickDown = false,
         RStickDown = false,
         psDown = false,
         padDown = false,
         upDown = false,
         downDown = false,
         leftDown = false,
         rightDown = false;
    
    
public:
    bool squarePressed = false,
         crossPressed = false,
         circlePressed = false,
         trianglePressed = false,
         lBumperPressed = false,
         rBumperPressed = false,
         lTriggerPressed = false,
         rTriggerPressed = false,
         sharePressed = false,
         optionsPressed = false,
         LStickPressed = false,
         RStickPressed = false,
         psPressed = false,
         padPressed = false,
         upPressed = false,
         downPressed = false,
         leftPressed = false,
         rightPressed = false;
    
    PlaystationController(int p_sf_Joystick_index)
    {   sf_Joystick_index = p_sf_Joystick_index; }
    
    bool isConnected()  {
        if (sf_Joystick_index < 0 || sf_Joystick_index > sf::Joystick::Count)
            return false;
        else
            return sf::Joystick::isConnected(sf_Joystick_index);
    }
    
    bool square()
    {    return sf::Joystick::isButtonPressed(sf_Joystick_index, 0);    }
    bool cross()
    {    return sf::Joystick::isButtonPressed(sf_Joystick_index, 1);    }
    bool circle()
    {    return sf::Joystick::isButtonPressed(sf_Joystick_index, 2);    }
    bool triangle()
    {    return sf::Joystick::isButtonPressed(sf_Joystick_index, 3);    }
    
    bool lBumper()
    {    return sf::Joystick::isButtonPressed(sf_Joystick_index, 4);    }
    bool rBumper()
    {    return sf::Joystick::isButtonPressed(sf_Joystick_index, 5);    }
    
    bool lTrigger()
    {    return sf::Joystick::isButtonPressed(sf_Joystick_index, 6);    }
    bool rTrigger()
    {    return sf::Joystick::isButtonPressed(sf_Joystick_index, 7);    }
    
    bool share()
    {    return sf::Joystick::isButtonPressed(sf_Joystick_index, 8);    }
    bool options()
    {    return sf::Joystick::isButtonPressed(sf_Joystick_index, 9);    }
    bool lStick()
    {    return sf::Joystick::isButtonPressed(sf_Joystick_index, 10);    }
    bool rStick()
    {    return sf::Joystick::isButtonPressed(sf_Joystick_index, 11);    }
    
    bool ps()
    {    return sf::Joystick::isButtonPressed(sf_Joystick_index, 12);    }
    bool pad()
    {    return sf::Joystick::isButtonPressed(sf_Joystick_index, 13);    }
    
    bool up()
    {    return sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::PovY) > 0; }
    bool down()
    {    return sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::PovY) < 0; }
    bool left()
    {    return sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::PovY) < 0; }
    bool right()
    {    return sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::PovY) > 0; }
    
    float lTriggerValue()
    {   return sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::U);    }
    float rTriggerValue()
    {   return sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::V);   }

    
    sf::Vector2f LeftStick()
    {   return sf::Vector2f(sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::X),
                            sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Y));     }
    sf::Vector2f RightStick()
    {   return sf::Vector2f(sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Z),
                            sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::R));     }
/*
    if (()) {
        Pressed = !Down;
        Down = true;
    } else {
        Down = false;
    }
 
    */
    void update() {
        if (square()) {
            squarePressed = !squareDown;
            squareDown = true;
        } else {
            squareDown = false;
        }
        
        if (cross()) {
            crossPressed = !crossDown;
            crossDown = true;
        } else {
            crossDown = false;
        }
        
        if (circle()) {
            circlePressed = !circleDown;
            circleDown = true;
        } else {
            circleDown = false;
        }
        
        if (triangle()) {
            trianglePressed = !triangleDown;
            triangleDown = true;
        } else {
            triangleDown = false;
        }
        
        if (lBumper()) {
            lBumperPressed = !lBumperDown;
            lBumperDown = true;
        } else {
            lBumperDown = false;
        }
        
        if (rBumper()) {
            rBumperPressed = !rBumperDown;
            rBumperDown = true;
        } else {
            rBumperDown = false;
        }
        
        if (lTrigger()) {
            lTriggerPressed = !lTriggerDown;
            lTriggerDown = true;
        } else {
            lTriggerDown = false;
        }
        
        if (rTrigger()) {
            rTriggerPressed = !rTriggerDown;
            rTriggerDown = true;
        } else {
            rTriggerDown = false;
        }
        
        if (share()) {
            sharePressed = !shareDown;
            shareDown = true;
        } else {
            shareDown = false;
        }
        
        if (options()) {
            optionsPressed = !optionsDown;
            optionsDown = true;
        } else {
            optionsDown = false;
        }
        
        if (lStick()) {
            LStickPressed = !LStickDown;
            LStickDown = true;
        } else {
            LStickDown = false;
        }
        
        if (rStick()) {
            RStickPressed = !RStickDown;
            RStickDown = true;
        } else {
            RStickDown = false;
        }
        
        if (ps()) {
            psPressed = !psDown;
            psDown = true;
        } else {
            psDown = false;
        }
        
        if (pad()) {
            padPressed = !padDown;
            padDown = true;
        } else {
            padDown = false;
        }
        
        if (up()) {
            upPressed = !upDown;
            upDown = true;
        } else {
            upDown = false;
        }
        
        if (down()) {
            downPressed = !downDown;
            downDown = true;
        } else {
            downDown = false;
        }
        
        if (left()) {
            leftPressed = !leftDown;
            leftDown = true;
        } else {
            leftDown = false;
        }
        
        if (right()) {
            rightPressed = !rightDown;
            rightDown = true;
        } else {
            rightDown = false;
        }
    }
};

#endif /* PlaystationGamepad_hpp */
