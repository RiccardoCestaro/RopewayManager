######################################################################
# Automatically generated by qmake (3.1)
######################################################################

TEMPLATE = app
TARGET = RopewayManager
INCLUDEPATH += .
QT += widgets
QMAKE_CXXFLAGS += -std=c++11

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += Model/Gerarchia/Utils/ammorsamento.h \
           Model/Gerarchia/Utils/gancio.h \
           Model/Gerarchia/Utils/produttore.h \
           Model/Gerarchia/Utils/tecbin.h \
           Model/Gerarchia/Utils/tipologia.h \
           Model/Gerarchia/Utils/ropewayutils.h \
           Model/Gerarchia/impianto.h \
           Model/Gerarchia/movimentazionecontinua.h \
           Model/Gerarchia/movimentazionevaevieni.h \
           Model/Gerarchia/cabinovia.h \
           Model/Gerarchia/seggiovia.h \
           Model/Gerarchia/telemix.h \
           Model/Gerarchia/sciovia.h \
           Model/Gerarchia/funivia.h \
           Model/Gerarchia/funicolare.h \
           Model/Gerarchia/funifor.h \
           Model/container.h \
           Model/deepptr.h \
           Model/io.h \
           Model/model.h \
           Model/modeladapter.h \
           Model/proxymodel.h \
           Model/invalidstringtoenumexception.h \
           View/Components/insertropeway.h \
           View/Components/tabbar.h \
           View/Components/tableheader.h \
           View/Components/toolbar.h \
           View/Components/viewropeway.h \
           View/Components/tableview.h \
           View/mainwindow.h \
           View/showallspec.h


SOURCES += Model/Gerarchia/Utils/ammorsamento.cpp \
           Model/Gerarchia/Utils/gancio.cpp \
           Model/Gerarchia/Utils/produttore.cpp \
           Model/Gerarchia/Utils/tecbin.cpp \
           Model/Gerarchia/Utils/tipologia.cpp \
           Model/Gerarchia/Utils/ropewayutils.cpp \
           Model/Gerarchia/impianto.cpp \
           Model/Gerarchia/movimentazionecontinua.cpp \
           Model/Gerarchia/movimentazionevaevieni.cpp \
           Model/Gerarchia/cabinovia.cpp \
           Model/Gerarchia/seggiovia.cpp \
           Model/Gerarchia/telemix.cpp \
           Model/Gerarchia/sciovia.cpp \
           Model/Gerarchia/funivia.cpp \
           Model/Gerarchia/funicolare.cpp \
           Model/Gerarchia/funifor.cpp \
           Model/io.cpp \
           Model/model.cpp \
           Model/modeladapter.cpp \
           Model/proxymodel.cpp \
           Model/invalidstringtoenumexception.cpp \
           View/Components/insertropeway.cpp \
           View/Components/tabbar.cpp \
           View/Components/tableheader.cpp \
           View/Components/toolbar.cpp \
           View/Components/viewropeway.cpp \
           View/Components/tableview.cpp \
           View/main.cpp \
           View/mainwindow.cpp \
           View/showallspec.cpp



RESOURCES += \
    resources.qrc
