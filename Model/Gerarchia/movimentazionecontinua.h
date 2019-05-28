#ifndef MOVIMENTAZIONECONTINUA_H
#define MOVIMENTAZIONECONTINUA_H

#include "Model/Gerarchia/impianto.h"
#include "Model/Gerarchia/Utils/ammorsamento.h"

/**
 * @brief The MovimentazioneContinua class
 *
 * Estende la classe impianto agli ampianti a
 * Movimentazione Continua, aggiungendo caratteristiche
 * comuni agli impianti a movimentazione continua
 */
class MovimentazioneContinua : public Impianto{
private:
    /** Ammorsamento fisso o automatico di un impianto a movimentazione continua */
     Ammorsamento ammorsamento;

protected:
    /** metodo per la serializzazione */
    void write(QXmlStreamWriter* writer) const override;

public:
    MovimentazioneContinua(const unsigned short& = 0L,  const string& = "NoImage", const string& = "Unknown", const short& = 0L, const unsigned int& = 0L,
                           const unsigned int& = 0L, const double& = 0L, const float& = 0L,  const Produttore& = "Unknown", const short& = 0L, const Ammorsamento& = "fisso");

    /** Profilo preferenziale di tutti gli impianti a movimentazione continua */
    static string profiloPreferenziale;

    /** Ritorna il tipo di movimentazione */
    string getMovimentazione() const override;

    /** Getters e Setters per l'ottenimento e la modifica dei campi della classe astratta movimentazioneContinua */
    Ammorsamento getAmmorsamento() const;
    void setAmmorsamento(const Ammorsamento& value);

};

#endif // MOVIMENTAZIONECONTINUA_H
