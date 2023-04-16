#include <iostream>
#include <string>
using namespace std;


/* Prototypes */
class Enemy;
class Player;
void enemyEncounter(Player& player, Enemy& enemy); /// Encounter/battle function
void gameOver(); /// If you die


/* Class Definitons */
class Player { /// Player class, constructor values exist because this class is only created
    int hp;    /// when the game is started.
    int maxHP;
    int damage;
    float accuracy;
    int armor;
    int level;
    int xp;
    int inventory[];
public:
    Player() {
        maxHP = 10;
        hp = maxHP;
        damage = 1;
        accuracy = 0.9;
        armor = 0;
        level = 1;
        xp = 0;
        cout << "You wake up in your room in Florida, near Lake Okeechobee. \"Another day, another dollar,\" you say"   /// Find a fix for breaking strings into 120
                " to yourself, praying" << endl << "that today will break you out of your cycle of monotony. Luckily, " /// char segments. Low priority
                                                   "something insane is about to happen." << endl;
    }
    void takeDamage(int damageTaken) {
        hp -= damageTaken;
        if (hp <= 0) {
            gameOver();
        }
    }
    friend void enemyEncounter(Player& player, Enemy& enemy);
};

class Enemy { /// Template for enemies in encounters
    int hp;
    int damage;
    int armor;
    float accuracy;
public:
    Enemy(int X, int Y, int Z, float J) {
        hp = X;
        damage = Y;
        armor = Z;
        accuracy = J;
    }
    friend void enemyEncounter(Player& player, Enemy& enemy);
};


/* Function Definitions */
void enemyEncounter(Player& player, Enemy& enemy) {
    string input = "";
    do {
        cout << "What will you do? (Fight, Item, Run)" << endl; /// Player turn, goes first cause uhhhhhhh
        cin >> input;
    } while (enemy.hp >= 0);
}


int main() {
    Player mainPlayer;
    Enemy testEnemy(1, 1, 0, 1);
    enemyEncounter(mainPlayer, testEnemy);
    return 0;
}

/// Shoutouts 45 moment 2