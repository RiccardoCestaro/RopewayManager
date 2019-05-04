#ifndef MOVIMENTAZIONECONTINUA_H
#define MOVIMENTAZIONECONTINUA_H

#include "impianto.h"

class Amm{
private:
    bool value;
public:
    Amm(const string& = "fisso");
    string toString() const;
};


class MovimentazioneContinua : public Impianto{

private:
    /* Ammorsamento fisso o automatico di un impianto a movimentazione continua */
    Amm ammorsamento;

protected:
    /* metodo per la serializzazione */
    void write(QXmlStreamWriter* writer) const override;

public:
    MovimentazioneContinua(const unsigned short& = 0L,  const string& = "NoImage", const string& = "Unknown", const short& = 0L, const unsigned int& = 0L,
                           const unsigned int& = 0L, const double& = 0L, const float& = 0L,  const string& = "Unknown", const short& = 0L, const Amm& = string("fisso"));

    /* Profilo preferenziale di tutti gli impianti a movimentazione continua */
    static string profiloPreferenziale;


    /* Ritorna il tipo di movimentazione */
    string getMovimentazione() const override;

    /* Getters e Setters per l'ottenimento e la modifica dei campi della classe astratta movimentazioneContinua */
    Amm getAmmorsamento() const;
    void setAmmorsamento(const Amm& value);

};

#endif // MOVIMENTAZIONECONTINUA_H
