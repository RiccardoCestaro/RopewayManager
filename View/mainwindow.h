#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTabBar>
#include "Components/toolbar.h"
#include "Components/viewropeway.h"
#include "Components/insertropeway.h"

class Model; // definizioni incomplete
class TableView;
class QTableModelAdapter;
class QLineEdit;
class QFilterProxyModel;
class QCloseEvent;
class QComboBox;

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr, bool load=true, int offset=0);
    ~MainWindow() override = default;// NB: non distrugge i QWidget (di quello se ne occupa Qt)
    QSize sizeHint() const override;
protected:
    virtual void closeEvent (QCloseEvent *event) override;
private:
    int offset;
    ToolBar* toolbar;
    QTabBar* tabbar;
    InsertRopeway* insertPage;
    ViewRopeway* viewPage;

    QString fileName;

    static QStringList typeOfLift;



private slots:
    void showInsertPage() const;
    void showViewPage() const;

    void showPage(int) const;

    void newBeauty() const;
    void loadNewBeauty() const ;
    void saveData() ; //potrebbe modificare il WindowTitle perché chiama saveAsData
    void loadData();
    void saveAsData();
    void showMore() const;
    //void use();
    //void useResults() const;
    void add() const;
    void remove() const;
    void removeResults() const;
    void changedFilter() const;

};

#endif // MAINWINDOW_H
