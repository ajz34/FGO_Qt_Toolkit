#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

#include "qclickablefigurelabel.h"
#include "tab_widget_servant.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT;

	//--- A. tab widgets
	QTabWidget *main_tabwidget;
	tab_widget_servant *tab_servant;

    //--- M. menu
    QAction *action_open;
    QAction *action_exit;
    QAction *action_about;
    QAction *action_bibliography;
	QMenu *menu_file;
	QMenu *menu_about;
    void menu_create_action();
    void set_menu();

    //--- N. layout
	QGridLayout *main_layout;
	QLabel *status_bar;
	void set_main_layout();
	// status bar
	// servant class label

    // not classified

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

};

#endif // MAINWINDOW_H
