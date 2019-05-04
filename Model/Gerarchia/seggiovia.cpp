#include "Model/Gerarchia/seggiovia.h"

/* Inizializzazione dei campi statici */
float Seggiovia::velocitaEsercizioAutomaticoMax = 6;
float Seggiovia::velocitaEsercizioFissoMax = 2.5;


Seggiovia::Seggiovia(const unsigned short& i, const string& img, const string& nm, const short& ca, const unsigned int& qv, const unsigned int& qm, const double& pm,
                     const float& ve, const string& pro, const short& ac, const Amm& a, const bool& c, const bool& as) :
                MovimentazioneContinua(i,img,nm,ca,qv,qm,pm,ve,pro,ac,a), copertura(c), appoggiaSci(as)
{
    /* da valutare se aggiungere eccezioni */
    /* esegue dei controlli sui campi */
    if(Impianto::compareString(getAmmorsamento().toString(),"fisso") && getVelocitaEsercizio() > velocitaEsercizioFissoMax) setVelocitaEsercizio(-1);
    else if(Impianto::compareString(getAmmorsamento().toString(),"automatico") && getVelocitaEsercizio() > velocitaEsercizioAutomaticoMax) setVelocitaEsercizio(-1);
}


/* Getters e Setters per l'ottenimento e la modifica dei campi della classe cabinovia */
bool Seggiovia::isCoperta() const{
    return copertura;
}
bool Seggiovia::hasAppoggiaSci() const{
    return appoggiaSci;
}
void Seggiovia::setCopertura(const bool& value){
    copertura = value;
}
void Seggiovia::setAppoggiaSci(const bool& value){
    appoggiaSci = value;
}

/* vedere se mantenere */
unsigned int Seggiovia::PortataOraria() const{
    return 0; //vedere su funivie.org
}

/* Metodo per la clonazione polimorfa */
Seggiovia* Seggiovia::clone() const {
    return new Seggiovia(*this);
}
/* metodo per il ritorno del tipo di impianto */
string Seggiovia::getType() const{
    return "seggiovia";
}

/* Metodo per la deserializzazione */
Seggiovia* Seggiovia::read(QXmlStreamReader *reader){

    Impianto::values* r = Impianto::read(reader);

    Amm ammorsamento;
    bool copertura;
    bool appoggiaSci;

    if(reader->readNextStartElement() && reader->name()=="Ammorsamento")
        ammorsamento =  reader->readElementText().toStdString();
    if(reader->readNextStartElement() && reader->name()=="Copertura")
        copertura = reader->readElementText().toInt();
    if(reader->readNextStartElement() && reader->name()=="AppoggiaSci")
        appoggiaSci = reader->readElementText().toInt();

    std::cout << r->id<< r->nome<<r->capienzaVeicolo<<r->quotaValle<<r->quotaMonte<<r->potenzaMotore<<r->velocitaEsercizio<<
            r->produttore << r->annoCostruzione << ammorsamento.toString() << copertura << appoggiaSci << std::endl;

    return new Seggiovia(r->id,r->immagine,r->nome,r->capienzaVeicolo,r->quotaValle,r->quotaMonte,r->potenzaMotore,r->velocitaEsercizio,
                         r->produttore,r->annoCostruzione,ammorsamento,copertura,appoggiaSci);
}

void Seggiovia::write(QXmlStreamWriter* writer) const {
    MovimentazioneContinua::write(writer);
    writer->writeStartElement("Copertura");
    writer->writeCharacters(QString::number(copertura));
    writer->writeEndElement();
    writer->writeStartElement("AppoggiaSci");
    writer->writeCharacters(QString::number(appoggiaSci));
    writer->writeEndElement();
}





