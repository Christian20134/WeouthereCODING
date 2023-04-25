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
    narrator,
    godred,
    lowIQ
};

enum DecisionType {
    action,
    dialogue
};

/* Prototypes */
class Enemy;
class Player;
void enemyEncounter(Player& player, Enemy& enemy); /// Encounter/battle function
void displayText(string& displayedText, int delay, int interLineDelay);
void chooseReturnDecision();


/* Class definitions */
class Text { /// Scene #, dialogue #, choice #
private:
    string userPromptBegin = "What will you do?";

    string userPromptBeginDialogue = "How will you respond?";

    string badInput = "Traveler, I do not understand your command. (Input any of the numbers given.)";

    string repeatedBadInput = "Okay, you're doing this on purpose. You think you're funny? Gonna have a little bit of "
                              "fun with the person trying to help you on your stupid quest? Well, I quit. No more story. "
                              "No more adventure. I'm done. Find a new narrator.";

    string continueText = "Restart from your last decision? (Y/N)";

    string exitText = "Understood. Exiting...";

    string breakText = "Press ENTER to continue...";

    string gameOverStr = "\nG A M E   O V E R\nReason for death: ";

    string reasonSimple = "The pinnacle of idiocy. Absolute buffoonery. Take your simpleton brain somewhere else";

    string reasonPond = "Got relaxed. Maybe a little too relaxed...";

    string reasonBadInput = "Pissed off the wrong person.";

    string reasonGodred = "Don't say his name.";

    string reasonLowIQ = "Frankly, I'm stunned at how moronic you are.";

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

    string scene1d2c2 = "Going right, you travel the path carved through the water. You notice sticks pointing in different "
                        "directions, marked with rocks guiding you. Eventually, you end up at a village? Despite how "
                        "ludicrous it seems, there is clearly a village in front of you. However, you are not afforded "
                        "much time to be in awe, as you are quickly surrounded by villagers who all have spears aimed at "
                        "your throat.";

    string scene1d3 = "The village elder emerges, masked from head to toe in gorgeous apparel with a feathery touch to "
                      "every piece, appearing almost like an apex predator bird coming down upon its prey. \"Who are you "
                      "and what is your business?\" he asks.";

    string scene1d3c = "1. \"A simple adventurer I mean no harm to you and your people\"\n2. \"Godred.\"";

    string scene1d3c1 = "\"Many of you have passed through these marshlands,\" he states, \"yet so many always return empty "
                        "handed. Adventurer, tell me, are you after the same thing they all seek?\" he asks, \"If so, let it "
                        "be known that you cannot and will not succeed.\" Plain as day, he tells you that you cannot "
                        "succeed on your quest. But that can't be this whole adventure. You refuse. You will not return "
                        "empty handed. A fire in your stomach has been lit and you refuse to let it die. \"Yet even after"
                        " I tell you this… I can see the spark behind your eyes,\" he states. \"Men, lower your weapons. "
                        "I wish to speak to this man and make him understand why he will lose,\" he commands. You are "
                        "urged to his hut where he invites you inside to a one on one chat.";

    string scene1d3c2 = "Upon hearing the name of the one down below, they all shake, as his name has not been uttered in "
                        "ages. The ground shakes, and you see the sun turn bright red. The warriors once surrounding "
                        "you are gone. The world around you is dark, the sun is gone and you are met with his"
                        " grace. You grovel at what you perceive to be his feet and beg to not be taken so early, but "
                        "instead not a word is said as his expressionless void of a face stares at you, as your world "
                        "turns completely dark, as your clothes remain behind for the villagers to see. ";

    string scene1d4 = "\"I apologize for the way you were treated upon stumbling upon our village, but surely you "
                      "understand. Our village is one of many in these beautiful lands. We all have a copy of each "
                      "other's gems as a form of peace treaty. Blue is us, green is Pluchiase, orange is Guranchase, "
                      "and purple is Mangiolo follow after, Do you comprehend what I'm saying?\"\n";

