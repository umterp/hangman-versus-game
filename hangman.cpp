/*
 * @author: Christopher Mudd
 * @date: June 1, 2021
 * @description: the code for a competitive game of hangman, allowing up to 4 players per round
 */

//local libraries
#include"hangman.hpp"

//namespace
using namespace std;

//function declarations
int getNumPlayers();
string getPhraseForGame();

//static variables
int MAX_TRIES = 5;

int main() {
    bool isWinner = false;

    string guessPhrase (getPhraseForGame());
    string blankGuess (stripLettersFromAnswer(guessPhrase));
    string *guessStripped = &blankGuess;

    int numPlayers = getNumPlayers();

    cout << "Guess Phrase: " << guessPhrase << endl;
    cout << "Blank Lines for Guesses: " << blankGuess << endl;
    cout << "numPlayers: " << numPlayers << endl;
    cout << "isWinner: " << isWinner << endl;
    
    Player newPlayers[numPlayers];
    

    // continue allowing players to guess in sequential order until a winner is determined
    while (!isWinner) {
        for (int i =0; i < numPlayers; i++) {
            Player player = newPlayers[i];
            char guessChar = getGuess(*guessStripped, "test");
            int numMatches = getCompareGuess(&player, guessPhrase, guessStripped, guessChar);
            cout << "Guess: " << guessChar << endl;
            cout << "Num Matches: " << numMatches << endl;
        }
        isWinner = true;
    }

    cout << "isWinner: " << isWinner << endl;
    
    return 0;
}


/*
  +---+
  |   |
  O   |
 /|\  |
 / \  |
      |
=========''']
*/