/* 
 * File:   P4cmr.cpp
 * Author: camilo
 * 
 * Created on 15. mars 2016, 11:29
 */


#include <limits>
#include <algorithm>

#include "P4cmr.h"

using namespace std;

std::ostream& operator << ( std::ostream&, const P4cmr& );

// A COMPLETER SELON VOS BESOINS EN ATTRIBUTS ET METHODES PRIVEES


/**
 *  @brief Constructeur par defaut
 */
P4cmr::P4cmr()
: m_rows(6), m_cols(7), m_name("BRO4CE")
{
   m_board.resize(m_cols);
   for(unsigned i = 0; i < m_cols ; i ++)
   {
      m_board[i].resize(m_rows);
      for(unsigned j = 0 ; j < m_rows ; j++)
      {
         m_board[i][j] = Player::EMPTY;
      }
   }
}


/**
 *  @brief Remet à zèro les attributs pour jouer une nouvelle partie
 */
void P4cmr::reset()
{
   for(auto&  col : m_board)
   {
      for(auto& square : col)
      {
         square = Player::EMPTY;
      }
   }
}

/**
 *  @brief Le joueur p joue dans la colonne c.
 *
 *  @param c Le numero de colonne entre 0 et 6
 *  @param p Le joueur X ou O
 */
void P4cmr::playInColumn(size_t c, Player p)
{
   for(unsigned r = 0; r < m_rows ; r++)
   {
      if(m_board[c][r] == Player::EMPTY)
      {
         m_board[c][r] = p;
         break;
      }
   }
}

/**
 *  @brief Verifie si le joueur p gagne
 *
 *  @param p Le joueur X ou O
 *
 *  @return vrai si 4 a la suite pour p, faux sinon
 */
bool P4cmr::isWinner(Player p) const
{   
   //Par direction---
   
   //--Horizontal
   for(unsigned r = 0; r < m_rows; r++)
   {
      for(unsigned c = 0; c < m_cols - 3; c++)
      {
         bool isWinner = true;
         //Si c'est pas la couleur du Player, pas pris en compte
         for(unsigned x = 0; x < 4; x++) //Il suffit de parcourir les 4 premieres cases
         {
            if(m_board[c + x][r] != p) //La case n'est pas gagnante
            {
               isWinner = false;
               break;
            }
         }
         if(isWinner)
         {
            return true; //Aucune case sauté -> toute les cases au joueur
         }
      }
   } 
   
   //--Vertical
   for(unsigned r = 0; r < m_rows - 3; r++)
   {
      for(unsigned c = 0; c < m_cols; c++)
      {
         bool isWinner = true;
         //Si c'est pas la couleur du Player, pas pris en compte
         for(unsigned x = 0; x < 4; x++) //Il suffit de parcourir les 4 premieres cases
         {
            if(m_board[c][r + x] != p) //La case n'est pas gagnante
            {
               isWinner = false;
               break;
            }
         }
         if(isWinner)
         {
            return true; //Aucune case sauté -> toute les cases au joueur
         }
      }
   }
   
   

   //Diagonale NE
   for(unsigned r = 0; r < m_rows - 3; r++)
   {
      for(unsigned c = 0; c < m_cols - 3; c++)
      {
         bool isWinner = true;
         //Si c'est pas la couleur du Player, pas pris en compte
         for(unsigned x = 0; x < 4; x++) //Il suffit de parcourir les 4 premieres cases
         {
            if(m_board[c + x][r + x] != p) //La case n'est pas gagnante
            {
               isWinner = false;
               //cout << "ON break en " << c << ", " << r << +"("+ x+")";
               break;
            }
         }
         if(isWinner)
         {
            return true; //Aucune case sauté -> toute les cases au joueur
         }
      }
   }
   
   
   //Diagonale NO
   for(unsigned r = 0; r < m_rows - 3; r++)
   {
      for(unsigned c = 3; c < m_cols; c++)
      {
         bool isWinner = true;
         //Si c'est pas la couleur du Player, pas pris en compte
         for(unsigned x = 0; x < 4; x++) //Il suffit de parcourir les 4 premieres cases
         {
            if(m_board[c - x][r + x] != p) //La case n'est pas gagnante
            {
               isWinner = false;
               break;
            }
         }
         if(isWinner)
         {
            return true; //Aucune case sauté -> toute les cases au joueur
         }
      }
   }
   
   return false;
}

