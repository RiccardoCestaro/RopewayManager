#include "Model/xmlio.h"
#include "Model/Gerarchia/seggiovia.h"
#include "Model/Gerarchia/cabinovia.h"
#include "Model/Gerarchia/telemix.h"
#include "Model/Gerarchia/sciovia.h"
#include "Model/Gerarchia/funicolare.h"
#include "Model/Gerarchia/funifor.h"
#include "Model/Gerarchia/funivia.h"
#include <QFile>
#include <QSaveFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <QDebug>

Container<DeepPtr<Impianto>> XmlIO::read(string filename) {
    Container<DeepPtr<Impianto>> contenitore;
    QFile file(QString::fromStdString(filename));
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox box(QMessageBox::Warning, "Errore di apertura", "Non è stato possibile aprire il file", QMessageBox::Ok);
        return contenitore;
    }
    QXmlStreamReader reader(&file); // QIODevice*
    if(reader.readNextStartElement() && reader.name() == "root"){
        while(reader.readNextStartElement() && reader.name() == "Impianto") {
            std::cout << reader.name().toString().toStdString() << std::endl;
            try{
                if (reader.readNextStartElement() && reader.name() == "Tipo"){
                    string tipo = reader.readElementText().toStdString();
                    if(tipo == "seggiovia")
                        contenitore.push_back(Seggiovia::read(&reader));
                    else if(tipo == "cabinovia")
                        contenitore.push_back(Cabinovia::read(&reader));
                    else if(tipo == "telemix")
                        contenitore.push_back(Telemix::read(&reader));
                    else if(tipo == "sciovia")
                        contenitore.push_back(Sciovia::read(&reader));
                    else if(tipo == "funifor")
                        contenitore.push_back(Funifor::read(&reader));
                    else if(tipo == "funivia")
                        contenitore.push_back(Funivia::read(&reader));
                    else if(tipo == "funicolare")
                        contenitore.push_back(Funicolare::read(&reader));
                }
                std::cout << contenitore.size() << std::endl;
                std::cout << reader.name().toString().toStdString() << std::endl;
            } catch(std::string s) {
                QMessageBox box(QMessageBox::Warning, "Errore in lettura", "Qualche elemento potrebbe non essere stato letto correttamente", QMessageBox::Ok);
            }
           reader.readNextStartElement();
        }
    }else{
        QMessageBox box(QMessageBox::Warning, "Errore di schema", "Il file non e' stato creato con RopewayManager", QMessageBox::Ok);
    }
    file.close();
    return contenitore;
}

void XmlIO::write(const Container<DeepPtr<Impianto>>& container,string filename){

    QSaveFile file(QString::fromStdString(filename));
    if(!file.open(QIODevice::WriteOnly)) {
        throw std::exception();
    }
    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true); // Per leggibilità del file XML
    writer.writeStartDocument();    // Scrive le intestazioni XML
    writer.writeComment("File di salvataggio dell'applicazione. Non modificare a mano.");
    writer.writeStartElement("root");
    auto citer = container.begin();
    for ( ; citer!=container.end() ; ++citer ){
        writer.writeStartElement("Impianto");
        writer.writeStartElement("Tipo");
        writer.writeCharacters(QString::fromStdString((*citer)->getType()));
        writer.writeEndElement();
        (*citer)->write(&writer);
        writer.writeEndElement();
        if (writer.hasError()) // se c'è stato un problema in scrittura interrompe ed esce
            throw std::exception();
    }
    writer.writeEndElement();                                        // </root>
    writer.writeEndDocument();  // chiude eventuali tag lasciati aperti e aggiunge una riga vuota alla fine
    file.commit(); // Scrive il file temporaneo su disco
}
