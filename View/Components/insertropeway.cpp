#include "insertropeway.h"
#include "Model/Gerarchia/Utils/tipologia.h"
#include "Model/Gerarchia/Utils/ammorsamento.h"
#include "Model/Gerarchia/Utils/produttore.h"
#include "Model/Gerarchia/Utils/tecbin.h"
#include "Model/Gerarchia/Utils/gancio.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFileDialog>
#include <iostream>
#include <QBuffer>


InsertRopeway::InsertRopeway(QWidget *parent) :
    QWidget(parent),
    type(new QLabel(this)),
    name(new QLabel(this)),
    id(new QLabel(this)),
    capacity(new QLabel(this)),
    manufacter(new QLabel(this)),
    heightMountain(new QLabel(this)),
    heightValley(new QLabel(this)),
    drivingSpeedLine(new QLabel(this)),
    yearOfConstruction(new QLabel(this)),
    enginePower(new QLabel(this)),
    detachT(new QLabel(this)),
    skiRests(new QLabel(this)),
    coverage(new QLabel(this)),
    ropeNumber(new QLabel(this)),
    hook(new QLabel(this)),
    tecBin(new QLabel(this)),
    funiforCabinNumber(new QLabel(this)),
    time(new QLabel(this)),
    cabinCapacity(new QLabel(this)),
    editName(new QLineEdit(this)),
    addItem(new QPushButton(this)),
    spinCapacity(new QSpinBox(this)),
    spinId(new QSpinBox(this)),
    spinHeightValley(new QSpinBox(this)),
    spinHeightMountain(new QSpinBox(this)),
    spinEnginePower(new QSpinBox(this)),
    spinDrivingSpeedLine(new QSpinBox(this)),
    spinYearOfConstruction(new QSpinBox(this)),
    spinRopeNumber(new QSpinBox(this)),
    spinCabinCapacity(new QSpinBox(this)),
    spinTime(new QSpinBox(this)),
    checkBoxSkiRests(new QCheckBox(this)),
    checkBoxCoverage(new QCheckBox(this)),
    comboHook(new QComboBox(this)),
    comboType(new QComboBox(this)),
    comboManufacter(new QComboBox(this)),
    comboDetachable(new QComboBox(this)),
    comboCabinNumber(new QComboBox(this)),
    comboTecBin(new QComboBox(this)),
    photoString(QString()){

    mainLayout = new QVBoxLayout(this);
    insertLayout = new QHBoxLayout();
    photoLayout = new QVBoxLayout();
    formLayout = new QFormLayout();

    type -> setText("Type: ");
    comboType -> addItems(Tipologia::values);

    id -> setText("Id:");
    spinId->setRange(0,999);

    name -> setText("Nome:");
    /** Crea un validatore per QLineEdit usando regex*/
    QRegExp rx("(\\w+\\s)+");
    QRegExpValidator *validator = new QRegExpValidator(rx, this);
    editName->setValidator(validator);
    editName->setMaxLength(30);

    capacity->setText("Capienza Veicoli:");
    spinCapacity->setRange(1,200);

    manufacter -> setText("Produttore:");
    comboManufacter -> addItems(Produttore::values);

    heightValley -> setText("Altezza stazione di valle:");
    spinHeightValley -> setRange(0,8000);
    spinHeightValley -> setSuffix("m");

    heightMountain -> setText("Altezza stazione di monte:");
    spinHeightMountain ->setRange(0,8000);
    spinHeightMountain -> setSuffix("m");

    drivingSpeedLine -> setText("Velocità di esercizio:");
    spinDrivingSpeedLine->setRange(1,12);
    spinDrivingSpeedLine->setSuffix("m/s");

    yearOfConstruction -> setText("Anno di costruzione:");
    spinYearOfConstruction->setRange(1900,QDate::currentDate().year());

    enginePower -> setText("Potenza motore:");
    spinEnginePower->setRange(50,2000);
    spinEnginePower->setSuffix("kW");

    /** Movimentazione continua */
    detachT -> setText("Ammorsamento:");
    comboDetachable -> addItems(Ammorsamento::values);

    /** Seggiovia */
    skiRests->setText("Appoggia sci:");
    checkBoxSkiRests->setChecked(true);
    coverage->setText("Copertura:");

    /** Cabinovia */
    ropeNumber->setText("Numero funi:");
    spinRopeNumber->setRange(1,3);
    ropeNumber->hide();
    spinRopeNumber->hide();
    
    /** Sciovia */
    hook -> setText("Gancio:");
    comboHook -> addItems(Gancio::values);
    hook->hide();
    comboHook->hide();
    
    /** Telemix */
    cabinCapacity -> setText("Capienza Cabine: ");
    spinCabinCapacity -> setRange( 6,18 );
    cabinCapacity -> hide();
    spinCabinCapacity -> hide();
    
    /** VaeVieni */
    time -> setText("Tempo attesa: ");
    spinTime -> setRange( 0,3600 );
    spinTime -> setSuffix("s");
    time -> hide();
    spinTime -> hide();
    
    /** Funifor */
    funiforCabinNumber -> setText( "Numero Cabine: ");
    comboCabinNumber -> addItem("Una");
    comboCabinNumber -> addItem("Due");
    funiforCabinNumber -> hide();
    comboCabinNumber -> hide();
    /** Funicolare */
    tecBin -> setText("Tecnica binario:" );
    comboTecBin -> addItem("Doppio");
    comboTecBin -> addItem("Unico");
    tecBin -> hide();
    comboTecBin -> hide();

    addItem->setText("Aggiungi Impianto");
    addItem->setFixedHeight(50);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout -> addLayout(insertLayout);
    insertLayout -> addLayout(formLayout);
    formLayout -> setAlignment(Qt::AlignLeft);

    formLayout -> addRow(type,comboType);
    formLayout -> addRow(id,spinId);
    formLayout -> addRow(name,editName);
    formLayout -> addRow(capacity,spinCapacity);
    formLayout -> addRow(cabinCapacity,spinCabinCapacity);
    formLayout -> addRow(manufacter,comboManufacter);
    formLayout -> addRow(heightValley,spinHeightValley);
    formLayout -> addRow(heightMountain, spinHeightMountain);
    formLayout -> addRow(drivingSpeedLine,spinDrivingSpeedLine);
    formLayout -> addRow(yearOfConstruction,spinYearOfConstruction);
    formLayout -> addRow(enginePower,spinEnginePower);
    formLayout -> addRow(detachT,comboDetachable);
    formLayout -> addRow(skiRests,checkBoxSkiRests);
    formLayout -> addRow(coverage,checkBoxCoverage);
    formLayout -> addRow(ropeNumber,spinRopeNumber);
    formLayout -> addRow(hook,comboHook);
    formLayout -> addRow(time,spinTime);
    formLayout -> addRow(tecBin,comboTecBin);
    formLayout -> addRow(funiforCabinNumber,comboCabinNumber);

    insertLayout -> addLayout(photoLayout);
    photoLayout -> setAlignment(Qt::AlignRight);

    QPushButton* loadPhoto = new QPushButton(this);
    loadPhoto ->setFixedSize(150,50);
    loadPhoto->setText("Carica foto");

    QVBoxLayout* selectPhoto = new QVBoxLayout();

    selectPhoto -> setAlignment(Qt::AlignCenter);
    photoLayout-> addLayout(selectPhoto);
    selectPhoto->addWidget(loadPhoto);

    QWidget* borders = new QWidget(this);
    borders->setFixedSize(500,400);
    imageLabel = new QLabel(this);
    imageLabel->setParent(borders);
    imageLabel->setFixedSize(450,350);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->move(30,25);
    imageLabel->setScaledContents(true);
    imageLabel->setStyleSheet("QLabel {border: 1px solid white;border-radius: 2px;background-color: gray;padding: 5px 5px 5px 5px;}");

    photoLayout->addWidget(borders);
    mainLayout -> addWidget(addItem);

    connect(comboType,SIGNAL(currentIndexChanged(int)),this,SLOT(slotEditType()));
    connect(spinHeightValley,SIGNAL(valueChanged(int)),this,SLOT(slotEditValleyMetres()));
    connect(loadPhoto,SIGNAL(clicked()),this,SLOT(slotLoadPhoto()));
}

