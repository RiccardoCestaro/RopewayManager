#ifndef TOOLBAR_H
#define TOOLBAR_H
#include <QWidget>
#include <QMenuBar>

/**
 * @brief The ToolBar class
 *
 * Estende da QMenuBar,
 * ToolBar dell'utility
 */
class ToolBar : public QMenuBar{
private:
    Q_OBJECT
    QWidget* parent;

    QMenu* file;
    QAction* help;
    QAction* newArray;
    QAction* deleteArray;
    QAction* loadFromXml;
    QAction* saveToXml;
    QAction* saveAsToXml;

public:
    explicit ToolBar(QWidget* = nullptr);

    QMenu *getFile() const;
    QAction *getHelp() const;
    QAction *getNewArray() const;
    QAction *getDeleteArray() const;
    QAction *getLoadFromXml() const;
    QAction *getSaveToXml() const;
    QAction *getSaveAsToXml() const;

private slots:

    void about() const;

};

#endif // TOOLBAR_H