    string scene1d4scroll = "You take in the information, recall the scroll, and link the cities and gems to the riddle "
                            "on the scroll.";

    string scene1d4noScroll = "You do not quite understand what he is getting at, however, you do realize you are a bit "
                              "hungry and could really use a whole chicken breast, as that's all you've been thinking about "
                              "and smelling since you arrived.";

    string scene1d4continued = "\"Regardless if you do, I must ask the elephant in the room, \"What are your intentions "
                               "with the temple?\"";

    string scene1d4c = "1.Seeking the immense riches\n2.Immortality from the fountain within\n3.Glory for finding and "
                       "entering the temple.";

    string scene1d5 = "\"I see. So be it, as many have done before. I can offer you the necessary materials to enter the "
                      "temple, however, be warned young adventurer. What lies in there is not for the faint of heart, "
                      "and you will be tested beyond belief, but and at the end lies what you have been waiting for.\" "
                      "he states. \"Now be on your way from this village. Take a left and follow the ancient path to the "
                      "temple and take on the challenge you seek.\"\n\nNow set on your way and with the gems in hand, you "
                      "begin to ponder. Is this worth what lies at the end? Can you stand up to the difficulties ahead? "
                      "Nevertheless you must press on. Following the instructions, you end up at the fork in the road.";

    string scene1d5c = "1. Left like you were told\n2. Forward\n3. Right ";

    string scene1d5c1 = "Following the instructions the elder gave you, walking amongst endless wetland and trees that "
                        "provide excellent shade for you and any predator that may be lurking in them, you cautiously "
                        "tread. You arrive at an empty field, which is odd to you, considering the village elder mentioned "
                        "a temple. You notice a pattern on the floor that leads to different pillars. Each pillar marked "
                        "with a symbol that represents a city. You figure it is a puzzle and the only way to enter the "
                        "temple.";

    string scene1d5c2 = "You once again show your ineptness to follow instructions and head the complete wrong way, "
                        "despite being instructed on where to go. Except this time, the way is tangled and confusing, "
                        "much like the tree roots you run around. Confused, desperate, and losing hope, you wander "
                        "straight into a den of lit up eyes. You know full well what this means, yet you have only "
                        "yourself to blame. Your handgun is powerful, but only limited by its bullets in its chambers. "
                        "You brace yourself as you count more lit up eyes than you can handle, and pray for salvation.";


public:
    void textBreak() {
        displayText(breakText, STANDARD_DELAY, 1);
        cin.get();
        cin.ignore(1, '\n');
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

    friend class Player;
    friend class Logic;
};
class Player { /// Player class, constructor values exist because this class is only created
    int hp;    /// when the game is started.
    bool scrollChecked;
    int lastDecision;
public:
    Player() {
        scrollChecked = 0;
        lastDecision = 0;
    }
    void setScrollStatus() {
        scrollChecked = 1;
    }
    friend class Text;
    friend class Logic;
};

class Logic : private Text, private Player { /// Kinda genius play for functions that read both Text and Player vals
public:
    Logic() {
        displayText(introText, STANDARD_DELAY, 1);
        transition();
    }

    void gameOver(int deathReason) {
        char continueChoice = 'J';
        displayText(gameOverStr, 50, 1000);
        switch (deathReason) {
            case simpleton:
                displayText(reasonSimple, STANDARD_DELAY, 1000);
                break;
            case pond:
                displayText(reasonPond, STANDARD_DELAY, 1000);
                break;
            case narrator:
                displayText(reasonBadInput, STANDARD_DELAY, 1000);
                break;
            case godred:
                displayText(reasonGodred, STANDARD_DELAY, 1000);
                break;
        }
        displayText(continueText, STANDARD_DELAY, 1);
        cin >> continueChoice;
        if (continueChoice == 'Y') {
            switch (lastDecision) {
                case 1:
                    scene1();
                    break;
                case 2:
                    decision2();
                    break;
                case 3:
                    decision3();
                    break;
            }
            lastDecision--;
        } else {
            displayText(exitText, STANDARD_DELAY, 500);
        }
        textBreak();
    }

