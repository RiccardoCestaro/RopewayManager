#include "modeladapter.h"
#include "View/showallspec.h"
#include "Model/Gerarchia/seggiovia.h"
#include "Model/Gerarchia/cabinovia.h"
#include "Model/Gerarchia/telemix.h"
#include "Model/Gerarchia/sciovia.h"
#include "Model/Gerarchia/funivia.h"
#include "Model/Gerarchia/funifor.h"
#include "Model/Gerarchia/funicolare.h"

#include <QFont>
#include <QColor>
#include <QBrush>
#include <QVariant>
#include <QPushButton>
#include <QRegExp>
#include <QDebug>
#include <utility>

ModelAdapter::ModelAdapter(QObject* parent, const InsertRopeway* i) :
    QAbstractTableModel(parent),
    model(new Model()),
    insert(i){}

/**
 * @brief ModelAdapter::~ModelAdapter
 *
 * Distruttore profondo, elimina la memoria
 * puntata da model
 */
ModelAdapter::~ModelAdapter() {
    if(model) delete model;
}

/**
 * @brief ModelAdapter::rowCount
 * @return
 *
 * ritorna il numero delle righe della tabella,
 * in base alla size del container
 */
int ModelAdapter::rowCount(const QModelIndex &) const {
    return static_cast<int>(model->getSize());
}

/**
 * @brief ModelAdapter::columnCount
 * @return
 *
 * ritorna il numero delle colonne della tableView
 */
int ModelAdapter::columnCount(const QModelIndex &) const {
    return 7;
}

/**
 * @brief ModelAdapter::headerData
 * @param section
 * @param orientation
 * @param role
 * @return
 *
 * personalizza l'header
 */
QVariant ModelAdapter::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (role != Qt::FontRole)
    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Numero");
        case 1:
            return QString("Nome");
        case 2:
            return QString("Tipologia");
        case 3:
            return QString("Produttore");
        case 4:
            return QString("Dislivello");
        case 5:
            return QString("Velocità Esercizio");
        case 6:
            return QString("Anno Costruzione");
        default:
            return QVariant();
        }
    }
    return QVariant();
}

/**
 * @brief ModelAdapter::data
 * @param index
 * @param role
 * @return
 *
 * personalizza la tableView,
 * indica i campi dell'oggetto da visualizzare
 * nella tabella
 */
QVariant ModelAdapter::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || static_cast<unsigned int>(index.row()) >= model->getSize() || index.row()<0)
        return QVariant();
    switch(role){
        case Qt::BackgroundColorRole:
            return QVariant(QBrush(QColor(Qt::black)));
        case Qt::TextAlignmentRole:
            return QVariant ( Qt::AlignVCenter | Qt::AlignHCenter );
        case Qt::SizeHintRole:
            return QSize( 500, 0 );
        case Qt::DisplayRole:
        {
            switch(index.column())
            {
            case 0:
                return model->getRopeway(static_cast<unsigned int>(index.row()))->getId();
            case 1:
                return QString::fromStdString(model->getRopeway(static_cast<unsigned int>(index.row()))->getNome());
            case 2:
                return QString::fromStdString(model->getRopeway(static_cast<unsigned int>(index.row()))->getType());
            case 3:
                return QString::fromStdString(model->getRopeway(static_cast<unsigned int>(index.row()))->getProduttore().toString());
            case 4:
                return model->getRopeway(static_cast<unsigned int>(index.row()))->getQuotaMonte()-model->getRopeway(static_cast<unsigned int>(index.row()))->getQuotaValle();
            case 5:
                return model->getRopeway(static_cast<unsigned int>(index.row()))->getVelocitaEsercizio();
            case 6:
                return model->getRopeway(static_cast<unsigned int>(index.row()))->getAnnoCostruzione();
            default:
                return QVariant();
            }
        }
    }
    return QVariant();
}

/**
 * @brief ModelAdapter::insertRows
 * @param begin
 * @param count
 * @param parent
 * @return true
 *
 * Consente di inserire un oggetto nel container, e nella tabella
 */
