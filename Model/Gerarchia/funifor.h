#ifndef FUNIFOR_H
#define FUNIFOR_H

#include "Model/Gerarchia/movimentazionevaevieni.h"

/**
 * @brief The Funifor class
 *
 * Contiene buona parte delle caratteristiche di un Funifor,
 * si estene dalla classe astratta MovimentazioneContinua
 */
class Funifor : public MovimentazioneVaeVieni{
private:
    /** Indica il numero di cabine ( se una o due ) */
    short numeroCabine;

public:
    Funifor(const unsigned short& = 0, const string& = "NoImage", const string& = "Unknown", const short& = -1, const unsigned int& = 0,const unsigned int& = 0,
            const double& = -1,const float& = -1, const Produttore& = "Unknown", const short& = -1, const float& = -1,const short& = -1);

    /** Getters e Setters per l'ottenimento e la modifica dei campi della classe funifor */
    short getNumeroCabine() const;
    void setNumeroCabine(const short& value);

    /** definizione dei metodi per la non-astrazione della classe */
    Funifor* clone() const override;
    string getType() const override;

    /** velocita massima di tutti i funifor (FUF) */
    static float velocitaEsercizioMax;
    /** campo statico che contiene 2 come numero massimo possibile di cabine di un funifor */
    static short numeroCabineMax;

    /** Deserializzazione */
    static Funifor* build(QXmlStreamReader*,const values*);

    /** Serializzazione */
    void write(QXmlStreamWriter*) const override;
};

#endif // FUNIFOR_H
