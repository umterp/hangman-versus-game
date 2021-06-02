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

//static variables
const int SPACE_ASCII_VALUE = 32;
const string GUESS_PHRASES[5] = {"a short fuse","butterflies in my stomach",
                                "cat got your tongue","boy who cried wolf","cut me some slack"};

class Player {
    public:
        string name;
        int numGuesses;
        int numStrikes;
        bool isWinner;
    
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

char getGuess(string &guessStripped, string playerName) {
    string guess ("");
    bool isValid = false;
    regex str_expr ("[a-zA-Z]{1}");
    cout << "Solve: " << guessStripped << endl;
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
    for (it = guessPhrase.begin(); it != guessPhrase.end(); it++) {
        if (int(*it) == int(guessChar)) {
            cout << "Char: " << guessChar << endl;
            tempGuessStripped.push_back(guessChar);
            tempGuessStripped.append(" ");
            cout << tempGuessStripped << endl;
            numMatches++;
        } else if (int(*it) == SPACE_ASCII_VALUE) {
            tempGuessStripped.append("  ");
        } else {
            tempGuessStripped.append("_ ");
        }
    }
    *guessStripped = tempGuessStripped;
    if (numMatches > 0) {
        player->numStrikes++;
    }
    cout << tempGuessStripped << endl;
    return numMatches;
}