    void whatWillYouDo(int decisionType) {
        switch(decisionType) {
            case action:
                displayText(userPromptBegin, STANDARD_DELAY, 250);
                break;
            case dialogue:
                displayText(userPromptBeginDialogue, STANDARD_DELAY, 250);
                break;
        }
        lastDecision++;
    }


    int readInput() {
        int badChoiceCounter = 0;
        int choice = 0;
        cin >> choice;
        while (choice != 1 && choice != 2 && choice != 3) {
            if (badChoiceCounter > 3) {
                displayText(repeatedBadInput, STANDARD_DELAY, 1);
                gameOver(narrator);
                break;
            } else {
                displayText(badInput, STANDARD_DELAY, 1);
                badChoiceCounter++;
            }
            cin >> choice;
        }
        return choice;
    }

    void scene1() {
        displayText(scene1d1, STANDARD_DELAY, 1);
        whatWillYouDo(action);
        displayText(scene1d1c, STANDARD_DELAY, 250);
        switch (readInput()) {
            case 1:
                displayText(scene1d1c1, 20, 250);
                setScrollStatus();
                textBreak();
            case 2:
                displayText(scene1d1c2, STANDARD_DELAY, 1);
                decision2();
                break;
        }
    }
    void decision2() {
        displayText(scene1d2, STANDARD_DELAY, 1);
        whatWillYouDo(action);
        displayText(scene1d2c, STANDARD_DELAY, 250);
        switch (readInput()) {
            case 1:
                displayText(scene1d2c1, STANDARD_DELAY, 1);
                gameOver(pond);
                break;
            case 2:
                displayText(scene1d2c2, STANDARD_DELAY, 1);
                break;
            case 3:
                displayText(scene1d2c3, STANDARD_DELAY, 1);
                gameOver(simpleton);
                break;
        }
    }
    void decision3() {
        displayText(scene1d3, STANDARD_DELAY, 1);
        whatWillYouDo(dialogue);
        displayText(scene1d3c, STANDARD_DELAY,1);
        switch (readInput()) {
            case 1:
                displayText(scene1d3c1, STANDARD_DELAY, 1);
                decision4();
                break;
            case 2:
                displayText(scene1d3c2, STANDARD_DELAY,1);
                gameOver(godred);
                break;
        }
    }
    void decision4() {
        displayText(scene1d4, STANDARD_DELAY, 1);
        if (scrollChecked == 0) {
            displayText(scene1d4noScroll, STANDARD_DELAY, 1);
        } else {
            displayText(scene1d4scroll, STANDARD_DELAY, 1);
        }
        displayText(scene1d4continued, STANDARD_DELAY, 1);
        whatWillYouDo(dialogue);
        displayText(scene1d4c, STANDARD_DELAY, 250);
        readInput();
        decision5();
    }

    void decision5() {
        displayText(scene1d5, STANDARD_DELAY, 1);
        whatWillYouDo(dialogue);
        displayText(scene1d5c, STANDARD_DELAY, 250);
        switch (readInput()) {
            case 1:
                displayText(scene1d5c1, STANDARD_DELAY, 1);
                break;
            case 2:
                displayText(scene1d5c2, STANDARD_DELAY, 1);
                gameOver(lowIQ);
                break;
            case 3:
                displayText(scene1d5c2, STANDARD_DELAY, 1);
                gameOver(lowIQ);
                break;
        }
    }

};

/* Function Definitions */
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

int main() {
    Player player;
    Text text;
    Logic logic;
    logic.scene1();
    return 0;
}

/// Shoutouts 45 moment 2