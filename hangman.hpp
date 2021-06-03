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
const int UNDERSCORE_ASCII_VALUE = 95;
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

//utility function declarations
string formattedBlankString(string blankGuess, int strLen);
bool isSuccessfulGuessForTotalPhrase(Player *player, string guessPhrase);
bool isSuccessfulSingleGuess(Player *player, string guessPhrase, string *guessStripped, char guessChar);


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
        int(*it) == SPACE_ASCII_VALUE ? guessStripped.append(" ") : guessStripped.append("_");
    }
    return guessStripped;
}

/* TODO need to output all of the letters that have been guessed
    *  so that no letters can be repeated.
    */

string getGuess(string &guessStripped, string playerName) {
    string guess ("");
    bool isValid = false;
    regex guess_expr ("[a-zA-Z]{1}");
    regex win_expr ("[g]{2}");
    cout << "Solve: " << formattedBlankString(guessStripped, guessStripped.size()) << endl;
    while(!isValid) {
        cout << playerName << ", enter your guess: " << endl;
        cin >> guess;

        isValid = regex_match(guess, guess_expr) || regex_match(guess, win_expr);
        if (!isValid) {
            cout << "Oops, something looks wrong. Enter a single letter A-Z!" << endl;
        }
    }
    return guess;
}

bool getFoundWinningGuess(Player *player, string &guessPhrase, string *guessStripped, string guessChar) {
    bool isWinnerFound;
    if (guessChar.compare("gg") == 0) {
        isWinnerFound = isSuccessfulGuessForTotalPhrase(player, guessPhrase);
    } else {
        isWinnerFound = isSuccessfulSingleGuess(player, guessPhrase, guessStripped, guessChar[0]);
    }
    return isWinnerFound;
}

bool isSuccessfulGuessForTotalPhrase(Player *player, string guessPhrase) {
    string finalGuess;
    bool isWinnerFound;
    
    cout << "Feeling lucky, " << player->name << "? What's your answer, bub?" << endl;
    cin.ignore();
    getline(cin, finalGuess);

    transform(finalGuess.begin(), finalGuess.end(), finalGuess.begin(), ::tolower);
    isWinnerFound = guessPhrase.compare(finalGuess) == 0;
    if (isWinnerFound) {
        cout << player->name << " is the Winner!! Thanks for playing!" << endl;
        player->isWinner = true;
    } else {
        cout << "Dude.... Really??" << endl;
    }
    return isWinnerFound;
}

bool isSuccessfulSingleGuess(Player *player, string guessPhrase, string *guessStripped, char guessChar) {
    int numMatches = 0;
    string tempGuessStripped ("");
    bool isUnderscorePresent;

    /* TODO need to edit this to observe the blank string as well so
    *  no already guessed letters are overwritten with blanks.
    */
    for (int i =0; i < guessPhrase.size(); i++) {
        if (guessPhrase[i] == guessChar) {
            tempGuessStripped.push_back(guessChar);
            numMatches++;
        }  else if (int(guessPhrase[i]) == SPACE_ASCII_VALUE) {
            tempGuessStripped.append(" ");
        } else if (int((*guessStripped)[i]) != UNDERSCORE_ASCII_VALUE) {
            tempGuessStripped.push_back((*guessStripped)[i]);
        } else {
            tempGuessStripped.append("_");
            isUnderscorePresent = true;
        }
    }
    if (numMatches > 0) {
        *guessStripped = tempGuessStripped;
        player->numMatches = player->numMatches + numMatches;
        player->numStrikes++;

        cout << "You got " << numMatches << " matches, " << player->name << ". Good job!" << endl;
    } else {
        cout << "Sorry, " << player->name << ", but you didn't get any matches. Try harder." << endl;
    }
    player->numGuesses++;
    return !isUnderscorePresent;
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
    for (int i = 0; i <= strLen - 1; i++) {
        tempString.push_back(blankGuess[i]);
        tempString.append(" ");
    }
    return tempString;
}