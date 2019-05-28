#include "Model/Gerarchia/Utils/ropewayutils.h"
#include "Model/invalidstringtoenumexception.h"

#include <QRegExp>


/**
 * @brief RopewayUtils::compareString
 * @param str1
 * @param str2
 * @return boolean
 *
 * Lambda espressione per confrontare due stringhe in modo case insensitive
 */
bool RopewayUtils::compareString(const std::string& str1,const std::string& str2){
    return ((str1.size() == str2.size()) && std::equal(str1.begin(), str1.end(), str2.begin(), [](const char & c1, const char & c2){
                            return (c1 == c2 || std::toupper(c1) == std::toupper(c2));
    }));
}







