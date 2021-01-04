//
//  main.cpp
//  Bloodborne_Stream_App
//
//  Created by Michael Schuff on 1/3/21.
//  Copyright © 2021 Michael Schuff. All rights reserved.
//


#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Timer.hpp"
#include "PlaystationController.hpp"
#include <math.h>

using namespace std;
using namespace sf;

int main() {
    int spacing = 29;
    float kerning = 1;
    int width = 400;
    int height = 370;
    PlaystationController con(0);
//    for(int i = 0; i < 8; i++) {
//        if (sf::Joystick::isConnected(i)) {
//            con = PlaystationController(i);
//        }
//    }
    
    const string resourcePath = "/Users/michael/ComputerScience/C++/"
                                "Bloodborne_Stream_App/Bloodborne_Stream_App/Resources/";
    int current_boss = -1;
    const int num_bosses = 22;
    int best_hits[num_bosses];
    int hits[num_bosses];
    int num_displayed = 9;
    int that_num = min(max(0, current_boss - num_displayed/2), num_bosses - num_displayed);
    float border_radius = 4;
//    string bosses[num_bosses] = {
//        "Cleric Beast",
//        "Father Gascoigne",
//        "Blood Starved Beast",
//        "Vicar Amelia",
//        "The Witch of Hemwick",
//        "Shadow of Yharman",
//        "Rom, the Vacuous Spider",
//        "Martyr Logarius",
//        "Darkbeast Paarl",
//        "The One Reborn",
//        "Celestial Emissary",
//        "Ebrietas, Daughter of the Cosmos",
//        "Amygdala",
//        "Micolash, Host of the Nightmare",
//        "Mergos Wet Nurse",
//        "Gherman, the First Hunter",
//        "Moon Presence",
//        "Ludwig, The Holy Blade",
//        "Orphan of Kos",
//        "Lady Maria of the Astral Clocktower",
//        "Living Failures",
//        "Laurance, the First Vicar",
//    };
    int reorder[] = {
        1,
        2,
        3,
        8,
        5,
        6,
        9,
        13,
        14,
        12,
        10,
        11,
        0,
        17,
        20,
        19,
        18,
        21,
        4,
        7,
        15,
        16
    };
    string bosses[num_bosses] = {
        "Cleric Beast",
        "Father Gascoigne",
        "Blood Starved Beast",
        "Vicar Amelia",
        "Witch of Hemwick",
        "Shadow of Yharman",
        "Rom",
        "Martyr Logarius",
        "Darkbeast Paarl",
        "The One Reborn",
        "Celestial Emissary",
        "Ebrietas",
        "Amygdala",
        "Micolash",
        "Mergos Wet Nurse",
        "Gherman",
        "Moon Presence",
        "Ludwig",
        "Orphan of Kos",
        "Lady Maria",
        "Living Failures",
        "Laurance",
    };
    ifstream best(resourcePath + "bloodborne_best.txt");
    
    Timer boss_timers[num_bosses];
    Timer main_timer;
    for (int i = 0; i < num_bosses; i++) {
        best >> best_hits[i];
        boss_timers[i] = Timer();
        hits[i] = 0;
    }
    best.close();
    
    RenderWindow window(VideoMode(width, height), "SFML window");
    Font font1, font2;
//    if (!font1.loadFromFile(resourcePath + "arial-monospaced-mt.ttf")) {
//    if (!font1.loadFromFile(resourcePath + "Sansation_Regular.ttf")) {
//    if (!font1.loadFromFile(resourcePath + "CaviarDreams.ttf")) {
//    if (!font1.loadFromFile(resourcePath + "Retroica.ttf")) {
//    if (!font1.loadFromFile(resourcePath + "KeepCalm-Medium.ttf")) {
//    if (!font1.loadFromFile(resourcePath + "FUTRFW.ttf")) {
//    if (!font1.loadFromFile(resourcePath + "JAi.ttf")) {
    if (!font1.loadFromFile(resourcePath + "Anonymous.ttf")) {
//    if (!font1.loadFromFile(resourcePath + "Lonely.ttf")) {
        cout << "error loading font from file" << endl;
    }
        if (!font2.loadFromFile(resourcePath + "arial-monospaced-mt.ttf")) {
    //    if (!font2.loadFromFile(resourcePath + "Sansation_Regular.ttf")) {
    //    if (!font2.loadFromFile(resourcePath + "CaviarDreams.ttf")) {
    //    if (!font2.loadFromFile(resourcePath + "Retroica.ttf")) {
    //    if (!font2.loadFromFile(resourcePath + "KeepCalm-Medium.ttf")) {
    //    if (!font2.loadFromFile(resourcePath + "FUTRFW.ttf")) {
    //    if (!font2.loadFromFile(resourcePath + "JAi.ttf")) {
//        if (!font2.loadFromFile(resourcePath + "Anonymous.ttf")) {
//        if (!font2.loadFromFile(resourcePath + "Lonely.ttf")) {
            cout << "error loading font from file" << endl;
        }
    
    
    
    
    Text game_time("", font2);
    game_time.setCharacterSize(60);
    game_time.setFillColor(Color(127, 187, 255));
    game_time.setLetterSpacing(0.5);
    
    Text best_hits_text[num_bosses];
    Text hits_text[num_bosses];
    Text boss_text[num_bosses];
    
    
    for (int i = 0; i < num_bosses; i++) {
        boss_text[i] = Text(bosses[i], font1);
        boss_text[i].setCharacterSize(25);
        boss_text[i].setLetterSpacing(kerning);
        
        hits_text[i] = Text(to_string(hits[i]), font2);
        hits_text[i].setCharacterSize(25);
        hits_text[i].setLetterSpacing(0.5);
        
        best_hits_text[i] = Text(to_string(best_hits[i+that_num]), font2);
        best_hits_text[i].setCharacterSize(25);
        best_hits_text[i].setLetterSpacing(kerning);
    }
    Color h_color(100, 120, 255);
    RectangleShape highlight(Vector2f(width-2*border_radius, 30-2*border_radius));
    RectangleShape h_left(Vector2f(border_radius, 30-2*border_radius));
    RectangleShape h_right(Vector2f(border_radius, 30-2*border_radius));
    RectangleShape h_top(Vector2f(width-2*border_radius, border_radius));
    RectangleShape h_bottom(Vector2f(width-2*border_radius, border_radius));
    highlight.setFillColor(h_color);
    h_left.setFillColor(h_color);
    h_right.setFillColor(h_color);
    h_top.setFillColor(h_color);
    h_bottom.setFillColor(h_color);
    
    CircleShape h_tl(border_radius);
    CircleShape h_tr(border_radius);
    CircleShape h_bl(border_radius);
    CircleShape h_br(border_radius);
    h_tl.setFillColor(h_color);
    h_tr.setFillColor(h_color);
    h_bl.setFillColor(h_color);
    h_br.setFillColor(h_color);
    
    while (window.isOpen()) {
        
        con.update();
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                window.close();
            }
        }

        window.clear();
        if (con.squarePressed) {
            if (current_boss == -1) {
                main_timer.start();
            }
            if (current_boss >= 0) {
                boss_timers[current_boss].stop();
            }
            current_boss++;
            if (current_boss == num_bosses) {
                main_timer.stop();
            }
            that_num = min(max(0, current_boss - num_displayed/2), num_bosses - num_displayed);
            if (current_boss < num_bosses) {
                boss_timers[current_boss].start();
            }
        }
        
        if (con.crossPressed && current_boss >= 0 && current_boss < num_bosses) {
            hits[current_boss]++;
        }
        
        if (current_boss != -1 && current_boss < num_bosses) {
            if (current_boss <= num_displayed/2) {
                int n = spacing * current_boss;
                highlight.setPosition(border_radius, border_radius + n);
                h_top.setPosition(border_radius, spacing * current_boss);
                h_bottom.setPosition(border_radius, 30 - border_radius + n);
                h_left.setPosition(0, border_radius + n);
                h_right.setPosition(width - border_radius, border_radius + n);
                
                h_tl.setPosition(0, n);
                h_tr.setPosition(width - 2*border_radius, n);
                h_bl.setPosition(0, 30 - 2*border_radius + n);
                h_br.setPosition(width - 2*border_radius, 30 - 2*border_radius + n);
            } else if (current_boss >= num_bosses - num_displayed/2) {
                int n = spacing * (current_boss - (num_bosses - num_displayed));
                highlight.setPosition(border_radius, border_radius + n);
                h_top.setPosition(border_radius, n);
                h_bottom.setPosition(border_radius, 30 - border_radius + n);
                h_left.setPosition(0, border_radius + n);
                h_right.setPosition(width - border_radius, border_radius + n);
                
                h_tl.setPosition(0, n);
                h_tr.setPosition(width - 2*border_radius, n);
                h_bl.setPosition(0, 30 - 2*border_radius + n);
                h_br.setPosition(width - 2*border_radius, 30 - 2*border_radius + n);
            }
            window.draw(h_tl);
            window.draw(h_tr);
            window.draw(h_bl);
            window.draw(h_br);
            window.draw(highlight);
            window.draw(h_top);
            window.draw(h_bottom);
            window.draw(h_right);
            window.draw(h_left);
        }
        
        
        for (int i = 0; i < num_displayed; i++) {
            boss_text[i+that_num].setString(bosses[i+that_num]);
            boss_text[i+that_num].setPosition(5, i*spacing);
            window.draw(boss_text[i+that_num]);
            
//            Text boss_time_text(boss_timers[i].formattedTime(), font);
//            boss_time_text.setPosition(300, i*18);
//            boss_time_text.setCharacterSize(15);
//            window.draw(boss_time_text);
            
            hits_text[i+that_num].setString(to_string(hits[i+that_num]));
            hits_text[i+that_num].setPosition(width - 15 - hits_text[i+that_num].getGlobalBounds().width/2, i*spacing);
            if (i+that_num <= current_boss) {
                if (hits[i+that_num] < best_hits[i+that_num]) {
                    hits_text[i+that_num].setFillColor(Color(0, 200, 50));
                }
                if (hits[i+that_num] > best_hits[i+that_num]) {
                    hits_text[i+that_num].setFillColor(Color(200, 0, 50));
                }
            }
            window.draw(hits_text[i+that_num]);
            
            best_hits_text[i+that_num].setString(to_string(best_hits[i+that_num]));
            best_hits_text[i+that_num].setPosition(width - 40 - best_hits_text[i+that_num].getGlobalBounds().width/2, i*spacing);
            
            window.draw(best_hits_text[i+that_num]);
        }
        
        game_time.setString(main_timer.formattedTime());
        game_time.setPosition(width - 20 - 298, num_displayed*spacing);
        window.draw(game_time);
        window.display();
    }
    
    fstream pbs(resourcePath + "bloodborne_best.txt");
    string write = "";
    for (int i = 0; i < num_bosses; i++) {
        int h;
        pbs >> h;
        write += to_string(min(h, hits[i])) + "\n";
    }
    int time;
    pbs >> time;
    write += to_string(min(time, main_timer.milliseconds())) + "\n";
    pbs.close();
    
    pbs.open(resourcePath + "bloodborne_best.txt", ios::out | ios::trunc);
    pbs << write;
    pbs.close();

    return EXIT_SUCCESS;
}
