#include "Model/Gerarchia/impianto.h"
#include "Model/Gerarchia/telemix.h"
#include "Model/Gerarchia/funicolare.h"
#include "Model/Gerarchia/sciovia.h"
#include "Model/Gerarchia/funifor.h"
#include "Model/Gerarchia/funivia.h"

#include "Model/Gerarchia/Utils/tipologia.h"

#include <QRegularExpression>

/**
 * @brief Impianto::Impianto
 *
 * Costruttore della classe impianto
 */
Impianto::Impianto(const unsigned short& i,const string& img, const string& nm,const short& c, const unsigned int& qv,
                   const unsigned int& qm, const double& pm, const float& ve, const Produttore& pro, const short& ac)
                    : id(i),immagine(img), nome(nm), capienzaVeicolo(c), quotaValle(qv), quotaMonte(qm),
                      potenzaMotore(pm), velocitaEsercizio(ve), produttore(pro), annoCostruzione(ac) {}


/**
 * @brief Impianto::getId
 * @return id
 */
unsigned short Impianto::getId() const{
    return id;
}

/**
 * @brief Impianto::getNome
 * @return nome
 */
string Impianto::getNome() const{
    return nome;
}

/**
 * @brief Impianto::getCapienzaVeicolo
 * @return capienzaVeicoli
 */
short Impianto::getCapienzaVeicolo() const{
    return capienzaVeicolo;
}

/**
 * @brief Impianto::getQuotaValle
 * @return quotaValle
 */
unsigned int Impianto::getQuotaValle() const{
    return quotaValle;
}

/**
 * @brief Impianto::getQuotaMonte
 * @return quotaMonte
 */
unsigned int Impianto::getQuotaMonte() const{
    return quotaMonte;
}

/**
 * @brief Impianto::getPotenzaMotore
 * @return potenzaMotore
 */
double Impianto::getPotenzaMotore() const{
    return potenzaMotore;
}

/**
 * @brief Impianto::getVelocitaEsercizio
 * @return velocitaEsercizio
 */
float Impianto::getVelocitaEsercizio() const{
    return velocitaEsercizio;
}

/**
 * @brief Impianto::getProduttore
 * @return produttore
 */
Produttore Impianto::getProduttore() const{
    return produttore;
}

/**
 * @brief Impianto::getAnnoCostruzione
 * @return annoCostruzione
 */
short Impianto::getAnnoCostruzione() const{
    return annoCostruzione;
}

/**
 * @brief Impianto::getImmagine
 * @return immagine
 */
string Impianto::getImmagine() const{
    return immagine;
}

/**
 * @brief Impianto::setId
 * @param i
 */
void Impianto::setId(const unsigned short & i){
    id = i;
}

/**
 * @brief Impianto::setNome
 * @param nm
 */
void Impianto::setNome(const string & nm){
    nome = nm;
}

/**
 * @brief Impianto::setCapienzaVeicolo
 * @param c
 */
void Impianto::setCapienzaVeicolo(const short& c){
    capienzaVeicolo = c;
}

/**
 * @brief Impianto::setQuotaValle
 * @param qv
 */
void Impianto::setQuotaValle(const unsigned int & qv){
    quotaValle = qv;
}

/**
 * @brief Impianto::setQuotaMonte
 * @param qm
 */
void Impianto::setQuotaMonte(const unsigned int & qm){
    quotaMonte = qm;
}

/**
 * @brief Impianto::setPotenzaMotore
 * @param pm
 */
void Impianto::setPotenzaMotore(const double & pm){
    potenzaMotore = pm;
}

/**
 * @brief Impianto::setVelocitaEsercizio
 * @param ve
 */
void Impianto::setVelocitaEsercizio(const float & ve){
    velocitaEsercizio = ve;
}

/**
 * @brief Impianto::setProduttore
 * @param pro
 */
void Impianto::setProduttore(const Produttore& pro){
    produttore = pro;
}

/**
 * @brief Impianto::setAnnoCostruzione
 * @param ac
 */
void Impianto::setAnnoCostruzione(const short & ac){
    annoCostruzione = ac;
}

/**
 * @brief Impianto::setImmagine
 * @param img
 */
void Impianto::setImmagine(const string &img){
    immagine = img;
}

/**
 * @brief Impianto::read
 * @param reader
 * @return Impianto pointer
 *
 * metodo che si occupa di costruire un oggetto di classe Impianto
 * deserializzando un file in formato XML
 * Il metodo si occupa di deserializzare i campi comuni radicati
 * in impianto, e poi, in base al tipo di impianto, vengono richiamati
 * i metodi di costruzione che deserializzano i campi specifici.
 * Il metodo della sottoclasse ritorna un puntatore all'oggetto
 * costruito, che verra' ritornato da questo metodo.
 */
