#include "player.hpp"


using namespace ariel;
    Player::Player() {}

    Player::Player(std::string name) {
        this->name = name;
        this->cards = std::vector<Card>();
        this->cardsWon = std::vector<Card>();
        numOfWins = 0;
    }

    void Player::takeCard(Card card) {
        if(cards.size() >= 26) return;
        
        this->cards.push_back(card);

    }

    int Player::stacksize()  {
       if (cards.size() <= 0 )
       {
        return 0;
       }
       
        return cards.size();
    }

    int Player::cardesTaken() const {
        return cardsWon.size();
    }

    std::vector<Card> Player::getCards() const {
    return cards;
}

    std::vector<Card> Player::getCardsWon() const {
    return cardsWon;
}

    std::string Player::toString() const {
        // std::ostringstream oss;
        // oss << name << "'s hand: ";
        // for (const auto& card : cards) {
        //     oss << cardToString(card) << " ";
        // }
        return "";//oss.str();
    }

    void Player::clearCardsWon() {
    cardsWon.clear();
}
