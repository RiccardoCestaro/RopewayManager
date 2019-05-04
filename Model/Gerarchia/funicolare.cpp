#include "Model/Gerarchia/funicolare.h"
#include "invalidstringtoenumexception.h"
#include <iostream>

#include <string>
#include <cctype>




/* Costruttore della classe tecBin tramite string */
tecBin::tecBin(const string& s) : value(Impianto::compareString(s,"unico") ? true : (Impianto::compareString(s,"doppio") ? false : throw (InvalidStringToEnumException()))){}
/* Metodo ritornante la stringa corrispondente al boleano */
string tecBin::toString() const{
    if(value == true) return "unico";
    else return "doppio";
}


/* Imposta la massima velocita dei funicolari a 10 metri al secondo */
float Funicolare::velocitaEsercizioMax = 10;

Funicolare::Funicolare(const unsigned short& i, const string& img, const string& nm, const short& c, const unsigned int& qv, const unsigned int& qm, const double& pm, const float& ve,
                       const string& pro, const short& ac, const float& tp, const tecBin& t) : MovimentazioneVaeVieni(i, img, nm, c, qv, qm, pm, ve, pro, ac, tp), tecBinario(t)
{
    /* da valutare se aggiungere eccezioni */
    /* esegue dei controlli sui campi */
    if(getVelocitaEsercizio() > velocitaEsercizioMax) setVelocitaEsercizio(-1);
}


/* Getters e Setters per l'ottenimento e la modifica dei campi della classe funicolare */
tecBin Funicolare::getTecBinario() const{
    return tecBinario;
}
void Funicolare::setTecBinario(const tecBin &v){
    tecBinario = v;
}

/* Metodo per la clonazione polimorfa */
Funicolare* Funicolare::clone() const {
    return new Funicolare(*this);
}
/* Metodo per ritornare il tipo dell'impianto */
string Funicolare::getType() const{
    return "funicolare";
}


/* Vedere se mantenere */
unsigned int Funicolare::PortataOraria() const{
    return 0;
}

/* Serializzazione */
Funicolare *Funicolare::read(QXmlStreamReader* reader){

    Impianto::values* r = Impianto::read(reader);

    int tempoPausa;
    string tecBinario;

    if(reader->readNextStartElement() && reader->name()=="TempoAttesa")
        tempoPausa = reader->readElementText().toInt();
    if(reader->readNextStartElement() && reader->name()=="TecnicaBinario")
        tecBinario = reader->readElementText().toStdString();

    return new Funicolare(r->id,r->immagine,r->nome,r->capienzaVeicolo,r->quotaValle,r->quotaMonte,r->potenzaMotore,r->velocitaEsercizio,
                          r->produttore,r->annoCostruzione,tempoPausa,tecBinario);

}


void Funicolare::write(QXmlStreamWriter* writer) const{

    MovimentazioneVaeVieni::write(writer);
    writer->writeStartElement("TecnicaBinario");
    writer->writeCharacters(QString::fromStdString(tecBinario.toString()));
    writer->writeEndElement();
}

