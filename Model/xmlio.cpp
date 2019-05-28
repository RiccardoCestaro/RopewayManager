#include "Model/xmlio.h"
#include "Model/Gerarchia/impianto.h"
#include <QFile>
#include <QSaveFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <QDebug>

/**
 * @brief IO::read
 * @param __filename
 * @return Cointainer
 *
 * metodo che inizializza la lettura di un file XML
 */
IO::deep_vector IO::read(string __filename) {
    IO::deep_vector contenitore;
    QFile file(QString::fromStdString(__filename));
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox box(QMessageBox::Warning, "Errore di apertura", "Impossibile aprire il file", QMessageBox::Ok);
        return contenitore;
    }
    QXmlStreamReader reader(&file);
    if(reader.readNextStartElement() && reader.name() == "root"){
        while(reader.readNextStartElement() && reader.name() == "Impianto") {
            try{
                Impianto* rope = Impianto::read(&reader);
                if(rope)    contenitore.push_back(rope);
            } catch(std::string s) {
                QMessageBox box(QMessageBox::Warning, "Errore in lettura", "Qualche elemento potrebbe non essere stato letto correttamente", QMessageBox::Ok);
            }
           reader.readNextStartElement();
        }
    }else{
        QMessageBox box(QMessageBox::Warning, "Errore!", "File non valido!", QMessageBox::Ok);
    }
    file.close();
    return contenitore;
}

/**
 * @brief IO::write
 * @param __container
 * @param __filename
 *
 * metodo che inizializza la scrittura di un file XML, tramite un Container
 */
void IO::write(const IO::deep_vector& __container,string __filename){

    QSaveFile file(QString::fromStdString(__filename));
    if(!file.open(QIODevice::WriteOnly)) {
        throw std::exception();
    }
    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeComment("File di salvataggio");
    writer.writeStartElement("root");
    auto it = __container.begin();
    for (;it!=__container.end();++it){
        (*it)->write(&writer);
        if (writer.hasError())
            throw std::exception();
    }
    writer.writeEndElement();
    writer.writeEndDocument();
    file.commit();
}
