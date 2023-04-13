#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>



 namespace ariel{
class Card {
public:
    enum Suit { HEARTS, DIAMONDS, CLUBS, SPADES };
    enum Value { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
    
    Card(Value value, Suit suit);
    Value getValue() const;
    Suit getSuit() const;
    bool operator>(const Card& other) const;
    bool operator==(const Card& other) const;
    std:: string printCard() const ;
    // int Card::setValue() ;

    // int Card::setValue() ;

private:
    Value value;
    Suit suit;
};
}
#endif // CARD_HPP
