#ifndef FUNIVIA_H
#define FUNIVIA_H

#include "Model/Gerarchia/movimentazionevaevieni.h"

class Funivia : public MovimentazioneVaeVieni{

public:
    Funivia(const unsigned short& = 0, const string& = "NoImage", const string& = "Unknown", const short& = -1, const unsigned int& = 0,const unsigned int& = 0,
            const double& = -1,const float& = -1, const string& = "Unknown", const short& = -1, const float& = -1);

    /* Vedere se mantenere */
    unsigned int PortataOraria() const;

    /* definizione dei metodi per la non-astrazione della classe */
    Funivia* clone() const override;
    string getType() const override;

    /* velocita massima di tutte le funivie (FUF) */
    static float velocitaEsercizioMax;

    /* Deserializzazione */
    static Funivia* read(QXmlStreamReader*);

    /* Serializzazione */
    void write(QXmlStreamWriter*);
};

#endif // FUNIVIA_H
