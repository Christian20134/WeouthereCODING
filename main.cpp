#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;

/* Dialogue storage */
struct Dialogue {
    string introText = "This is a tale of adventure, YOUR tale of adventure to find the fabled fountain of youth located deep within the Everglades. Many perils await you, brave explorer, twists and turns only the mind can fathom. Do you have what it takes to brave the wild? Or will you fail and never reach the glory you're striving for?";

};


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
void enemyEncounter(Player& player, Enemy& enemy) {                                                                     /// This isn't done yet, but we'll work on it later
    string input = "";
    do {
        cout << "What will you do? (Fight, Item, Run)" << endl; /// Player turn, goes first cause uhhhhhhh
        cin >> input;
    } while (enemy.hp >= 0);
}

void displayText(string& displayedText) {
    int colCounter = 0;
    for (int i = 0; i < displayedText.length(); i++) {
        cout << displayedText[i];
        colCounter++;
        this_thread::sleep_for(chrono::milliseconds(1));
        if (displayedText[i] == ' ' && colCounter > 112) {
            cout << " ";
            cout << endl;
            colCounter = 0;
        } else continue;
    }
}


int main() {
    Player mainPlayer;
    Dialogue dialogue;
    displayText(dialogue.introText);
    return 0;
}

/// Shoutouts 45 moment 2