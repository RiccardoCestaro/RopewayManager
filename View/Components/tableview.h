#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>
#include <View/Components/tableheader.h>

/**
 * @brief The TableView class
 *
 * Estende QTableView
 * Vengono ridefiniti gli eventi di click e doppio click,
 * e fissata la dimensione della tabella
 * Inoltre viene aggiunto l'evento per l'ordinamento tramite
 * un click nella header della tabella
 */
class TableView : public QTableView {
    Q_OBJECT
private:

    TableHeader* header;
    bool orderSense;

public:

    TableView(QWidget* = nullptr, const bool& = true);
    QSize sizeHint() const override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseDoubleClickEvent(QMouseEvent*) override;

private slots:
    void slotSectionClicked(int index);
};

#endif // TABLEVIEW_H
