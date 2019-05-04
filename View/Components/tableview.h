#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>

#include <View/Components/tableheader.h>

/*
 * Classe utile per dimensionare correttamente la view con sizeHint()
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
