#ifndef QLISTMODELADAPTER_H
#define QLISTMODELADAPTER_H

#include <QAbstractTableModel>
#include <vector>
class BeautyItem;
class InsertRopeway;
class QRegExp;
class Model;
class ShowAllSpec;

class QTableModelAdapter: public QAbstractTableModel {
private:
    Model* model;
    const InsertRopeway* insert;
public:
    QTableModelAdapter(QObject* = nullptr, const InsertRopeway* = nullptr);
    ~QTableModelAdapter() override;
    int rowCount(const QModelIndex& = QModelIndex()) const override;
    int columnCount(const QModelIndex& = QModelIndex()) const override;
    QVariant headerData(int, Qt::Orientation, int) const override;
    QVariant data(const QModelIndex&, int = Qt::DisplayRole) const override;

    bool insertRows(int, int = 1, const QModelIndex& = QModelIndex()) override;
    bool removeRows(int, int = 1, const QModelIndex& = QModelIndex()) override;
    void showMore(const QModelIndex&);
    void saveToFile(const std::string&) const;
    void loadFromFile(const std::string &) const;
    const InsertRopeway* getInsertWidget() const;

    void removeResults(const std::vector<unsigned int> &);
    bool match(unsigned int,const QRegExp&) const;
};

#endif // QLISTMODELADAPTER_H
