#include "Model/Gerarchia/funivia.h"

/**
 * Campo dati statico che contiene
 * la velocita d'esercizio massima
 * di un impianto di tipo Funivia
 */
float Funivia::velocitaEsercizioMax = 12;

/**
 * @brief Funivia::Funivia
 *
 * Costruttore della classe Funivia,
 * esegue dei controlli sui campi,
 * come la velocita' d'esercizio
 */
Funivia::Funivia(const unsigned short& i, const string& img, const string& nm, const short& c, const unsigned int& qv, const unsigned int& qm,
                 const double& pm, const float& ve, const Produttore& pro, const short& ac, const float& tp)
                : MovimentazioneVaeVieni(i, img, nm, c, qv, qm, pm, ve, pro, ac, tp){
    if(getVelocitaEsercizio() > velocitaEsercizioMax) setVelocitaEsercizio(-1);
}

/**
 * @brief Funivia::clone
 * @return Funivia pointer
 *
 * Metodo di clonazione polimorfa
 */
Funivia* Funivia::clone() const{
    return new Funivia(*this);
}

/**
 * @brief Funivia::getType
 * @return std::string "funivia"
 */
string Funivia::getType() const{
    return "funivia";
}

/**
 * @brief Funivia::build
 * @param reader
 * @param r
 * @return Funivia pointer
 *
 * metodo che si occupa di costruire un oggetto di classe Funivia
 * deserializzando un file in formato XML
 * Il metodo viene chiamato dalla classe base, dalla quale vengono
 * passati i valori radicati nella classe base.
 * inoltre ritorna un puntatore all'oggetto appena costruito
 */
Funivia* Funivia::build(QXmlStreamReader* reader,const values* r){
    float tempoPausa = -1;
    if(reader->readNextStartElement() && reader->name()=="TempoAttesa")
        tempoPausa = reader->readElementText().toInt();
    return new Funivia(r->id,r->immagine,r->nome,r->capienzaVeicolo,r->quotaValle,r->quotaMonte,r->potenzaMotore,r->velocitaEsercizio,
                       r->produttore,r->annoCostruzione,tempoPausa);
}

/**
 * @brief Funivia::write
 * @param writer
 *
 * permette la serializzazione in XML di un oggetto di classe funivia
 * richiama il metodo write delle classi superiori per aumentare
 * l'estendibilita' del codice
 */
void Funivia::write(QXmlStreamWriter* writer) const{
    MovimentazioneVaeVieni::write(writer);
    writer->writeEndElement();
}
