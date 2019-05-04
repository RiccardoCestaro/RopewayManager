#include "mainwindow.h"
#include "Model/qtablemodeladapter.h"
#include "Model/qfilterproxymodel.h"

#include <QDesktopWidget>
#include <QApplication>
#include <QLayout>
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QLineEdit>
#include <QCloseEvent>
#include <QComboBox>
#include <QFileDialog>
#include <QDebug>
#include <QTabBar>

QStringList MainWindow::typeOfLift = {"Seggiovia","Cabinovia","Telemix","Sciovia","Funivia","Funifor","Funicolare"};

MainWindow::MainWindow(QWidget *parent, bool load, int o) : QWidget(parent),
    offset(o),
    toolbar(new ToolBar(this)),
    tabbar(new QTabBar(this)),
    insertPage(new InsertRopeway(this)),
    viewPage(new ViewRopeway(this,insertPage)),
    fileName(QString()){

    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,this->size(),qApp->desktop()->availableGeometry()));

    setWindowTitle(tr("Ropeway Manager")); //titolo applicazione
    setWindowIcon(QIcon(":/icon.svg")); // icona del programma
    setFixedSize(QSize(950, 600)); //dimensione fissa non ridimensionabile

    if(load)
        loadData(); //caricamento modello

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(toolbar);

    tabbar->addTab("Visualizza");
    tabbar->addTab("Inserisci");
    tabbar->setCurrentIndex(0);
    mainLayout->addWidget(tabbar);

    showViewPage();
    mainLayout->addWidget(viewPage);
    mainLayout->addWidget(insertPage,1,Qt::AlignTop);
    // CONNECT
    connect(tabbar,SIGNAL(currentChanged(int)),this,SLOT(showPage(int)));

    connect(toolbar->getNewArray(), SIGNAL(triggered()), this, SLOT(newBeauty()));
    //connect(toolbar->getLoadFromXml(), SIGNAL(triggered()), this, SLOT(loadNewBeauty()));
    connect(toolbar->getLoadFromXml(), SIGNAL(triggered()), this, SLOT(loadData()));
    connect(toolbar->getSaveToXml(), SIGNAL(triggered()), this, SLOT(saveData()));
    //connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAsData()));
    //connect(exitAction, SIGNAL(triggered()), this, SLOT(close())); --> toolbar does not include close QmenuAction
    connect(viewPage->getShowAllSpec(), SIGNAL(clicked()), this, SLOT(showMore()));
    //connect(useButton, SIGNAL(clicked()), this, SLOT(use()));
    //connect(useResultsButton, SIGNAL(clicked()), this, SLOT(useResults()));
    connect(viewPage->getRemoveButton(), SIGNAL(clicked()), this, SLOT(remove()));
    //connect(removeResultsButton, SIGNAL(clicked()), this, SLOT(removeResults()));
    //connect(viewPage->getSearchList(), SIGNAL(currentIndexChanged(const QString&)), this, SLOT(textFilterChanged()));


    /* Signals used to filtering polymorphic object of class impianto
     * by type and manufacter
     */
    connect(viewPage->getSearchList(), SIGNAL(currentTextChanged(const QString&)), this, SLOT(changedFilter()));
    connect(viewPage->getSearchManufacters(), SIGNAL(currentTextChanged(const QString&)), this, SLOT(changedFilter()));

    //connect(clearSearchButton, SIGNAL(clicked()), searchbar, SLOT(clear()));
    connect(insertPage->getAddItem(), SIGNAL(clicked()), this, SLOT(add())); //--> add an impianto polymorphic object

}
QSize MainWindow::sizeHint() const {
    return QSize(500, 600);
}
void MainWindow::saveData() {
    if(!fileName.isEmpty()){
        try {
            viewPage->getModel()->saveToFile(fileName.toStdString());
        } catch (std::exception) {
            QMessageBox box(QMessageBox::Warning, "Errore di salvataggio", "Non è stato possibile scrivere sul file", QMessageBox::Ok);
            box.exec();
        }
    }
    else saveAsData();
}
void MainWindow::saveAsData() {
    fileName = QFileDialog::getSaveFileName(this,
                                            tr("Save to a file"), "",
                                            tr("XML (*.xml);;All Files (*)"));
    if(!fileName.isEmpty()){
        setWindowTitle(QFileInfo(fileName).fileName() + tr(" - My Beauty"));
        try {
            viewPage->getModel()->saveToFile(fileName.toStdString());
        } catch (std::exception) {
            QMessageBox box(QMessageBox::Warning, "Errore di salvataggio", "Non è stato possibile scrivere sul file", QMessageBox::Ok);
            box.exec();
        }
    }
}
void MainWindow::loadData() {
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Load from a file"), "",
                                            tr("XML (*.xml);;All Files (*)"));
    if(!fileName.isEmpty()){
        std::cout << fileName.toStdString() << std::endl;

        viewPage->getModel()->loadFromFile(fileName.toStdString());

    }else{
        QMessageBox::StandardButton defaultOrEmpty = QMessageBox::question( this, tr("RopewayManager"),
                                                                    tr("Caricare i valori di default?\n"),
                                                                    QMessageBox::No | QMessageBox::Yes,
                                                                    QMessageBox::Yes);
        if(defaultOrEmpty==QMessageBox::Yes)
            viewPage->getModel()->loadFromFile(":/default.xml");
    }
    viewPage->updateTable();
}
void MainWindow::add() const{
    viewPage->getProxymodel()->insertRows(viewPage->getProxymodel()->rowCount(), 1);
    viewPage->getView()->clearSelection();
    viewPage->getView()->selectionModel()->clearCurrentIndex();
    viewPage->getView()->selectionModel()->select(viewPage->getProxymodel()->index(viewPage->getModel()->rowCount() - 1, 0), QItemSelectionModel::Select);
}
void MainWindow::remove() const{
    // prende l'elenco degli elementi selezionati dalla view
    const QModelIndexList selection = viewPage->getView()->selectionModel()->selectedIndexes();
    if(selection.size() > 0)
        viewPage->getProxymodel()->removeRows(selection.at(0).row(), 1);
}

