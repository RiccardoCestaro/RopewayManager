#include "tipologia.h"


/**
 * Array std::string statico.
 * Contiene la tipologia degli impianti di risalita
 */
QStringList Tipologia::values = {"seggiovia","cabinovia","telemix","sciovia","funivia","funifor","funicolare"};

/**
 * @brief RopewayUtils::Tipologia::Tipologia
 * @param t
 *
 * Costruttore tramite std::string
 */
Tipologia::Tipologia(const std::string& t)
    : value(static_cast<short>(values.indexOf(QRegExp(QString::fromStdString(t),Qt::CaseInsensitive)))) {}

/**
 * @brief RopewayUtils::Tipologia::Tipologia
 * @param t
 *
 * Costruttore tramite const char[]
 */
Tipologia::Tipologia(const char t[])
    : value(static_cast<short>(values.indexOf(QRegExp(QString::fromStdString(t),Qt::CaseInsensitive)))) {}

/**
 * @brief operator <<
 * @param os
 * @param t
 * @return t.values[t.value]
 *
 * Ridefinizione dell'operatore di output. Permette di eseguire una
 * stampa dell'oggetto
 */
std::ostream& operator<<(std::ostream& os, const Tipologia& t){
    return os << t.values.takeAt(t.value).toStdString();
}
