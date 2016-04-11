#ifndef P4CMR_h
#define P4CMR_h

#include "P4Interface.h"
#include <iostream>
#include <vector>


typedef std::vector<std::vector<Player>> Board;

class P4cmr : public P4Interface
{
   friend std::ostream& operator << ( std::ostream&, const P4cmr& );

   // A COMPLETER SELON VOS BESOINS EN ATTRIBUTS ET METHODES PRIVEES
    
public:
   // NE PAS MODIFIER L'INTERFACE PUBLIC.
   // IMPLEMENTER LES METHODES SEPAREMENT
   // DANS UN FICHIER .CPP

   /**
    *  @brief Constructeur par defaut
    */
   P4cmr();
    
   /**
    *  @brief Remet à zèro les attributs pour jouer une nouvelle partie
    */
   void reset();

   /**
    *  @brief Le joueur p joue dans la colonne c.
    *
    *  @param c Le numero de colonne entre 0 et 6
    *  @param p Le joueur X ou O
    */
   void playInColumn(size_t c, Player p);

   /**
    *  @brief Verifie si le joueur p gagne
    *
    *  @param p Le joueur X ou O
    *
    *  @return vrai si 4 a la suite pour p, faux sinon
    */
   bool isWinner(Player p) const;

   /**
    *  @brief Verifie si jouer dans la colonne c est valide
    *
    *  @param c Le numero de colonne entre 0 et 6
    *
    *  @return vrai si c est entre 0 et 6 et que la 
    *          colonne n'est pas pleine. Faux sinon
    */
   bool isValidMove(size_t c) const;

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
   size_t chooseNextMove(Player p, unsigned depth);

   /**
    *  @brief Renvoie le nom de votre classe pour le tournoi
    *
    *  @return Un nom qui sera typiquement tronque a l'affichage
    *          pour ne garder que les 4 premieres lettres
    */
   std::string getName() const;
   
   void printBoard(std::ostream& flow) const;
   
   //debug
   void play(size_t c, size_t r, const Player& p);
   
   
   private:
      size_t m_rows;
      size_t m_cols;
      
      /*
       Au format [colonne (gauche->droite)][ligne(bas -> haut)]
       */
      Board m_board;
      std::string m_name;
      
      int evalBoard(Player p);
      int calculScore(size_t col, Player p, size_t depth);
      bool isBoardFull();
      void unplayInColumn(size_t c);
      
      int alphaBetaScore(size_t col, Player p, int alpha, int beta, size_t depth);
      
};

/**
 *  @brief Surcharge de << pour afficher la grille du jeu
 *
 *  @param std::ostream&     le flux utilise pour laffichage
 *  @param P4_NOM_A_CHANGER& un objet de votre classe P4
 *
 *  @return le flux original
 */
std::ostream& operator << ( std::ostream&, const P4cmr& );


#endif /* P4CMR_h */

