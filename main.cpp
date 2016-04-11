/* 
 * File:   main.cpp
 * Author: camilo
 *
 * Created on 15. mars 2016, 11:01
 */

#include <cstdlib>
#include <iostream>
#include <limits>
#include <ctime>

#include "P4cmr.h"

using namespace std;

// BASE SUR LE TIC TAC TOE 
//
// choisit interactivement le prochain mouvement
// en le demandant au joueur et en verifiant que
// le choix est licite.
// cette fonction est recursive si le choix est
// illicite.
int interactive(Player player, const P4cmr& p4Game) {
    cout << endl << "Prochain mouvement du joueur " << ((player==X) ? "X" : "O" ) << ": " << flush;
    
    int n;
    cin >> n;
    cout << endl;
    
    if(!cin.good() || !p4Game.isValidMove(n - 1)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Mouvement non valide. Essayez encore." << endl;
        return interactive(player, p4Game);
    } else
        return n - 1;
}

// indique si le tableau est plein
// (les cases du haut sont remplies)
bool isBoardFull(P4cmr p4Game) 
{
   for (int cols=0; cols < 7; cols++)
   {
      if (p4Game.isValidMove(cols)) //On regarde si les colonnes sont remplies
      {
         return false;
      }
   }
   return true;
}


// choisit interactivement le nombre de joueurs humains
// en le demandant au joueur et en verifiant que
// le choix est licite.
// cette fonction est recursive si le choix est
// illicite.
int askNumberOfPlayers() {
    
    cout << "Combien de joueurs humains? (0,1 ou 2) " << flush;
    
    int n;
    cin >> n;
    cout << endl;
    
    if(!cin.good() || (n < 0) || (n>2) ) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Nombre de joueur invalide. " << endl;
        return askNumberOfPlayers();
    }
    else
        return n;
}


int main() 
{   
   
   //Base sur le TIC TAC TOE
   
   P4cmr p4Game;
   p4Game.reset();
   Player currentPlayer = Player::O;
   bool human[2] = {1, 1};
   
   srand ( (int) time(0) );
    
   int np = askNumberOfPlayers();

   switch(np) 
   {
      case 0:
         human[0] = human[1] = false;
         break;
      case 1:
         human[0] = rand() % 2;  // choix aleatoire du premier joueur
         human[1] = !human[0];
         break;
      case 2:
         human[0] = human[1] = true;
         break;
   }   
   
   while(!p4Game.isWinner(O) && !p4Game.isWinner(X) && !isBoardFull(p4Game)) 
   {
      p4Game.printBoard(cout);

      int nextMove;
      if (human[(currentPlayer + 1) / 2])
          nextMove = interactive(currentPlayer, p4Game);
      else {
          nextMove = p4Game.chooseNextMove(currentPlayer, 7);
          cout << endl << "AI joue " << nextMove + 1 << endl;
      }
      p4Game.playInColumn(nextMove, currentPlayer);
      
      currentPlayer = (Player)(-currentPlayer);
   }
   
   p4Game.printBoard(cout);   
   
   if (p4Game.isWinner(X) || p4Game.isWinner(O)) //Si l'un des joueurs a gagne
   {      
      cout << " \n\n" << (p4Game.isWinner(X) ? 'X' : 'O') << " gagne! \n\n\n";
   }
   else
   {
      cout << " \n\n Egalité! \n\n\n";
   }
   
   system("PAUSE");

   return EXIT_SUCCESS;


}

