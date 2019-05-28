#ifndef TELEMIX_H
#define TELEMIX_H

#include "seggiovia.h"
#include "cabinovia.h"

/**
 * @brief The Telemix class
 *
 * Contiene buona parte delle caratteristiche dei telemix
 * Eredita dalle classi concrete seggiovia e cabinovia
 * (il telemix e' un particolare tipo di impianto che funge sia
 * da cabinovia che da seggiovia)
 */
class Telemix : public Seggiovia, public Cabinovia{
private:
    /** Devo sapere anche la capienza delle cabine, nel caso fossero diverse da quella delle seggiole */
    short capienzaCabina;

public:
    Telemix(const unsigned short& = 0, const string& = "NoImage", const string& = "Unknown", const short& = -1, const short& = -1, const unsigned int& = 0, const unsigned int& = 0, const double& = -1,
            const float& = -1, const Produttore& = "Unknown", const short& = -1, const bool& = false, const bool& = true);

    /** definizione dei metodi per la non-astrazione della classe */
    Telemix* clone() const override;
    string getType() const override;

    /** Getters e Setters per l'ottenimento e la modifica dei campi della classe seggiovia */
    short getCapienzaCabina() const;
    void setCapienzaCabina(const short&);

    /** Metodo per la deserializzazione */
    static Telemix* build(QXmlStreamReader*,const values*);

    /** Metodo per la serializzazione */
    void write(QXmlStreamWriter*) const override;
};

#endif // TELEMIX_H
