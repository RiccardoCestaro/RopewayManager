#ifndef SEGGIOVIA_H
#define SEGGIOVIA_H

#include "Model/Gerarchia/movimentazionecontinua.h"


class Seggiovia : virtual public MovimentazioneContinua{
private:
    /* indica se e' presente la copertura semovente */
    bool copertura;
    /* indica se e' presente un appoggia sci */
    bool appoggiaSci;

public:
    Seggiovia(const unsigned short& = 0, const string& = "NoImage", const string& = "Unknown", const short& = -1, const unsigned int& = 0, const unsigned int& = 0, const double& = -1,
              const float& = -1, const string& = "Unknown", const short& = -1, const Amm& = string("fisso"), const bool& = false, const bool& = true);

    /* vedere se mantenere */
    unsigned int PortataOraria() const;

    /* definizione dei metodi per la non-astrazione della classe */
    Seggiovia* clone() const override;
    string getType() const override;

    /* Getters e Setters per l'ottenimento e la modifica dei campi della classe seggiovia */
    bool isCoperta() const;
    bool hasAppoggiaSci() const;
    void setCopertura(const bool& value);
    void setAppoggiaSci(const bool& value);

    /* velocita massima di tutte le seggiovie ad ammorsamento automatico (CLD,CLD/B) */
    static float velocitaEsercizioAutomaticoMax;
    /* velocita massima di tutte le seggiovie ad ammorsamento fisso (CLF) */
    static float velocitaEsercizioFissoMax;

    /* Metodo per la deserializzazione */
    static Seggiovia* read(QXmlStreamReader*);

    /* Serializzazione */
    void write(QXmlStreamWriter*) const override;

};

#endif // SEGGIOVIA_H
