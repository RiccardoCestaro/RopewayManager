#include "Model/Gerarchia/cabinovia.h"
#include "Model/Gerarchia/Utils/ropewayutils.h"

/**
 * Campi dati statici che contengono valori massimi di velocita'
 * e di funi di un impianto di tipo Cabinovia
 */
float Cabinovia::velocitaEsercizioAutomaticoMax = 7;
float Cabinovia::velocitaEsercizioFissoMax = 2;
short Cabinovia::numeroFuniMax = 3;

/**
 * @brief Cabinovia::Cabinovia
 *
 * Costruttore della classe Cabinovia
 * Esegue dei controlli sui campi, quali il
 * numero di funi e la velocita' d'esercizio
 */
Cabinovia::Cabinovia(const unsigned short& i,const string& img, const string& nm, const short& c, const unsigned int& qv, const unsigned int& qm,
                     const double& pm, const float& ve, const Produttore& pro, const short& ac, const Ammorsamento& a, const short& nf)
                    : MovimentazioneContinua(i,img,nm,c,qv,qm,pm,ve,pro,ac,a), numeroFuni(nf){
    if (numeroFuni > 3 || numeroFuni < 1) numeroFuni = -1;
    if(RopewayUtils::compareString(getAmmorsamento().toString(),Ammorsamento::values.at(0).toStdString()) && getVelocitaEsercizio() > velocitaEsercizioFissoMax) setVelocitaEsercizio(-1);
    else if(RopewayUtils::compareString(getAmmorsamento().toString(),Ammorsamento::values.at(1).toStdString()) && getVelocitaEsercizio() > velocitaEsercizioAutomaticoMax) setVelocitaEsercizio(-1);
}

/**
 * @brief Cabinovia::getNumeroFuni
 * @return numeroFuni
 */
short Cabinovia::getNumeroFuni() const{
    return numeroFuni;
}

/**
 * @brief Cabinovia::setNumeroFuni
 * @param nf
 */
void Cabinovia::setNumeroFuni(const short& nf){
    numeroFuni = nf;
}

/**
 * @brief Cabinovia::clone
 * @return Cabinovia pointer
 *
 * metodo di clonazione polimorfa
 */
Cabinovia* Cabinovia::clone() const {
    return new Cabinovia(*this);
}

/**
 * @brief Cabinovia::getType
 * @return std::string "cabinovia"
 */
string Cabinovia::getType() const{
    return "cabinovia";
}

/**
 * @brief Cabinovia::build
 * @param reader
 * @param r
 * @return Cabinovia pointer
 *
 * metodo che si occupa di costruire un oggetto di classe Cabinovia
 * deserializzando un file in formato XML
 * Il metodo viene chiamato dalla classe base, dalla quale vengono
 * passati i valori radicati nella classe base.
 * inoltre ritorna un puntatore all'oggetto appena costruito
 */
Cabinovia* Cabinovia::build(QXmlStreamReader *reader,const values* r){
    Ammorsamento ammorsamento;
    short numeroFuni;
    if(reader->readNextStartElement() && reader->name()=="Ammorsamento")
        ammorsamento =  reader->readElementText().toStdString();
    if(reader->readNextStartElement() && reader->name()=="NumeroFuni")
        numeroFuni = reader->readElementText().toShort();
    return new Cabinovia(r->id,r->immagine,r->nome,r->capienzaVeicolo,r->quotaValle,r->quotaMonte,r->potenzaMotore,r->velocitaEsercizio,
                         r->produttore,r->annoCostruzione,ammorsamento,numeroFuni);
}

/**
 * @brief Cabinovia::write
 * @param writer
 *
 * permette la serializzazione in XML di un oggetto di classe cabinovia
 * richiama il metodo write delle classi superiori per aumentare
 * l'estendibilita' del codice
 */
void Cabinovia::write(QXmlStreamWriter *writer) const{
    MovimentazioneContinua::write(writer);
    writer->writeStartElement("NumeroFuni");
    writer->writeCharacters(QString::number(numeroFuni));
    writer->writeEndElement();
    writer->writeEndElement();
}






