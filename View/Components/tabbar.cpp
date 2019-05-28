#include "tabbar.h"

/**
 * @brief TabBar::TabBar
 * @param p
 *
 * Costruttore di TabBar,
 * imposta la grafica
 */
TabBar::TabBar(QWidget* p) : parent(p){
    addTab("Visualizza");
    addTab("Inserisci");
    setCurrentIndex(0);
}
