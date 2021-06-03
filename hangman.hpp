/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

 // libraries for input and output
#include<iostream>

//string operations
#include <string>

//standard c libraries
#include<cstdlib>
#include<regex>

//time libraries
#include<ctime>

//namespace
using namespace std;

//utility function declarations
string formattedBlankString(string blankGuess, int strLen);

//static variables
const int SPACE_ASCII_VALUE = 32;
const string GUESS_PHRASES[5] = {"a short fuse","butterflies in my stomach",
                                "cat got your tongue","boy who cried wolf","cut me some slack"};

class Player {
    public:
        string name;
        int numGuesses;
        int numStrikes;
        int numMatches;
        bool isWinner;
        Player(string playerName) {
            name = playerName;
            numStrikes = 0;
            numMatches = 0;
            numGuesses = 0;
            isWinner = false;
            
        }
        Player() {
            numStrikes = 0;
            numMatches = 0;
            numGuesses = 0;
            isWinner = false;
        }
};

int getNumPlayers() {
    string numPlayersString ("0");
    bool isValid = false;
    regex str_expr ("[1-4]");
    
    while(!isValid) {
        cout << "How many players?! Enter a number 1-4" << endl;
        cin >> numPlayersString;
        isValid = regex_match(numPlayersString, str_expr);
        if (!isValid) {
            cout << "Oops, something looks wrong. Try again!" << endl;
        }
    }
    return stoi(numPlayersString);
}

string getPhraseForGame() {
    srand((unsigned) time(0));
    int randomNumber = (rand() % 5);
    return GUESS_PHRASES[randomNumber];
}

string stripLettersFromAnswer(string &guessPhrase) {
    string guessStripped ("");
    string::iterator it;
    for (it = guessPhrase.begin(); it != guessPhrase.end(); it++) {
        int(*it) == SPACE_ASCII_VALUE ? guessStripped.append("  ") : guessStripped.append("_ ");
    }
    return guessStripped;
}

/* TODO need to output all of the letters that have been guessed
    *  so that no letters can be repeated.
    */

char getGuess(string &guessStripped, string playerName) {
    string guess ("");
    bool isValid = false;
    regex str_expr ("[a-zA-Z]{1}");
    cout << "Solve: " << formattedBlankString(guessStripped, guessStripped.size()) << endl;
    while(!isValid) {
        cout << playerName << ", enter your guess: " << endl;
        cin >> guess;
        isValid = regex_match(guess, str_expr);
        if (!isValid) {
            cout << "Oops, something looks wrong. Enter a single letter A-Z!" << endl;
        }
    }
    return guess[0];
}

int getCompareGuess(Player *player, string &guessPhrase, string *guessStripped, char guessChar) {
    int numMatches = 0;
    string tempGuessStripped ("");
    string::iterator it;

    /* TODO need to edit this to observe the blank string as well so
    *  no already guessed letters are overwritten with blanks.
    */

    for (it = guessPhrase.begin(); it != guessPhrase.end(); it++) {
        if (int(*it) == int(guessChar)) {
            cout << "Char: " << guessChar << endl;
            tempGuessStripped.push_back(guessChar);
            numMatches++;
        } else if (int(*it) == SPACE_ASCII_VALUE) {
            tempGuessStripped.append(" ");
        } else {
            tempGuessStripped.append("_");
        }
    }
    *guessStripped = tempGuessStripped;
    if (numMatches > 0) {
        player->numMatches = player->numMatches + numMatches;
        player->numStrikes++;
    }
    player->numGuesses++;
    cout << tempGuessStripped << endl;
    return numMatches;
}

void getPlayersList(int numPlayers, Player *players) {
    string playerName;
    for (int i=0; i < numPlayers; i++) {
        cout << "Player " << i + 1 << ", please enter your name: " << endl;
        cin >> playerName;
        players[i] = Player(playerName);
    }
}

string formattedBlankString(string blankGuess, int strLen) {
    string tempString ("");
    for (int i=0; i < blankGuess.size(); i++) {
        tempString.push_back(blankGuess[i]);
        tempString.append(" ");
    }
    return tempString;
}