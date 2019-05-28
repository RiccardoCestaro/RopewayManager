#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTabBar>
#include "Components/toolbar.h"
#include "Components/viewropeway.h"
#include "Components/insertropeway.h"
#include "Components/tabbar.h"

/**
 * @brief The MainWindow class
 *
 * View: vista padre dell'utility
 */
class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr, bool load=true, int offset=0);
protected:
    virtual void closeEvent (QCloseEvent *event) override;
private:

    int offset;
    ToolBar* toolbar;
    TabBar* tabbar;
    InsertRopeway* insertPage;
    ViewRopeway* viewPage;

    QString fileName;
    static QStringList typeOfLift;

    void showInsertPage() const;
    void showViewPage() const;

private slots:

    void showPage(int) const;
    void newManager() const;
    void deleteArray();
    void saveData();
    void loadData();
    void saveAsData();
    void showMore() const;
    void add() const;
    void remove() const;
    void removeResults() const;
    void changedFilter() const;

};

#endif // MAINWINDOW_H
