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

   board.playInColumn(3, O);
 
   
   board.play(4, 1, X);   
   board.play(3, 2, O);
   board.play(2, 3, X);
   board.play(1, 4, X);
   
   //   board.play(0,0,X);
//   board.play(0,2,O);
//   board.play(0,1,O);
//   board.play(0,4,X);
//   board.play(0,3,O);
//   board.play(0,5,X);
//   board.play(2,1,X);
//   board.play(5,1,O);
//   board.play(6,1,X);
   
   board.printBoard(cout);
   
   cout << boolalpha << 
           board.isWinner(X) << endl;

   return 0;
}

