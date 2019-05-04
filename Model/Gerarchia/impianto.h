#ifndef ROPEWAY_H
#define ROPEWAY_H

#include<iostream>

#include <QXmlStreamReader>
#include <QXmlStreamWriter>

using std::string;

class Impianto{
private:
    /* Numero di identificazione dell'impianto */
    unsigned short id;
    /* Immagine */
    string immagine;
    /* Nome dell'impianto */
    string nome;
    /* Capienza di un singolo veicolo */
    short capienzaVeicolo;
    /* Quota delle stazioni di valle e di monte */
    unsigned int quotaValle,quotaMonte;
    /* Potenza media erogata durante il servizio */
    double potenzaMotore;
    /* Velocita media in servizio */
    float velocitaEsercizio;
    /* Produttore dell'impianto */
    string produttore;
    /* Anno della costruzione dell'impianto */
    short annoCostruzione;



    /* IN PIU */
    string sigla;


protected:
    /* definisco una struct per il return dei valori dal metodo statico read */
    struct values{
        unsigned short id;
        string immagine;
        string nome;
        short capienzaVeicolo;
        unsigned int quotaValle,quotaMonte;
        double potenzaMotore;
        float velocitaEsercizio;
        string produttore;
        short annoCostruzione;
    };

    /* metodo per la deserializzazione */
    static values* read(QXmlStreamReader* reader);
public:
    /* Costruttore di impianto, vedere se mantenere valori di default ????? */
    Impianto(const unsigned short& = 0L, const string& = "NoImage", const string& = "Unknown", const short& = 0L, const unsigned int& = 0L, const unsigned int& = 0L,
             const double& = 0L, const float& = 0L,  const string& = "Unknown", const short& = 0L);

    /* Distruttore virtuale con comportamento di default */
    virtual ~Impianto() = default;
    /* Metodo di clonazione polimorfa */
    virtual Impianto* clone() const = 0;
    /* Metodo virtuale puro per il ritorno del tipo di impianto */
    virtual string getType() const = 0;
    /* Metodo virtuale puro per sapere il tipo di movimentazione */
    virtual string getMovimentazione() const = 0;

    /* virtual unsigned short portataOraria() const = 0; */
    /* Dislivello vedere se mantenere, se c'e' tempo */
    unsigned int dislivello() const;

    /* Getters per l'ottenimento dei campi radicati nella classe astratta impianto */
    unsigned short getId() const;
    string getNome() const;
    short getCapienzaVeicolo() const;
    unsigned int getQuotaValle() const;
    unsigned int getQuotaMonte() const;
    double getPotenzaMotore() const;
    float getVelocitaEsercizio() const;
    string getProduttore() const;
    string getSigla() const;
    short getAnnoCostruzione() const;
    string getImmagine() const;

    /* Setters per modificare i campi radicati nella classe astratta impianto */
    void setId(const unsigned short&);
    void setNome(const string&);
    void setCapienzaVeicolo(const short&);
    void setQuotaValle(const unsigned int&);
    void setQuotaMonte(const unsigned int&);
    void setPotenzaMotore(const double&);
    void setVelocitaEsercizio(const float&);
    void setSigla(const string&);
    void setProduttore(const string&);
    void setAnnoCostruzione(const short&);
    void setImmagine(const string&);

    /* metodo per la serializzazione */
    virtual void write(QXmlStreamWriter* writer) const;
    /* Lambda espressione per confrontare due stringhe in modo case insensitive */
    static bool compareString(const string&,const string&);
};



#endif // ROPEWAY_H
