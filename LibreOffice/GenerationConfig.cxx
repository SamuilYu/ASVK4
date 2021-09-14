#include "GenerationConfig.h"
#include <cstdlib>
#include <ctime>

#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>

#include <com/sun/star/frame/XComponentLoader.hpp>

#include <com/sun/star/text/XTextDocument.hpp>
#include <com/sun/star/text/XText.hpp>
#include <com/sun/star/frame/Desktop.hpp>

using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::beans;
using namespace com::sun::star::frame;
using namespace com::sun::star::text;

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
    textEnd -> setString(newText);
}

