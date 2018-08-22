#-------------------------------------------------
#
# Project created by QtCreator 2018-08-14T09:59:33
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = FGO_Helper_ajz_0_1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    qclickablefigurelabel.cpp \
    qrightclickpushbutton.cpp \
    resource_consume_connection.cpp \
    resource_consume_layout.cpp \
    tab_widget_servant_connection.cpp \
    tab_widget_servant_list.cpp \
    treeitem.cpp \
    treemodel.cpp \
    xml_editable_mainwindow.cpp \
    database_dialog.cpp \
    global_var.cpp

HEADERS += \
    mainwindow.h \
    qclickablefigurelabel.h \
    qrightclickpushbutton.h \
    resource_consume.h \
    tab_widget_servant.h \
    treeitem.h \
    treemodel.h \
    xml_editable_mainwindow.h \
    database_dialog.h \
    global_var.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    xml_editable_mainwindow.ui

RESOURCES += \
    widget_images.qrc

DISTFILES +=
