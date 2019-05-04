#include "Model/Gerarchia/sciovia.h"
#include "invalidstringtoenumexception.h"

Gancio::Gancio(const string& g) : value(Impianto::compareString(g,"piattello") ? true : (Impianto::compareString(g,"ancora") ? false : throw(InvalidStringToEnumException()))){}
string Gancio::toString() const{
    if (value == true) return "piattello";
    return "ancora";
}



/*
 * La capienza di un singolo veicolo di una sciovia e' determinata dal tipo di gancio, viene quindi creato l'oggetto con un intero in base al gancio,
 * se il tipo di gancio e' a piattello allora la capienza dei veicoli sara' 1 ,invece ad ancora, la capienza dei veicoli sara' 2.
 * Tutte le sciovie hanno ammorsamento fisso.
 */

float Sciovia::velocitaEsercizioMax = 2.5;

Sciovia::Sciovia(const unsigned short& i, const string& img, const string& nm, const unsigned int& qv, const unsigned int& qm, const double& pm,
                 const float& ve, const string& pro, const short& ac,const Gancio& t) :
                MovimentazioneContinua(i, img, nm,t.toString() == "piattello" ? 1 : 2,qv,qm,pm,ve,pro,ac,string("fisso")), gancio(t)
{
    /* da valutare se aggiungere eccezioni */
    /* esegue dei controlli sui campi */
    if(getVelocitaEsercizio() > velocitaEsercizioMax) setVelocitaEsercizio(-1);
}

/* Getters e Setters per l'ottenimento e la modifica dei campi della classe sciovia */
Gancio Sciovia::getGancio() const{
    return gancio;
}
void Sciovia::setGancio(const Gancio &value){
    gancio = value;
}

/* Metodo per la clonazione polimorfa */
Sciovia* Sciovia::clone() const{
    return new Sciovia(*this);
}
/* Metodo per il ritorno del tipo di impianto */
string Sciovia::getType() const{
    return "sciovia";
}
/* vedere se mantenere */
unsigned int Sciovia::PortataOraria() const{
    return 0;
}

/* Serializzazione */
Sciovia* Sciovia::read(QXmlStreamReader* reader){

    Impianto::values* r = Impianto::read(reader);

    string gancio;

    /* salta ammorsamento */
    reader->readNextStartElement();
    reader->readNextStartElement();

    if(reader->readNextStartElement() && reader->name()=="Gancio"){
        gancio = reader->readElementText().toStdString();
    }

    return new Sciovia(r->id,r->immagine,r->nome,r->quotaValle,r->quotaMonte,r->potenzaMotore,r->velocitaEsercizio,
                       r->produttore,r->annoCostruzione,gancio);

}

void Sciovia::write(QXmlStreamWriter* writer) const{
    MovimentazioneContinua::write(writer);
    writer->writeStartElement("Gancio");
    writer->writeCharacters(QString::fromStdString(gancio.toString()));
    writer->writeEndElement();
}

