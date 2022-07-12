#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>


#define MAX_GUESSES 6
#define MAX_WORD_LENGTH 5
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"


typedef std::string string;
typedef std::fstream file;

typedef std::initializer_list<string> strInitList;
typedef std::vector<string> strvec;
typedef std::map<char, int> map;



strvec getWords() {
    string tempWord;
    strvec wordVector;
    file f;
    f.open("words.txt", std::ios::in);
    while (std::getline(f, tempWord)) {
        if (tempWord.length() > MAX_WORD_LENGTH || tempWord.length() < MAX_WORD_LENGTH) {
            continue;
        } else {
            wordVector.push_back(tempWord);
        }
    }
    f.close();
    return wordVector;
}

map getCharCount(string word) {
    map charCountMap;
    for (char c : word) {
        c = toupper(c);
        if (charCountMap.find(c) == charCountMap.end()) {
            charCountMap[c] = 1;
        } else {
            charCountMap[c]++;
        }
    }
    return charCountMap;
}

string joinString(strvec str, string str2) {
    string result = "";
    for (string chr : str) {
        result += chr;
        result += str2;
    }
    return result;
}

string connectWord (char c, strInitList str) {
    string result = "" + *(str.begin()) + c + *(str.begin() + 1);
    return result;
}



string generateColoredWord(string guessedWord, string actualWord) {
    map charCountMap = getCharCount(actualWord);
    strvec result(MAX_WORD_LENGTH);
    for (int i = 0; i < guessedWord.length(); i++) {
        string tmpStr = "";
        char tmpChr = toupper(guessedWord[i]);
        if (guessedWord[i] == actualWord[i]) {
            result[i] = connectWord(tmpChr, {GREEN, RESET});
            charCountMap[tmpChr]--;
        }
    }
    for (int i = 0; i < guessedWord.length(); i++) {
        string tmpStr = "";
        char tmpChr = toupper(guessedWord[i]);
         if (
            actualWord.find(guessedWord[i]) != string::npos 
            && 
            charCountMap[tmpChr] > 0
            && 
            result[i].length() == 0
        ) {
            result[i] = connectWord(tmpChr, {YELLOW, RESET});
            charCountMap[tmpChr]--;
        } else if (actualWord[i] != guessedWord[i]) {
            result[i] = connectWord(tmpChr, {RED, RESET});
        }
    }
    return joinString(result, " ");
}

string generateWordBox(string actualWord, int guessed, strvec guessedWords) {
    string result = "=============\n";
    int loopInvariant = MAX_GUESSES - guessed;
    for (int i = 0; i < guessed; i++) {
        result += "| ";
        string tempWord = generateColoredWord(guessedWords[i], actualWord);
        result += tempWord + "|\n";
    }

    for (int i = 0; i < loopInvariant; i++) {
        result += "|";
        result += " _ _ _ _ _ ";
        result += "|\n";
    }
    result += "=============";
    return result;
}

string getString(string prompt) {
    string result;
    std::cout << prompt;
    std::getline(std::cin >> std::ws, result);
    return result;
}