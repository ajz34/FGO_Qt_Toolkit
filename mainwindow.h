#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

#include "qclickablefigurelabel.h"
#include "tab_widget_servant.h"
#include "database_dialog.h"
#include "treemodel.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT;

	//--- HAND MADE PARAMETERS
	const QString INI_SETTING_FILE_PATH = QString("fgo_helper_ajz_0_1");  // settings of database
	const QVector<QString> INI_SETTING_FILE_INDEX{
		"wiki_xml_path", "servant_icon_present",
	};

	//--- A. tab widgets
	QTabWidget *main_tabwidget;
	tab_widget_servant *tab_servant;

    //--- B. menu
    QAction *action_open;
	QAction *action_database;
	QVector<QString> ini_setting_data;
	void ini_setting_read();
	void ini_setting_write();
    QAction *action_exit;
    QAction *action_about;
    QAction *action_bibliography;
	QMenu *menu_file;
	QMenu *menu_about;
    void menu_create_action();
    void set_menu();

	//--- C. wiki database
	QVector<TreeModel*> wiki_database{};

    //--- N. layout
	QGridLayout *main_layout;
	QLabel *status_bar;
	void set_main_layout();

	//--- O. actions on data
	// setting
	database_dialog *database_confirm_dialog;
	// wiki xml data
	void initialize_wiki_database();

    // not classified

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
	//--- B. menu
	// database
	void action_database_transout(QVector<QString> path_pack);
	void action_database_to_tableview(QVector<QString> path_pack, QVector<TreeModel*> tree_model);

private slots:
	//--- B. menu
	// database
	void action_database_slot();
	void action_database_transin(QVector<QString> path_pack);

};

#endif // MAINWINDOW_H
