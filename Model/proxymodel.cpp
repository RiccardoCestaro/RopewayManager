#include "proxymodel.h"
#include "modeladapter.h"
#include <vector>
#include <QComboBox>

#include <iostream>

ProxyModel::ProxyModel(QObject* parent, const QComboBox* c, const QComboBox* m) :
      QSortFilterProxyModel (parent),
      ropewayType(c),
      ropewayManufacter(m){}

/**
 * @brief ProxyModel::showMore
 * @param index
 *
 * richiama il metodo showMore di tableModel
 * che permette di visualizzare showAllSpec
 */
void ProxyModel::showMore(const QModelIndex& index) const{
    QModelIndex index_source = mapToSource(index);
    static_cast<ModelAdapter*>(sourceModel())->showMore(index_source);
}

/**
 * @brief ProxyModel::removeResults
 *
 * rimuove tutte le righe della tabella
 */
void ProxyModel::removeResults() {
    while(rowCount()){
        removeRows(0,1);
    }
}

/**
 * @brief ProxyModel::insertRows
 * @param begin
 * @param count
 * @param parent
 * @return
 *
 * richiama il metodo insertRows del tableModel,
 * che consente di inserire oggetti
 */
bool ProxyModel::insertRows(int begin, int count, const QModelIndex& parent) {
    bool result = sourceModel()->insertRows(begin, count, parent);
    invalidateFilter();
    return result;
}

/**
 * @brief ProxyModel::clear
 *
 * richiama il metodo clear della classe tableModel,
 * che permette di pulire il container
 */
void ProxyModel::clear(){
    while(rowCount()){
        removeRows(0,1);
    }
    return static_cast<ModelAdapter*>(sourceModel())->clear();
}

/**
 * @brief ProxyModel::filterAcceptsRow
 * @param row_source
 * @return
 *
 * permette la ricerca degli oggetti
 */
bool ProxyModel::filterAcceptsRow(int row_source, const QModelIndex&) const {
    if (filterRegExp().isEmpty()) return true;
    ModelAdapter* qtma = static_cast<ModelAdapter*>(sourceModel());
    return qtma->matchX(static_cast<unsigned int>(row_source),filterRegExp());
}





