#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;

/* Consts */
const int STANDARD_DELAY = 10; /// I think I can incorporate this into a class somehow. Templates with separate classes? Med priority
                               /// Also, when compiling for Windows, set to 1, it looks nicer, doesn't work on Unix for some reason.
                               /// Use 10 for Mac/Linux

/* Death IDs */
enum Death {
    simpleton,
    pond,
    narrator
};

/* Text storage */
struct Text { /// Scene #, dialogue #, choice #
    string userPromptBegin = "What will you do?";

    string badInput = "Traveler, I do not understand your command. (Input any of the numbers given.)";

    string repeatedBadInput = "Okay, you're doing this on purpose. You think you're funny? Gonna have a little bit of "
                              "fun with the person trying to help you on your stupid quest? Well, I quit. No more story. "
                              "No more adventure. I'm done. Find a new narrator.";

    string breakText = "Press ENTER to continue...";

    string gameOver = "\nG A M E   O V E R\nReason for death: ";

    string reasonSimple = "The pinnacle of idiocy. Absolute buffoonery. Take your simpleton brain somewhere else";

    string reasonPond = "Got relaxed. Maybe a little too relaxed...";

    string reasonBadInput = "Pissed off the wrong person.";

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
                        "Nevertheless, you pressed on, finding reprieve in the fact that you remembered a handgun, although "
                        "only eight bullets could fit alongside it.\n";

    string scene1d2 = "\nComing to a fork in the glades, you have two choices: a path to the right that looks traveled "
                      "at a glance, with a clear line to follow through - perhaps it leads somewhere? Or, a path to the "
                      "left that seems less traveled, and may lead you astray.";

    string scene1d2c = "1. Go left\n2. Go right\n3. Go forward";

    string scene1d2c3 = "You aren't a person who listens to rules set in front of you, are you? No, you thought you had "
                        "to be above everyone else and carve your own path, didn't you? Well, despite the fact you IGNORED the "
                        "paths laid ahead of you, you arrive at the temple. However, because you went on the straight "
                        "path, you don't know anything about how to get into the temple, you imbecile. Your adventure was "
                        "technically for naught, as you are simpleminded. You give up and head home empty handed.";

    string scene1d2c1 = "You clear through the brush on the path of the left side of the fork. It's quite a narrow path, "
                        "and windy at that too. You're taking a lot of care not to stray far from the path, as there are "
                        "dangerous creatures ready to end you at either side. After quite some time walking, you come "
                        "across a gentle stream, flowing out of a sizeable pond. You decide to go closer to the edge of "
                        "the pond to investigate. What a relaxing spot! You dip your hand gingerly into the water to feel "
                        "the cold water run through your fingers and around your hand. \"Ah, that's nice,\" you think to "
                        "yourself, as you pull your hand back into the open air. It's gone. There's no more hand. You now "
                        "have a mere stump, drenched in blood. You succumb to your injuries.";
};

/* Prototypes */
class Enemy;
class Player;
void enemyEncounter(Player& player, Enemy& enemy); /// Encounter/battle function
void gameOver(Text& text, int deathReason); /// If you die
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
    /*void takeDamage(int damageTaken) {
        hp -= damageTaken;
        if (hp <= 0) {
            void;
        }
    } */
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

/// I really want to move everything that takes Text struct input into the class with Text, but idk how to do that
/// without breaking everything. Maybe separate class with inheritance? Figure out soon, bonus points for OOP

void displayText(string& displayedText, int delay, int interLineDelay) { /// Takes string input and delay between chars in ms.
    int colCounter = 0;
    for (int i = 0; i < displayedText.length(); i++) {
        cout << displayedText[i];
        cout.flush();
        colCounter++;
        this_thread::sleep_for(chrono::milliseconds(delay));
        if (displayedText[i] == ' ' && colCounter > 110) {
            cout << " ";
            cout << endl;
            cout.flush();
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
            cout.flush();
            this_thread::sleep_for(chrono::milliseconds(STANDARD_DELAY));
        }
        cout << endl;
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
};

void textBreak(Text& text) {
    displayText(text.breakText, STANDARD_DELAY, 1);
    cin.get();
    cin.ignore(1, '\n');
}

void whatWillYouDo(Text& text) {
    displayText(text.userPromptBegin, STANDARD_DELAY, 250);
}

int readInput(Text& text) {
    int badChoiceCounter = 0;
    int choice = 0;
    cin >> choice;
    while (choice != 1 && choice != 2 && choice != 3) {
        if (badChoiceCounter > 3) {
            displayText(text.repeatedBadInput, STANDARD_DELAY, 1);
            gameOver(text, narrator);
            break;
        } else {
            displayText(text.badInput, STANDARD_DELAY, 1);
            badChoiceCounter++;
        }
        cin >> choice;
    }
    return choice;
}

void gameOver(Text& text, int deathReason) {
    displayText(text.gameOver, 50, 1000);
    switch (deathReason) {
        case simpleton:
            displayText(text.reasonSimple, STANDARD_DELAY, 1000);
            break;
        case pond:
            displayText(text.reasonPond, STANDARD_DELAY, 1000);
            break;
        case narrator:
            displayText(text.reasonBadInput, STANDARD_DELAY, 1000);
            break;
    }
    textBreak(text);
}

void scene1(Text& text, Player& player) {
    int choice1 = 0;
    displayText(text.scene1d1, STANDARD_DELAY, 1);
    whatWillYouDo(text);
    displayText(text.scene1d1c, STANDARD_DELAY, 250);
    switch (readInput(text)) {
        case 1:
            displayText(text.scene1d1c1, 20, 250);
            player.setScrollStatus();
            textBreak(text);
        case 2:
            displayText(text.scene1d1c2, STANDARD_DELAY, 1);
            displayText(text.scene1d2, STANDARD_DELAY, 1);
            whatWillYouDo(text);
            displayText(text.scene1d2c, STANDARD_DELAY, 250);
            switch (readInput(text)) {
                case 1:
                    displayText(text.scene1d2c1, STANDARD_DELAY, 1);
                    gameOver(text, pond);
                    break;
                case 2:

                case 3:
                    displayText(text.scene1d2c3, STANDARD_DELAY, 1);
                    gameOver(text, simpleton);
                    break;
            }
            break;
    }
}


int main() {
    Player mainPlayer;
    Text text;
    displayText(text.introText, STANDARD_DELAY, 1);
    transition();
    scene1(text, mainPlayer);
    return 0;
}

/// Shoutouts 45 moment 2