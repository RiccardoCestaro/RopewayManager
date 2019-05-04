#include "View/Components/viewropeway.h"
#include <QLabel>
#include <QHeaderView>



ViewRopeway::ViewRopeway(QWidget *parent, InsertRopeway* i) :
    QWidget(parent){

    view = new TableView(this,true);
    model = new QTableModelAdapter(parent,i);

    proxymodel = new QFilterProxyModel(parent,searchType,searchManufacters);


    //PULSANTI
    showAllSpec = new QPushButton("Visualizza",this);
    showAllSpec->setToolTip(tr("See more info about the selected item"));

    removeButton = new QPushButton("Rimuovi",this);
    removeButton->setToolTip(tr("Remove the selected  item"));

//LAYOUT
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    // Searchbar sottolayout
    QHBoxLayout* searchLayout = new QHBoxLayout();

    QLabel* searchTypeLabel = new QLabel(this);
    QLabel* searchManufacterLabel = new QLabel(this);

    searchTypeLabel->setText("Filtra per tipologia:");
    searchManufacterLabel->setText("Filtra per produttore: ");

    searchType = new QComboBox(this);
    searchManufacters = new QComboBox(this);

    searchType->addItem("Tutto");
    searchType->addItems(InsertRopeway::typeOfLift);

    searchManufacters->addItem("Tutto");
    searchManufacters->addItems(InsertRopeway::manufacters);

    searchLayout->addWidget(searchTypeLabel,0,Qt::AlignRight);
    searchLayout->addWidget(searchType,0,Qt::AlignLeft);

    searchLayout->addWidget(searchManufacterLabel,0,Qt::AlignRight);
    searchLayout->addWidget(searchManufacters,0,Qt::AlignLeft);


    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(showAllSpec);
    buttonsLayout->addWidget(removeButton);

    mainLayout->addLayout(searchLayout, 50);


    mainLayout->addWidget(view, 0, Qt::AlignCenter);
    mainLayout->addLayout(buttonsLayout, 50); // stretch = 50 per distanziare i bottoni

}


TableView *ViewRopeway::getView() const{
    return view;
}

QLineEdit *ViewRopeway::getSearchbar() const{
    return searchbar;
}

QFilterProxyModel *ViewRopeway::getProxymodel() const{
    return proxymodel;
}

QTableModelAdapter *ViewRopeway::getModel() const{
    return model;
}

QPushButton *ViewRopeway::getRemoveButton() const{
    return removeButton;
}

QPushButton *ViewRopeway::getShowAllSpec() const{
    return showAllSpec;
}


/*
 * IMPOSTA IL PROXYMODEL ALLA TABELLA DOPO IL CARICAMENTO DEI DATI VIA XML
 * E VISUALIZZA TUTTO IL CONTAINER APPENA RIEMPITO
 *
 */
void ViewRopeway::updateTable() const{
    proxymodel->setSourceModel(model);
    view->setModel(proxymodel);
    proxymodel->setFilterKeyColumn(-1);

    /* Imposta la larghezza delle singole colonne */
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

/*
 *
 * GETTERS PER RITORNARE I DUE COMBOBOX PER IL FILTERING
 *
 */
QComboBox *ViewRopeway::getSearchList() const{
    return searchType;
}
QComboBox *ViewRopeway::getSearchManufacters() const{
    return searchManufacters;
}


