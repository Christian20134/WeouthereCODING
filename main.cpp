#include <iostream>
#include <string>
using namespace std;

class Player {
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
};

int main() {
    Player mainPlayer;
    return 0;
}

/// Shoutouts 45 moment