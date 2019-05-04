#include "Model/Gerarchia/movimentazionecontinua.h"
#include "invalidstringtoenumexception.h"

Amm::Amm(const string& s) : value(Impianto::compareString(s,"automatico") ? 1 : (Impianto::compareString(s,"fisso") ? 0 : throw (InvalidStringToEnumException()))){}
string Amm::toString() const{
    if (value == 1) return "automatico";
    return "fisso";
}


MovimentazioneContinua::MovimentazioneContinua(const unsigned short& i, const string& img, const string& nm, const short& c, const unsigned int& qv,
                                               const unsigned int& qm, const double& pm, const float& ve, const string& pro, const short& ac, const Amm& a) :
    Impianto(i,img,nm,c,qv,qm,pm,ve,pro,ac), ammorsamento(a){}

/* Ritorna la movimentazione */
std::string MovimentazioneContinua::getMovimentazione() const{
    return "Continua";
}

/* Getters per l'ottenimento dei campi radicati nella classe astratta movimentazioneContinua */
Amm MovimentazioneContinua::getAmmorsamento() const{
    return ammorsamento;
}

/* Setters per la modifica dei campi radicati nella classe astratta  movimentazioneContinua*/
void MovimentazioneContinua::setAmmorsamento(const Amm &value){
    ammorsamento = value;
}

/* Imposto il campo statico profiloPreferenziale */
string MovimentazioneContinua::profiloPreferenziale = "Convesso";


void MovimentazioneContinua::write(QXmlStreamWriter *writer) const{
    Impianto::write(writer);
    writer->writeStartElement("Ammorsamento");
    writer->writeCharacters(QString::fromStdString(ammorsamento.toString()));
    writer->writeEndElement();
}
