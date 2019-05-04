#include "Model/Gerarchia/telemix.h"

/*
 * L'ammorsamento di una telemix e' sempre automatico
 * ed il numero di funi e' sempre pari a 1
 */

Telemix::Telemix(const unsigned short& i, const string& img, const string& nm, const short& cs,const short& cc, const unsigned int& qv, const unsigned int& qm, const double& pm,
                 const float& ve, const string& pro, const short& ac, const bool& c, const bool& as) :
    MovimentazioneContinua (i,img,nm,cs,qv,qm,pm,ve,pro,ac,string("automatico")),
            Seggiovia(i,img,nm,cs,qv,qm,pm,ve,pro,ac,string("automatico"),c,as), Cabinovia(i,img,nm,cc,qv,qm,pm,ve,pro,ac,string("automatico"),1)
{
    /* da valutare se aggiungere eccezioni */
    /* esegue dei controlli sui campi */
    if(getVelocitaEsercizio() > Seggiovia::velocitaEsercizioAutomaticoMax) setVelocitaEsercizio(-1);
}


/* metodo di clonazione polimorfa */
Telemix* Telemix::clone() const{
    return new Telemix(*this);
}
/* metodo per il ritorno del tipo di impianto */
string Telemix::getType() const{
    return "telemix";
}


/* Getters e Setters per l'ottenimento e la modifica dei campi della classe seggiovia */
short Telemix::getCapienzaCabina() const{
    return capienzaCabina;
}
void Telemix::setCapienzaCabina(const short& value){
    capienzaCabina = value;
}

/* vedere se mantenere */
unsigned int Telemix::PortataOraria() const{
    return 0;
}

/* Deserializzazione */
Telemix *Telemix::read(QXmlStreamReader* reader){

    Impianto::values* r = Impianto::read(reader);

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
/* Serializzazione */
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
}

