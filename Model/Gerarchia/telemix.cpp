#include "Model/Gerarchia/telemix.h"
#include "Model/Gerarchia/Utils/produttore.h"

/**
 * @brief Telemix::Telemix
 *
 * Costruttore della classe Telemix,
 * effettua dei controlli sui campi
 *
 * L'ammorsamento di una telemix e' sempre automatico
 * ed il numero di funi e' sempre pari a 1
 */
Telemix::Telemix(const unsigned short& i, const string& img, const string& nm, const short& cs,const short& cc, const unsigned int& qv,
                 const unsigned int& qm, const double& pm, const float& ve, const Produttore& pro, const short& ac, const bool& c, const bool& as) :
            MovimentazioneContinua(i,img,nm,c,qv,qm,pm,ve,pro,ac,"automatico"),
            Seggiovia(i,img,nm,cs,qv,qm,pm,ve,pro,ac,"automatico",c,as), Cabinovia(i,img,nm,cc,qv,qm,pm,ve,pro,ac,"automatico",1){
    if(getVelocitaEsercizio() > Seggiovia::velocitaEsercizioAutomaticoMax) setVelocitaEsercizio(-1);
}

/**
 * @brief Telemix::clone
 * @return Telemix pointer
 */
Telemix* Telemix::clone() const{
    return new Telemix(*this);
}

/**
 * @brief Telemix::getType
 * @return std::string "telemix"
 */
string Telemix::getType() const{
    return "telemix";
}

/**
 * @brief Telemix::getCapienzaCabina
 * @return capienzaCabina
 */
short Telemix::getCapienzaCabina() const{
    return capienzaCabina;
}

/**
 * @brief Telemix::setCapienzaCabina
 * @param cc
 */
void Telemix::setCapienzaCabina(const short& cc){
    capienzaCabina = cc;
}

/**
 * @brief Telemix::build
 * @param reader
 * @param r
 * @return Telemix pointer
 *
 * metodo che si occupa di costruire un oggetto di classe Telemix
 * deserializzando un file in formato XML
 * Il metodo viene chiamato dalla classe base, dalla quale vengono
 * passati i valori radicati nella classe base.
 * inoltre ritorna un puntatore all'oggetto appena costruito
 */
Telemix *Telemix::build(QXmlStreamReader* reader,const values* r){
    short capienzaCabina;
    bool copertura;
    bool appoggiaSci;
    if(reader->readNextStartElement() && reader->name()=="CapienzaCabina")
        capienzaCabina = reader->readElementText().toShort();
    if(reader->readNextStartElement() && reader->name()=="Copertura")
        copertura = reader->readElementText().toInt();
    if(reader->readNextStartElement() && reader->name()=="AppoggiaSci")
        appoggiaSci = reader->readElementText().toInt();
    return new Telemix(r->id,r->immagine,r->nome,r->capienzaVeicolo,capienzaCabina,r->quotaValle,r->quotaMonte,r->potenzaMotore,r->velocitaEsercizio,
                       r->produttore,r->annoCostruzione,copertura,appoggiaSci);
}

/**
 * @brief Telemix::write
 * @param writer
 *
 * permette la serializzazione in XML di un oggetto di classe telemix
 * richiama il metodo write delle classi superiori per aumentare
 * l'estendibilita' del codice
 */
void Telemix::write(QXmlStreamWriter* writer) const{
    MovimentazioneContinua::write(writer);
    writer->writeStartElement("CapienzaCabina");
    writer->writeCharacters(QString::number(capienzaCabina));
    writer->writeEndElement();
    writer->writeStartElement("Copertura");
    writer->writeCharacters(QString::number(isCoperta()));
    writer->writeEndElement();
    writer->writeStartElement("AppoggiaSci");
    writer->writeCharacters(QString::number(hasAppoggiaSci()));
    writer->writeEndElement();
    writer->writeEndElement();
}

