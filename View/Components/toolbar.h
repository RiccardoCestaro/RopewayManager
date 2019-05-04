#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QMenuBar>

/*
 *  ToolBar sottoclasse di QMenuBar
 *
 *  Contiene le azioni generali per la gestione dello spostamento tra viste
 *  e la gestione del caricamento/salvataggio su XML
 *
 */

class ToolBar : public QMenuBar{
private:
    Q_OBJECT
    QWidget* parent;

    QMenu* file;
    QMenu* help;

    QAction* newArray;
    QAction* deleteArray;
    QAction* loadFromXml;
    QAction* saveToXml;

public:
    explicit ToolBar(QWidget* = nullptr);

    QMenu *getFile() const;
    QMenu *getHelp() const;
    QAction *getNewArray() const;
    QAction *getDeleteArray() const;
    QAction *getLoadFromXml() const;
    QAction *getSaveToXml() const;

signals:

public slots:
};

#endif // TOOLBAR_H
