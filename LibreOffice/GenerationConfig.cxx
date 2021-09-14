#include "GenerationConfig.h"
#include <cstdlib>
#include <ctime>


std::map<AlphabetType, std::u16string> myAlphabets {
        std::make_pair(Latin, u"AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz"),
        std::make_pair(Cyrillic, u"АаБбВвГгДдЕеЁёЖжЗзИиКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщЪъЫыЬьЭэЮюЯя"),
        std::make_pair(Mixed, u"AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZzАаБбВвГгДдЕеЁёЖжЗзИиКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщЪъЫыЬьЭэЮюЯя")
};

::rtl::OUString generateText(GenerationConfig config) {
    std::srand(std::time(nullptr));
    rtl::OUString fullText = "";
    for (int i = 0; i < config.getNumberOfWords(); i++) {
        int actualWordLength = std::rand() % config.getMaxNumOfLetters() + 1;
        fullText += (" " + generateWord(config.getAlphabet(), actualWordLength));
    }
    return fullText.copy(1, fullText.getLength() - 1);
}

::rtl::OUString generateWord(AlphabetType alphabet, int length) {
    rtl::OUString fullWord = "";
    for (int i = 0; i < length; i++) {
        rtl::OUString randomLetter = rtl::OUString(myAlphabets[alphabet][std::rand()%myAlphabets[alphabet].size()]);
        fullWord += randomLetter;
    }
    return fullWord;
}

