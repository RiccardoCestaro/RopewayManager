#ifndef FUNIVIA_H
#define FUNIVIA_H

#include "Model/Gerarchia/movimentazionevaevieni.h"

/**
 * @brief The Funivia class
 *
 * Contiene buona parte delle caratteristiche di una funivia,
 * si estende dalla classe astratta MovimentazioneContinua
 */
class Funivia : public MovimentazioneVaeVieni{

public:
    Funivia(const unsigned short& = 0, const string& = "NoImage", const string& = "Unknown", const short& = -1, const unsigned int& = 0,const unsigned int& = 0,
            const double& = -1,const float& = -1, const Produttore& = "Unknown", const short& = -1, const float& = -1);

    /** definizione dei metodi per la non-astrazione della classe */
    Funivia* clone() const override;
    string getType() const override;

    /** velocita massima di tutte le funivie (AT,ATW) */
    static float velocitaEsercizioMax;

    /** Deserializzazione */
    static Funivia* build(QXmlStreamReader*,const values*);

    /** Serializzazione */
    void write(QXmlStreamWriter* writer) const override;
};

#endif // FUNIVIA_H
