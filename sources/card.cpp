#include "card.hpp"

using namespace ariel;
    Card::Card(Value value, Suit suit) {
        this->value = value;
        this->suit = suit;
    }

    Card::Value Card::getValue() const {
        return value;
    }

    Card::Suit Card::getSuit() const {
        return suit;
    }
   

    
    
    
    bool Card::operator>(const Card& other) const {
        if (value != other.value) {
            return value > other.value;
        } else {
            return other.value > value;
        }
    }

    bool Card::operator==(const Card& other) const {
        return value == other.value && suit == other.suit;
    }


std::string Card::printCard() const {
    std::string value_str;
    switch (value) {
        case ACE: value_str = "Ace"; break;
        case TWO: value_str = "Two"; break;
        case THREE: value_str = "Three"; break;
        case FOUR: value_str = "Four"; break;
        case FIVE: value_str = "Five"; break;
        case SIX: value_str = "Six"; break;
        case SEVEN: value_str = "Seven"; break;
        case EIGHT: value_str = "Eight"; break;
        case NINE: value_str = "Nine"; break;
        case TEN: value_str = "Ten"; break;
        case JACK: value_str = "Jack"; break;
        case QUEEN: value_str = "Queen"; break;
        case KING: value_str = "King"; break;
    }
    std::string suit_str;
    switch (suit) {
        case HEARTS: suit_str = "Hearts"; break;
        case DIAMONDS: suit_str = "Diamonds"; break;
        case CLUBS: suit_str = "Clubs"; break;
        case SPADES: suit_str = "Spades"; break;
    }
    return value_str + " of " + suit_str;
}
