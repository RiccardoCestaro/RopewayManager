#ifndef TELEMIX_H
#define TELEMIX_H

#include "seggiovia.h"
#include "cabinovia.h"


class Telemix : public Seggiovia, public Cabinovia{
private:

    /* Devo sapere anche la capienza delle cabine, nel caso fossero diverse da quella delle seggiole */
    short capienzaCabina;

public:
    Telemix(const unsigned short& = 0, const string& = "NoImage", const string& = "Unknown", const short& = -1, const short& = -1, const unsigned int& = 0, const unsigned int& = 0, const double& = -1,
            const float& = -1, const string& = "Unknown", const short& = -1, const bool& = false, const bool& = true);

    /* vedere se mantanere */
    unsigned int PortataOraria() const;

    /* definizione dei metodi per la non-astrazione della classe */
    Telemix* clone() const override;
    string getType() const override;

    /* Getters e Setters per l'ottenimento e la modifica dei campi della classe seggiovia */
    short getCapienzaCabina() const;
    void setCapienzaCabina(const short&);

    /* Deserializzazione */
    static Telemix* read(QXmlStreamReader*);

    /* Serializzazione */
    void write(QXmlStreamWriter*) const override;
};

#endif // TELEMIX_H
