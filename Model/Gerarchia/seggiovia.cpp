#include "Model/Gerarchia/seggiovia.h"
#include "Model/Gerarchia/Utils/ropewayutils.h"

/**
 * Campi dati statici che contengono i valori massimi
 * di velocita' di esercizio di una seggiovia
 */
float Seggiovia::velocitaEsercizioAutomaticoMax = 6;
float Seggiovia::velocitaEsercizioFissoMax = 2.5;

/**
 * @brief Seggiovia::Seggiovia
 *
 * Costruttore della classe seggiovia,
 * esegue dei controlli sui campi,
 * come la velocita' di esercizio.
 */
Seggiovia::Seggiovia(const unsigned short& i, const string& img, const string& nm, const short& ca, const unsigned int& qv, const unsigned int& qm,
                     const double& pm, const float& ve, const Produttore& pro, const short& ac, const Ammorsamento& a, const bool& c, const bool& as) :
                    MovimentazioneContinua(i,img,nm,ca,qv,qm,pm,ve,pro,ac,a), copertura(c), appoggiaSci(as){
    if(RopewayUtils::compareString(getAmmorsamento().toString(),"fisso") && getVelocitaEsercizio() > velocitaEsercizioFissoMax) setVelocitaEsercizio(-1);
    else if(RopewayUtils::compareString(getAmmorsamento().toString(),"automatico") && getVelocitaEsercizio() > velocitaEsercizioAutomaticoMax) setVelocitaEsercizio(-1);
}

/**
 * @brief Seggiovia::isCoperta
 * @return copertura
 */
bool Seggiovia::isCoperta() const{
    return copertura;
}

/**
 * @brief Seggiovia::hasAppoggiaSci
 * @return appoggiaSci
 */
bool Seggiovia::hasAppoggiaSci() const{
    return appoggiaSci;
}

/**
 * @brief Seggiovia::setCopertura
 * @param c
 */
void Seggiovia::setCopertura(const bool& c){
    copertura = c;
}

/**
 * @brief Seggiovia::setAppoggiaSci
 * @param as
 */
void Seggiovia::setAppoggiaSci(const bool& as){
    appoggiaSci = as;
}

/**
 * @brief Seggiovia::clone
 * @return Seggiovia pointer
 *
 * metodo di clonazione polimorfa
 */
Seggiovia* Seggiovia::clone() const {
    return new Seggiovia(*this);
}

/**
 * @brief Seggiovia::getType
 * @return std::string "seggiovia"
 */
string Seggiovia::getType() const{
    return "seggiovia";
}

/**
 * @brief Seggiovia::build
 * @param reader
 * @param r
 * @return Seggiovia pointer
 *
 * metodo che si occupa di costruire un oggetto di classe Seggiovia
 * deserializzando un file in formato XML
 * Il metodo viene chiamato dalla classe base, dalla quale vengono
 * passati i valori radicati nella classe base.
 * inoltre ritorna un puntatore all'oggetto appena costruito
 */
Seggiovia* Seggiovia::build(QXmlStreamReader *reader,const values* r){
    Ammorsamento ammorsamento;
    bool copertura;
    bool appoggiaSci;
    if(reader->readNextStartElement() && reader->name()=="Ammorsamento")
        ammorsamento =  reader->readElementText().toStdString();
    if(reader->readNextStartElement() && reader->name()=="Copertura")
        copertura = reader->readElementText().toInt();
    if(reader->readNextStartElement() && reader->name()=="AppoggiaSci")
        appoggiaSci = reader->readElementText().toInt();
    return new Seggiovia(r->id,r->immagine,r->nome,r->capienzaVeicolo,r->quotaValle,r->quotaMonte,r->potenzaMotore,r->velocitaEsercizio,
                         r->produttore,r->annoCostruzione,ammorsamento,copertura,appoggiaSci);
}

/**
 * @brief Seggiovia::write
 * @param writer
 *
 * permette la serializzazione in XML di un oggetto di classe seggiovia
 * richiama il metodo write delle classi superiori per aumentare
 * l'estendibilita' del codice
 */
void Seggiovia::write(QXmlStreamWriter* writer) const {
    MovimentazioneContinua::write(writer);
    writer->writeStartElement("Copertura");
    writer->writeCharacters(QString::number(copertura));
    writer->writeEndElement();
    writer->writeStartElement("AppoggiaSci");
    writer->writeCharacters(QString::number(appoggiaSci));
    writer->writeEndElement();
    writer->writeEndElement();
}





