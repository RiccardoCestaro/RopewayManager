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

/**
 * @brief The InsertRopeway class
 *
 * View: grafica relativa all'inserimento di un impianto
 */
class InsertRopeway : public QWidget{
private:

    Q_OBJECT
    QVBoxLayout* mainLayout;
    QHBoxLayout* insertLayout;
    QVBoxLayout* photoLayout;
    QFormLayout* formLayout;

    QLabel *type, *name, *id,*capacity, *manufacter, *heightMountain, *heightValley,
    *drivingSpeedLine, *yearOfConstruction, *enginePower,*detachT, *skiRests, 
    *coverage,*ropeNumber, *hook,*tecBin, *funiforCabinNumber, *time, *cabinCapacity;

    QLineEdit* editName;
    QPushButton* addItem;

    QSpinBox *spinCapacity, *spinId, *spinHeightValley, *spinHeightMountain, *spinEnginePower,
    *spinDrivingSpeedLine, *spinYearOfConstruction, *spinRopeNumber, *spinCabinCapacity, *spinTime;

    QCheckBox *checkBoxSkiRests, *checkBoxCoverage;

    QComboBox *comboHook, *comboType, *comboManufacter, *comboDetachable, *comboCabinNumber, *comboTecBin;

    QString photoString;
    QImage image;
    QByteArray imageBytes;
    QLabel* imageLabel;

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

public slots:

    void slotEditValleyMetres() const;
    void slotEditType() const;
    void slotLoadPhoto();

};

#endif // INSERTROPEWAY_H
