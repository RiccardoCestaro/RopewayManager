#include "ammorsamento.h"

#include "Model/Gerarchia/Utils/ropewayutils.h"
#include "Model/invalidstringtoenumexception.h"

/**
 * Array std::string statico.
 * Contiene l'ammorsamento di un impianto di risalita
 */
QStringList Ammorsamento::values = {"fisso","automatico"};

/**
 * @brief RopewayUtils::Ammorsamento::Ammorsamento
 * @param s
 *
 * Costruttore tramite std::string
 */
Ammorsamento::Ammorsamento(const std::string& s) :
    value(RopewayUtils::compareString(s,values.at(1).toStdString()) ? 1 : (RopewayUtils::compareString(s,values.at(0).toStdString()) ? 0 : throw (InvalidStringToEnumException()))){}

/**
 * @brief RopewayUtils::Ammorsamento::Ammorsamento
 * @param s
 *
 * Costruttore tramite const char[]
 */
Ammorsamento::Ammorsamento(const char d[]) :
    value(RopewayUtils::compareString(d,values.at(1).toStdString()) ? 1 : (RopewayUtils::compareString(d,values.at(0).toStdString()) ? 0 : throw (InvalidStringToEnumException()))){}

/**
 * @brief RopewayUtils::Ammorsamento::toString
 *
 * Metodo ritornante la stringa del corrispondente valore booleano
 */

std::string Ammorsamento::toString() const{
    return values.at(value).toStdString();
}

/**
 * @brief operator <<
 * @param os
 * @param a
 * @return a.values[a.value]
 *
 * Ridefinizione dell'operatore di output. Permette di eseguire una
 * stampa dell'oggetto
 */
std::ostream& operator<<(std::ostream& os, const Ammorsamento& a){
    return os << a.values.at(a.value).toStdString();
}
