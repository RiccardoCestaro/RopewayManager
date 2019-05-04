#include "Model/Gerarchia/impianto.h"

/* Costruttore di impianto */
Impianto::Impianto(const unsigned short& i,const string& img, const string& nm,const short& c, const unsigned int& qv, const unsigned int& qm, const double& pm, const float& ve, const string& pro, const short& ac) :
                    id(i),immagine(img), nome(nm), capienzaVeicolo(c), quotaValle(qv), quotaMonte(qm), potenzaMotore(pm), velocitaEsercizio(ve), produttore(pro), annoCostruzione(ac) {}


/* Getters per l'ottenimento dei campi radicati nella classe astratta impianto */
unsigned short Impianto::getId() const{
    return id;
}
string Impianto::getNome() const{
    return nome;
}
short Impianto::getCapienzaVeicolo() const{
    return capienzaVeicolo;
}
unsigned int Impianto::getQuotaValle() const{
    return quotaValle;
}
unsigned int Impianto::getQuotaMonte() const{
    return quotaMonte;
}
double Impianto::getPotenzaMotore() const{
    return potenzaMotore;
}
float Impianto::getVelocitaEsercizio() const{
    return velocitaEsercizio;
}
string Impianto::getSigla() const{
    return sigla;
}
string Impianto::getProduttore() const{
    return produttore;
}
short Impianto::getAnnoCostruzione() const{
    return annoCostruzione;
}


/* Setters per la modifica dei campi radicati nella classe astratta impianto */

void Impianto::setId(const unsigned short & i){
    id = i;
}
void Impianto::setNome(const string & nm){
    nome = nm;
}
void Impianto::setCapienzaVeicolo(const short& c){
    capienzaVeicolo = c;
}
void Impianto::setQuotaValle(const unsigned int & qv){
    quotaValle = qv;
}
void Impianto::setQuotaMonte(const unsigned int & qm){
    quotaMonte = qm;
}
void Impianto::setPotenzaMotore(const double & pm){
    potenzaMotore = pm;
}
void Impianto::setVelocitaEsercizio(const float & ve){
    velocitaEsercizio = ve;
}
void Impianto::setProduttore(const string & pro){
    produttore = pro;
}
void Impianto::setAnnoCostruzione(const short & ac){
    annoCostruzione = ac;
}
string Impianto::getImmagine() const{
    return immagine;
}
void Impianto::setImmagine(const string &img){
    immagine = img;
}

/* Deserializzazione */
Impianto::values* Impianto::read(QXmlStreamReader* reader){
    Impianto::values* results = new Impianto::values;

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

    return results;
}

void Impianto::write(QXmlStreamWriter* writer) const{

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
    writer->writeCharacters(QString::fromStdString(produttore));
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
    writer->writeCharacters(QString::number(velocitaEsercizio));
    writer->writeEndElement();
    writer->writeStartElement("PotenzaMotore");
    writer->writeCharacters(QString::number(potenzaMotore));
    writer->writeEndElement();
}

/* Lambda espressione per confrontare due stringhe in modo case insensitive */

bool Impianto::compareString(const string& str1,const string& str2){
    return ((str1.size() == str2.size()) && std::equal(str1.begin(), str1.end(), str2.begin(), [](const char & c1, const char & c2){
                            return (c1 == c2 || std::toupper(c1) == std::toupper(c2));
        }));
}

/*
 *  DA QUI IN POI DA SISTEMARE
 *
 */

/* Vedere se mantenere */
unsigned int Impianto::dislivello() const{
    return quotaMonte-quotaValle;
}





