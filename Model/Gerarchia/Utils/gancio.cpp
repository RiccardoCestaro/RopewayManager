#include "gancio.h"

#include "Model/Gerarchia/Utils/ropewayutils.h"
#include "Model/invalidstringtoenumexception.h"

/**
 * Array std::string statico.
 * Contiene i possibili ganci di una sciovia
 */
QStringList Gancio::values = {"piattello","ancora"};

/**
 * @brief Gancio::Gancio
 * @param g
 *
 * Costruttore tramite std::string
 */
Gancio::Gancio(const std::string& g) :
    value(RopewayUtils::compareString(g,values.at(1).toStdString()) ? 1 : (RopewayUtils::compareString(g,values.at(0).toStdString()) ? 0 : throw(InvalidStringToEnumException()))){}

/**
 * @brief Gancio::Gancio
 * @param g
 *
 * Costruttore tramite const char[]
 */
Gancio::Gancio(const char g[]) :
    value(RopewayUtils::compareString(g,values.at(1).toStdString()) ? 1 : (RopewayUtils::compareString(g,values.at(0).toStdString()) ? 0 : throw(InvalidStringToEnumException()))){}

/**
 * @brief RopewayUtils::Gancio::toString
 *
 * Metodo ritornante la stringa del corrispondente valore booleano
 */
std::string Gancio::toString() const{
    return values.at(value).toStdString();
}

/**
 * @brief operator <<
 * @param os
 * @param g
 * @return g.values[g.value]
 *
 * Ridefinizione dell'operatore di output. Permette di eseguire una
 * stampa dell'oggetto
 */
std::ostream& operator<<(std::ostream& os, const Gancio& g){
    return os << g.values.at(g.value).toStdString();
}