/**
 * @brief InsertRopeway::getEditManufacter
 * @return comboManufacter
 */
QComboBox *InsertRopeway::getEditManufacter() const{
    return comboManufacter;
}

/**
 * @brief InsertRopeway::getEditName
 * @return editName
 */
QLineEdit *InsertRopeway::getEditName() const{
    return editName;
}

/**
 * @brief InsertRopeway::getComboDetachable
 * @return comboDetachable
 */
QComboBox *InsertRopeway::getComboDetachable() const{
    return comboDetachable;
}

/**
 * @brief InsertRopeway::getAddItem
 * @return addItem
 */
QPushButton *InsertRopeway::getAddItem() const{
    return addItem;
}

/**
 * @brief InsertRopeway::getSpinId
 * @return spinId
 */
QSpinBox *InsertRopeway::getSpinId() const{
    return spinId;
}

/**
 * @brief InsertRopeway::getSpinHeightValley
 * @return spinHeightValley
 */
QSpinBox *InsertRopeway::getSpinHeightValley() const{
    return spinHeightValley;
}

/**
 * @brief InsertRopeway::getSpinHeightMountain
 * @return spinHeightMountain
 */
QSpinBox *InsertRopeway::getSpinHeightMountain() const{
    return spinHeightMountain;
}

/**
 * @brief InsertRopeway::getSpinCapacity
 * @return spinCapacity
 */
