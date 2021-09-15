#ifndef SASVK4_GENERATIONCONFIG_H
#define SASVK4_GENERATIONCONFIG_H
#include <string>
#include <map>
#include <utility>
#include <stdexcept>
#include <rtl/ustring.hxx>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>

using namespace com::sun::star::uno;

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

::rtl::OUString generateText(GenerationConfig config);
::rtl::OUString generateWord(AlphabetType alphabet, int length);
void newDocumentAndGenerateText(Reference<XComponentContext> xContext, GenerationConfig config);
std::map<int, int> collectStatistics(rtl::OUString text);

#endif //SASVK4_GENERATIONCONFIG_H
