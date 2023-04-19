#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;

/* Text storage */
struct Text { /// Scene #, dialogue #, choice #
    string userPromptBegin = "What will you do?";

    string badInput = "Traveler, I do not understand your command. (Input any of the numbers given.)";

    string breakText = "Press ENTER to continue...";

    string introText = "This is a tale of adventure, YOUR tale of adventure to find the fabled fountain of youth located"
                       " deep within the Everglades. Many perils await you, brave explorer, twists and turns only the "
                       "mind can fathom. Do you have what it takes to brave the wild? Or will you fail and never reach "
                       "the glory you're striving for?";

    string scene1d1 = "Facing you are the harsh marshes of the Everglades. You were told by your late spelunking "
                      "grandfather that he found some hints on a text scroll found while exploring a cave near a "
                      "village. The scroll says that the heart of the Everglades contains a temple buried underneath, "
                      "lost to the sands of time. However, the explorer that finds the temple will be rewarded with "
                      "eternal life.";

    string scene1d1c = "1. Check the scroll \n2. Set off on your adventure";

    string scene1d1c1 = "\"Heart of the marshes is where you go, treasure hidden deep down below, Entry guarded a riddle "
                        "again, place the gems in order of the cities within.\"";

    string scene1d1c2 = "You take your first steps into the marsh. It's humid, and you are surrounded by trees all attached "
                        "to the water you walk in currently. You shift carefully, as any gator in the area could easily "
                        "stop you in your tracks and end your adventure permanently. However, you chose a specific time "
                        "they are less active. Specifically, the afternoon, as the temperature drop makes them less active. "
                        "Nevertheless, you pressed on, finding reprieve in the fact that you remembered a handgun, although"
                        "only eight bullets could fit alongside it.\n";

    string scene1d2 = "\nComing to a fork in the glades, you have two choices: a path to the right that looks traveled "
                      "at a glance, with a clear line to follow through - perhaps it leads somewhere? Or, a path to the "
                      "left that seems less traveled, and may lead you astray.";
};

/* Prototypes */
class Enemy;
class Player;
void enemyEncounter(Player& player, Enemy& enemy); /// Encounter/battle function
void gameOver(); /// If you die
void displayText(string& displayedText, int delay, int interLineDelay);
int readInput(Text& text);


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
    void setScrollStatus() {
        scrollChecked = 1;
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
        } else if (displayedText[i] == '!' || displayedText[i] == '.' || displayedText[i] == ',' || displayedText[i] == '?' || displayedText[i] == '-') {
            this_thread::sleep_for(chrono::milliseconds(delay + 200));
        }
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

void textBreak(Text& text) {
    displayText(text.breakText, 1, 1);
    cin.get();
    cin.ignore(1, '\n');
}

int choice(Text& text) {                                                                                                /// Find a way to make this a thing. Low priority
    displayText(text.userPromptBegin, 1, 250);
}

void whatWillYouDo(Text& text) {
    displayText(text.userPromptBegin, 1, 250);
}

int scene1(Text& text, Player& player) {
    int choice1 = 0;
    displayText(text.scene1d1, 1, 1);
    whatWillYouDo(text);
    displayText(text.scene1d1c, 1, 250);
    switch (readInput(text)) {
        case 1:
            displayText(text.scene1d1c1, 20, 250);
            player.setScrollStatus();
            textBreak(text);
        case 2:
            displayText(text.scene1d1c2, 1, 1);
            displayText(text.scene1d2, 1, 1);
            break;
    }
}

int readInput(Text& text) {
    int choice = 0;
    cin >> choice;
    while (choice != 1 && choice != 2 && choice != 3) {
        displayText(text.badInput, 1, 1);
        cin >> choice;
    }
    return choice;
}

int main() {
    Player mainPlayer;
    Text text;
    displayText(text.introText, 1, 1);
    transition();
    scene1(text, mainPlayer);
    return 0;
}

/// Shoutouts 45 moment 2