#ifndef FUNICOLARE_H
#define FUNICOLARE_H

#include "Model/Gerarchia/movimentazionevaevieni.h"



class tecBin{
private:
    bool value;
public:
    string toString() const;
    tecBin(const string&);
};

class Funicolare : public MovimentazioneVaeVieni{
private:
    /* Indica il numero di binari, doppio oppure unico con sdoppiamento al centro */
    tecBin tecBinario;
public:
    Funicolare(const unsigned short& = 0, const string& = "NoImage", const string& = "Unknown", const short& = -1, const unsigned int& = 0, const unsigned int& = 0,
               const double& = -1, const float& = -1, const string& = "Unknown", const short& = -1, const float& = -1, const tecBin& = string("unico"));

    /* Getters e Setters per l'ottenimento e la modifica dei campi della classe funicolare */
    tecBin getTecBinario() const;
    void setTecBinario(const tecBin&);

    /* definizione dei metodi per la non-astrazione della classe */
    Funicolare* clone() const override;
    string getType() const override;

    /* vedere se lasciare */
    unsigned int PortataOraria() const;

    /* velocita massima di tutti i funicolari (FUC) */
    static float velocitaEsercizioMax;

    /* Deserializzazione */
    static Funicolare* read(QXmlStreamReader*);

    /* Serializzazione */
    void write(QXmlStreamWriter*) const override;
};


#endif // FUNICOLARE_H
