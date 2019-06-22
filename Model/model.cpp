#include "model.h"
#include "io.h"
#include <algorithm>
#include <QDebug>

/**
 * @brief Model::saveToFile
 * @param filename
 *
 * permette la serializzazione
 */
void Model::saveToFile(const std::string &filename) const {
    IO::write(contenitore,filename);
}

/**
 * @brief Model::loadFromFile
 * @param filename
 *
 * permette la deserializzazione
 */
void Model::loadFromFile(const std::string& filename) {
    contenitore = IO::read(filename);
}

/**
 * @brief Model::getSize
 * @return
 *
 * Ritorna la size del container
 */
unsigned int Model::getSize() const{
    return contenitore.size();
}

/**
 * @brief Model::add
 * @param bt
 *
 * Aggiunge un oggetto al container
 */
void Model::add(Impianto* bt){
    contenitore.push_back(DeepPtr<Impianto>(bt));
}

/**
 * @brief Model::remove
 * @param index
 *
 *  rimuove l'oggetto in posizione index
 */
void Model::remove(unsigned int index) {
    contenitore.erase(contenitore.begin()+static_cast<int>(index));
}

/**
 * @brief Model::operator []
 * @param i
 * @return Impianto*
 *
 * ottenimento dell'oggetto in posizione i
 */
Impianto* Model::operator[](unsigned int i) const {
    return contenitore[i].operator->();
}

/**
 * @brief Model::getRopeway
 * @param i
 * @return Impianto*
 *
 * ottenimento sicuro dell'oggetto in posizione i
 */
Impianto* Model::getRopeway(unsigned int i) const{
    return contenitore.at(i).operator->();
}

/**
 * @brief Model::erase
 *
 * richiama il metodo clear del container,
 * che lo svuota
 */
void Model::erase(){
    contenitore.clear();
}


