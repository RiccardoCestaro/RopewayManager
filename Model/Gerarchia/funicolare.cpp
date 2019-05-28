#include "Model/Gerarchia/funicolare.h"
#include "invalidstringtoenumexception.h"
#include <iostream>

#include <string>
#include <cctype>

/**
 * Campi dati statici che contengono valori massimi di velocita'
 * di un impianto di tipo Funicolare
 */
float Funicolare::velocitaEsercizioMax = 10;

/**
 * @brief Funicolare::Funicolare
 *
 * Costruttore della classe Funicolare
 * Esegue dei controlli sui campi,
 * come la velocita' d'esercizio
 */
Funicolare::Funicolare(const unsigned short& i, const string& img, const string& nm, const short& c, const unsigned int& qv, const unsigned int& qm,
                       const double& pm, const float& ve, const Produttore& pro, const short& ac, const float& tp, const TecBin& t)
                        : MovimentazioneVaeVieni(i, img, nm, c, qv, qm, pm, ve, pro, ac, tp), tecBinario(t){
    if(getVelocitaEsercizio() > velocitaEsercizioMax) setVelocitaEsercizio(-1);
}


/**
 * @brief Funicolare::getTecBinario
 * @return TecBinario
 */
TecBin Funicolare::getTecBinario() const{
    return tecBinario;
}

/**
 * @brief Funicolare::setTecBinario
 * @param v
 */
void Funicolare::setTecBinario(const TecBin &v){
    tecBinario = v;
}

/**
 * @brief Funicolare::clone
 * @return Funicolare pointer
 *
 * metodo di clonazione polimorfa
 */
Funicolare* Funicolare::clone() const {
    return new Funicolare(*this);
}

/**
 * @brief Funicolare::getType
 * @return std::string "funivia"
 */
string Funicolare::getType() const{
    return "funicolare";
}

/**
 * @brief Funicolare::build
 * @param reader
 * @param r
 * @return Funicolare pointer
 *
 * metodo che si occupa di costruire un oggetto di classe Funicolare
 * deserializzando un file in formato XML
 * Il metodo viene chiamato dalla classe base, dalla quale vengono
 * passati i valori radicati nella classe base.
 * inoltre ritorna un puntatore all'oggetto appena costruito
 */
Funicolare *Funicolare::build(QXmlStreamReader* reader,const values* r){
    float tempoPausa = -1;
    TecBin tecBinario = "doppio";
    if(reader->readNextStartElement() && reader->name()=="TempoAttesa")
        tempoPausa = reader->readElementText().toInt();
    if(reader->readNextStartElement() && reader->name()=="TecnicaBinario")
        tecBinario = reader->readElementText().toStdString();
    return new Funicolare(r->id,r->immagine,r->nome,r->capienzaVeicolo,r->quotaValle,r->quotaMonte,r->potenzaMotore,r->velocitaEsercizio,
                          r->produttore,r->annoCostruzione,tempoPausa,tecBinario);
}

/**
 * @brief Funicolare::write
 * @param writer
 *
 * permette la serializzazione in XML di un oggetto di classe funicolare
 * richiama il metodo write delle classi superiori per aumentare
 * l'estendibilita' del codice
 */
void Funicolare::write(QXmlStreamWriter* writer) const{
    MovimentazioneVaeVieni::write(writer);
    writer->writeStartElement("TecnicaBinario");
    writer->writeCharacters(QString::fromStdString(tecBinario.toString()));
    writer->writeEndElement();
    writer->writeEndElement();
}

