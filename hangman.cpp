#include <iostream>
#include <string>
#include <cstdlib>  
#include <ctime>    
#include <cctype>    
using namespace std;

// Draws the hangman
// the mistakes into a stage from 0 to 6, whatever the max lives are.
void drawHangman(int wrongCount, int maxLives) {
    int stage = (wrongCount * 6 + maxLives - 1) / maxLives;

    cout << "  +---+" << endl;
    cout << "  |   |" << endl;

    if (stage >= 1) cout << "  |   O" << endl;
    else            cout << "  |" << endl;

    if (stage == 2)      cout << "  |   |" << endl;
    else if (stage == 3) cout << "  |  /|" << endl;
    else if (stage >= 4) cout << "  |  /|\\" << endl;
    else                 cout << "  |" << endl;

    if (stage == 5)      cout << "  |  /" << endl;
    else if (stage >= 6) cout << "  |  / \\" << endl;
    else                 cout << "  |" << endl;

    cout << "  |" << endl;
    cout << "=====" << endl;
}

// Plays ONE round with the given number of lives
void playRound(int maxLives) {
    // a predefined list of words, one chosen at random
    const int WORD_COUNT = 10;
    string words[WORD_COUNT] = {"tiger", "elephant", "giraffe", "dolphin",
                                "penguin", "rabbit", "monkey", "turtle",
                                "zebra", "camel"};
    string word = words[rand() % WORD_COUNT];

    string display = string(word.size(), '_');
    string incorrect = "";
    string guessed = "";
    int guessesLeft = maxLives;

    cout << "\nHint: the word is an animal." << endl;

    while (guessesLeft > 0 && display != word) {

        cout << endl;
        drawHangman(maxLives - guessesLeft, maxLives);
        cout << "Word: " << display << endl;
        cout << "Incorrect Guesses: " << incorrect << endl;
        cout << "Guesses Left: " << guessesLeft << endl;

        string input;
        cout << "Guess a letter: ";
        cin >> input;

        if (input.size() != 1 || !isalpha(input[0])) {
            cout << "Please type a single letter." << endl;
            continue;
        }

        char letter = tolower(input[0]);

        if (guessed.find(letter) != string::npos) {
            cout << "You already guessed that!" << endl;
            continue;
        }
        guessed = guessed + letter;

        bool found = false;
        for (int i = 0; i < word.size(); i++) {
            if (word[i] == letter) {
                display[i] = letter;
                found = true;
            }
        }

        if (found == false) {
            guessesLeft = guessesLeft - 1;
            incorrect = incorrect + letter + " ";
        }
    }

    cout << endl;
    if (display == word) {
        cout << "Congratulations! You guessed the word \""
             << word << "\" correctly!" << endl;
    } else {
        drawHangman(maxLives - guessesLeft, maxLives);
        cout << "Game over! The word was \"" << word << "\"." << endl;
    }
}

// Asks the player for a difficulty and returns the number of lives
int chooseDifficulty() {
    cout << "\nChoose a difficulty:" << endl;
    cout << "  1. Easy   (8 wrong guesses allowed)" << endl;
    cout << "  2. Medium (6 wrong guesses allowed)" << endl;
    cout << "  3. Hard   (4 wrong guesses allowed)" << endl;

    while (true) {
        string input;
        cout << "Your choice: ";
        cin >> input;

        if (input == "1") return 8;
        if (input == "2") return 6;
        if (input == "3") return 4;

        cout << "Please type 1, 2 or 3." << endl;
    }
}
int main() {
    srand(time(0));   // called ONCE, so every round gets a different word
    cout << "Welcome to Hangman!" << endl;
    char again;
    do {
        int lives = chooseDifficulty();
        playRound(lives);
        cout << "\nPlay another round? (y/n): ";
        cin >> again;
    } while (again == 'y' || again == 'Y');
    cout << "Thanks for playing!" << endl;
    return 0;
}
