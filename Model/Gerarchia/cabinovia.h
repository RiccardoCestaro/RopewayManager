#ifndef CABINOVIA_H
#define CABINOVIA_H

#include "Model/Gerarchia/movimentazionecontinua.h"

class Cabinovia : virtual public MovimentazioneContinua{
private:
    /* numero di funi della cabinovia ( MGD..BL= 1, 2S..DMC = 2, 3S = 3) */
    short numeroFuni;


public:

    Cabinovia(const unsigned short& = 0, const string& = "NoImage", const string& = "Unknown", const short& = -1, const unsigned int& = 0,const unsigned int& = 0,
              const double& = -1,const float& = -1, const string& = "Unknown", const short& = -1, const Amm& = string("automatico"), const short& = 1);

    /* altri metodi da vedar se tegnar */
    unsigned int PortataOraria() const;

    /* definizione dei metodi per la non-astrazione della classe */
    Cabinovia* clone() const override;
    string getType() const override;

    /* Getters e Setters per l'ottenimento e la modifica dei campi della classe cabinovia */
    short getNumeroFuni() const;
    void setNumeroFuni(const short& value);

    /* velocita massima di tutte le cabinovie ad ammorsamento automatico (MGD,DMC,2S,3S)*/
    static float velocitaEsercizioAutomaticoMax;
    /* velocita massima di tutte le cabinovie ad ammorsamento fisso (BL)*/
    static float velocitaEsercizioFissoMax;
    /* numero di funi massimo ( 1-3 max ) */
    static short numeroFuniMax;

    /* metodo per la deserializzazione */
    static Cabinovia* read(QXmlStreamReader* reader);

    /* metodo per la serializzazione */
    void write(QXmlStreamWriter* writer) const override;
};

#endif // CABINOVIA_H