void MainWindow::showMore() const{
    const QModelIndexList selection = viewPage->getView()->selectionModel()->selectedIndexes();
    if(selection.size() > 0)
        viewPage->getProxymodel()->showMore(selection.at(0));
}
/*
 * FILTERING
 */
void MainWindow::changedFilter() const {
    QRegExp regex(viewPage->getSearchList()->currentText()+'|'+viewPage->getSearchManufacters()->currentText(), Qt::CaseInsensitive, QRegExp::Wildcard);
    viewPage->getProxymodel()->setFilterRegExp(regex);
}

void MainWindow::newBeauty() const {
    MainWindow* newRopewayManager = new MainWindow(nullptr, false, offset+20);
    newRopewayManager->setAttribute(Qt::WA_DeleteOnClose); //viene distrutto alla chiusura del nuovo beauty
    newRopewayManager->show();
}
void MainWindow::loadNewBeauty() const{
    MainWindow* beauty = new MainWindow(nullptr, true, offset+20);
    beauty->setAttribute(Qt::WA_DeleteOnClose); //viene distrutto alla chiusura del nuovo beauty
    beauty->show();
}
void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, tr("RopewayManager"),
                                                                tr("Do you want to save?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if(resBtn==QMessageBox::Cancel)
        event->ignore();
    else {
        if(resBtn==QMessageBox::Yes)
            saveData();
        event->accept();
    }
}

void MainWindow::showInsertPage() const{
    viewPage->hide();
    insertPage->show();
}

void MainWindow::showViewPage() const{
    insertPage->hide();
    viewPage->show();
}


void MainWindow::removeResults() const{
    viewPage->getProxymodel()->removeResults();
}

void MainWindow::showPage(int currentTab) const{
    std::cout << currentTab << std::endl;
    if(currentTab == 0)
        showViewPage();
    else if(currentTab == 1)
        showInsertPage();
}
