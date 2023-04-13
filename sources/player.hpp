#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "card.hpp"

 namespace ariel{


class Player {
public:
   std:: string name;

    Player();
    Player(std:: string name);

   void takeCard(Card card); 

   int stacksize(); 
    
   std::string toString() const;
   int cardesTaken()const; 
   std::vector<Card> getCards() const;
   std::vector<Card> getCardsWon() const; 
   bool isPlaying;
   int numOfWins;
    void clearCardsWon();

    std::vector<Card> cards;
    std::vector<Card> cardsWon;

   private:
    //  std::vector<Card> cards;
    //  std::vector<Card> cardsWon;

    
};
}
#endif