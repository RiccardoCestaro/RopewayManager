#include "tableview.h"
#include "Model/qfilterproxymodel.h"

#include <QMouseEvent>
#include <QHeaderView>
#include <QModelIndex>

#include <iostream>

TableView::TableView(QWidget* parent, const bool& o) : QTableView(parent), header(new TableHeader()), orderSense(o) {
    // rendiamo possibile la selezione di un singolo elemento alla volta
    setSelectionBehavior(QAbstractItemView::SelectRows);

    setHorizontalHeader(header);

    /* Imposta stili */
    setStyleSheet("QTableView::item:selected { color:white; background:#232326; font-weight:900; }"
                               "QTableCornerButton::section { background-color:#232326; }"
                  "QHeaderView::section { color:white; background-color:#232326; }");


    /* Crea evento nel header per l'ordinamento */
    connect(horizontalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(slotSectionClicked(int)));

}
/*
 * Override del metodo mouseDoubleClickEvent, apre la finestra
 * di modifica dell'impianto, come il QPushButton della ViewRopeway.
 */
void TableView::mouseDoubleClickEvent(QMouseEvent *event) {
    if (indexAt(event->pos()).isValid()) {
        static_cast<QFilterProxyModel*>(model())->showMore(indexAt(event->pos()));
    }
}

// override delle dimensioni della view per farla espandere con il pannello
QSize TableView::sizeHint() const {
    return QSize(1200, 400);
}

void TableView::mousePressEvent(QMouseEvent* event) {
     if (!indexAt(event->pos()).isValid()) {
        clearSelection();
        selectionModel()->clearCurrentIndex();
    }
    QTableView::mousePressEvent(event);
}


/*
 * In base al click imposta il tipo di ordinamento
 */
void TableView::slotSectionClicked(int index){
    if (orderSense)
        static_cast<QFilterProxyModel*>(model())->sort(index,Qt::AscendingOrder);
    else static_cast<QFilterProxyModel*>(model())->sort(index,Qt::DescendingOrder);
    orderSense = !orderSense;
}





