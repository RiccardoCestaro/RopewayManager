#ifndef QFILTERPROXYMODEL_H
#define QFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QAbstractItemModel>
#include <QComboBox>

/**
 * @brief The ProxyModel class
 *
 * Estende QSortFilterProxyModel,
 * consente di eseguire delle operazioni
 * sugli elementi della tabella
 */
class ProxyModel : public QSortFilterProxyModel {
private:
    const QComboBox* ropewayType;
    const QComboBox* ropewayManufacter;
protected:
    bool filterAcceptsRow(int, const QModelIndex&) const override;
public:
    ProxyModel(QObject* = nullptr, const QComboBox* = nullptr,const QComboBox* = nullptr);

    void removeResults();
    void showMore(const QModelIndex&) const;
    bool insertRows(int, int = 1, const QModelIndex& = QModelIndex()) override;
    void clear();
};

#endif // QFILTERPROXYMODEL_H
