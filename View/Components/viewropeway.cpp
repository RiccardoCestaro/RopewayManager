#include "View/Components/viewropeway.h"
#include "Model/Gerarchia/Utils/tipologia.h"

#include <QLabel>
#include <QHeaderView>

/**
 * @brief ViewRopeway::ViewRopeway
 * @param parent
 * @param i
 *
 * Costruttore della classe ViewRopeway
 */
ViewRopeway::ViewRopeway(QWidget *parent, InsertRopeway* i) :
    QWidget(parent),
    searchType(new QComboBox(this)),
    searchManufacters(new QComboBox(this)),
    proxymodel(new ProxyModel(parent,searchType,searchManufacters)),
    model(new ModelAdapter(parent,i)),
    view(new TableView(this,true)),
    removeButton(new QPushButton("Rimuovi",this)),
    showAllSpec(new QPushButton("Visualizza",this)){


    showAllSpec->setToolTip(tr("See more info about the selected item"));
    removeButton->setToolTip(tr("Remove the selected  item"));

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* searchLayout = new QHBoxLayout();

    QLabel* searchTypeLabel = new QLabel(this);
    QLabel* searchManufacterLabel = new QLabel(this);

    searchTypeLabel->setText("Filtra per tipologia:");
    searchManufacterLabel->setText("Filtra per produttore: ");

    searchType->addItem("Tutto");
    searchType->addItems(Tipologia::values);

    searchManufacters->addItem("Tutto");
    searchManufacters->addItems(Produttore::values);

    searchLayout->addWidget(searchTypeLabel,0,Qt::AlignRight);
    searchLayout->addWidget(searchType,0,Qt::AlignLeft);

    searchLayout->addWidget(searchManufacterLabel,0,Qt::AlignRight);
    searchLayout->addWidget(searchManufacters,0,Qt::AlignLeft);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(showAllSpec);
    buttonsLayout->addWidget(removeButton);

    mainLayout->addLayout(searchLayout, 50);

    mainLayout->addWidget(view, 0, Qt::AlignCenter);
    mainLayout->addLayout(buttonsLayout, 50);
}

/**
 * @brief ViewRopeway::getView
 * @return view
 *
 * Metodo pubblico:
 * Metodo getter che ritorna la TableView view
 */
TableView *ViewRopeway::getView() const{
    return view;
}

/**
 * @brief ViewRopeway::getProxymodel
 * @return proxymodel
 *
 * Metodo pubblico:
 * Metodo getter che ritorna il ProxyModel proxymodel
 */
ProxyModel *ViewRopeway::getProxymodel() const{
    return proxymodel;
}

/**
 * @brief ViewRopeway::getModel
 * @return model
 *
 * Metodo pubblico:
 * Metodo getter che ritorna la ModelAdapter model
 */
ModelAdapter *ViewRopeway::getModel() const{
    return model;
}

/**
 * @brief ViewRopeway::getRemoveButton
 * @return removeButton
 *
 * Metodo pubblico:
 * Metodo getter che ritorna il QPushButton removeButton
 */
QPushButton *ViewRopeway::getRemoveButton() const{
    return removeButton;
}

/**
 * @brief ViewRopeway::getShowAllSpec
 * @return showAllSpec
 *
 * Metodo pubblico:
 * Metodo getter che ritorna il QPushButton showAllSpec
 */
QPushButton *ViewRopeway::getShowAllSpec() const{
    return showAllSpec;
}

/**
 * @brief ViewRopeway::updateTable
 *
 * Metodo pubblico:
 * La tabella viene completamente ricaricata,
 * quindi viene ricaricato il modello e il proxyModel
 *
 * Inoltre vengono impostate le dimensioni delle colonne,
 * e l'altezza delle righe
 */
void ViewRopeway::updateTable() const{
    proxymodel->setSourceModel(model);
    view->setModel(proxymodel);
    proxymodel->setFilterKeyColumn(-1);

    view->setColumnWidth(0,85);
    view->setColumnWidth(1,175);
    view->setColumnWidth(2,125);
    view->setColumnWidth(3,125);
    view->setColumnWidth(4,125);
    view->setColumnWidth(5,125);
    view->setColumnWidth(6,130);

    for(int i=0;i<view->model()->rowCount();++i)
        view->setRowHeight(i,40);
}

/**
 * @brief ViewRopeway::getSearchList
 * @return searchType
 *
 * Metodo pubblico:
 * Metodo getter che ritorna la QComboBox serchType
 */
QComboBox *ViewRopeway::getSearchList() const{
    return searchType;
}

/**
 * @brief ViewRopeway::getSearchManufacters
 * @return searchManufacters
 *
 * Metodo pubblico:
 * Metodo getter che ritorna la QComboBox searchManufacters
 */
QComboBox *ViewRopeway::getSearchManufacters() const{
    return searchManufacters;
}


