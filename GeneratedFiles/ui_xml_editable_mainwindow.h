/********************************************************************************
** Form generated from reading UI file 'xml_editable_mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XML_EDITABLE_MAINWINDOW_H
#define UI_XML_EDITABLE_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_xml_editable_mainwindow
{
public:
    QAction *exitAction;
    QAction *insertRowAction;
    QAction *removeRowAction;
    QAction *insertColumnAction;
    QAction *removeColumnAction;
    QAction *insertChildAction;
    QAction *saveAction;
    QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    QTreeView *view;
    QMenuBar *menubar;
    QMenu *fileMenu;
    QMenu *actionsMenu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *xml_editable_mainwindow)
    {
        if (xml_editable_mainwindow->objectName().isEmpty())
            xml_editable_mainwindow->setObjectName(QStringLiteral("xml_editable_mainwindow"));
        xml_editable_mainwindow->resize(573, 468);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(xml_editable_mainwindow->sizePolicy().hasHeightForWidth());
        xml_editable_mainwindow->setSizePolicy(sizePolicy);
        exitAction = new QAction(xml_editable_mainwindow);
        exitAction->setObjectName(QStringLiteral("exitAction"));
        insertRowAction = new QAction(xml_editable_mainwindow);
        insertRowAction->setObjectName(QStringLiteral("insertRowAction"));
        removeRowAction = new QAction(xml_editable_mainwindow);
        removeRowAction->setObjectName(QStringLiteral("removeRowAction"));
        insertColumnAction = new QAction(xml_editable_mainwindow);
        insertColumnAction->setObjectName(QStringLiteral("insertColumnAction"));
        removeColumnAction = new QAction(xml_editable_mainwindow);
        removeColumnAction->setObjectName(QStringLiteral("removeColumnAction"));
        insertChildAction = new QAction(xml_editable_mainwindow);
        insertChildAction->setObjectName(QStringLiteral("insertChildAction"));
        saveAction = new QAction(xml_editable_mainwindow);
        saveAction->setObjectName(QStringLiteral("saveAction"));
        centralwidget = new QWidget(xml_editable_mainwindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        vboxLayout = new QVBoxLayout(centralwidget);
        vboxLayout->setSpacing(0);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        view = new QTreeView(centralwidget);
        view->setObjectName(QStringLiteral("view"));
        view->setAlternatingRowColors(true);
        view->setSelectionBehavior(QAbstractItemView::SelectItems);
        view->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        view->setAnimated(false);
        view->setAllColumnsShowFocus(true);

        vboxLayout->addWidget(view);

        xml_editable_mainwindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(xml_editable_mainwindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 573, 26));
        fileMenu = new QMenu(menubar);
        fileMenu->setObjectName(QStringLiteral("fileMenu"));
        actionsMenu = new QMenu(menubar);
        actionsMenu->setObjectName(QStringLiteral("actionsMenu"));
        xml_editable_mainwindow->setMenuBar(menubar);
        statusbar = new QStatusBar(xml_editable_mainwindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        xml_editable_mainwindow->setStatusBar(statusbar);

        menubar->addAction(fileMenu->menuAction());
        menubar->addAction(actionsMenu->menuAction());
        fileMenu->addAction(saveAction);
        fileMenu->addAction(exitAction);
        actionsMenu->addAction(insertRowAction);
        actionsMenu->addAction(removeRowAction);
        actionsMenu->addSeparator();
        actionsMenu->addAction(insertChildAction);

        retranslateUi(xml_editable_mainwindow);

        QMetaObject::connectSlotsByName(xml_editable_mainwindow);
    } // setupUi

    void retranslateUi(QMainWindow *xml_editable_mainwindow)
    {
        xml_editable_mainwindow->setWindowTitle(QApplication::translate("xml_editable_mainwindow", "Editable Tree Model", nullptr));
        exitAction->setText(QApplication::translate("xml_editable_mainwindow", "E&xit", nullptr));
#ifndef QT_NO_SHORTCUT
        exitAction->setShortcut(QApplication::translate("xml_editable_mainwindow", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
        insertRowAction->setText(QApplication::translate("xml_editable_mainwindow", "Insert Row", nullptr));
#ifndef QT_NO_SHORTCUT
        insertRowAction->setShortcut(QApplication::translate("xml_editable_mainwindow", "Ctrl+I, R", nullptr));
#endif // QT_NO_SHORTCUT
        removeRowAction->setText(QApplication::translate("xml_editable_mainwindow", "Remove Row", nullptr));
#ifndef QT_NO_SHORTCUT
        removeRowAction->setShortcut(QApplication::translate("xml_editable_mainwindow", "Ctrl+R, R", nullptr));
#endif // QT_NO_SHORTCUT
        insertColumnAction->setText(QApplication::translate("xml_editable_mainwindow", "Insert Column", nullptr));
#ifndef QT_NO_SHORTCUT
        insertColumnAction->setShortcut(QApplication::translate("xml_editable_mainwindow", "Ctrl+I, C", nullptr));
#endif // QT_NO_SHORTCUT
        removeColumnAction->setText(QApplication::translate("xml_editable_mainwindow", "Remove Column", nullptr));
#ifndef QT_NO_SHORTCUT
        removeColumnAction->setShortcut(QApplication::translate("xml_editable_mainwindow", "Ctrl+R, C", nullptr));
#endif // QT_NO_SHORTCUT
        insertChildAction->setText(QApplication::translate("xml_editable_mainwindow", "Insert Child", nullptr));
#ifndef QT_NO_SHORTCUT
        insertChildAction->setShortcut(QApplication::translate("xml_editable_mainwindow", "Ctrl+N", nullptr));
#endif // QT_NO_SHORTCUT
        saveAction->setText(QApplication::translate("xml_editable_mainwindow", "Save", nullptr));
#ifndef QT_NO_SHORTCUT
        saveAction->setShortcut(QApplication::translate("xml_editable_mainwindow", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        fileMenu->setTitle(QApplication::translate("xml_editable_mainwindow", "&File", nullptr));
        actionsMenu->setTitle(QApplication::translate("xml_editable_mainwindow", "&Actions", nullptr));
    } // retranslateUi

};

namespace Ui {
    class xml_editable_mainwindow: public Ui_xml_editable_mainwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XML_EDITABLE_MAINWINDOW_H
