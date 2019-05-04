#ifndef MOVIMENTAZIONEVAEVIENI_H
#define MOVIMENTAZIONEVAEVIENI_H

#include "impianto.h"

class MovimentazioneVaeVieni : public Impianto{
private:
    /* Tempo di attesa tra una partenza e l'altra */
    int tempoPausa;

protected:
    /* metodo per la serializzazione */
    void write(QXmlStreamWriter* writer) const override;

public:
    MovimentazioneVaeVieni(const unsigned short& = 0L, const string& = "NoImage", const string& = "Unknown", const short& = 0L, const unsigned int& = 0L, const unsigned int& = 0L,
                           const double& = 0L, const float& = 0L,  const string& = "Unknown", const short& = 0L, const float& = 0L);

    /* Profilo preferenziale di tutti gli impianti a movimentazione va e vieni */
    static string profiloPreferenziale;

    /* Ritorna il tipo di movimentazione */
    string getMovimentazione() const override;

    /* Getters e Setters per l'ottenimento e la modifica dei campi della classe astratta MovimentazioneVaeVieni */
    int getTempoPausa() const;
    void setTempoPausa(const int& tp);
};

#endif // MOVIMENTAZIONEVAEVIENI_H
