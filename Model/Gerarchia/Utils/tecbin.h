#ifndef TECBIN_H
#define TECBIN_H

#include <iostream>
#include <QStringList>

/**
 * @brief The TecBin class
 *
 * Classe creata per indicare il tipo di funicolare,
 * se utilizza un binario unico oppure uno a sdoppiamento centrale
 * per consetire il transito di due carrozze
 */
class TecBin{
private:
    short value;

public:
    TecBin(const std::string& = values.at(0).toStdString());
    TecBin(const char[]);
    static QStringList values;
    std::string toString() const;
    friend std::ostream& operator<<(std::ostream& os, const TecBin& g);
};

#endif // TECBIN_H
