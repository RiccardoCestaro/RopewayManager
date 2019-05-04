#include "insertropeway.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFileDialog>
#include <iostream>
#include <QBuffer>

QStringList InsertRopeway::manufacters = {"Leitner", "Doppelmayr", "Agudio", "Zemella", "Graffer", "Agamatic", "Poma", "Nascivera",
                             "Bartholet", "Garaventa","Hölzl", "Marchisio", "Ceretti Tanfani"};

QStringList InsertRopeway::typeOfLift = {"Seggiovia","Cabinovia","Telemix","Sciovia","Funivia","Funifor","Funicolare"};


InsertRopeway::InsertRopeway(QWidget *parent) :
    QWidget(parent),
    mainLayout(new QVBoxLayout(this)),
    insertLayout(new QHBoxLayout()),
    photoLayout(new QVBoxLayout()),
    formLayout(new QFormLayout()),
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
    comboType(new QComboBox(this)),
    comboManufacter(new QComboBox(this)),
    comboDetachable(new QComboBox(this)),
    spinCapacity(new QSpinBox(this)),
    spinId(new QSpinBox(this)),
    spinHeightValley(new QSpinBox(this)),
    spinHeightMountain(new QSpinBox(this)),
    spinEnginePower(new QSpinBox(this)),
    spinDrivingSpeedLine(new QSpinBox(this)),
    spinYearOfConstruction(new QSpinBox(this)),
    checkBoxSkiRests(new QCheckBox(this)),
    checkBoxCoverage(new QCheckBox(this)),
    comboHook(new QComboBox(this)),
    spinRopeNumber(new QSpinBox(this)),
    spinCabinCapacity(new QSpinBox(this)),
    spinTime(new QSpinBox(this)),
    comboCabinNumber(new QComboBox(this)),
    comboTecBin(new QComboBox(this)),
    photoString(QString()),
    imageLabel(new QLabel(this)){

    type -> setText("Type: ");
    comboType -> addItems(typeOfLift);

    id -> setText("Id:");
    spinId->setRange(0,999);


    name -> setText("Nome:");
    /* Creating validator for QLineEdit using regex*/
    QRegExp rx("(\\w+\\s)+");
    QRegExpValidator *validator = new QRegExpValidator(rx, this);
    editName->setValidator(validator);
    editName->setMaxLength(30);

    capacity->setText("Capienza Veicoli:");
    spinCapacity->setRange(1,200);

    manufacter -> setText("Produttore:");
    comboManufacter -> addItems(manufacters);

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

    /*
     * Movimentazione continua
     */
    detachT -> setText("Ammorsamento:");
    comboDetachable -> addItem("Automatico");
    comboDetachable -> addItem("Fisso");

    /*
     * Seggiovia
     */
    skiRests->setText("Appoggia sci:");
    checkBoxSkiRests->setChecked(true);
    coverage->setText("Copertura:");

    /*
     * Cabinovia
     */
    ropeNumber->setText("Numero funi:");
    spinRopeNumber->setRange(1,3);
    ropeNumber->hide();
    spinRopeNumber->hide();
    /*
     * Sciovia
     */
    hook -> setText("Gancio:");
    comboHook -> addItem("Ancora");
    comboHook -> addItem("Piattello");
    hook->hide();
    comboHook->hide();
    /*
     * Telemix
     */
    cabinCapacity -> setText("Capienza Cabine: ");
    spinCabinCapacity -> setRange( 6,18 );
    cabinCapacity -> hide();
    spinCabinCapacity -> hide();
    /*
     * VaeVieni
     */
    time -> setText("Tempo attesa: ");
    spinTime -> setRange( 0,3600 );
    spinTime -> setSuffix("s");
    time -> hide();
    spinTime -> hide();
    /*
     * Funifor
     */
    funiforCabinNumber -> setText( "Numero Cabine: ");
    comboCabinNumber -> addItem("Una");
    comboCabinNumber -> addItem("Due");
    funiforCabinNumber -> hide();
    comboCabinNumber -> hide();
    /*
     * Funicolare
     */
    tecBin -> setText("Tecnica binario:" );
    comboTecBin -> addItem("Doppio");
    comboTecBin -> addItem("Unico");
    tecBin -> hide();
    comboTecBin -> hide();


    addItem->setText("Aggiungi Impianto");


    mainLayout -> addLayout(insertLayout);


    insertLayout -> addLayout(formLayout);
    formLayout -> setAlignment(Qt::AlignLeft);

    formLayout -> addRow(type,comboType);
    formLayout -> addRow(id,spinId);
    formLayout -> addRow(name,editName);
    formLayout -> addRow(capacity,spinCapacity);
    /* Telemix */
    formLayout -> addRow(cabinCapacity,spinCabinCapacity);
    formLayout -> addRow(manufacter,comboManufacter);
    formLayout -> addRow(heightValley,spinHeightValley);
    formLayout -> addRow(heightMountain, spinHeightMountain);
    formLayout -> addRow(drivingSpeedLine,spinDrivingSpeedLine);
    formLayout -> addRow(yearOfConstruction,spinYearOfConstruction);
    formLayout -> addRow(enginePower,spinEnginePower);

    //continue

    formLayout -> addRow(detachT,comboDetachable);

    //chairlift

    formLayout -> addRow(skiRests,checkBoxSkiRests);
    formLayout -> addRow(coverage,checkBoxCoverage);

    //gondola lift

    formLayout -> addRow(ropeNumber,spinRopeNumber);

    //skilift

    formLayout -> addRow(hook,comboHook);

    /* Pulsee */

    formLayout -> addRow(time,spinTime);

    //funicolar

    formLayout -> addRow(tecBin,comboTecBin);

    //funifor

    formLayout -> addRow(funiforCabinNumber,comboCabinNumber);


    //aerial tramway

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




QComboBox *InsertRopeway::getEditManufacter() const{
    return comboManufacter;
}

QLineEdit *InsertRopeway::getEditName() const{
    return editName;
}

QComboBox *InsertRopeway::getComboDetachable() const{
    return comboDetachable;
}

QPushButton *InsertRopeway::getAddItem() const{
    return addItem;
}

QSpinBox *InsertRopeway::getSpinId() const{
    return spinId;
}

QSpinBox *InsertRopeway::getSpinHeightValley() const{
    return spinHeightValley;
}

QSpinBox *InsertRopeway::getSpinHeightMountain() const{
    return spinHeightMountain;
}
QSpinBox *InsertRopeway::getSpinCapacity() const{
    return spinCapacity;
}

QSpinBox *InsertRopeway::getSpinEnginePower() const{
    return spinEnginePower;
}

QSpinBox *InsertRopeway::getSpinDrivingSpeedLine() const{
    return spinDrivingSpeedLine;
}

QSpinBox *InsertRopeway::getSpinYearOfConstruction() const{
    return spinYearOfConstruction;
}

QCheckBox *InsertRopeway::getCheckBoxSkiRests() const{
    return checkBoxSkiRests;
}

QCheckBox *InsertRopeway::getCheckBoxCoverage() const{
    return checkBoxCoverage;
}

QComboBox *InsertRopeway::getComboHook() const{
    return comboHook;
}

QSpinBox *InsertRopeway::getSpinRopeNumber() const{
    return spinRopeNumber;
}

QSpinBox *InsertRopeway::getSpinTime() const{
    return spinTime;
}

QComboBox *InsertRopeway::getComboCabinNumber() const{
    return comboCabinNumber;
}

QComboBox *InsertRopeway::getComboTecBin() const{
    return comboTecBin;
}

QSpinBox *InsertRopeway::getSpinCabinCapacity() const{
    return spinCabinCapacity;
}


QImage InsertRopeway::getImage() const{
    return image;
}


QString InsertRopeway::getCurrentType() const{
    return comboType->currentText();
}

QString InsertRopeway::getPhoto() const{
    return photoString;
}

QByteArray InsertRopeway::getImageBytes() const{
    return imageBytes;
}

/*
 *  syncronize valley metres with mountain metres
 *
 */
void InsertRopeway::slotEditValleyMetres() const{
    spinHeightMountain->setValue(spinHeightValley->value());
    spinHeightMountain->setMinimum(spinHeightValley->value());
}


void InsertRopeway::defaultForm() const{
    std::cout << formLayout->rowCount() << std::endl;


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


void InsertRopeway::showContinue() const{
    detachT->show();
    comboDetachable->show();
}

void InsertRopeway::showPulsee() const{
    time -> show();
    spinTime -> show();
}

void InsertRopeway::showGondolaLift() const{
    showContinue();
    ropeNumber -> show();
    spinRopeNumber -> show();
}

void InsertRopeway::showChairLift() const{
    showContinue();
    coverage->show();
    checkBoxCoverage->show();
    skiRests->show();
    checkBoxSkiRests->show();
}

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

void InsertRopeway::showSkilift() const{
    showContinue();
    comboHook->show();
    hook->show();
    detachT->hide();
    comboDetachable->hide();
    capacity->hide();
    spinCapacity->hide();
}

void InsertRopeway::showFunifor() const{
    showPulsee();
    funiforCabinNumber -> show();
    comboCabinNumber -> show();
    }

void InsertRopeway::showAerialTramway() const{
    showPulsee();
}

void InsertRopeway::showFunicolar() const{
    showPulsee();
    tecBin -> show();
    comboTecBin -> show();
}





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