/**
 *  @brief Verifie si jouer dans la colonne c est valide
 *
 *  @param c Le numero de colonne entre 0 et 6
 *
 *  @return vrai si c est entre 0 et 6 et que la 
 *          colonne n'est pas pleine. Faux sinon
 */
bool P4cmr::isValidMove(size_t c) const
{
   if(m_cols < c)
   {
      return false;
   }
   // suffisant de tester la case du haut
   return m_board[c][m_rows - 1] == Player::EMPTY; 
}


/**
 *  @brief Choisit la prochain mouvement pour le joueur p
 *
 *  @param p     Le joueur X ou O
 *  @param depth La profondeur de recherche de l'algorithme minimax
 *
 *  @return retourne un numero de colonne entre 0 et 6
 *          sans modifier l'etat de la grille du jeu
 *          typiquement calcule avec une variante a 
 *          choix de l'algorithme minimax
 */
size_t P4cmr::chooseNextMove(Player p, unsigned depth)
{  
   cout << " " ;
   int bestScore = -numeric_limits<int>::max();
   size_t columnSelected = 0;
   
   //Explore en permutant gauche-droite
   for(double i = 0; i <= m_cols /2; i += 0.5)
   {      
      int col = m_cols / 2;
      if((double)ceil(i) == i)
      {
         col += ceil(i);
      }
      else
      {
         col -= ceil(i);
      }
      
      if(isValidMove(col))
      {
         int score = -alphaBetaScore(col, (Player)p, -numeric_limits<int>::max(), numeric_limits<int>::max(), depth);
         
         if(score > bestScore)
         {
            bestScore = score;
            columnSelected = col;
         }
         cout << "score : " << score ;
         
      }
   }
   
   return columnSelected;
}

bool P4cmr::isBoardFull()
{
   for(size_t col = 0; col < m_cols; col++)
   {
      if(isValidMove(col))
      {
         return false;
      }
   }
   return true;
}

int P4cmr::calculScore(size_t col, Player p, size_t depth)
{   
   playInColumn(col, p);
   
   int score;
   
   if(isWinner(p))
   {
      score = numeric_limits<int>::max();
   }
   else if(depth == 0 || isBoardFull())
   {
      score = evalBoard(p);
   }
   else
   {
      int bestScore = -numeric_limits<int>::max();
      for(int col = 0; col < m_cols; col++)
      {
         if(isValidMove(col))
         {
            int opponentScore = calculScore(col, (Player)-p, depth - 1);

            if(opponentScore > bestScore)
            {
               bestScore = opponentScore;
            }
         }
      }
      score = -bestScore;      
   }
   
   unplayInColumn(col);
   
   return score;   
}


int P4cmr::evalBoard(Player p)
{
   
   if(isWinner(p))
   {
      return numeric_limits<int>::max();
   }
   else if(isWinner((Player)-p))
   {
      return -numeric_limits<int>::max();
   }
   else
   {
      return 0;
      // plusse le joueur a de triplets, plusse la board a de points.
      unsigned triplets = 0;
      
      
      
      //Par direction---
   
   //--Horizontal Ouest à Est
   for(unsigned r = 0; r < m_rows; r++) // toutes les lignes
   {
      for(unsigned c = 0; c < m_cols - 4; c++)  // colonnes indicées de 0 à 7-4 = 3 suffisent
      {
         for(unsigned x = 0; x < 3; x++) //Il suffit de parcourir les 3 premieres cases à l'est
         {
            //Si c'est pas la couleur du Player, pas pris en compte
            if(m_board[c + x][r] != p) //La case n'est pas gagnante
            {
               break;
            }
            triplets++; // aucun sauté, donc trois de suite. alors on incrémente.
         }
      }
   } 
   
   //--Vertical du sud au nord
   for(unsigned r = 0; r < m_rows - 4; r++) // seulement les 4 lignes du bas indicées de 0 à 6-4 = 2
   {
      for(unsigned c = 0; c < m_cols; c++) // toutes les colonnes
      {
         
         
         for(unsigned x = 0; x < 3; x++) //Il suffit de parcourir les 3 premieres cases
         {
            //Si c'est pas la couleur du Player, pas pris en compte
            if(m_board[c][r + x] != p) //La case n'est pas gagnante
            {
               break;
            }
            // sinon on incrémente
            triplets++;
         }
         
      }
   }
   
   

   //Diagonale SO à NE
   for(unsigned r = 0; r < m_rows - 4; r++)  // lignes indicées de 0 à 2 = 6-4
   {
      for(unsigned c = 0; c < m_cols - 4; c++) // lignes indicées de 0 à 3 = 7-4
      {
         for(unsigned x = 0; x < 3; x++) //Il suffit de parcourir les 4 premieres cases
         {
            //Si c'est pas la couleur du Player, pas pris en compte
            if(m_board[c + x][r + x] != p) //La case n'est pas gagnante
            {
               //cout << "ON break en " << c << ", " << r << +"("+ x+")";
               break;
            }
         }
         triplets++;
      }
   }
   
   
   //Diagonale SE à NO
   for(unsigned r = 0; r < m_rows - 4 ; r++) // lignes indicées de 0 à 2 = 6-4
   {
      for(unsigned c = 3; c < m_cols; c++) // colonnes indicées de 3 = 7-4 à 6<m_cols
      {
         
         for(unsigned x = 0; x < 3; x++) //Il suffit de parcourir les 4 premieres cases
         {
            //Si c'est pas la couleur du Player, pas pris en compte
            if(m_board[c - x][r + x] != p) //La case n'est pas gagnante
            {
               break;
            }
         }
         triplets++;
      }
   }
   
   return triplets;
   }
}

