#include "qfilterproxymodel.h"
#include "qtablemodeladapter.h"
#include <vector>
#include <QComboBox>

#include <iostream>

QFilterProxyModel::QFilterProxyModel(QObject* parent, const QComboBox* c, const QComboBox* m)
    : QSortFilterProxyModel (parent), ropewayType(c), ropewayManufacter(m){

}

void QFilterProxyModel::showMore(const QModelIndex& index) const{
    QModelIndex index_source = mapToSource(index);
    static_cast<QTableModelAdapter*>(sourceModel())->showMore(index_source);
}

void QFilterProxyModel::removeResults() {
    while(rowCount()){
        removeRows(0,1);
    }
}

bool QFilterProxyModel::insertRows(int begin, int count, const QModelIndex& parent) {
    bool result = sourceModel()->insertRows(begin, count, parent);
    invalidateFilter();
    return result;
}

bool QFilterProxyModel::filterAcceptsRow(int row_source, const QModelIndex& s) const {
    if (filterRegExp().isEmpty()) return true;
    QTableModelAdapter* qtma = static_cast<QTableModelAdapter*>(sourceModel());
    return qtma->match(static_cast<unsigned int>(row_source),filterRegExp());
}