QSpinBox *InsertRopeway::getSpinCapacity() const{
    return spinCapacity;
}

/**
 * @brief InsertRopeway::getSpinEnginePower
 * @return spinEnginePower
 */
QSpinBox *InsertRopeway::getSpinEnginePower() const{
    return spinEnginePower;
}

/**
 * @brief InsertRopeway::getSpinDrivingSpeedLine
 * @return spinDrivingSpeedLine
 */
QSpinBox *InsertRopeway::getSpinDrivingSpeedLine() const{
    return spinDrivingSpeedLine;
}

/**
 * @brief InsertRopeway::getSpinYearOfConstruction
 * @return spinYearOfConstruction
 */
QSpinBox *InsertRopeway::getSpinYearOfConstruction() const{
    return spinYearOfConstruction;
}

/**
 * @brief InsertRopeway::getCheckBoxSkiRests
 * @return checkBoxSkiRests
 */
QCheckBox *InsertRopeway::getCheckBoxSkiRests() const{
    return checkBoxSkiRests;
}

/**
 * @brief InsertRopeway::getCheckBoxCoverage
 * @return checkBoxCoverage
 */
QCheckBox *InsertRopeway::getCheckBoxCoverage() const{
    return checkBoxCoverage;
}

/**
 * @brief InsertRopeway::getComboHook
 * @return comboHook
 */
QComboBox *InsertRopeway::getComboHook() const{
    return comboHook;
}

/**
 * @brief InsertRopeway::getSpinRopeNumber
 * @return spinRopeNumber
 */
QSpinBox *InsertRopeway::getSpinRopeNumber() const{
    return spinRopeNumber;
}

/**
 * @brief InsertRopeway::getSpinTime
 * @return spinTime
 */
QSpinBox *InsertRopeway::getSpinTime() const{
    return spinTime;
}

/**
 * @brief InsertRopeway::getComboCabinNumber
 * @return comboCabinNumber
 */
QComboBox *InsertRopeway::getComboCabinNumber() const{
    return comboCabinNumber;
}

/**
 * @brief InsertRopeway::getComboTecBin
 * @return comboTecBin
 */
QComboBox *InsertRopeway::getComboTecBin() const{
    return comboTecBin;
}

/**
 * @brief InsertRopeway::getSpinCabinCapacity
 * @return spinCabinCapacity
 */
QSpinBox *InsertRopeway::getSpinCabinCapacity() const{
    return spinCabinCapacity;
}

/**
 * @brief InsertRopeway::getImage
 * @return image
 */
QImage InsertRopeway::getImage() const{
    return image;
}

/**
 * @brief InsertRopeway::getCurrentType
 * @return comboType->currentText()
 */
QString InsertRopeway::getCurrentType() const{
    return comboType->currentText();
}

/**
 * @brief InsertRopeway::getPhoto
 * @return photoString
 */
QString InsertRopeway::getPhoto() const{
    return photoString;
}

/**
 * @brief InsertRopeway::getImageBytes
 * @return imageBytes
 */
QByteArray InsertRopeway::getImageBytes() const{
    return imageBytes;
}

/**
 * @brief InsertRopeway::slotEditValleyMetres
 *
 * Slot privato:
 * consente di sincronizzare l'altitudine della stazione
 * di monte con l'altitudine della stazione di valle
 */
void InsertRopeway::slotEditValleyMetres() const{
    spinHeightMountain->setValue(spinHeightValley->value());
    spinHeightMountain->setMinimum(spinHeightValley->value());
}

/**
 * @brief InsertRopeway::defaultForm
 *
 * Metodo privato:
 * visualizza i campi necessari ad inizializzare
 * i campi come da default
 */
void InsertRopeway::defaultForm() const{
    detachT->hide();
    comboDetachable->hide();
    coverage->hide();
    checkBoxCoverage->hide();
    skiRests->hide();
    checkBoxSkiRests->hide();
    ropeNumber->hide();
    spinRopeNumber->hide();
    hook->hide();
    comboHook->hide();
    time -> hide();
    spinTime -> hide();
    funiforCabinNumber -> hide();
    comboCabinNumber -> hide();
    tecBin -> hide();
    comboTecBin -> hide();
    cabinCapacity -> hide();
    spinCabinCapacity -> hide();
    capacity->show();
    spinCapacity->show();
    capacity -> setText("Capienza veicolo: ");
}