void P4cmr::unplayInColumn(size_t c)
{
   for(long int r = m_rows; r >= 0 ; r--)
   {
      //A revoir, TOUT N'EST PAS REMPLIS A 0 PAR DEFAUT
      if(m_board[c][r] == O || m_board[c][r] == X)
      {
         m_board[c][r] = Player::EMPTY;
         break;
      }
   }
}
/**
 *  @brief Renvoie le nom de votre classe pour le tournoi
 *
 *  @return Un nom qui sera typiquement tronque a l'affichage
 *          pour ne garder que les 4 premieres lettres
 */
std::string P4cmr::getName() const
{
   return m_name;
}


void P4cmr::printBoard(std::ostream& flow) const
{
   
   //Affichage de la grille
   for(int i = m_rows -1  ; i >= 0 ; i--)
   {
      for(unsigned j = 0 ; j < m_cols ; j++)
      {
         flow << "|";
         if(m_board[j][i] == Player::EMPTY)
         {
            flow << "_";
         }
         else if(m_board[j][i] == Player::O)
         {
            flow << "o";
         }
         else if(m_board[j][i] == Player::X)
         {
            flow << "x";
         }
         
      }
      flow << "|" << endl;
   }
   
   
   //Affichage du choix
   flow << " ";
   for(unsigned x = 1; x <= m_cols; x++)
   {
      flow << x << " ";
   }
   flow << endl;
}


// to delete
void P4cmr::play(size_t c, size_t r, const Player& p)
{
   this->m_board[c][r] = p;
}

int P4cmr::alphaBetaScore(size_t col, Player p, int alpha, int beta, size_t depth) {

   // cout << " alpha : " << alpha << ", beta : " << beta;
   //playInColumn(col, p);

   if (depth == 0 or isBoardFull() or isWinner(p)) {
      return -evalBoard(p);
   }
   playInColumn(col, p);


   /*
   int score;
   
   if(isWinner(p))
   {
      score = numeric_limits<int>::max();
   }
   else if(depth == 0 || isBoardFull())
   {
      score = -evalBoard(p);
   }
   else
   {
    */
   int bestScore = -numeric_limits<int>::max();
   for (int col = 0; col < m_cols; col++) {
      if (isValidMove(col)) {
         int scoreNextMove = -alphaBetaScore(col, (Player) - p, -beta, -alpha, depth - 1);

         if (scoreNextMove > bestScore) {
            bestScore = scoreNextMove;
         }

         if (alpha < scoreNextMove) {
            alpha = scoreNextMove;
         }

         // élagage
         if (alpha >= beta) {
            break;
         }
      }
      //}

   }

   unplayInColumn(col);

   return bestScore;
}










/**
*  @brief Surcharge de << pour afficher la grille du jeu
*
*  @param std::ostream&     le flux utilise pour laffichage
*  @param P4_NOM_A_CHANGER& un objet de votre classe P4
*
*  @return le flux original
*/
std::ostream& operator << ( std::ostream& flow, const P4cmr& b)
{
   b.printBoard(flow);
   return flow;
}




