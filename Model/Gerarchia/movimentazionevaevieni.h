#ifndef MOVIMENTAZIONEVAEVIENI_H
#define MOVIMENTAZIONEVAEVIENI_H

#include "Model/Gerarchia/impianto.h"

/**
 * @brief The MovimentazioneVaeVieni class
 *
 * Estende la classe impianto agli ampianti a
 * Movimentazione Va e Vieni, aggiungendo caratteristiche
 * comuni agli impianti a movimentazione Va e Vieni
 */
class MovimentazioneVaeVieni : public Impianto{
private:
    /** Tempo di attesa tra una partenza e l'altra */
    float tempoPausa;

protected:
    /** metodo per la serializzazione */
    void write(QXmlStreamWriter* writer) const override;

public:
    MovimentazioneVaeVieni(const unsigned short& = 0L, const string& = "NoImage", const string& = "Unknown", const short& = 0L, const unsigned int& = 0L, const unsigned int& = 0L,
                           const double& = 0L, const float& = 0L,  const Produttore& = "Unknown", const short& = 0L, const float& = 0L);

    /** Profilo preferenziale di tutti gli impianti a movimentazione va e vieni */
    static string profiloPreferenziale;

    /** Ritorna il tipo di movimentazione */
    string getMovimentazione() const override;

    /** Getters e Setters per l'ottenimento e la modifica dei campi della classe astratta MovimentazioneVaeVieni */
    float getTempoPausa() const;
    void setTempoPausa(const float& tp);
};

#endif // MOVIMENTAZIONEVAEVIENI_H
