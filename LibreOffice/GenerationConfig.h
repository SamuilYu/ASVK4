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
    int getAlphabet() { return alphabet; }
};

std::string generateText(GenerationConfig config);

#endif //SASVK4_GENERATIONCONFIG_H
