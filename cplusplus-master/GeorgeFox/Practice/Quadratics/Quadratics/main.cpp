//
//  main.cpp
//  Quadratics
//
//  Created by Michael Schuff on 2/6/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#include <iostream>
#include <ifstream>

using namespace std;

int main() {
    ifstream myfile("input.txt");
    if (myfile.is_open())
    {
      while ( getline (myfile,line) )
      {
        cout << line << '\n';
      }
      myfile.close();
    }
}
