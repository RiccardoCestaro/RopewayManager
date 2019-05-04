#include "Model/Gerarchia/funivia.h"

float Funivia::velocitaEsercizioMax = 12;

Funivia::Funivia(const unsigned short& i, const string& img, const string& nm, const short& c, const unsigned int& qv, const unsigned int& qm, const double& pm, const float& ve, const string& pro,
                 const short& ac, const float& tp) : MovimentazioneVaeVieni(i, img, nm, c, qv, qm, pm, ve, pro, ac, tp)
{
    /* da valutare se aggiungere eccezioni */
    /* esegue dei controlli sui campi */
    if(getVelocitaEsercizio() > velocitaEsercizioMax) setVelocitaEsercizio(-1);
}


/* Metodo per la clonazione polimorfa */
Funivia* Funivia::clone() const{
    return new Funivia(*this);
}

/* Metodo per il ritorno del tipo di impianto */
string Funivia::getType() const{
    return "funivia";
}

/* Portata oraria */
unsigned int Funivia::PortataOraria() const{
    return 0;
}

/* Serializzazione */
Funivia *Funivia::read(QXmlStreamReader* reader){

    Impianto::values* r = Impianto::read(reader);

    int tempoPausa;

    if(reader->readNextStartElement() && reader->name()=="TempoAttesa")
        tempoPausa = reader->readElementText().toInt();

    return new Funivia(r->id,r->immagine,r->nome,r->capienzaVeicolo,r->quotaValle,r->quotaMonte,r->potenzaMotore,r->velocitaEsercizio,
                       r->produttore,r->annoCostruzione,tempoPausa);

}

void Funivia::write(QXmlStreamWriter* writer){
    MovimentazioneVaeVieni::write(writer);
}
