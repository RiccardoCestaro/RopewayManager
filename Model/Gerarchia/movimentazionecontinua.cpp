#include "Model/Gerarchia/movimentazionecontinua.h"
#include "invalidstringtoenumexception.h"

/**
 * Campo dati statico che contiene il profilo preferenziale della
 * classe di topo MovimentazioneContinua
 */
string MovimentazioneContinua::profiloPreferenziale = "Convesso";

/**
 * @brief MovimentazioneContinua::MovimentazioneContinua
 *
 * Costruttore della classe MovimentazioneContinua
 */
MovimentazioneContinua::MovimentazioneContinua(const unsigned short& i, const string& img, const string& nm, const short& c, const unsigned int& qv,
                                               const unsigned int& qm, const double& pm, const float& ve, const Produttore& pro, const short& ac, const Ammorsamento& a) :
    Impianto(i,img,nm,c,qv,qm,pm,ve,pro,ac), ammorsamento(a){}

/**
 * @brief MovimentazioneContinua::getMovimentazione
 * @return std::string "Continua"
 */
std::string MovimentazioneContinua::getMovimentazione() const{
    return "Continua";
}

/**
 * @brief MovimentazioneContinua::getAmmorsamento
 * @return ammorsamento
 */
Ammorsamento MovimentazioneContinua::getAmmorsamento() const{
    return ammorsamento;
}

/**
 * @brief MovimentazioneContinua::setAmmorsamento
 * @param amm
 */
void MovimentazioneContinua::setAmmorsamento(const Ammorsamento &amm){
    ammorsamento = amm;
}

/**
 * @brief MovimentazioneContinua::write
 * @param writer
 *
 * permette la serializzazione in XML di un oggetto di classe MovimentazioneContinua
 * richiama il metodo write delle classi superiori per aumentare
 * l'estendibilita' del codice
 */
void MovimentazioneContinua::write(QXmlStreamWriter *writer) const{
    Impianto::write(writer);
    writer->writeStartElement("Ammorsamento");
    writer->writeCharacters(QString::fromStdString(ammorsamento.toString()));
    writer->writeEndElement();
}
