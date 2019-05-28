#ifndef AMMORSAMENTO_H
#define AMMORSAMENTO_H

#include <iostream>
#include <QStringList>

/**
 * @brief The Ammorsamento class
 *
 * Classe creata per indicare il tipo di ammorsamento
 * di un impianto a fune a movimentazione continua: fisso o automatico
 */
class Ammorsamento{
private:
    short value;

public:
    Ammorsamento(const std::string& = values.at(1).toStdString());
    Ammorsamento(const char[]);
    static QStringList values;
    std::string toString() const;
    friend std::ostream& operator<<(std::ostream& os, const Ammorsamento& g);
};

#endif // AMMORSAMENTO_H
