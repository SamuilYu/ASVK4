#ifndef SASVK4_GENERATIONCONFIG_H
#define SASVK4_GENERATIONCONFIG_H
#include <string>
#include <map>
#include <utility>
#include <stdexcept>
#include <rtl/ustring.hxx>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>
#include <com/sun/star/text/XTextDocument.hpp>
#include <com/sun/star/text/XTextTable.hpp>

using namespace com::sun::star::uno;
using namespace com::sun::star::text;

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
void createStatisticsTable(Reference<XTextDocument> text_document);
Reference <XTextTable> createTable(Reference<XTextDocument> text_document, int num_of_row, int num_of_col);
void fillTable(Reference <XTextTable> table, std::map<int, int> stat);

#endif //SASVK4_GENERATIONCONFIG_H