Impianto* Impianto::read(QXmlStreamReader* reader){
    Impianto::values* results = new Impianto::values;
    short tipo;
    if(reader->readNextStartElement() && reader->name()=="Tipo")
    /* Tag Tipo */
        tipo = static_cast<short>(Tipologia::values.indexOf(reader->readElementText()));

    if(reader->readNextStartElement() && reader->name()=="Id")
    /* Tag Id */
        results->id = reader->readElementText().toUShort();

    if(reader->readNextStartElement() && reader->name()=="Immagine")
    /* Tag Immagine */
        results->immagine = reader->readElementText().toStdString();

    if(reader->readNextStartElement() && reader->name()=="Nome")
    /* Tag Nome */
        results->nome = reader->readElementText().toStdString();

    if(reader->readNextStartElement() && reader->name()=="Capienza")
    /* Tag Capienza */
        results->capienzaVeicolo = reader->readElementText().toShort();

    if(reader->readNextStartElement() && reader->name()=="Produttore")
    /* Tag Produttore */
        results->produttore = reader->readElementText().toStdString();

    if(reader->readNextStartElement() && reader->name()=="AnnoCostruzione")
    /* Tag AnnoCostruzione */
        results->annoCostruzione = reader->readElementText().toShort();

    if(reader->readNextStartElement() && reader->name()=="QuotaValle")
    /* Tag QuotaValle */
        results->quotaValle = reader->readElementText().toUInt();

    if(reader->readNextStartElement() && reader->name()=="QuotaMonte")
    /* Tag QuotaMonte */
        results->quotaMonte = reader->readElementText().toUInt();

    if(reader->readNextStartElement() && reader->name()=="VelocitaEsercizio")
    /* Tag VelocitaEsercizio */
        results->velocitaEsercizio = reader->readElementText().toFloat();

    if(reader->readNextStartElement() && reader->name()=="PotenzaMotore")
    /* Tag PotenzaMotore */
        results->potenzaMotore = reader->readElementText().toDouble();

    Impianto* impianto = nullptr;
    switch(tipo){
    case 0:
        impianto = Seggiovia::build(reader,results);
        break;
    case 1:
        impianto = Cabinovia::build(reader,results);
        break;
    case 2:
        impianto = Telemix::build(reader,results);
        break;
    case 3:
        impianto = Sciovia::build(reader,results);
        break;
    case 4:
        impianto = Funivia::build(reader,results);
        break;
    case 5:
        impianto = Funifor::build(reader,results);
        break;
    case 6:
        impianto = Funicolare::build(reader,results);
        break;
    }
    return impianto;
}

/**
 * @brief Impianto::write
 * @param writer
 *
 * permette la serializzazione in XML di un oggetto di classe impianto
 * o derivati.
 * Il metodo viene chiamato dalle sottoclassi, per serializzare i
 * campi comuni radicati in impianto.
 */
void Impianto::write(QXmlStreamWriter* writer) const{
    writer->writeStartElement("Impianto");
    writer->writeStartElement("Tipo");
    writer->writeCharacters(QString::fromStdString(getType()));
    writer->writeEndElement();
    writer->writeStartElement("Id");
    writer->writeCharacters(QString::number(id));
    writer->writeEndElement();
    writer->writeStartElement("Immagine");
    writer->writeCharacters(QString::fromStdString(immagine));
    writer->writeEndElement();
    writer->writeStartElement("Nome");
    writer->writeCharacters(QString::fromStdString(nome));
    writer->writeEndElement();
    writer->writeStartElement("Capienza");
    writer->writeCharacters(QString::number(capienzaVeicolo));
    writer->writeEndElement();
    writer->writeStartElement("Produttore");
    writer->writeCharacters(QString::fromStdString(produttore.toString()));
    writer->writeEndElement();
    writer->writeStartElement("AnnoCostruzione");
    writer->writeCharacters(QString::number(annoCostruzione));
    writer->writeEndElement();
    writer->writeStartElement("QuotaValle");
    writer->writeCharacters(QString::number(quotaValle));
    writer->writeEndElement();
    writer->writeStartElement("QuotaMonte");
    writer->writeCharacters(QString::number(quotaMonte));
    writer->writeEndElement();
    writer->writeStartElement("VelocitaEsercizio");
    writer->writeCharacters(QString::number(static_cast<double>(velocitaEsercizio)));
    writer->writeEndElement();
    writer->writeStartElement("PotenzaMotore");
    writer->writeCharacters(QString::number(potenzaMotore));
    writer->writeEndElement();
}






