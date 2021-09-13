#include "GenerationConfig.h"

std::map<AlphabetType, std::string> myAlphabets{
        std::make_pair(Latin, "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz"),
        std::make_pair(Cyrillic, "АаБбВвГгДдЕеЁёЖжЗзИиКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщЪъЫыЬьЭэЮюЯя")
};

std::string generateText(GenerationConfig config) {
    throw std::runtime_error("Not Implemented");
}

