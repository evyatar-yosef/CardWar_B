#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"
#include "card.hpp"
#include <algorithm>
#include <random>




namespace ariel{

struct Turn {
    std::string player1Name;
    Card card1;
    std::string player2Name;
    Card card2;
    int res;
};
class Game {
public:
    Game(Player &pl1, Player &pl2);
   
    void printLastTurn();
    void printTurn(Turn& turn);
    void playTurn();
    void playAll();
    void  printWiner();
    void printLog();
    void printStats();
    
  

private:
 std::vector<Card> deck;
 std::vector<Turn> turns;
    bool gameOver;
    int numOfRound;
    int numOfDrews;
        Player &pl1;
        Player &pl2;
        void shuffleDeck();
        void startGame();
        int compareCards(const Card& card1, const Card& card2);
        int handleDrew(Turn& turn);
    
};
}
#endif // GAME_HPP
