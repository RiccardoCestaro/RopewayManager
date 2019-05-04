#include "showallspec.h"

#include "Model/Gerarchia/seggiovia.h"
#include "Model/Gerarchia/cabinovia.h"
#include "Model/Gerarchia/telemix.h"
#include "Model/Gerarchia/sciovia.h"
#include "Model/Gerarchia/funifor.h"
#include "Model/Gerarchia/funivia.h"
#include "Model/Gerarchia/funicolare.h"

#include <QDate>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QModelIndex>
#include <QCheckBox>
#include <QStyle>
#include <QDesktopWidget>
#include <QBuffer>


ShowAllSpec::ShowAllSpec(Impianto* _p,const QModelIndex& b, const QModelIndex& e, QWidget* parent) : QWidget(parent),p(_p), begin(b), end(e),imageString(QString()){

    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        )
    );



    setWindowTitle(tr(p->getNome().c_str())); //titolo applicazione
    setWindowIcon(QIcon(":/icon.svg")); // icona del programma
    setFixedSize(QSize(850,500)); //dimensione fissa non ridimensionabile

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* typeLayout = new QHBoxLayout();

    QLabel* typeLabel = new QLabel("Tipo: ");
    typeLabel->setStyleSheet("font-size: 18px; font: bold large 'Times New Roman'");
    QLabel* type = new QLabel(QString::fromStdString(p->getType()));
    type->setStyleSheet("font-size: 18px; font: bold large 'Times New Roman'");

    typeLayout->setAlignment(Qt::AlignCenter);

    typeLayout->addWidget(typeLabel);
    typeLayout->addWidget(type);

    mainLayout->addLayout(typeLayout);

    QHBoxLayout* generalLayout = new QHBoxLayout();
    mainLayout -> addLayout(generalLayout);

    QVBoxLayout* imageLayout = new QVBoxLayout();

    image = new QLabel(this);
    QWidget* borders = new QWidget(this);
    borders->setFixedSize(500,400);
    image->setParent(borders);
    image->setFixedSize(450,350);
    image->move(30,20);

    image->setScaledContents(true);
    image->setStyleSheet("QLabel {border: 1px solid white;border-radius: 2px;background-color: gray;padding: 5px 5px 5px 5px;}");

    string imm = p->getImmagine();


    QByteArray array = QByteArray(imm.data());
    QImage* qimage = new QImage();
    qimage->loadFromData(QByteArray::fromBase64(array),"JPG");

    image->setPixmap(QPixmap::fromImage(*qimage));


    imageLayout->addWidget(borders);
    imageLayout->setAlignment(Qt::AlignCenter);

    QWidget* buttonChangePosition = new QWidget(this);
    QWidget* buttonRemovePosition = new QWidget(this);
    QPushButton* changeImage = new QPushButton(this);
    QPushButton* removeImage = new QPushButton(this);
    buttonChangePosition->setParent(changeImage);
    buttonRemovePosition->setParent(removeImage);
    changeImage->setText("Cambia foto");
    removeImage->setText("Rimuovi foto");
    changeImage->setFixedSize(QSize(150,30));
    removeImage->setFixedSize(QSize(150,30));
    changeImage->move(100,430);
    removeImage->move(260,430);

    imageLayout->addWidget(buttonChangePosition);

    generalLayout->addLayout(imageLayout);

    QVBoxLayout* fieldsLayout = new QVBoxLayout();

    /* set top margin to move formLayout */
    fieldsLayout->setContentsMargins(0,50,0,0);

    QFormLayout* formLayout = new QFormLayout();

    generalLayout->addLayout(fieldsLayout);

    spinId = new QSpinBox(this);
    spinId -> setRange(1,999);
    spinId -> setValue(p->getId());
    formLayout->addRow(new QLabel("Id: "),spinId);

    editName = new QLineEdit(this);
    /* Creating validator for QLineEdit using regex*/
    QRegExp rx("(\\w+\\s)+");
    QRegExpValidator *validator = new QRegExpValidator(rx, this);
    editName->setValidator(validator);
    editName->setMaxLength(30);
    editName->setText(QString::fromStdString(p->getNome()));
    formLayout -> addRow(new QLabel("Nome: "),editName);

    spinCapacity = new QSpinBox(this);
    spinCapacity -> setRange(1,200);
    spinCapacity -> setValue(p->getCapienzaVeicolo());
    formLayout->addRow(new QLabel("Capienza veicoli: "),spinCapacity);

    manufacters = new QComboBox(this);
    manufacters->addItems(QStringList({"Leitner", "Doppelmayr", "Agudio", "Zemella", "Graffer", "Agamatic", "Poma", "Nascivera",
                                       "Bartholet", "Garaventa","Hölzl", "Marchisio", "Ceretti Tanfani"}));
    manufacters->setCurrentText(QString::fromStdString(p->getProduttore()));
    formLayout->addRow(new QLabel("Produttore: "),manufacters);

    spinHeightValley = new QSpinBox(this);
    spinHeightValley -> setRange(0,8000);
    spinHeightValley -> setSuffix("m");
    spinHeightValley -> setValue(static_cast<int>(p->getQuotaValle()));
    formLayout->addRow(new QLabel("QuotaValle: "),spinHeightValley);

    spinHeightMountain = new QSpinBox(this);
    spinHeightMountain -> setRange(0,8000);
    spinHeightMountain -> setSuffix("m");
    spinHeightMountain -> setValue(static_cast<int>(p->getQuotaMonte()));
    formLayout->addRow(new QLabel("QuotaMonte: "),spinHeightMountain);

    spinDrivingSpeedLine = new QDoubleSpinBox(this);
    spinDrivingSpeedLine->setRange(1,12);
    spinDrivingSpeedLine->setSuffix("m/s");
    spinDrivingSpeedLine->setValue(static_cast<double>(p->getVelocitaEsercizio()));
    formLayout->addRow(new QLabel("Velocita Esercizio: "),spinDrivingSpeedLine);

    spinYearOfConstruction = new QSpinBox(this);
    spinYearOfConstruction->setRange(1900,QDate::currentDate().year());
    spinYearOfConstruction->setValue(p->getAnnoCostruzione());
    formLayout -> addRow(new QLabel("Anno Costruzione: "),spinYearOfConstruction);

    spinEnginePower = new QDoubleSpinBox(this);
    spinEnginePower->setRange(50,2000);
    spinEnginePower->setSuffix("kW");
    spinEnginePower->setValue(p->getPotenzaMotore());
    formLayout->addRow(new QLabel("Potenza Motore: "),spinEnginePower);

    if(p->getMovimentazione()=="Continua"){
        MovimentazioneContinua* mc = static_cast<MovimentazioneContinua*>(p);

        comboDetachable = new QComboBox(this);
        comboDetachable->addItem("fisso");
        comboDetachable->addItem("automatico");

        comboDetachable->setCurrentText(QString::fromStdString(mc->getAmmorsamento().toString()));
        formLayout->addRow(new QLabel("Ammorsamento: "),comboDetachable);

        if(p->getType()=="seggiovia"){
            Seggiovia* s = dynamic_cast<Seggiovia*>(p);

            checkBoxSkiRests = new QCheckBox(this);
            checkBoxSkiRests->setChecked(s->hasAppoggiaSci());
            checkBoxCoverage = new QCheckBox(this);
            checkBoxCoverage->setChecked(s->isCoperta());
            formLayout->addRow(new QLabel("Appoggia Sci: "), checkBoxSkiRests);
            formLayout->addRow(new QLabel("Copertura"), checkBoxCoverage);

        }else if(p->getType()=="cabinovia"){
            Cabinovia* c = dynamic_cast<Cabinovia*>(p);

            spinRopeNumber = new QSpinBox(this);
            spinRopeNumber->setRange(1,3);
            spinRopeNumber->setValue(c->getNumeroFuni());
            formLayout->addRow(new QLabel("Numero Funi: "),spinRopeNumber);

        }else if(p->getType()=="telemix"){
            Telemix* t = dynamic_cast<Telemix*>(p);

            spinCabinCapacity = new QSpinBox(this);
            spinCabinCapacity->setRange(6,18);
            spinCabinCapacity->setValue(t->getCapienzaCabina());
            formLayout->addRow(new QLabel("Capacita' cabine: "),spinCabinCapacity);

        }else if (p->getType()=="sciovia"){
            Sciovia* s = static_cast<Sciovia*>(p);

            comboHook = new QComboBox(this);
            comboHook->addItems(QStringList({"ancora","piattello"}));
            comboHook->setCurrentText(QString::fromStdString(s->getGancio().toString()));
            formLayout->addRow(new QLabel("Gancio: "),comboHook);

        }

    }else if(p->getMovimentazione()=="Va e Vieni"){
        MovimentazioneVaeVieni* vev = static_cast<MovimentazioneVaeVieni*>(p);

        spinTime = new QSpinBox(this);
        spinTime->setRange(0,3600);
        spinTime->setSuffix("s");
        spinTime->setValue(vev->getTempoPausa());
        formLayout->addRow(new QLabel("Tempo Attesa: "),spinTime);

        if(p->getType()=="funifor"){
            Funifor* f = static_cast<Funifor*>(p);

            spinCabinNumber = new QSpinBox(this);
            spinCabinNumber->setRange(1,2);
            spinCabinNumber->setValue(f->getNumeroCabine());
            formLayout->addRow(new QLabel("Numero Cabine: "),spinCabinNumber);

        }else if(p->getType()=="funicolare"){
            Funicolare* f = static_cast<Funicolare*>(p);

            comboTecBin = new QComboBox(this);
            comboTecBin->addItems(QStringList({"Doppio","Unico"}));
            comboTecBin->setCurrentText(QString::fromStdString(f->getTecBinario().toString()));
            formLayout->addRow(new QLabel("Tecnica Binari: "),comboTecBin);
        }
    }

    fieldsLayout->addLayout(formLayout);

    QPushButton* saveButton = new QPushButton(tr("Salva"));
    saveButton->setToolTip(tr("Salva i dati"));
    mainLayout->addWidget(saveButton);

    setLayout(mainLayout);

    connect(changeImage,SIGNAL(clicked()),this,SLOT(slotLoadPhoto()));
    connect(removeImage,SIGNAL(clicked()),this,SLOT(slotRemoveImage()));
    connect(spinHeightValley,SIGNAL(valueChanged(int)),this,SLOT(slotEditValleyMetres()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveSettings()));
}
void ShowAllSpec::saveSettings(){

    p->setId(static_cast<unsigned short>(spinId->value()));
    if (!imageString.isEmpty()){
        if (imageString == "NoImage")
            p->setImmagine(imageString.toStdString());
        else
            p->setImmagine(imageBytes.toBase64().toStdString());
    }
    p->setNome(editName->text().toStdString());
    p->setProduttore(manufacters->currentText().toStdString());
    p->setQuotaValle(static_cast<unsigned int>(spinHeightValley->value()));
    p->setQuotaMonte(static_cast<unsigned int>(spinHeightMountain->value()));
    p->setPotenzaMotore(spinEnginePower->value());
    p->setVelocitaEsercizio(static_cast<float>(spinDrivingSpeedLine->value()));
    p->setAnnoCostruzione(static_cast<short>(spinYearOfConstruction->value()));
    p->setCapienzaVeicolo(static_cast<short>(spinCapacity->value()));
    if(p->getMovimentazione()=="Continua"){
        MovimentazioneContinua* mc = static_cast<MovimentazioneContinua*>(p);
        mc->setAmmorsamento(comboDetachable->currentIndex() == 1 ? string("automatico") : string("fisso"));

        if(p->getType()=="seggiovia"){
            Seggiovia* s = dynamic_cast<Seggiovia*>(p);
            s->setCopertura(checkBoxCoverage->isChecked());
            s->setAppoggiaSci(checkBoxSkiRests->isChecked());

        }else if(p->getType()=="cabinovia"){
            Cabinovia* c = dynamic_cast<Cabinovia*>(p);
            c->setNumeroFuni(static_cast<short>(spinRopeNumber->value()));

        }else if(p->getType()=="telemix"){
            Telemix* t = dynamic_cast<Telemix*>(p);
            t->setCopertura(checkBoxCoverage->isChecked());
            t->setAppoggiaSci(checkBoxSkiRests->isChecked());
            t->setCapienzaCabina(static_cast<short>(spinCabinCapacity->value()));

        }else if (p->getType()=="sciovia"){
            Sciovia* s = static_cast<Sciovia*>(p);
            s->setGancio(comboHook->currentText().toStdString());
        }

    }else if(p->getMovimentazione()=="Va e Vieni"){
        MovimentazioneVaeVieni* vev = static_cast<MovimentazioneVaeVieni*>(p);
        vev->setTempoPausa(spinTime->value());

        if(p->getType()=="funifor"){
            Funifor* f = static_cast<Funifor*>(p);
            f->setNumeroCabine(static_cast<short>(spinCabinNumber->value()));

        }else if(p->getType()=="funicolare"){
            Funicolare* f = static_cast<Funicolare*>(p);
            f->setTecBinario(comboTecBin->currentText().toStdString());
        }
    }


    emit dataChanged(begin, end);
    this->close();
}


void ShowAllSpec::slotEditValleyMetres() const{
    spinHeightMountain->setValue(spinHeightValley->value());
    spinHeightMountain->setMinimum(spinHeightValley->value());
}

void ShowAllSpec::slotLoadPhoto(){
   imageString = QFileDialog::getOpenFileName(this,tr("Selezione l'immagine: "), "",tr("JPG (*.jpg);;PNG (*.png);;All Files (*)"));

   if (!imageString.isEmpty()){
        savePhoto = QImage(imageString);

        imageBytes = QByteArray();
        QBuffer buffer(&imageBytes);

        savePhoto.save(&buffer,"JPG");

        image->setPixmap(QPixmap::fromImage(savePhoto));
   }
}

void ShowAllSpec::slotRemoveImage(){
    image->clear();
    imageString = "NoImage";
}
