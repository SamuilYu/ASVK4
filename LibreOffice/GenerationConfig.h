#ifndef SASVK4_GENERATIONCONFIG_H
#define SASVK4_GENERATIONCONFIG_H
#include <string>
#include <map>
#include <utility>
#include <stdexcept>

enum AlphabetType {Latin, Cyrillic, Mixed};

class GenerationConfig {
private:
    int numberOfWords = 0;
    int maxNumOfLetters = 0;
    AlphabetType alphabet = Latin;
public:
    void setNumberOfWords(int num) { numberOfWords = num; }
    int getNumberOfWords() { return numberOfWords; }

    void setMaxNumOfLetters(int num) { maxNumOfLetters = num; }
    int getMaxNumOfLetters() { return maxNumOfLetters; }

    void setAlphabet(AlphabetType alpha) { alphabet = alpha; }
    AlphabetType getAlphabet() { return alphabet; }
};

std::string generateText(GenerationConfig config);
std::string generateWord(AlphabetType alphabet, int length);

#endif //SASVK4_GENERATIONCONFIG_H
