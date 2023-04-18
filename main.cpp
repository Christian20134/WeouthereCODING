#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;

/* Text storage */
struct Text { /// Scene #, dialogue #, choice #
    string introText = "This is a tale of adventure, YOUR tale of adventure to find the fabled fountain of youth located"
                       " deep within the Everglades. Many perils await you, brave explorer, twists and turns only the "
                       "mind can fathom. Do you have what it takes to brave the wild? Or will you fail and never reach "
                       "the glory you're striving for?";
    string scene1intro = "Facing you are the harsh marshes of the Everglades. You were told by your late spelunking "
                      "grandfather that he found some hints on a text scroll found while exploring a cave near a "
                      "village. The scroll says that the heart of the Everglades contains a temple buried underneath, "
                      "lost to the sands of time. However, the explorer that finds the temple will be rewarded with "
                      "eternal life.";
    string userPromptBegin = "What will you do?";
    string scene1d1c1 = "1. Check the scroll \n 2. Set off on your adventure";
};


/* Prototypes */
class Enemy;
class Player;
void enemyEncounter(Player& player, Enemy& enemy); /// Encounter/battle function
void gameOver(); /// If you die
void displayText(string& displayedText, int delay, int interLineDelay);


/* Class Definitons */
class Player { /// Player class, constructor values exist because this class is only created
    int hp;    /// when the game is started.
    int maxHP;
    int damage;
    float accuracy;
    int armor;
    int level;
    int xp;
    bool scrollChecked;
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
        scrollChecked = 0;

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

void displayText(string& displayedText, int delay, int interLineDelay) { /// Takes string input and delay between chars in ms.
    int colCounter = 0;
    for (int i = 0; i < displayedText.length(); i++) {
        cout << displayedText[i];
        colCounter++;
        this_thread::sleep_for(chrono::milliseconds(delay));
        if (displayedText[i] == ' ' && colCounter > 110) {
            cout << " ";
            cout << endl;
            colCounter = 0;
            this_thread::sleep_for(chrono::milliseconds(interLineDelay));
        } else continue;
    }
    cout << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
}

void transition() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 10; j++) {
            cout << ".";
            this_thread::sleep_for(chrono::milliseconds(1));
        }
        cout << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
};

int choice(Text& text) {
    displayText(text.userPromptBegin, 1, 250);
}

int scene1(Text& text) {
    displayText(text.scene1intro, 1,1);
}

int main() {
    Player mainPlayer;
    Text text;
    displayText(text.introText, 1, 1);
    transition();
    scene1(text);
    return 0;
}

/// Shoutouts 45 moment 2