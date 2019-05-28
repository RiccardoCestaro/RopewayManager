#ifndef TABBAR_H
#define TABBAR_H

#include <QTabBar>

/**
 * @brief The TabBar class
 *
 * Estende da QTabBar,
 * TabBar dell'utility
 */
class TabBar : public QTabBar{
private:
    QWidget* parent;
public:
    TabBar(QWidget* = nullptr);
};

#endif // TABBAR_H
