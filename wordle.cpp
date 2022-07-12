#include <iostream>
#include <algorithm>


#include "utils.h"


// The grid below represents the game grid.
// =============
// | _ _ _ _ _ |
// | _ _ _ _ _ |
// | _ _ _ _ _ |
// | _ _ _ _ _ |
// | _ _ _ _ _ |
// | _ _ _ _ _ |
// =============


int main() {
    strvec words = getWords();

    std::srand (time(0));
    int randIndex = (int) (std::rand() % words.size());
    auto wordIt = words.begin();
    std::advance(wordIt, randIndex);
    string actualWord = *wordIt;
    printf("The word is: %s\n", actualWord.c_str());
    bool isGameOver = false;
    int guessCount = 0;

    strvec guessedWords(MAX_GUESSES);

    while (!isGameOver) {
        string guess;
        printf("%sRED%s, %sYELLOW%s, %sGREEN%s\n", RED, RESET, YELLOW, RESET, GREEN, RESET);
        std::cout << generateWordBox(actualWord, guessCount, guessedWords) << std::endl;
        if (guessCount == MAX_GUESSES) {
            printf("You lost! The word was %s\n", actualWord.c_str());
            isGameOver = true;
            break;
        }
        printf("----------------------------------------------------\n");
        string guessedWord = getString("Guess word: ");
        std::transform(guessedWord.begin(), guessedWord.end(), guessedWord.begin(), ::tolower);
        printf("----------------------------------------------------\n");
        if (guessedWord.length() > MAX_WORD_LENGTH) {
            printf("Word is too long! (5 Letters only!)\n");
            printf("----------------------------------------------------\n");
            continue;
        } else if (guessedWord.length() < MAX_WORD_LENGTH) {
            printf("Word is too short! (5 Letters only!)\n");
            printf("----------------------------------------------------\n");
            continue;
        } else if (std::find(words.begin(), words.end(), guessedWord) == words.end()) {
            printf("That is not a valid word in the word list.\n");
            printf("----------------------------------------------------\n");
            continue;

        }
        std::transform(guessedWord.begin(), guessedWord.end(), guessedWord.begin(), ::tolower);
        guessedWords[guessCount] = guessedWord;
        guessCount++;

        if (guessedWord == actualWord) {
            isGameOver = true;
            std::cout << generateWordBox(actualWord, guessCount, guessedWords) << std::endl;
            printf("%sRED%s, %sYELLOW%s, %sGREEN%s\n", RED, RESET, YELLOW, RESET, GREEN, RESET);
            printf("You guessed the word!\n");
            printf("It took you %d guesses.\n", guessCount);
            printf("----------------------------------------------------\n");
            break;
        }

    }  

}
