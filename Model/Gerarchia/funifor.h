#ifndef FUNIFOR_H
#define FUNIFOR_H

#include "movimentazionevaevieni.h"



class Funifor : public MovimentazioneVaeVieni{
private:
    /* Indica il numero di cabine ( se una o due ) */
    short numeroCabine;

public:
    Funifor(const unsigned short& = 0, const string& = "NoImage", const string& = "Unknown", const short& = -1, const unsigned int& = 0,const unsigned int& = 0,
            const double& = -1,const float& = -1, const string& = "Unknown", const short& = -1, const float& = -1,const short& = -1);

    /* Getters e Setters per l'ottenimento e la modifica dei campi della classe funifor */
    short getNumeroCabine() const;
    void setNumeroCabine(const short& value);

    /* vedere se lasciare */
    unsigned int PortataOraria() const;

    /* definizione dei metodi per la non-astrazione della classe */
    Funifor* clone() const override;
    string getType() const override;

    /* velocita massima di tutti i funifor (FUC) */
    static float velocitaEsercizioMax;
    /* campo statico che contiene 2 come numero massimo possibile di cabine di un funifor */
    static short numeroCabineMax;

    /* Deserializzazione */
    static Funifor* read(QXmlStreamReader*);

    /* Serializzazione */
    void write(QXmlStreamWriter*) const override;
};

#endif // FUNIFOR_H
