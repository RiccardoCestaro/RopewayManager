#ifndef SCIOVIA_H
#define SCIOVIA_H

#include "Model/Gerarchia/movimentazionecontinua.h"

class Gancio{
private:
    bool value;
public:
    Gancio(const string&);
    string toString() const;
};



class Sciovia : public MovimentazioneContinua{
public:
    Sciovia(const unsigned short& = 0, const string& = "NoImage", const string& = "Unknown", const unsigned int& = 0, const unsigned int& = 0, const double& = -1,
            const float& = -1, const string& = "Unknown", const short& = -1, const Gancio& = string("piattello"));

    /* Vedere se mantenere */
    unsigned int PortataOraria() const;

    /* definizione dei metodi per la non-astrazione della classe */
    Sciovia* clone() const override;
    string getType() const override;

    /* Getters e Setters per l'ottenimento e la modifica dei campi della classe sciovia */
    Gancio getGancio() const;
    void setGancio(const Gancio&);

    /* velocita massima di tutte le sciovie (SL) */
    static float velocitaEsercizioMax;

    /* Deserializzazione */
    static Sciovia* read(QXmlStreamReader*);

    /* Serializzazione */
    void write(QXmlStreamWriter*) const override;

private:
    /* tipo di gancio della sciovia */
    Gancio gancio;


};

#endif // SCIOVIA_H
