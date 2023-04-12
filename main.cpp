#include <iostream>
#include <string>
using namespace std;

void enemyEncounter() {}; /// Encounter/battle function prototype

class Player { /// Player class, constructor values exist because this class is only created
               /// when the game is started.
    int hp;
    int maxHP;
    int damage;
    float accuracy;
    int armor;
    int inventory[];
public:
    Player() {
        maxHP = 10;
        hp = maxHP;
        damage = 1;
        accuracy = 0.9;
        armor = 0;
        cout << "Object of class Player created. ";
    }
    friend void enemyEncounter();
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
};

int main() {
    Player mainPlayer;
    return 0;
}

/// Shoutouts 45 moment 2