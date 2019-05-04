#ifndef VIEWROPEWAY_H
#define VIEWROPEWAY_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "Model/qfilterproxymodel.h"
#include "Model/qtablemodeladapter.h"
#include "View/Components/tableview.h"
#include "View/Components/insertropeway.h"

class ViewRopeway : public QWidget{
private:
    Q_OBJECT
    QLineEdit* searchbar;
    QFilterProxyModel* proxymodel;
    QTableModelAdapter* model;
    TableView* view;

    QComboBox* searchType;
    QComboBox* searchManufacters;

    QPushButton* removeButton;
    QPushButton* showAllSpec;
public:
    explicit ViewRopeway(QWidget *parent = nullptr,InsertRopeway* i = nullptr );

    TableView *getView() const;
    QLineEdit *getSearchbar() const;
    QFilterProxyModel *getProxymodel() const;
    QTableModelAdapter *getModel() const;
    QPushButton *getRemoveButton() const;


    QComboBox *getSearchList() const;
    QComboBox *getSearchManufacters() const;
    QPushButton *getShowAllSpec() const;


    void updateTable() const;

signals:

public slots:
};

#endif // VIEWROPEWAY_H
