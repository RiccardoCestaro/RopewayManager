#include "tableheader.h"

TableHeader::TableHeader(QWidget* parent) :QHeaderView (Qt::Horizontal,parent){

    /** Blocca la larghezza delle colonne della QTable */
    setSectionResizeMode(QHeaderView::Fixed);
    setFixedHeight(40);

    /** Imposta cliccabile l'header per l'ordinamento */
    setSectionsClickable(true);

    /** Setta un tooltip */
    setToolTip(tr("Click per ordinare"));

    /** Imposta gli stili */
    setStyleSheet("QHeaderView::section { color:white; background-color:#232326; }"
                  "QHeaderView::section:hover { color:#cccccc; background:#232326; font-weight:900; }");

}