/**
 * @brief InsertRopeway::showContinue
 *
 * Metodo privato:
 * visualizza i campi necessari ad inizializzare
 * i campi di un impianto a movimentazione continua
 */
void InsertRopeway::showContinue() const{
    detachT->show();
    comboDetachable->show();
}

/**
 * @brief InsertRopeway::showPulsee
 *
 * Metodo privato:
 * visualizza i campi necessari ad inizializzare
 * i campi di un impianto a movimentazione va e vieni
 */
void InsertRopeway::showPulsee() const{
    time -> show();
    spinTime -> show();
}

/**
 * @brief InsertRopeway::showGondolaLift
 *
 * Metodo privato:
 * visualizza i campi necessari ad inizializzare
 * i campi di Cabinovia
 */
void InsertRopeway::showGondolaLift() const{
    showContinue();
    ropeNumber -> show();
    spinRopeNumber -> show();
}

/**
 * @brief InsertRopeway::showChairLift
 *
 * Metodo privato:
 * visualizza i campi necessari ad inizializzare
 * i campi di seggiovia
 */
void InsertRopeway::showChairLift() const{
    showContinue();
    coverage->show();
    checkBoxCoverage->show();
    skiRests->show();
    checkBoxSkiRests->show();
}

/**
 * @brief InsertRopeway::showTelemix
 *
 * Metodo privato:
 * visualizza i campi necessari ad inizializzare
 * i campi di Telemix
 */
void InsertRopeway::showTelemix() const{
    showContinue();
    detachT->hide();
    comboDetachable->hide();
    ropeNumber->hide();
    spinRopeNumber->hide();
    coverage->show();
    checkBoxCoverage->show();
    skiRests->show();
    checkBoxSkiRests->show();
    cabinCapacity->show();
    spinCabinCapacity-> show();
    capacity -> setText("Capienza seggiole: ");
}

/**
 * @brief InsertRopeway::showSkilift
 *
 * Metodo privato:
 * visualizza i campi necessari ad inizializzare
 * i campi di Skilift
 */
void InsertRopeway::showSkilift() const{
    showContinue();
    comboHook->show();
    hook->show();
    detachT->hide();
    comboDetachable->hide();
    capacity->hide();
    spinCapacity->hide();
}

/**
 * @brief InsertRopeway::showFunifor
 *
 * Metodo privato:
 * visualizza i campi necessari ad inizializzare
 * i campi di Funifor
 */
void InsertRopeway::showFunifor() const{
    showPulsee();
    funiforCabinNumber -> show();
    comboCabinNumber -> show();
    }

/**
 * @brief InsertRopeway::showAerialTramway
 *
 * Metodo privato:
 * visualizza i campi necessari ad inizializzare
 * i campi della funivia
 */
void InsertRopeway::showAerialTramway() const{
    showPulsee();
}

/**
 * @brief InsertRopeway::showFunicolar
 *
 * Metodo Privato:
 * visualizza i campi necessari ad inizializzare
 * i campi di funicolare
 */
void InsertRopeway::showFunicolar() const{
    showPulsee();
    tecBin -> show();
    comboTecBin -> show();
}

/**
 * @brief InsertRopeway::slotEditType
 *
 * Slot privato:
 * consente di visualizzare i campi da inizializzare
 * per il tipo di impianto scelto
 */
void InsertRopeway::slotEditType() const{
    defaultForm();
    QString type = comboType->currentText();
    if ( type == "Sciovia") showSkilift();
    else if( type == "Seggiovia") showChairLift();
    else if( type == "Cabinovia") showGondolaLift();
    else if( type == "Telemix") showTelemix();
    else if( type == "Funifor") showFunifor();
    else if( type == "Funivia") showAerialTramway();
    else if ( type == "Funicolare") showFunicolar();
}

/**
 * @brief InsertRopeway::slotLoadPhoto
 *
 * Slot privato:
 * consente di scegliere e caricare un immagine
 * di tipo JPG o PNG
 */
void InsertRopeway::slotLoadPhoto(){
   photoString = QFileDialog::getOpenFileName(this,tr("Selezione l'immagine: "), "",tr("JPG (*.jpg);;PNG (*.png);;All Files (*)"));

   if (!photoString.isEmpty()){
        image = QImage(photoString);
        imageBytes = QByteArray();
        QBuffer buffer(&imageBytes);

        image.save(&buffer,"JPG");
        imageLabel->setPixmap(QPixmap::fromImage(image));
   }
}



