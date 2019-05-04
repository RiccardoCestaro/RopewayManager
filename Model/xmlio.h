#ifndef XMLIO_H
#define XMLIO_H

#include "container.h"
#include "deepptr.h"
#include "Gerarchia/impianto.h"
class XmlIO {
public:
    static Container<DeepPtr<Impianto>> read(string filename);
    static void write(const Container<DeepPtr<Impianto>>&,string filename);
};

#endif // XMLIO_H
