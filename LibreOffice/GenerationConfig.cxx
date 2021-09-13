#include "GenerationConfig.h"
#include <cstdlib>
#include <ctime>

std::map<AlphabetType, std::string> myAlphabets{
        std::make_pair(Latin, "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz"),
        std::make_pair(Cyrillic, "АаБбВвГгДдЕеЁёЖжЗзИиКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщЪъЫыЬьЭэЮюЯя"),
        std::make_pair(Mixed, "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZzАаБбВвГгДдЕеЁёЖжЗзИиКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщЪъЫыЬьЭэЮюЯя")
};

std::string generateText(GenerationConfig config) {
    std::srand(std::time(nullptr));
    std::string fullText = "";
    for (int i = 0; i < config.getNumberOfWords(); i++) {
        int actualWordLength = std::rand() % config.getMaxNumOfLetters() + 1;
        fullText += (" " + generateWord(config.getAlphabet(), actualWordLength));
    }
    return fullText.substr(1, fullText.length() - 1);
}

std::string generateWord(AlphabetType alphabet, int length) {
    std::string fullWord = "";
    for (int i = 0; i < length; i++) {
        std::string randomLetter = std::string(1, myAlphabets[alphabet][std::rand()%myAlphabets[alphabet].size()]);
        fullWord += randomLetter;
    }
    return fullWord;
}

