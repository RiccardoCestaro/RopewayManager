#ifndef TABLEHEADER_H
#define TABLEHEADER_H

#include <QHeaderView>

/**
 * @brief The TableHeader class
 *
 * Estende da QHeaderView
 */
class TableHeader : public QHeaderView{
public:
    TableHeader(QWidget* = nullptr);
};

#endif // TABLEHEADER_H