bool ModelAdapter::insertRows(int begin, int count, const QModelIndex& parent) {
    beginInsertRows(parent, begin, begin + count - 1);
    std::string s = insert->getCurrentType().toStdString();

    if ( s == "Seggiovia"){
        model->add(new Seggiovia(static_cast<unsigned short>(insert->getSpinId()->value()),insert->getImageBytes().toBase64().toStdString(),insert->getEditName()->text().toStdString(),
                                 static_cast<short>(insert->getSpinCapacity()->value()),static_cast<unsigned int>(insert->getSpinHeightValley()->value()),
                                 static_cast<unsigned int>(insert->getSpinHeightMountain()->value()),insert->getSpinEnginePower()->value(),
                                 insert->getSpinDrivingSpeedLine()->value(),insert->getEditManufacter()->currentText().toStdString(),
                                 static_cast<short>(insert->getSpinYearOfConstruction()->value()),insert->getComboDetachable()->currentText().toStdString(),insert->getCheckBoxCoverage()->isChecked(),
                                 insert->getCheckBoxSkiRests()->isChecked()));

    }else if ( s == "Cabinovia"){
        model->add(new Cabinovia(static_cast<unsigned short>(insert->getSpinId()->value()),insert->getImageBytes().toBase64().toStdString(),insert->getEditName()->text().toStdString(),
                                 static_cast<short>(insert->getSpinCapacity()->value()),static_cast<unsigned int>(insert->getSpinHeightValley()->value()),
                                 static_cast<unsigned int>(insert->getSpinHeightMountain()->value()),insert->getSpinEnginePower()->value(),
                                 insert->getSpinDrivingSpeedLine()->value(),insert->getEditManufacter()->currentText().toStdString(),
                                 static_cast<short>(insert->getSpinYearOfConstruction()->value()),insert->getComboDetachable()->currentText().toStdString(),static_cast<short>(insert->getSpinRopeNumber()->value())));
    }else if ( s == "Telemix"){
        model->add(new Telemix(static_cast<unsigned short>(insert->getSpinId()->value()),insert->getImageBytes().toBase64().toStdString(),insert->getEditName()->text().toStdString(),
                               static_cast<short>(insert->getSpinCapacity()->value()),static_cast<short>(insert->getSpinCabinCapacity()->value()),
                               static_cast<unsigned int>(insert->getSpinHeightValley()->value()), static_cast<unsigned int>(insert->getSpinHeightMountain()->value()),
                               insert->getSpinEnginePower()->value(), insert->getSpinDrivingSpeedLine()->value(),insert->getEditManufacter()->currentText().toStdString(),
                               static_cast<short>(insert->getSpinYearOfConstruction()->value()), insert->getCheckBoxCoverage()->isChecked(),insert->getCheckBoxSkiRests()->isChecked()));
    }else if ( s == "Sciovia"){
        string gancio = insert->getComboHook()->currentText().toStdString();
        model->add(new Sciovia(static_cast<unsigned short>(insert->getSpinId()->value()),insert->getImageBytes().toBase64().toStdString(),insert->getEditName()->text().toStdString(),
                               static_cast<unsigned int>(insert->getSpinHeightValley()->value()), static_cast<unsigned int>(insert->getSpinHeightMountain()->value()),
                               insert->getSpinEnginePower()->value(), insert->getSpinDrivingSpeedLine()->value(),insert->getEditManufacter()->currentText().toStdString(),
                               static_cast<short>(insert->getSpinYearOfConstruction()->value()),gancio));
    }else if ( s == "Funivia"){
        model->add(new Funivia(static_cast<unsigned short>(insert->getSpinId()->value()),insert->getImageBytes().toBase64().toStdString(),insert->getEditName()->text().toStdString(),
                               static_cast<short>(insert->getSpinCapacity()->value()),static_cast<unsigned int>(insert->getSpinHeightValley()->value()),
                               static_cast<unsigned int>(insert->getSpinHeightMountain()->value()),insert->getSpinEnginePower()->value(),
                               insert->getSpinDrivingSpeedLine()->value(),insert->getEditManufacter()->currentText().toStdString(),
                               static_cast<short>(insert->getSpinYearOfConstruction()->value()),insert->getSpinTime()->value()));
    }else if ( s == "Funifor"){
        model->add(new Funifor(static_cast<unsigned short>(insert->getSpinId()->value()),insert->getImageBytes().toBase64().toStdString(),insert->getEditName()->text().toStdString(),
                               static_cast<short>(insert->getSpinCapacity()->value()),static_cast<unsigned int>(insert->getSpinHeightValley()->value()),
                               static_cast<unsigned int>(insert->getSpinHeightMountain()->value()),insert->getSpinEnginePower()->value(),
                               insert->getSpinDrivingSpeedLine()->value(),insert->getEditManufacter()->currentText().toStdString(),
                               static_cast<short>(insert->getSpinYearOfConstruction()->value()),insert->getSpinTime()->value(),
                               static_cast<short>(insert->getComboCabinNumber()->currentIndex())));
    }else if ( s == "Funicolare"){
        model->add(new Funicolare(static_cast<unsigned short>(insert->getSpinId()->value()),insert->getImageBytes().toBase64().toStdString(),insert->getEditName()->text().toStdString(),
                                  static_cast<short>(insert->getSpinCapacity()->value()),static_cast<unsigned int>(insert->getSpinHeightValley()->value()),
                                  static_cast<unsigned int>(insert->getSpinHeightMountain()->value()),insert->getSpinEnginePower()->value(),
                                  insert->getSpinDrivingSpeedLine()->value(),insert->getEditManufacter()->currentText().toStdString(),
                                  static_cast<short>(insert->getSpinYearOfConstruction()->value()),insert->getSpinTime()->value(),insert->getComboTecBin()->currentText().toStdString()));
    }
    endInsertRows();
    return true;
}

