#include "Model/Gerarchia/funifor.h"

float Funifor::velocitaEsercizioMax = 14;
short Funifor::numeroCabineMax = 2;


Funifor::Funifor(const unsigned short& i, const string& img, const string& nm, const short& c, const unsigned int& qv, const unsigned int& qm, const double& pm, const float& ve, const string& pro,
                 const short& ac, const float& tp, const short& nc) : MovimentazioneVaeVieni(i, img, nm, c, qv, qm, pm, ve, pro, ac, tp), numeroCabine(nc)
{
    /* da valutare se aggiungere eccezioni */
    /* esegue dei controlli sui campi */
    if(getVelocitaEsercizio() > velocitaEsercizioMax) setVelocitaEsercizio(-1);
    if(numeroCabine > numeroCabineMax) numeroCabine = -1;
}


/* Getters e Setters per l'ottenimento e la modifica dei campi della classe funifor */
short Funifor::getNumeroCabine() const{
    return numeroCabine;
}
void Funifor::setNumeroCabine(const short& nc){
    numeroCabine = nc;
}

/* Metodo per la clonazione polimorfa */
Funifor* Funifor::clone() const{
    return new Funifor(*this);
}
/* Metodo per il ritorno del tipo di impianto */
string Funifor::getType() const {
    return "funifor";
}

/* Vedere se implementare */
unsigned int Funifor::PortataOraria() const{
    return 0;
}

/* Serializzazione */
Funifor *Funifor::read(QXmlStreamReader* reader){

    Impianto::values* r = Impianto::read(reader);

    int tempoPausa;
    short numeroCabine;

    if(reader->readNextStartElement() && reader->name()=="TempoAttesa")
        tempoPausa = reader->readElementText().toInt();
    if(reader->readNextStartElement() && reader->name()=="NumeroCabine")
        numeroCabine = reader->readElementText().toShort();

    return new Funifor(r->id,r->immagine,r->nome,r->capienzaVeicolo,r->quotaValle,r->quotaMonte,r->potenzaMotore,r->velocitaEsercizio,
                       r->produttore,r->annoCostruzione,tempoPausa,numeroCabine);

}

void Funifor::write(QXmlStreamWriter* writer) const{
    MovimentazioneVaeVieni::write(writer);
    writer->writeStartElement("NumeroCabine");
    writer->writeCharacters(QString::number(numeroCabine));
    writer->writeEndElement();
}
