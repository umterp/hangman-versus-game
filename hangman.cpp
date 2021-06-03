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
string getGuess(string &guessStripped, string playerName);
int getFoundWinningGuess(Player *player, string &guessPhrase, string *guessStripped, char guessChar);
void getPlayersList(int numPlayers, Player *players);

//static variables
int MAX_TRIES = 5;

int main() {
    bool isWinner = false;

    string guessPhrase (getPhraseForGame());
    string blankGuess (stripLettersFromAnswer(guessPhrase));
    string *guessStripped = &blankGuess;

    int numPlayers = getNumPlayers();
    
    Player newPlayers[numPlayers];
    Player *players = newPlayers;
    
    getPlayersList(numPlayers, players);

    // continue allowing players to guess in sequential order until a winner is determined
    while (!isWinner) {
        for (int i =0; i < numPlayers; i++) {
            Player player = *(players + i);
            string guessChar = getGuess(*guessStripped, player.name);
            isWinner = getFoundWinningGuess(&player, guessPhrase, guessStripped, guessChar);
            if (isWinner) {
                break;
            }
        }
    }
    
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