/**
 * @brief ModelAdapter::removeRows
 * @param begin
 * @param count
 * @param parent
 * @return true
 *
 * Overloading di removeRows, si occupa di rimuovere le righe
 * della tabella, e gli oggetti dal container
 */
bool ModelAdapter::removeRows(int begin, int count, const QModelIndex& parent) {
    beginRemoveRows(parent, begin, begin + count - 1);
    model->remove(static_cast<unsigned int>(begin));
    endRemoveRows();
    return true;
}

/**
 * @brief ModelAdapter::clear
 *
 * Richiama il metodo erase() del container,
 * che si occupa di pulire l'array
 */
void ModelAdapter::clear(){
    model->erase();
}

/**
 * @brief ModelAdapter::showMore
 * @param index
 *
 * Metodo per aprire
 */
void ModelAdapter::showMore(const QModelIndex& index){
    if (index.isValid() && index.row() < rowCount() && index.column()<columnCount()){
        ShowAllSpec* item = new ShowAllSpec(model->getRopeway(static_cast<unsigned int>(index.row())), QAbstractTableModel::createIndex(index.row(), 0), QAbstractTableModel::createIndex(index.row(), columnCount()-1));
        connect(item, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)));
        item->setAttribute(Qt::WA_DeleteOnClose);
        item->show();
    }

}

/**
 * @brief ModelAdapter::saveToFile
 * @param filename
 *
 * Metodo per la serializzazione
 */
void ModelAdapter::saveToFile(const std::string& filename) const {
    model->saveToFile(filename);
}

/**
 * @brief ModelAdapter::loadFromFile
 * @param filename
 *
 * Metodo per la deserializzazione
 */
void ModelAdapter::loadFromFile(const std::string& filename) const {
    model->loadFromFile(filename);
}

/**
 * @brief ModelAdapter::getInsertWidget
 * @return InsertRopeway* insert
 *
 * Ritorna un puntatore costante alla vista InsertRopeway*
 */
const InsertRopeway* ModelAdapter::getInsertWidget() const{
    return insert;
}

/**
 * @brief ModelAdapter::matchX
 * @param r unsigned
 * @param i QRegExp
 * @return true se produttore e tipologia
 *          dell'impianto corrispondono
 *         false altrimenti
 */
bool ModelAdapter::matchX(unsigned int r,const QRegExp& i) const{
    QStringList patterns = i.pattern().split("|", QString::SkipEmptyParts);
    if(patterns.size() > 1 ){
    return (patterns.at(0) == "Tutto" ? true : (QString::fromStdString(model->getRopeway(r)->getType()).contains(patterns.at(0).toLower()))) &&
           (patterns.at(1) == "Tutto" ? true : (QString::fromStdString(model->getRopeway(r)->getProduttore().toString()).contains(patterns.at(1))));
    }
    return false;
}















