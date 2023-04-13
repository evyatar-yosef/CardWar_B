#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "game.hpp"
#include <random>



using namespace ariel ;

Game::Game(Player &pl1, Player &pl2) 
: pl1(pl1) , pl2(pl2)
{
    if(pl1.isPlaying == true || pl2.isPlaying == true){
      throw std::invalid_argument("one of the players playing in another game");
      }
      
    this->deck.reserve(52);
    this->turns.reserve(26);
    pl1.clearCardsWon(); // Clear the cardsWon vectors at the beginning of each new game
    pl2.clearCardsWon();
    pl1.isPlaying = true;
    pl2.isPlaying = true;
    gameOver = false;
     numOfRound = 0;
     numOfDrews = 0;
    // Initialize deck with 52 cards
    for (int suit = 0; suit < 4; suit++) {
        for (int value = 2; value <= 14; value++) {
           Card card(static_cast<Card::Value>(value), static_cast<Card::Suit>(suit));
       
            deck.push_back(card);
        }

    }
    startGame();
}
void Game::shuffleDeck() {
    static std::mt19937 rng(std::random_device{}());
    std::shuffle(deck.begin(), deck.end(), rng);
}


void Game::startGame() {
    // Shuffle deck before dealing
   shuffleDeck();
   if (deck.empty()) {
            throw std::invalid_argument("deck is empty");
        }

    // Deal 26 cards to each player
    for (int i = 0; i < 26; i++) {
        // Deal a card to player 1
        pl1.takeCard(deck.back());
        deck.pop_back();

        // Deal a card to player 2
        pl2.takeCard(deck.back());
        deck.pop_back();

    }
    }

// 1 = card 1 greater , -1 = card2 greater, 0 = drew
int Game::compareCards(const Card& card1, const Card& card2) {
    if (card1.getValue() > card2.getValue()) {
        return 1;
    } else if (card1.getValue() < card2.getValue()) {
        return -1;
    } else {
        return 0;
    }
}

void Game::playTurn() {
    if(gameOver == true){
        throw std::invalid_argument("The game is alredy finished");

    }

     if (&pl1 == &pl2) {
        throw std::invalid_argument("The two players are the same player.");
    }

    
    
    if (pl1.stacksize() == 0|| pl2.stacksize() == 0) {
        throw std::out_of_range("one of the Players stack is empty.");

    }
    if (pl1.cards.empty() || pl2.cards.empty()) {
    throw std::out_of_range("one of the Players stack is empty.");
    }
    numOfRound++;
    Card card1 = pl1.cards.front();
    Card card2 = pl2.cards.front();
    int result = compareCards(card1, card2);

    Turn turn = {
    pl1.name,
    card1,
    pl2.name,
    card2,
    result,
};
    //  if (pl1.cards.size() == 1 || pl2.cards.size() == 1) {
    //         result = compareCards(card1, card2);
    //         if (result == 1) {
    //            pl1.cardsWon.push_back(card2);
    //            pl1.cardsWon.push_back(card1);
    //            turns.push_back(turn);
    //            pl1.numOfWins ++;


    //        }else if (result == -1) {
    //         pl2.cardsWon.push_back(card1);
    //         pl2.cardsWon.push_back(card2);
    //         turns.push_back(turn);
    //         pl2.numOfWins++;
            
    //     }
    //     pl1.cards.erase(pl1.cards.begin());
    //     pl2.cards.erase(pl2.cards.begin());
    //     return;
    //     }
    // int result = compareCards(card1, card2);
    if (result == 1) {
        pl1.cardsWon.push_back(card2);
        pl1.cardsWon.push_back(card1);
        turns.push_back(turn);
        pl1.numOfWins++;


    } else if (result == -1) {
        pl2.cardsWon.push_back(card1);
        pl2.cardsWon.push_back(card2);
        turns.push_back(turn);
        pl2.numOfWins++;        
    }
    else {
        turn.res = 0;
        turns.push_back(turn);
        numOfDrews++;
             if (pl1.cards.size() == 1 || pl2.cards.size() == 1) {
                turn.card1 = pl1.cards.front();
                turn.card2 = pl2.cards.front();
                result = compareCards(card1, card2);
            if (result == 1) {
               pl1.cardsWon.push_back(card2);
               pl1.cardsWon.push_back(card1);
               turns.push_back(turn);
               pl1.numOfWins ++;


           }else if (result == -1) {
            pl2.cardsWon.push_back(card1);
            pl2.cardsWon.push_back(card2);
            turns.push_back(turn);
            pl2.numOfWins++;
            
        }
        pl1.cards.erase(pl1.cards.begin());
        pl2.cards.erase(pl2.cards.begin());
        return;
        }
     int drewWinner = handleDrew(turn);
     if (drewWinner == 1) {
            pl1.cardsWon.push_back(*pl1.cards.begin());        
            pl1.cardsWon.push_back(*pl2.cards.begin());
    } else if (drewWinner == -1) {
            pl2.cardsWon.push_back(*pl2.cards.begin());        
            pl2.cardsWon.push_back(*pl1.cards.begin());
    } 
    else if (drewWinner == 0) return;

    }
    
    // Remove the cards from the players' decks
    pl1.cards.erase(pl1.cards.begin());
    pl2.cards.erase(pl2.cards.begin());
}

