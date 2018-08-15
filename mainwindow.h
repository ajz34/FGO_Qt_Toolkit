#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

#include "qclickablefigurelabel.h"
#include "tab_widget_servant.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT;

	//--- HAND MADE PARAMETERS
	const QString INI_SETTING_FILE_PATH = QString("fgo_helper_ajz_0_1");  // settings of database

	//--- A. tab widgets
	QTabWidget *main_tabwidget;
	tab_widget_servant *tab_servant;

    //--- B. menu
    QAction *action_open;
	QAction *action_database;
    QAction *action_exit;
    QAction *action_about;
    QAction *action_bibliography;
	QMenu *menu_file;
	QMenu *menu_about;
    void menu_create_action();
    void set_menu();

	//--- C. wiki database
	QAbstractItemModel *wiki_database;

    //--- N. layout
	QGridLayout *main_layout;
	QLabel *status_bar;
	void set_main_layout();

	//--- O. actions on data
	// setting
	QString wiki_xml_path;
	void ini_setting_read();
	void ini_setting_write();
	// wiki xml data
	void initialize_wiki_database();
	void update_wiki_database();

    // not classified

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

};

#endif // MAINWINDOW_H
