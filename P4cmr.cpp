/* 
 * File:   P4cmr.cpp
 * Author: camilo
 * 
 * Created on 15. mars 2016, 11:29
 */

#include "P4cmr.h"

using namespace std;

std::ostream& operator << ( std::ostream&, const P4cmr& );

// A COMPLETER SELON VOS BESOINS EN ATTRIBUTS ET METHODES PRIVEES


// NE PAS MODIFIER L'INTERFACE PUBLIC.
// IMPLEMENTER LES METHODES SEPAREMENT
// DANS UN FICHIER .CPP

/**
 *  @brief Constructeur par defaut
 */
P4cmr::P4cmr()
: m_rows(6), m_cols(7), m_name("BRO4")
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
   // parcours de bas en haut, par dimension (horizontal, diagonales, )
   
   //Par direction
   
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
   
}

/**
 *  @brief Renvoie le nom de votre classe pour le tournoi
 *
 *  @return Un nom qui sera typiquement tronque a l'affichage
 *          pour ne garder que les 4 premieres lettres
 */
std::string P4cmr::getName() const
{
   string truncated = m_name.substr(5);
   return truncated;
}



void P4cmr::printBoard(std::ostream& flow) const
{
   string ligne = string( m_cols*2, '_');
   
   for(int i = m_rows -1  ; i >= 0 ; i--)
   {
      //flow << ligne << endl;
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
   
   flow << endl;
}


// to delete
void P4cmr::play(size_t c, size_t r, const Player& p)
{
   this->m_board[c][r] = p;
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




