#include "Model/Gerarchia/sciovia.h"
#include "Model/invalidstringtoenumexception.h"


/**
 * Campo dati statico che contiene il valore
 * massimo di velocita' di esercizio di una sciovia
 */
float Sciovia::velocitaEsercizioMax = 2.5;

/**
 * @brief Sciovia::Sciovia
 *
 * Costruttore della classe sciovia,
 * esegue dei controlli sui campi,
 * come la velocita' d'esercizio
 *
 * La capienza di un singolo veicolo di una sciovia e' determinata dal tipo di gancio, viene quindi creato l'oggetto con un intero in base al gancio,
 * se il tipo di gancio e' a piattello allora la capienza dei veicoli sara' 1 ,invece ad ancora, la capienza dei veicoli sara' 2.
 * Tutte le sciovie hanno ammorsamento fisso.
 */
Sciovia::Sciovia(const unsigned short& i, const string& img, const string& nm, const unsigned int& qv, const unsigned int& qm,
                 const double& pm, const float& ve, const Produttore& pro, const short& ac,const Gancio& t) :
                MovimentazioneContinua(i, img, nm,t.toString() == "piattello" ? 1 : 2,qv,qm,pm,ve,pro,ac,string("fisso")), gancio(t){
    if(getVelocitaEsercizio() > velocitaEsercizioMax) setVelocitaEsercizio(-1);
}

/**
 * @brief Sciovia::getGancio
 * @return gancio
 */
Gancio Sciovia::getGancio() const{
    return gancio;
}

/**
 * @brief Sciovia::setGancio
 * @param g
 */
void Sciovia::setGancio(const Gancio &g){
    gancio = g;
}

/**
 * @brief Sciovia::clone
 * @return Sciovia pointer
 *
 * metodo di clonazione polimorfa
 */
Sciovia* Sciovia::clone() const{
    return new Sciovia(*this);
}

/**
 * @brief Sciovia::getType
 * @return std::string "sciovia"
 */
string Sciovia::getType() const{
    return "sciovia";
}

/**
 * @brief Sciovia::build
 * @param reader
 * @param r
 * @return Sciovia pointer
 *
 * metodo che si occupa di costruire un oggetto di classe Sciovia
 * deserializzando un file in formato XML
 * Il metodo viene chiamato dalla classe base, dalla quale vengono
 * passati i valori radicati nella classe base.
 * inoltre ritorna un puntatore all'oggetto appena costruito
 */
Sciovia* Sciovia::build(QXmlStreamReader* reader,const values* r){
    string gancio;
    reader->readNextStartElement(); /** salta ammorsamento */
    reader->readNextStartElement();
    if(reader->readNextStartElement() && reader->name()=="Gancio")
        gancio = reader->readElementText().toStdString();
    return new Sciovia(r->id,r->immagine,r->nome,r->quotaValle,r->quotaMonte,r->potenzaMotore,r->velocitaEsercizio,
                       r->produttore,r->annoCostruzione,gancio);
}

/**
 * @brief Sciovia::write
 * @param writer
 *
 * permette la serializzazione in XML di un oggetto di classe sciovia
 * richiama il metodo write delle classi superiori per aumentare
 * l'estendibilita' del codice
 */
void Sciovia::write(QXmlStreamWriter* writer) const{
    MovimentazioneContinua::write(writer);
    writer->writeStartElement("Gancio");
    writer->writeCharacters(QString::fromStdString(gancio.toString()));
    writer->writeEndElement();
    writer->writeEndElement();
}

