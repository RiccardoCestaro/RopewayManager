#ifndef FUNICOLARE_H
#define FUNICOLARE_H

#include "Model/Gerarchia/movimentazionevaevieni.h"
#include "Model/Gerarchia/Utils/tecbin.h"

/**
 * @brief The Funicolare class
 *
 * Contiene buona parte delle caratteristiche di un funicolare,
 * si estende dalla classe astratta MovimentazioneVaeVieni
 */
class Funicolare : public MovimentazioneVaeVieni{
private:
    /** Indica il numero di binari, doppio oppure unico con sdoppiamento al centro */
    TecBin tecBinario;

public:
    Funicolare(const unsigned short& = 0, const string& = "NoImage", const string& = "Unknown", const short& = -1, const unsigned int& = 0, const unsigned int& = 0,
               const double& = -1, const float& = -1, const Produttore& = "Unknown", const short& = -1, const float& = -1, const TecBin& = "unico");

    /** Getters e Setters per l'ottenimento e la modifica dei campi della classe funicolare */
    TecBin getTecBinario() const;
    void setTecBinario(const TecBin&);

    /** definizione dei metodi per la non-astrazione della classe */
    Funicolare* clone() const override;
    string getType() const override;

    /** velocita massima di tutti i funicolari (FUC) */
    static float velocitaEsercizioMax;

    /** Deserializzazione */
    static Funicolare* build(QXmlStreamReader*,const values*);

    /** Serializzazione */
    void write(QXmlStreamWriter*) const override;
};


#endif // FUNICOLARE_H
