#include "GenerationConfig.h"
#include <cstdlib>
#include <ctime>

#include <sal/types.h>

#include <cppuhelper/queryinterface.hxx>

#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>

#include <com/sun/star/frame/XComponentLoader.hpp>

#include <com/sun/star/text/XTextDocument.hpp>
#include <com/sun/star/text/XTextTable.hpp>
#include <com/sun/star/text/XText.hpp>
#include <com/sun/star/frame/Desktop.hpp>

#include <com/sun/star/table/XCell.hpp>
#include <com/sun/star/table/XTable.hpp>



using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::beans;
using namespace com::sun::star::frame;
using namespace com::sun::star::text;
using namespace com::sun::star::table;

std::map<AlphabetType, std::u16string> myAlphabets {
        std::make_pair(Latin, u"AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz"),
        std::make_pair(Cyrillic, u"АаБбВвГгДдЕеЁёЖжЗзИиЙйКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщЪъЫыЬьЭэЮюЯя"),
        std::make_pair(Mixed, u"AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZzАаБбВвГгДдЕеЁёЖжЗзИиЙйКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщЪъЫыЬьЭэЮюЯя")
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

void newDocumentAndGenerateText(Reference<XComponentContext> xContext, GenerationConfig config) {
    Reference <XMultiComponentFactory> xServiceManager = xContext->getServiceManager();
    Reference <XInterface> xDesktop = xServiceManager->createInstanceWithContext(rtl::OUString("com.sun.star.frame.Desktop"),
                                                                                 xContext);
    Reference <XDesktop2> xDesktop2(xDesktop, UNO_QUERY);
    Reference <XComponent> xComponent = xDesktop2->loadComponentFromURL(
            rtl::OUString("private:factory/swriter"), // URL to the ods file
            rtl::OUString("_blank"), 0,
            Sequence<::com::sun::star::beans::PropertyValue>());
    Reference <XTextDocument> text_document(xComponent, UNO_QUERY);
    Reference <XText> text = text_document->getText();
    Reference <XTextRange> textEnd = text->getEnd();
    rtl::OUString newText = generateText(config);
    textEnd -> setString(newText+"\n");
}

std::map<int, int> collectStatistics(rtl::OUString text) {
    int i = 0;
    int size = 0;
    std::map<int, int> res;
    while (i < text.getLength()) {
        if (myAlphabets[Mixed].find(text[i]) != -1) {
            size++;
        } else if (size != 0) {
            if (res.find(size) != res.end()) {
                res[size]++;
            } else {
                res[size] = 1;
            }
            size = 0;
        }
        i++;
    }
    if (size != 0) {
        if (res.find(size) != res.end()) {
            res[size]++;
        } else {
            res[size] = 1;
        }
        size = 0;
    }
    return res;
}

void createStatisticsTable(Reference<XTextDocument> text_document) {
    Reference <XText> text = text_document->getText();
    auto stat = collectStatistics(text -> getString());

    Reference <XTextTable> table = createTable(text_document, stat.size() + 1, 2);

    Reference <XTextRange> text_range = text -> getEnd();
    Reference <XTextContent> text_content(table, UNO_QUERY);
    text->insertTextContent(text_range, text_content, (unsigned char) 0);

    fillTable(table, stat);
}

Reference <XTextTable> createTable(Reference<XTextDocument> text_document, int num_of_row, int num_of_col) {
    Reference <XMultiServiceFactory> document(text_document, UNO_QUERY);
    Reference <XTextTable> table(document->createInstance(rtl::OUString::createFromAscii("com.sun.star.text.TextTable")), UNO_QUERY);
    table -> initialize(num_of_row, num_of_col);
    return table;
}

std::string createName(uint32_t column, uint32_t row) {
    return (char)('A' + column) + std::to_string(row + 1);
}

void fillTable(Reference <XTextTable> table, std::map<int, int> stat) {
    Reference<XCell> cell1 = table->getCellByName(rtl::OUString("A1"));
    Reference<XText> cell_text1(cell1, UNO_QUERY);
    rtl::OUString cellVal1("Word length");
    cell_text1 -> setString(cellVal1);

    Reference<XCell> cell2 = table->getCellByName(rtl::OUString("B1"));
    Reference<XText> cell_text2(cell2, UNO_QUERY);
    rtl::OUString cellVal2("Count");
    cell_text2 -> setString(cellVal2);

    for (int x = 0; x < 2; x++) {
        int y = 1;
        for (auto pair: stat) {
            Reference<XCell> cell = table->getCellByName(rtl::OUString::createFromAscii(createName(x, y).c_str()));
            Reference<XText> cell_text(cell, UNO_QUERY);
            rtl::OUString cellVal = rtl::OUString::createFromAscii((std::to_string((x == 0) ? pair.first : pair.second)).c_str());
            cell_text -> setString(cellVal);
            y++;
        }
    }
}

bool hasMixedLetters(rtl::OUString word) {
    bool hasLatin = false;
    bool hasCyrillic = false;
    if (word.getLength() == 0)
        return false;
    for (int i = 0; i < word.getLength(); i++) {
        for(auto letter: myAlphabets[Latin])
            if (word[i] == letter) {
                hasLatin = true;
                break;
            }
        for(auto letter: myAlphabets[Cyrillic])
            if (word[i] == letter) {
                hasCyrillic = true;
                break;
            }
        if (hasCyrillic && hasLatin)
            return true;
    }
    return false;
}

bool hasOnlyLetters(rtl::OUString word) {
    bool isLetter = false;
    if (word.getLength() == 0)
        return true;
    for (int i = 0; i < word.getLength(); i++) {
        for(auto letter: myAlphabets[Mixed])
            if (word[i] == letter) {
                isLetter = true;
                break;
            }
        if (!isLetter)
            return false;
        isLetter = false;
    }
    return true;
}

bool hasNoLetters(rtl::OUString word) {
    bool isLetter = false;
    if (word.getLength() == 0)
        return true;
    for (int i = 0; i < word.getLength(); i++) {
        for(auto letter: myAlphabets[Mixed])
            if (word[i] == letter) {
                isLetter = true;
                break;
            }
        if (isLetter)
            return false;
        isLetter = false;
    }
    return true;
}

void highlight(Reference<XTextDocument> text_document) {
    bool hasTable = false;
    Reference <XText> text = text_document->getText();
    int size = (text -> getString()).getLength();
    Reference <XTextCursor> cursor = text -> createTextCursor();
    int i = 0;
    while (true) {
        hasTable = false;
        rtl::OUString previousString;
        while(hasOnlyLetters(cursor -> getString()) && i < size) {
            previousString = cursor -> getString();
            cursor -> goRight(1, true);
            rtl::OUString newString = cursor -> getString();
            i++;
            if (newString.getLength() != (previousString.getLength() + 1)) {
                hasTable = true;
                break;
            }
        }
        if (i < size) {
            cursor -> goLeft(1, true);
            i--;
        }
        if (hasMixedLetters(cursor -> getString())) {
            Reference <XPropertySet> properties(cursor, UNO_QUERY);
            properties -> setPropertyValue("CharColor", makeAny(255 * 65536));
        }
        cursor -> collapseToEnd();
        if (hasTable) {
            cursor -> goRight(1, true);
            i += (cursor -> getString()).getLength();
            cursor -> collapseToEnd();
            continue;
        }
        while (hasNoLetters(cursor -> getString()) && i < size) {
            previousString = cursor -> getString();
            cursor -> goRight(1, true);
            rtl::OUString newString = cursor -> getString();
            i++;
            if (newString.getLength() != (previousString.getLength() + 1)) {
                hasTable = true;
                break;
            }
        }
        if (i < size) {
            cursor -> goLeft(1, true);
            i--;
        }
        cursor -> collapseToEnd();
        if (hasTable) {
            cursor -> goRight(1, true);
            i += (cursor -> getString()).getLength();
            cursor -> collapseToEnd();
            continue;
        }
        if(i >= size)
            break;
    }
}


