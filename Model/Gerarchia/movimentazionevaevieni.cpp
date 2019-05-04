#include "Model/Gerarchia/movimentazionevaevieni.h"


MovimentazioneVaeVieni::MovimentazioneVaeVieni(const unsigned short& i, const string& img, const string& nm, const short& c, const unsigned int& qv, const unsigned int& qm,
                                               const double& pm,const float& ve, const string& pro, const short& ac, const float& tp) :
    Impianto(i,img,nm,c,qv,qm,pm,ve,pro,ac), tempoPausa(tp) {}

/* Ritorna la movimentazione */
std::string MovimentazioneVaeVieni::getMovimentazione() const{
    return "Va e Vieni";
}


/* Getters per l'ottenimento dei campi radicati nella classe astratta movimentazioneVaeVieni */
int MovimentazioneVaeVieni::getTempoPausa() const{
    return tempoPausa;
}

/* Setters per la modifica dei campi radicati nella classe astratta  movimentazioneVaeVieni */
void MovimentazioneVaeVieni::setTempoPausa(const int& tp){
    tempoPausa = tp;
}

/* Imposto il campo statico profiloPreferenziale */
string MovimentazioneVaeVieni::profiloPreferenziale = "Concavo";

/* Deserializzazione */
void MovimentazioneVaeVieni::write(QXmlStreamWriter *writer) const{
    Impianto::write(writer);
    writer->writeStartElement("TempoAttesa");
    writer->writeCharacters(QString::number(tempoPausa));
    writer->writeEndElement();
}
