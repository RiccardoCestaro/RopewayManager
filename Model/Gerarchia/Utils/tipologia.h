#ifndef TIPOLOGIA_H
#define TIPOLOGIA_H

#include <iostream>
#include <QStringList>

/**
 * @brief The Tipologia class
 *
 * Classe contenente tutte le tipologie di
 * impianti a fune
 */
class Tipologia{
private:
    short value;

public:
   Tipologia(const std::string& = values.at(0).toStdString());
   Tipologia(const char[]);
   static QStringList values;
   friend std::ostream& operator<<(std::ostream& os, const Tipologia& g);
};

#endif // TIPOLOGIA_H
