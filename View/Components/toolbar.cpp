#include "toolbar.h"


ToolBar::ToolBar(QWidget *p) :
    parent(p),
    file(new QMenu("File",this)),
    help(new QMenu("Help",this)),
    newArray(new QAction("New XML",file)),
    deleteArray(new QAction("Delete XML",file)),
    loadFromXml(new QAction("Load XML",file)),
    saveToXml(new QAction("Save XML",file)){

    addMenu(file);
    addMenu(help);

    file->addAction(newArray);
    file->addAction(loadFromXml);
    file->addAction(saveToXml);
}

QMenu *ToolBar::getFile() const{
    return file;
}

QMenu *ToolBar::getHelp() const{
    return help;
}

QAction *ToolBar::getNewArray() const{
    return newArray;
}

QAction *ToolBar::getDeleteArray() const{
    return deleteArray;
}

QAction *ToolBar::getLoadFromXml() const{
    return loadFromXml;
}

QAction *ToolBar::getSaveToXml() const{
    return saveToXml;
}
