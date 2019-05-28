#include "Model/Gerarchia/movimentazionevaevieni.h"

/**
 * Campo dati statico che contiene il profilo preferenziale
 * della classe statica MovimentazioneVaeVieni
 */
string MovimentazioneVaeVieni::profiloPreferenziale = "Concavo";

/**
 * @brief MovimentazioneVaeVieni::MovimentazioneVaeVieni
 *
 * Costruttore della classe MovimentazioneVaeVieni
 */
MovimentazioneVaeVieni::MovimentazioneVaeVieni(const unsigned short& i, const string& img, const string& nm, const short& c,
                                               const unsigned int& qv, const unsigned int& qm, const double& pm,
                                               const float& ve, const Produttore& pro, const short& ac, const float& tp)
                                                : Impianto(i,img,nm,c,qv,qm,pm,ve,pro,ac), tempoPausa(tp) {}

/**
 * @brief MovimentazioneVaeVieni::getMovimentazione
 * @return std::string "va e vieni"
 */
std::string MovimentazioneVaeVieni::getMovimentazione() const{
    return "Va e Vieni";
}

/**
 * @brief MovimentazioneVaeVieni::getTempoPausa
 * @return tempoPausa
 */
float MovimentazioneVaeVieni::getTempoPausa() const{
    return tempoPausa;
}

/**
 * @brief MovimentazioneVaeVieni::setTempoPausa
 * @param tp
 */
void MovimentazioneVaeVieni::setTempoPausa(const float& tp){
    tempoPausa = tp;
}

/**
 * @brief MovimentazioneVaeVieni::write
 * @param writer
 *
 * permette la serializzazione in XML di un oggetto di classe MovimentazioneVaeVieni
 * richiama il metodo write delle classi superiori per aumentare
 * l'estendibilita' del codice
 */
void MovimentazioneVaeVieni::write(QXmlStreamWriter *writer) const{
    Impianto::write(writer);
    writer->writeStartElement("TempoAttesa");
    writer->writeCharacters(QString::number(static_cast<double>(tempoPausa)));
    writer->writeEndElement();
}
