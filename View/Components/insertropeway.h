#ifndef INSERTROPEWAY_H
#define INSERTROPEWAY_H

#include <QWidget>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QDateEdit>
#include <QString>
#include <QSpinBox>
#include <QPushButton>

#include "Model/deepptr.h"
#include "Model/Gerarchia/impianto.h"

class InsertRopeway : public QWidget{
private:

    Q_OBJECT
    QVBoxLayout *mainLayout;
    QHBoxLayout *insertLayout;
    QVBoxLayout *photoLayout;

    QFormLayout* formLayout;

    QLabel *type, *name, *id,*capacity, *manufacter, *heightMountain, *heightValley,
    *drivingSpeedLine, *yearOfConstruction, *enginePower,
    *detachT, *numVehicles, *skiRests, *coverage,
    *ropeNumber, *hook,*tecBin, *funiforCabinNumber, *time, *cabinCapacity;

    QLineEdit  *editName;
    QPushButton* addItem;

    QComboBox* comboType;
    QComboBox* comboManufacter;
    QComboBox* comboDetachable;
    QSpinBox *spinCapacity;
    QSpinBox *spinId;
    QSpinBox *spinHeightValley, *spinHeightMountain;
    QSpinBox *spinEnginePower;
    QSpinBox *spinDrivingSpeedLine;
    QSpinBox *spinYearOfConstruction;
    QSpinBox *spinVehicles;

    QCheckBox *checkBoxSkiRests, *checkBoxCoverage;
    QComboBox *comboHook;
    QSpinBox *spinRopeNumber;
    QSpinBox *spinCabinCapacity;
    QSpinBox *spinTime;
    QComboBox *comboCabinNumber;
    QComboBox *comboTecBin;


    QString photoString;
    QImage image;
    QByteArray imageBytes;
    QLabel* imageLabel;

public:

    explicit InsertRopeway(QWidget *parent = nullptr);
    explicit InsertRopeway(DeepPtr<Impianto> lift, QWidget *parent = nullptr);


    QString getCurrentType() const;
    QComboBox *getEditManufacter() const;
    QLineEdit *getEditName() const;
    QSpinBox *getSpinId() const;
    QSpinBox *getSpinHeightValley() const;
    QSpinBox *getSpinHeightMountain() const;
    QSpinBox *getSpinCapacity() const;
    QSpinBox *getSpinEnginePower() const;
    QSpinBox *getSpinDrivingSpeedLine() const;
    QSpinBox *getSpinYearOfConstruction() const;
    QSpinBox *getSpinVehicles() const;
    QCheckBox *getCheckBoxSkiRests() const;
    QCheckBox *getCheckBoxCoverage() const;
    QSpinBox *getSpinRopeNumber() const;
    QSpinBox *getSpinTime() const;
    QComboBox *getComboCabinNumber() const;
    QComboBox *getComboTecBin() const;
    QSpinBox *getSpinCabinCapacity() const;
    QComboBox *getComboDetachable() const;
    QComboBox *getComboHook() const;
    QImage getImage() const;
    QByteArray getImageBytes() const;
    QString getPhoto() const;
    QPushButton *getAddItem() const;

    static QStringList manufacters, typeOfLift;


    void defaultForm() const;
    void showContinue() const;
    void showPulsee() const;
    void showGondolaLift() const;
    void showChairLift() const;
    void showTelemix() const;
    void showSkilift() const;
    void showFunifor() const;
    void showAerialTramway() const;
    void showFunicolar() const;





public slots:

    void slotEditValleyMetres() const;
    void slotEditType() const;
    void slotLoadPhoto();

};

#endif // INSERTROPEWAY_H
