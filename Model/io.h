#ifndef XMLIO_H
#define XMLIO_H

#include "container.h"
#include "deepptr.h"
#include "Gerarchia/impianto.h"

/**
 * @brief The IO class
 *
 * Inizializza la scrittura e la lettura di un file XML.
 */
class IO {
private:
    typedef Container<DeepPtr<Impianto>> deep_vector;
public:
    static deep_vector read(string filename);
    static void write(const deep_vector&,string filename);
};

#endif // XMLIO_H
