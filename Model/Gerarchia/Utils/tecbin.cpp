#include "tecbin.h"

#include "Model/Gerarchia/Utils/ropewayutils.h"
#include "Model/invalidstringtoenumexception.h"

/**
 * Array std::string statico.
 * Contiene la maodalita' di operazione di un funicolare
 */
QStringList TecBin::values = {"doppio","unico"};

/**
 * @brief RopewayUtils::TecBin::TecBin
 * @param s
 *
 * Costruttore tramite std::string
 */
TecBin::TecBin(const std::string& s) :
    value(RopewayUtils::compareString(s,values.at(1).toStdString()) ? 1 : (RopewayUtils::compareString(s,values.at(0).toStdString()) ? 0 : throw (InvalidStringToEnumException()))){}

/**
 * @brief RopewayUtils::TecBin::TecBin
 * @param s
 *
 * Costruttore tramite const char[]
 */
TecBin::TecBin(const char s[]) :
    value(RopewayUtils::compareString(s,values.at(1).toStdString()) ? 1 : (RopewayUtils::compareString(s,values.at(0).toStdString()) ? 0 : throw (InvalidStringToEnumException()))){}

/**
 * @brief RopewayUtils::TecBin::toString
 *
 * Metodo ritornante la stringa del corrispondente valore booleano
 */
std::string TecBin::toString() const{
    return values.takeAt(value).toStdString();
}

/**
 * @brief operator <<
 * @param os
 * @param t
 * @return t.values[t.value]
 *
 * Ridefinizione dell'operatore di output. Permette di eseguire una
 * stampa dell'oggetto
 */
std::ostream& operator<<(std::ostream& os, const TecBin& t){
    return os << t.values.takeAt(t.value).toStdString();
}
