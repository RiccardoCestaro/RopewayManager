#include "mainwindow.h"
#include "Model/modeladapter.h"
#include "Model/proxymodel.h"

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

/**
 * @brief MainWindow::MainWindow
 * @param parent
 * @param load
 * @param o
 *
 * Costruttore della classe MainWindow
 */
MainWindow::MainWindow(QWidget *parent, bool load, int o) : QWidget(parent),
    offset(o),
    toolbar(new ToolBar(this)),
    tabbar(new TabBar(this)),
    insertPage(new InsertRopeway(this)),
    viewPage(new ViewRopeway(this,insertPage)),
    fileName(QString()){

    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,this->size(),qApp->desktop()->availableGeometry()));

    setWindowTitle(tr("Ropeway Manager"));
    setWindowIcon(QIcon(":/icon.svg"));
    setFixedSize(QSize(950, 600));

    /** Precaricamento dei dati */
    if(load)
        loadData();

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(toolbar);

    mainLayout->addWidget(tabbar);

    showViewPage();
    mainLayout->addWidget(viewPage);
    mainLayout->addWidget(insertPage,1,Qt::AlignTop);

    connect(tabbar,SIGNAL(currentChanged(int)),this,SLOT(showPage(int)));
    connect(toolbar->getNewArray(), SIGNAL(triggered()), this, SLOT(newManager()));
    connect(toolbar->getDeleteArray(), SIGNAL(triggered()), this, SLOT(deleteArray()));
    connect(toolbar->getLoadFromXml(), SIGNAL(triggered()), this, SLOT(loadData()));
    connect(toolbar->getSaveToXml(), SIGNAL(triggered()), this, SLOT(saveData()));
    connect(toolbar->getSaveAsToXml(), SIGNAL(triggered()), this, SLOT(saveAsData()));
    connect(viewPage->getShowAllSpec(), SIGNAL(clicked()), this, SLOT(showMore()));
    connect(viewPage->getRemoveButton(), SIGNAL(clicked()), this, SLOT(remove()));
    connect(viewPage->getSearchList(), SIGNAL(currentTextChanged(const QString&)), this, SLOT(changedFilter()));
    connect(viewPage->getSearchManufacters(), SIGNAL(currentTextChanged(const QString&)), this, SLOT(changedFilter()));

    connect(insertPage->getAddItem(), SIGNAL(clicked()), this, SLOT(add()));

}

/**
 * @brief MainWindow::showInsertPage
 *
 * metodo privato:
 * che nasconde la pagina di visualizzazione
 * e mostra la pagina di inserimento degli impianti
 */
void MainWindow::showInsertPage() const{
    viewPage->hide();
    insertPage->show();
}

/**
 * @brief MainWindow::showViewPage
 *
 * metodo privato:
 * che nasconde la pagina di inserimento
 * e mostra la pagina di visualizzazione
 */

void MainWindow::showViewPage() const{
    insertPage->hide();
    viewPage->show();
}

/**
 * @brief MainWindow::saveData
 *
 * slot privato:
 * se il nome del file non e' vuoto
 * sovrascive il file con una deserializzazione
 * altrimenti chiama lo slot saveAsData()
 */

void MainWindow::saveData() {
    if(!fileName.isEmpty()){
        try {
            viewPage->getModel()->saveToFile(fileName.toStdString());
        } catch (std::exception) {
            QMessageBox box(QMessageBox::Warning, "Errore di salvataggio", "Non è stato possibile scrivere sul file", QMessageBox::Ok);
            box.exec();
        }
    }else saveAsData();
}

/**
 * @brief MainWindow::saveAsData
 *
 * slot privato:
 * Apre una finestra dove e' possibile
 * scegliere il nome del file di salvataggio
 * e la sua posizione nel disco rigido
 */
void MainWindow::saveAsData() {
    fileName = QFileDialog::getSaveFileName(this,
                                            tr("Save to a file"), "",
                                            tr("XML (*.xml);;All Files (*)"));
    if(!fileName.isEmpty()){
        try {
            viewPage->getModel()->saveToFile(fileName.toStdString());
        } catch (std::exception) {
            QMessageBox box(QMessageBox::Warning, "Errore di salvataggio", "Non è stato possibile scrivere sul file", QMessageBox::Ok);
            box.exec();
        }
    }
}

