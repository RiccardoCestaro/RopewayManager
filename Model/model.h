#ifndef MODELLO_H
#define MODELLO_H

#include "container.h"
#include "deepptr.h"
#include "Gerarchia/impianto.h"
#include <vector>

/**
 * @brief The Model class
 *
 * Gestisce il contenitore con oggetti della
 * gerarchia Impianto
 */
class Model{
private:
    Container<DeepPtr<Impianto>> contenitore;
public:
    Model() = default;
    ~Model() = default;
    void saveToFile(const std::string&) const;
    void loadFromFile(const std::string&);
    unsigned int getSize() const;
    void add(Impianto*);
    void remove(unsigned int);
    Impianto* operator[] (unsigned int) const;
    Impianto* getRopeway(unsigned int) const;
    void erase();
};

#endif // MODELLO_H
