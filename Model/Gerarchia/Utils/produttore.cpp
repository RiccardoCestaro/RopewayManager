#include "produttore.h"

QStringList Produttore::values = {"Leitner", "Doppelmayr", "Agudio", "Zemella", "Graffer", "Agamatic", "Poma", "Nascivera",
                                    "Bartholet", "Garaventa","Hölzl", "Marchisio", "Ceretti Tanfani"};

/**
 * @brief RopewayUtils::Produttore::Produttore
 * @param p
 *
 * Costruttore tramite std::string
 */
Produttore::Produttore(const std::string& p)
    : value(static_cast<short>(values.indexOf(QString::fromStdString(p),Qt::CaseInsensitive))) {}

/**
 * @brief RopewayUtils::Produttore::Produttore
 * @param p
 *
 * Costruttore tramite const char[]
 */
Produttore::Produttore(const char p[])
    : value(static_cast<short>(values.indexOf(QString::fromStdString(p),Qt::CaseInsensitive))) {}

/**
 * @brief RopewayUtils::Produttore::Produttore
 * @param p
 *
 * Costruttore tramite const char[]
 */
std::string Produttore::toString() const{
    return values.at(value).toStdString();
}

/**
 * @brief operator <<
 * @param os
 * @param a
 * @return p.values[p.value]
 *
 * Ridefinizione dell'operatore di output. Permette di eseguire una
 * stampa dell'oggetto
 */
std::ostream& operator<<(std::ostream& os, const Produttore& p){
    return os << p.values.at(p.value).toStdString();
}
