#ifndef ITEMVIEW_H
#define ITEMVIEW_H

#include <QWidget>
#include <QModelIndex>
#include <QLineEdit>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QString>
#include <QFileDialog>

#include "Model/Gerarchia/impianto.h"
#include "Model/Gerarchia/movimentazionecontinua.h"

/**
 * @brief The ShowAllSpec class
 *
 * View: grafica relativa alla visualizzazione e modifica dell'impianto
 */
class ShowAllSpec : public QWidget{

private:
    Q_OBJECT
    Impianto* p;
    const QModelIndex begin;
    const QModelIndex end;
    QLabel* tipo;
    QLabel* image;
    QString imageString;
    QLineEdit* nome;

    QSpinBox* spinId;
    QLineEdit* editName;
    QSpinBox* spinCapacity;
    QSpinBox *spinHeightValley, *spinHeightMountain;
    QDoubleSpinBox* spinEnginePower;
    QDoubleSpinBox* spinDrivingSpeedLine;
    QComboBox* manufacters;
    QSpinBox* spinYearOfConstruction;
    QComboBox* comboDetachable;
    QCheckBox* checkBoxSkiRests;
    QCheckBox* checkBoxCoverage;
    QSpinBox* spinRopeNumber;
    QSpinBox* spinCabinCapacity;
    QComboBox* comboHook;
    QSpinBox* spinTime;
    QSpinBox* spinCabinNumber;
    QComboBox* comboTecBin;
    QByteArray imageBytes;
    QImage savePhoto;
public:
    explicit ShowAllSpec(Impianto*, const QModelIndex&, const QModelIndex&, QWidget *parent = nullptr);

signals:
    void dataChanged(const QModelIndex&, const QModelIndex&);

private slots:
    void saveSettings();
    void slotEditValleyMetres() const;
    void slotLoadPhoto();
    void slotRemoveImage();
};

#endif // ITEMVIEW_H
