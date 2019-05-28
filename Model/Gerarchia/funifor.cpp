#include "Model/Gerarchia/funifor.h"

/**
 * Campi dati statici che contengono valori massimi di velocita'
 * e valori massimi di cabine di un impianto di tipo Funifor
 */
float Funifor::velocitaEsercizioMax = 14;
short Funifor::numeroCabineMax = 2;

/**
 * @brief Funifor::Funifor
 *
 * Costruttore della classe funifor,
 * esegue dei controlli sui campi, quali
 * la velocita' di esercizio e il numero
 * di cabine
 */
Funifor::Funifor(const unsigned short& i, const string& img, const string& nm, const short& c, const unsigned int& qv, const unsigned int& qm,
                 const double& pm, const float& ve, const Produttore& pro,const short& ac, const float& tp, const short& nc)
                : MovimentazioneVaeVieni(i, img, nm, c, qv, qm, pm, ve, pro, ac, tp), numeroCabine(nc){
    if(getVelocitaEsercizio() > velocitaEsercizioMax) setVelocitaEsercizio(-1);
    if(numeroCabine > numeroCabineMax) numeroCabine = -1;
}

/**
 * @brief Funifor::getNumeroCabine
 * @return numeroCabine
 */
short Funifor::getNumeroCabine() const{
    return numeroCabine;
}

/**
 * @brief Funifor::setNumeroCabine
 * @param nc
 */
void Funifor::setNumeroCabine(const short& nc){
    numeroCabine = nc;
}

/**
 * @brief Funifor::clone
 * @return Funifor pointer
 *
 * metodo per la clonazione polimorfa
 */
Funifor* Funifor::clone() const{
    return new Funifor(*this);
}

/**
 * @brief Funifor::getType
 * @return std::string "funifor"
 */
string Funifor::getType() const {
    return "funifor";
}

/**
 * @brief Funifor::build
 * @param reader
 * @param r
 * @return Funifor pointer
 *
 * metodo che si occupa di costruire un oggetto di classe Funifor
 * deserializzando un file in formato XML
 * Il metodo viene chiamato dalla classe base, dalla quale vengono
 * passati i valori radicati nella classe base.
 * inoltre ritorna un puntatore all'oggetto appena costruito
 */
Funifor *Funifor::build(QXmlStreamReader* reader,const values* r){
    float tempoPausa = -1;
    short numeroCabine = -1;
    if(reader->readNextStartElement() && reader->name()=="TempoAttesa")
        tempoPausa = reader->readElementText().toInt();
    if(reader->readNextStartElement() && reader->name()=="NumeroCabine")
        numeroCabine = reader->readElementText().toShort();
    return new Funifor(r->id,r->immagine,r->nome,r->capienzaVeicolo,r->quotaValle,r->quotaMonte,r->potenzaMotore,r->velocitaEsercizio,
                       r->produttore,r->annoCostruzione,tempoPausa,numeroCabine);
}

/**
 * @brief Funifor::write
 * @param writer
 *
 * permette la serializzazione in XML di un oggetto di classe funifor
 * richiama il metodo write delle classi superiori per aumentare
 * l'estendibilita' del codice
 */
void Funifor::write(QXmlStreamWriter* writer) const{
    MovimentazioneVaeVieni::write(writer);
    writer->writeStartElement("NumeroCabine");
    writer->writeCharacters(QString::number(numeroCabine));
    writer->writeEndElement();
    writer->writeEndElement();
}
