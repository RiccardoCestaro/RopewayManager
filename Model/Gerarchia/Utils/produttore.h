#ifndef PRODUTTORE_H
#define PRODUTTORE_H

#include <iostream>
#include <QStringList>

/**
 * @brief The Produttore class
 *
 * Classe contenente i possibili produttori di impianti a fune
 */
class Produttore{
private:
    short value;

public:
    Produttore(const std::string& = values.at(0).toStdString());
    Produttore(const char[]);
    static QStringList values;
    std::string toString() const;
    friend std::ostream& operator<<(std::ostream& os, const Produttore& g);
};

#endif // PRODUTTORE_H
