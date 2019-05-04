#include "Model/Gerarchia/cabinovia.h"

/* Inizializzazione dei campi statici */
float Cabinovia::velocitaEsercizioAutomaticoMax = 7;
float Cabinovia::velocitaEsercizioFissoMax = 2;
short Cabinovia::numeroFuniMax = 3;


Cabinovia::Cabinovia(const unsigned short& i,const string& img, const string& nm, const short& c, const unsigned int& qv, const unsigned int& qm, const double& pm, const float& ve,
                     const string& pro, const short& ac, const Amm& a, const short& nf) : MovimentazioneContinua(i,img,nm,c,qv,qm,pm,ve,pro,ac,a), numeroFuni(nf)
{
    /* da valutare se aggiungere eccezioni */
    /* esegue dei controlli sui campi */
    if (numeroFuni > 3 || numeroFuni < 1) numeroFuni = -1;
    if(Impianto::compareString(getAmmorsamento().toString(),"fisso") && getVelocitaEsercizio() > velocitaEsercizioFissoMax) setVelocitaEsercizio(-1);
    else if(Impianto::compareString(getAmmorsamento().toString(), "automatico") && getVelocitaEsercizio() > velocitaEsercizioAutomaticoMax) setVelocitaEsercizio(-1);
}



/* Getters e Setters per l'ottenimento e la modifica dei campi della classe cabinovia */
short Cabinovia::getNumeroFuni() const{
    return numeroFuni;
}
void Cabinovia::setNumeroFuni(const short& value){
    numeroFuni = value;
}

/* metodo per la clonazione polimorfa */
Cabinovia* Cabinovia::clone() const {
    return new Cabinovia(*this);
}

/* metodo per il ritorno del tipo di impianto */
string Cabinovia::getType() const{
    return "cabinovia";
}

/* vedere piu' avanti se implementare */
unsigned int Cabinovia::PortataOraria() const{
    return 0; //vedere su funivie.org
    // trovare distanza veicoli, lunghezza del cavo diviso il numero di seggiole - 1
    // (3600/distaza veicoli)*velocitaMax*capienzaVeicoli
}

/* Metodo per la deserializzazione */
Cabinovia* Cabinovia::read(QXmlStreamReader *reader){

    Impianto::values* r = Impianto::read(reader);

    Amm ammorsamento;
    short numeroFuni;

    if(reader->readNextStartElement() && reader->name()=="Ammorsamento")
        ammorsamento =  reader->readElementText().toStdString();
    if(reader->readNextStartElement() && reader->name()=="NumeroFuni")
        numeroFuni = reader->readElementText().toShort();

    return new Cabinovia(r->id,r->immagine,r->nome,r->capienzaVeicolo,r->quotaValle,r->quotaMonte,r->potenzaMotore,r->velocitaEsercizio,
                         r->produttore,r->annoCostruzione,ammorsamento,numeroFuni);
}

void Cabinovia::write(QXmlStreamWriter *writer) const{
    MovimentazioneContinua::write(writer);
    writer->writeStartElement("NumeroFuni");
    writer->writeCharacters(QString::number(numeroFuni));
    writer->writeEndElement();
}









