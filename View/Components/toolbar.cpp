#include "toolbar.h"

#include <QMessageBox>

/**
 * @brief ToolBar::ToolBar
 * @param p
 *
 * Costruttore di ToolBar
 * imposta la grafica e connette la QAction help
 * allo slot about()
 */
ToolBar::ToolBar(QWidget *p) :
    parent(p),
    file(new QMenu("File",this)),
    help(new QAction("About",this)),
    newArray(new QAction("New Window",file)),
    deleteArray(new QAction("Reset All",file)),
    loadFromXml(new QAction("Load",file)),
    saveToXml(new QAction("Save",file)),
    saveAsToXml(new QAction("Save As")){

    setFixedHeight(30);

    addMenu(file);
    addAction(help);

    file->addAction(newArray);
    file->addAction(deleteArray);
    file->addAction(loadFromXml);
    file->addAction(saveToXml);
    file->addAction(saveAsToXml);

    connect(help,SIGNAL(triggered()),this,SLOT(about()));
}

/**
 * @brief ToolBar::getFile
 * @return QMenu file
 */
QMenu *ToolBar::getFile() const{
    return file;
}

/**
 * @brief ToolBar::getHelp
 * @return QMenu help
 */
QAction *ToolBar::getHelp() const{
    return help;
}

/**
 * @brief ToolBar::getNewArray
 * @return QAction newArray
 */
QAction *ToolBar::getNewArray() const{
    return newArray;
}

/**
 * @brief ToolBar::getDeleteArray
 * @return QAction deleteArray
 */
QAction *ToolBar::getDeleteArray() const{
    return deleteArray;
}

/**
 * @brief ToolBar::getLoadFromXml
 * @return QAction loadFromXml
 */
QAction *ToolBar::getLoadFromXml() const{
    return loadFromXml;
}

/**
 * @brief ToolBar::getSaveToXml
 * @return QAction saveToXml
 */
QAction *ToolBar::getSaveToXml() const{
    return saveToXml;
}

/**
 * @brief ToolBar::getSaveAsToXml
 * @return QAction saveAsToXml
 */
QAction *ToolBar::getSaveAsToXml() const{
    return saveAsToXml;
}

/**
 * @brief ToolBar::about
 * Visualizza un messageBox
 */
void ToolBar::about() const{
    QMessageBox msgBox;
    msgBox.setWindowTitle("About");
    msgBox.setInformativeText("Utility creata da Riccardo Cestaro come progetto universitario");
    msgBox.setStandardButtons(QMessageBox::Close);
    msgBox.exec();
}
