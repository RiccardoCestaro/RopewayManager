#ifndef GANCIO_H
#define GANCIO_H

#include <iostream>
#include <QStringList>

/**
 * @brief The Gancio class
 *
 * Classe creata per indicare il tipo di Gancio
 * per gli impianti di tipo sciovia: piattello o ancora
 */
class Gancio{
private:
    short value;

public:
    Gancio(const std::string& = values.at(0).toStdString());
    Gancio(const char[]);
    static QStringList values;
    std::string toString() const;
    friend std::ostream& operator<<(std::ostream& os, const Gancio& g);
};

#endif // GANCIO_H
