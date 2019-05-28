#include "tableview.h"
#include "Model/proxymodel.h"

#include <QMouseEvent>
#include <QHeaderView>
#include <QModelIndex>
#include <iostream>

TableView::TableView(QWidget* parent, const bool& o) : QTableView(parent), header(new TableHeader()), orderSense(o) {
    /** rende possibile la selezione di un singolo elemento alla volta */
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setHorizontalHeader(header);

    /** Imposta stili
    setStyleSheet("QTableView::item:selected { color:white; background:#232326; font-weight:900; }"
                               "QTableCornerButton::section { background-color:#232326; }"
                  "QHeaderView::section { color:white; background-color:#232326; }");
    */
    /** Crea evento nel header per l'ordinamento */
    connect(horizontalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(slotSectionClicked(int)));
}

/**
 * @brief TableView::mouseDoubleClickEvent
 * @param event
 *
 * Override del metodo mouseDoubleClickEvent, che richiama
 * il metodo showMore della classe ModelAdapter, passandogli
 * la posizione, se valida.
 */
void TableView::mouseDoubleClickEvent(QMouseEvent *event) {
    if (indexAt(event->pos()).isValid()) {
        static_cast<ProxyModel*>(model())->showMore(indexAt(event->pos()));
    }
}

/**
 * @brief TableView::sizeHint
 * @return QSize
 *
 * override delle dimensioni della view
 *  per farla espandere con il pannello
 */
QSize TableView::sizeHint() const {
    return QSize(1200, 400);
}

/**
 * @brief TableView::mousePressEvent
 * @param event
 *
 * Seleziona la riga al click del muose,
 * cancellando tutte le precedenti selezioni
 */
void TableView::mousePressEvent(QMouseEvent* event) {
     if (!indexAt(event->pos()).isValid()) {
        clearSelection();
        selectionModel()->clearCurrentIndex();
    }
    QTableView::mousePressEvent(event);
}


/**
 * @brief TableView::slotSectionClicked
 * @param index
 *
 * Slot privato:
 * Permette di richiamare il metodo sort nel
 * proxyModel e ordinare la tabella sia in ordine
 * ascendente che discendente
 */
void TableView::slotSectionClicked(int index){
    if (orderSense) static_cast<ProxyModel*>(model())->sort(index,Qt::AscendingOrder);
    else static_cast<ProxyModel*>(model())->sort(index,Qt::DescendingOrder);
    orderSense = !orderSense;
}





