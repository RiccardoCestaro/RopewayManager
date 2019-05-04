#ifndef QFILTERPROXYMODEL_H
#define QFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QAbstractItemModel>
#include <QComboBox>

/*
 * Classe proxy che funzionerà da intermediario fra QTableModelAdapter e TableView
 * per permettere alla vista di visualizzare solo certi elementi sulla base
 * dell'input di ricerca inserito pur non dovendo effettuare alcuna operazione
 * sul reale modello dei dati sottostante e senza duplicare dati.
 */
class QFilterProxyModel : public QSortFilterProxyModel {
private:
    const QComboBox* ropewayType;
    const QComboBox* ropewayManufacter;
protected:
    bool filterAcceptsRow(int, const QModelIndex&) const override;
public:
    QFilterProxyModel(QObject* = nullptr, const QComboBox* = nullptr,const QComboBox* = nullptr);

    void removeResults() ;
    void showMore(const QModelIndex&) const;
    bool insertRows(int, int = 1, const QModelIndex& = QModelIndex()) override;

};

#endif // QFILTERPROXYMODEL_H
