#ifdef WIN32
// character in chinese can't display in visual studio
// if Qt environment, possibly you can delete this
// this line may be included in all header files
// https://blog.csdn.net/nabariou/article/details/60468627
#pragma execution_character_set("utf-8")  
#endif

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

#include "qclickablefigurelabel.h"
#include "tab_widget_servant.h"
#include "tab_widget_item.h"
#include "database_dialog.h"
#include "treemodel.h"
#include "xml_editable_mainwindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT;

private:
    // these variables should be accessible to its child widgets (not child classes)
    // however, I just know using signal-slot to trans them

    //--- HAND MADE PARAMETERS
    const int SERVANT_ICON_NUMBER = 500;
    const QString INI_SETTING_FILE_PATH = QString("fgo_helper_ajz_0_1");
    const QVector<QString> INI_SETTING_FILE_INDEX{
        "wiki_xml_path",
        "servant_icon_present",
        "cur_user_file_path",
        "event_item",
        "exchange_item",
        "event_figure",
    };

    //--- frequently used data
    QVector<QString> ini_setting_data{};
    QVector<TreeModel*> wiki_database = QVector<TreeModel*>(SERVANT_ICON_NUMBER, nullptr);
    TreeModel *user_data = nullptr;
    QVector<QPixmap> *servant_icon_button_image = nullptr;
    TreeModel *event_item = nullptr;
    TreeModel *exchange_item = nullptr;
    QHash<QString, QPixmap> *event_figure = nullptr;

private:

	//--- A. tab widgets
	QTabWidget *main_tabwidget = nullptr;
	tab_widget_servant *tab_servant = nullptr;
    tab_widget_item *tab_item = nullptr;

    //--- B. menu
    QAction *action_open = nullptr;
	QAction *action_new = nullptr;
	QAction *action_save = nullptr;
	QAction *action_save_as = nullptr;
	QAction *action_database = nullptr;
	void ini_setting_read();
	void ini_setting_write();
    QAction *action_exit = nullptr;
	QAction *action_japanese = nullptr;
	QAction *action_chinese = nullptr;
	QAction *action_traditional = nullptr;
	QAction *action_english = nullptr;
    QAction *action_about = nullptr;
    QAction *action_bibliography = nullptr;
	QMenu *menu_file = nullptr;
	QMenu *menu_about = nullptr;
    void menu_create_action();
    void set_menu();

    //--- N. layout
	QGridLayout *main_layout = nullptr;
	QLabel *status_bar = nullptr;
	void set_main_layout();

	//--- O. actions on data
	// setting
	database_dialog *database_confirm_dialog = nullptr;
	// wiki xml data
	void set_central_connection();
	void initialize_database();

	//--- P. action on user file
	QString cur_user_file_path;
	bool ok_to_continue();
	bool save();
	bool save_file(const QString &file_name);
	bool save_as();
	void open();
	bool load_file(const QString &file_name);
	void new_file();
	void set_cur_user_file_path(const QString &file_name);
	
protected:
	void closeEvent(QCloseEvent *event);

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
	//--- B. menu
	// database
	void action_database_transout(QVector<QString> path_pack);
	void signal_database_changed(
		QVector<QString> path_pack,
		QVector<TreeModel*> tree_model,
		TreeModel *user_dat,
        QVector<QPixmap> *serv_img);

	// file
	void signal_user_data_loaded(TreeModel *user_dat);

private slots:
	//--- B. menu
	// database
	void action_database_slot();
	void action_database_close();
	void action_japanese_slot();
	void action_chinese_slot();
	void action_traditional_slot();
	void action_english_slot();
	void action_database_transin(QVector<QString> path_pack);
    void from_tab_user_data_changed(TreeModel *user_dat);

};

#endif // MAINWINDOW_H
