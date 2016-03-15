/* 
 * File:   main.cpp
 * Author: camilo
 *
 * Created on 15. mars 2016, 11:01
 */

#include <cstdlib>
#include <iostream>

#include "P4cmr.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
   cout << "hello world" << endl;
   
   P4cmr board;
   
   board.play(2,3,X);
   board.play(1,1,O);
   
   board.printBoard(cout);

   return 0;
}

