#ifndef VIEWROPEWAY_H
#define VIEWROPEWAY_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "Model/proxymodel.h"
#include "Model/modeladapter.h"
#include "View/Components/tableview.h"
#include "View/Components/insertropeway.h"

/**
 * @brief The ViewRopeway class
 *
 * View: grafica relativa alla vista degli impianti
 */
class ViewRopeway : public QWidget{
private:
    Q_OBJECT
    QComboBox* searchType;
    QComboBox* searchManufacters;

    ProxyModel* proxymodel;
    ModelAdapter* model;
    TableView* view;

    QPushButton* removeButton;
    QPushButton* showAllSpec;
public:
    explicit ViewRopeway(QWidget *parent = nullptr,InsertRopeway* i = nullptr );

    TableView *getView() const;
    QLineEdit *getSearchbar() const;
    ProxyModel *getProxymodel() const;
    ModelAdapter *getModel() const;
    QPushButton *getRemoveButton() const;

    QComboBox *getSearchList() const;
    QComboBox *getSearchManufacters() const;
    QPushButton *getShowAllSpec() const;

    void updateTable() const;

};

#endif // VIEWROPEWAY_H
