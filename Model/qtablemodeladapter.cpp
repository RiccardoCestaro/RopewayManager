#include "qtablemodeladapter.h"
#include "model.h"
#include "View/Components/insertropeway.h"
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


QTableModelAdapter::QTableModelAdapter(QObject* parent, const InsertRopeway* i) :
    QAbstractTableModel(parent),
    model(new Model()),
    insert(i){}

QTableModelAdapter::~QTableModelAdapter() { //insert distrutto dal main
    if(model) delete model;
}

int QTableModelAdapter::rowCount(const QModelIndex &) const {
    return static_cast<int>(model->count());
}
int QTableModelAdapter::columnCount(const QModelIndex &) const {
    return 7;
}
QVariant QTableModelAdapter::headerData(int section, Qt::Orientation orientation, int role) const{
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
QVariant QTableModelAdapter::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || static_cast<unsigned int>(index.row()) >= model->count() || index.row()<0)
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
            return QString::fromStdString(model->getRopeway(static_cast<unsigned int>(index.row()))->getProduttore());
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

/*
 * Inserisce 'count' nuove righe nel modello a partire dall'elemento di indice 'begin'
 */

bool QTableModelAdapter::insertRows(int begin, int count, const QModelIndex& parent) {
    beginInsertRows(parent, begin, begin + count - 1);
    std::string s = insert->getCurrentType().toStdString();
    std::cout << s << std::endl;


            //Utils::getRawData(inserisciLayout->getScegliFoto()->pixmap()->toImage());
    if ( s == "Seggiovia"){
        //model->add(new Seggiovia(6,"FOto","Ciao",66,2033,2156,755,2,"Leitner"));
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
        tecBin tecBin = insert->getComboTecBin()->currentText().toStdString();
        model->add(new Funicolare(static_cast<unsigned short>(insert->getSpinId()->value()),insert->getImageBytes().toBase64().toStdString(),insert->getEditName()->text().toStdString(),
                                  static_cast<short>(insert->getSpinCapacity()->value()),static_cast<unsigned int>(insert->getSpinHeightValley()->value()),
                                  static_cast<unsigned int>(insert->getSpinHeightMountain()->value()),insert->getSpinEnginePower()->value(),
                                  insert->getSpinDrivingSpeedLine()->value(),insert->getEditManufacter()->currentText().toStdString(),
                                  static_cast<short>(insert->getSpinYearOfConstruction()->value()),insert->getSpinTime()->value(),tecBin));
    }
    endInsertRows();
    return true;
}
/*
 * sistemare il count
 */
bool QTableModelAdapter::removeRows(int begin, int count, const QModelIndex& parent) {
    beginRemoveRows(parent, begin, begin + count - 1);
    model->remove(static_cast<unsigned int>(begin));
    endRemoveRows();
    return true;
}
void QTableModelAdapter::showMore(const QModelIndex& index){

    if (index.isValid() && index.row() < rowCount() && index.column()<columnCount()){
        ShowAllSpec* item = new ShowAllSpec(model->getRopeway(static_cast<unsigned int>(index.row())), QAbstractTableModel::createIndex(index.row(), 0), QAbstractTableModel::createIndex(index.row(), columnCount()-1));
        connect(item, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)));
        item->setAttribute(Qt::WA_DeleteOnClose); //item viene distrutto alla sua chiusura
        item->show();
    }

}

void QTableModelAdapter::saveToFile(const std::string& filename) const {
    model->saveToFile(filename);
}
void QTableModelAdapter::loadFromFile(const std::string& filename) const {
    model->loadFromFile(filename);
}
const InsertRopeway* QTableModelAdapter::getInsertWidget() const{
    return insert;
}

bool QTableModelAdapter::match(unsigned int r,const QRegExp& i) const{
    QStringList patterns = i.pattern().split("|", QString::SkipEmptyParts);

    if(patterns.size() > 1 ){
    return (patterns.at(0) == "Tutto" ? true : (QString::fromStdString(model->getRopeway(r)->getType()).contains(patterns.at(0).toLower()))) &&
           (patterns.at(1) == "Tutto" ? true : (QString::fromStdString(model->getRopeway(r)->getProduttore()).contains(patterns.at(1))));
    }
    return false;
}