/**
 * @brief MainWindow::loadData
 *
 * slot privato:
 * Apre una finestra dove e' possibile
 * selezionare il file da cui eseguire
 * la deserializzazione dei dati.
 * Si puo' scegliere anche di caricare
 * i valori di default
 */
void MainWindow::loadData(){
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Load from a file"), "",
                                            tr("XML (*.xml);;All Files (*)"));
    if(!fileName.isEmpty()){
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

/**
 * @brief MainWindow::add
 *
 * slot privato:
 * aggiunge un nuovo oggetto alla tabella
 */
void MainWindow::add() const{
    viewPage->getProxymodel()->insertRows(viewPage->getProxymodel()->rowCount(), 1);
    viewPage->getView()->clearSelection();
    viewPage->getView()->selectionModel()->clearCurrentIndex();
    viewPage->getView()->selectionModel()->select(viewPage->getProxymodel()->index(viewPage->getModel()->rowCount() - 1, 0), QItemSelectionModel::Select);
    viewPage->updateTable();
}

/**
 * @brief MainWindow::remove
 *
 * slot privato:
 * rimuove gli oggetti dalla tabella
 * e dal container
 */
void MainWindow::remove() const{
    const QModelIndexList selection = viewPage->getView()->selectionModel()->selectedIndexes();
    if(selection.size() > 0)
        viewPage->getProxymodel()->removeRows(selection.at(0).row(), 1);
}

/**
 * @brief MainWindow::showMore
 *
 * slot privato:
 * visualizza la vista showallspec
 */
void MainWindow::showMore() const{
    const QModelIndexList selection = viewPage->getView()->selectionModel()->selectedIndexes();
    if(selection.size() > 0)
        viewPage->getProxymodel()->showMore(selection.at(0));
}

/**
 * @brief MainWindow::changedFilter
 *
 * slot privato:
 * crea un'espressione regolare contenente la scelta efettuata delle
 * due combobox di ricerca.
 * Permette di eseguire una ricerca incrociata.
 * La regex viene poi passata come parametro al metodo setFilterRegExp
 * della classe QProxyModel
 */
void MainWindow::changedFilter() const {
    QRegExp regex(viewPage->getSearchList()->currentText()+'|'+viewPage->getSearchManufacters()->currentText(), Qt::CaseInsensitive, QRegExp::Wildcard);
    viewPage->getProxymodel()->setFilterRegExp(regex);
}

/**
 * @brief MainWindow::newManager
 *
 * Slot privato:
 * Permette di aprire una nuova Window di Ropeway Manager
 */
void MainWindow::newManager() const {
    MainWindow* newRopewayManager = new MainWindow(nullptr, false, offset+20);
    newRopewayManager->setAttribute(Qt::WA_DeleteOnClose);
    newRopewayManager->show();
}

/**
 * @brief MainWindow::closeEvent
 * @param event
 *
 * Metodo protetto:
 * alla chiusura della finestra, visualizza un messageBox
 * che permette all'utente di scegliere se effettuare
 * la serializzazione del container
 */
void MainWindow::closeEvent(QCloseEvent *event){
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, tr("RopewayManager"),
                                                                tr("Do you want to save?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if(resBtn==QMessageBox::Cancel)
        event->ignore();
    else{
        if(resBtn==QMessageBox::Yes)
            saveData();
        event->accept();
    }
}

/**
 * @brief MainWindow::deleteArray
 *
 * slot privato:
 * Esegue una pulizia totale del container
 * e della tabella
 */

void MainWindow::deleteArray(){
    viewPage->getProxymodel()->clear();
}

/**
 * @brief MainWindow::removeResults
 *
 * slot privato:
 * Rimuove tutti gli oggetti visualizzati sulla tabella
 */
void MainWindow::removeResults() const{
    viewPage->getProxymodel()->removeResults();
}

/**
 * @brief MainWindow::showPage
 * @param currentTab
 *
 * slot privato:
 * visualizza la vista corrispondente
 * alla tab della tabbar scelta
 */
void MainWindow::showPage(int currentTab) const{
    if(currentTab == 0)
        showViewPage();
    else if(currentTab == 1)
        showInsertPage();
}


