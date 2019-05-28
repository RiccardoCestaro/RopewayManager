#ifndef SCIOVIA_H
#define SCIOVIA_H

#include "Model/Gerarchia/movimentazionecontinua.h"
#include "Model/Gerarchia/Utils/gancio.h"

/**
 * @brief The Sciovia class
 *
 * Contiene buona parte delle caratteristiche di una sciovia,
 * si estende dalla classe astratta MovimentazioneContinua
 */
class Sciovia : public MovimentazioneContinua{
private:
    /** tipo di gancio della sciovia */
    Gancio gancio;

public:
    Sciovia(const unsigned short& = 0, const string& = "NoImage", const string& = "Unknown", const unsigned int& = 0, const unsigned int& = 0, const double& = -1,
            const float& = -1, const Produttore& = "Unknown", const short& = -1, const Gancio& = "piattello");

    /** definizione dei metodi per la non-astrazione della classe */
    Sciovia* clone() const override;
    string getType() const override;

    /** Getters e Setters per l'ottenimento e la modifica dei campi della classe sciovia */
    Gancio getGancio() const;
    void setGancio(const Gancio&);

    /** velocita massima di tutte le sciovie (SL) */
    static float velocitaEsercizioMax;

    /** Deserializzazione */
    static Sciovia* build(QXmlStreamReader*,const values*);

    /** Serializzazione */
    void write(QXmlStreamWriter*) const override;

};

#endif // SCIOVIA_H