int Game::handleDrew(Turn& turn) {
    int winner = 0;
    numOfRound ++;
    while (winner == 0) {
        // Check if either player is out of cards
        if (pl1.cards.empty() || pl2.cards.empty()) {
            return 0;
        }
        // Each player plays one card face down and one card face up
        std::vector<Card> playedCards;
        playedCards.insert(playedCards.begin(), pl1.cards.begin(), pl1.cards.begin()+2 );
        playedCards.insert(playedCards.begin(), pl2.cards.begin(), pl2.cards.begin()+2 );

        turn.card1 = pl1.cards[1];
        turn.card2 = pl2.cards[1];
        
        pl1.cards.erase(pl1.cards.begin(), pl1.cards.begin() + 2);
        pl2.cards.erase(pl2.cards.begin(), pl2.cards.begin() + 2);

        if (compareCards(playedCards[1], playedCards[3]) == 1) {
            // Player 1 wins
            pl1.cardsWon.insert(pl1.cardsWon.end(), playedCards.begin(), playedCards.end());
            turns.push_back(turn);
            winner = 1;
            pl1.numOfWins++;
            return winner;
        } if (compareCards(playedCards[1], playedCards[3]) == -1) {
            // Player 2 wins
            pl2.cardsWon.insert(pl2.cardsWon.end(), playedCards.begin(), playedCards.end());
            turns.push_back(turn);
            winner = -1;
            pl2.numOfWins++;
            return winner;
        }
        

        // Check if the open cards are equal
  while (compareCards(playedCards[1], playedCards[3]) == 0) {
    // Place one card face down and on top of it a lesser card
    numOfRound++;
    numOfDrews++;
    if (pl1.cards.empty() || pl2.cards.empty()) {
        return 0;
    }
    turn.card1 = Card(pl1.cards[1]);
    turn.card2 = Card(pl2.cards[1]);
    
            playedCards.insert(playedCards.begin(), pl1.cards.begin(), pl1.cards.begin()+2 );
            pl1.cards.erase(pl1.cards.begin());
            pl2.cards.erase(pl1.cards.begin());
            playedCards.insert(playedCards.begin(),pl2.cards.begin(), pl2.cards.begin()+2 );
            pl1.cards.erase(pl2.cards.begin());
            pl2.cards.erase(pl2.cards.begin());
        

        // Determine the winner of this round
        if (compareCards(playedCards[1], playedCards[3]) == 1) {
            // Player 1 wins
            pl1.cardsWon.insert(pl1.cardsWon.end(), playedCards.begin(), playedCards.end());
            turns.push_back(turn);
            winner = 1;
        } else if (compareCards(playedCards[1], playedCards[3]) == -1) {
            // Player 2 wins
            pl2.cardsWon.insert(pl2.cardsWon.end(), playedCards.begin(), playedCards.end());
            turns.push_back(turn);
            winner = -1;
        }
    }if(winner == 0) {
        turns.push_back(turn);
    }
}
    return winner;

}

void Game::playAll() {
    while (!pl1.cards.empty() || !pl2.cards.empty()) {
        playTurn();
        
    }
    gameOver = true;
     pl1.isPlaying = false;
     pl2.isPlaying = false;
}


void Game::printLastTurn() {
    static std::vector<Turn>::size_type  i = 0;
    if(turns[i].res == 1 || turns[i].res == -1){
    printTurn(turns[i]);
    i++;
    }
    
    if(turns[i].res == 0)
    while (turns[i].res == 0)
    {
       printTurn(turns.back());
       i++;
    }
    

}

void Game:: printTurn(Turn& turn){
    std::cout << turn.player1Name << " played " <<  turn.card1.printCard() << " ";
    std::cout << turn.player2Name << " played " << turn.card2.printCard() << "./ ";
    if (turn.res == 1) {
        std::cout << turn.player1Name << " wins";
        
    } else if (turn.res == -1) {
        std::cout << turn.player2Name << " wins";
        
    } else {
        std::cout << "Draw \n";
    }
    std::cout << "--> ";
    std::cout << std::endl;



}

void Game::printWiner() {
    std::cout << "  the winner is: " << std::endl;

    if(pl1.cardesTaken() > pl2.cardesTaken()) 
        std::cout << pl1.name << std::endl;
    else if(pl2.cardesTaken() > pl1.cardesTaken()) 
        std::cout << pl2.name << std::endl;
    else  
        std::cout << "the game ended with a draw" << std::endl;
}


void Game::printLog() {
    for ( Turn& turn : turns) {
        printTurn(turn);
    }
}

void Game::printStats() {
double pl1WinRate = static_cast<double>(pl1.numOfWins) / numOfRound;
double pl2WinRate = static_cast<double>(pl2.numOfWins) / numOfRound;
double DrewRate = static_cast<double>(numOfDrews) / numOfRound;
std::cout << "the game stats:" << std::endl;
std::cout << "num of rounds:" << numOfRound<<std::endl;
std::cout << pl1.name <<" got : " << pl1.numOfWins << " wins in rate of : " << pl1WinRate << "%"<<" and won: " << pl1.cardesTaken() << "cards."<< std::endl;
std::cout << pl2.name <<" got : " << pl2.numOfWins << " wins in rate of : " << pl2WinRate << "%"<<" and won: " << pl2.cardesTaken() <<"cards."<< std::endl;
std::cout << "the game got : " << numOfDrews << " draws in rate of : "<<"%"<< DrewRate<< std::endl;
printWiner();
}


// Game::~Game() {
//     pl1.isPlaying = false;
//     pl2.isPlaying = false;
//     pl1.clearCardsWon(); // Clear the cardsWon vectors when the game ends
//     pl2.clearCardsWon();
// }