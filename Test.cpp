#include "doctest.h"
#include <stdexcept>
#include "iostream"
#include "stdio.h"
#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"
using namespace std;


TEST_CASE("Test initialization before the game")
{
    Player p1("Alice");
    Player p2("Bob");    
    CHECK(p1.stacksize() == 0);
    CHECK(p2.stacksize() == 0);
    CHECK(p1.cardesTaken() == 0);
    CHECK(p2.cardesTaken() == 0);
}

TEST_CASE("Test initialization of players and game")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    CHECK(p1.stacksize() == 26);
    CHECK(p2.stacksize() == 26);
    CHECK(p1.cardesTaken() == 0);
    CHECK(p2.cardesTaken() == 0);
}

TEST_CASE("Test game starts with 52 cards")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    CHECK(p1.stacksize() + p2.stacksize() == 52);
    CHECK(p1.cardesTaken() + p2.cardesTaken() == 0);////

}

TEST_CASE("Test cardesTaken() after game ends")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    game.playAll();
    int cardsTaken_p1 = p1.cardesTaken();
    int cardsTaken_p2 = p2.cardesTaken();
    CHECK(cardsTaken_p1 + cardsTaken_p2 == 52);
    CHECK(cardsTaken_p1 >0);
    CHECK(cardsTaken_p2 >0);
    

}


TEST_CASE("Test getting stack size after playing a turn")
{
Player p1("Alice");
Player p2("Bob");
Game game(p1, p2);
int initialStackSize = p1.stacksize() + p2.stacksize();
game.playTurn();
int newStackSize = p1.stacksize() + p2.stacksize();
CHECK(newStackSize < initialStackSize);
}

TEST_CASE("Test playing all turns in a game")
{
Player p1("Alice");
Player p2("Bob");
Game game(p1, p2);
CHECK_NOTHROW(game.playAll());

}


TEST_CASE("Test getting the winner after playing all turns in a game")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    game.playAll();
    std::string winner = game.printWiner();
    CHECK(winner != "");
    std::string all_turns = game.printLog();
    CHECK(all_turns != "");

}


TEST_CASE("Test printStats() when game has started")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    game.playTurn();
    std::string stats = game.printStats();
    CHECK(stats != "");
}

TEST_CASE("Test game log is not empty after playing a turn")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    game.playTurn();
    std::string log = game.printLog();
    CHECK(log != "");
}

TEST_CASE("Test cardesTaken() after game ends")
{
    Player p1("Alice");
    Player p2("Bob");
    bool b1 = p1.stacksize()==0 || p2.stacksize() == 0;
    Game game(p1, p2);
    game.playAll();
    CHECK(b1);
    
}
TEST_CASE("Test if the game ends after 26 turns")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    int turn = 0;
    while (turn < 26)
    {
        game.playTurn();
        turn++;
    }
    CHECK_THROWS(game.playTurn()); // The game should throw an exception after 26 turns
}
