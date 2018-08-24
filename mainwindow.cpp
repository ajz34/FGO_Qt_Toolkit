#include "mainwindow.h"
#include "global_var.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	// Qt + Visual Studio: https://stackoverflow.com/questions/28813526/qt-5-4-with-visual-studio-2013-qtcored-dll-missing
	// set path: %QTDIR%\bin;%PATH%; 

	GLOB::MAP_INIT();

	//--- B. menu
	menu_create_action();
	set_menu();

	//--- N. layout
	set_main_layout();

	//--- O. actions on data
	set_connection_tab_widgets();
	ini_setting_read();

}

MainWindow::~MainWindow()
{
	ini_setting_write();
}

//--- B. menu

void MainWindow::set_menu()
{
    menu_file = menuBar()->addMenu(tr("&File"));
    menu_file->addAction(action_new);
	menu_file->addAction(action_open);
	menu_file->addAction(action_save);
	menu_file->addAction(action_save_as);
	menu_file->addSeparator();
	menu_file->addAction(action_database);
	menu_file->addSeparator();
    menu_file->addAction(action_exit);

	menu_file = menuBar()->addMenu(tr("&Language"));
	auto action_language = new QActionGroup(this);
	action_language->addAction(action_japanese);
	action_language->addAction(action_chinese);
	action_language->addAction(action_traditional);
	action_language->addAction(action_english);
	menu_file->addAction(action_japanese);
	menu_file->addAction(action_chinese);
	menu_file->addAction(action_traditional);
	menu_file->addAction(action_english);
	QSettings settings(QSettings::NativeFormat, QSettings::UserScope,
		INI_SETTING_FILE_PATH, INI_SETTING_FILE_PATH);
	QString lang = settings.value("Language", "").toString();
	if (lang == QString("jp"))
		action_japanese->setChecked(true);
	else if (lang == QString("zh_sc"))
		action_chinese->setChecked(true);
	else if (lang == QString("zh_tc"))
		action_traditional->setChecked(true);
	else
		action_english->setChecked(true);

    menu_about = menuBar()->addMenu(tr("&About"));
	menu_about->addAction(action_about);
	menu_about->addAction(action_bibliography);
}

void MainWindow::menu_create_action()
{
	// new file
	action_new = new QAction(tr("&New"), this);
	action_new->setStatusTip(tr("Create a servant skill level document"));
	connect(action_new, &QAction::triggered, this, &MainWindow::new_file);

    // open file
    action_open = new QAction(tr("&Open"), this);
    action_open->setStatusTip(tr("Open your servant skill level document"));
	connect(action_open, &QAction::triggered, this, &MainWindow::open);

	// save file
	action_save = new QAction(tr("&Save"), this);
	action_save->setStatusTip(tr("Save your servant skill level document"));
	connect(action_save, &QAction::triggered, this, &MainWindow::save);

	// save as
	action_save_as = new QAction(tr("Sa&ve as"), this);
	action_save_as->setStatusTip(tr("Save your servant skill level document to a new file"));
    connect(action_save_as, &QAction::triggered, this, &MainWindow::save_as);

	// specify database
	action_database = new QAction(tr("&Database"), this);
	action_database->setStatusTip(tr("Specify master insensitive servant databases"));
	connect(action_database, &QAction::triggered, this, &MainWindow::action_database_slot);

	// language
	action_japanese = new QAction("日本語");
	action_chinese = new QAction("简体中文");
	action_traditional = new QAction("繁體中文");
	action_english = new QAction("English");
	action_japanese->setCheckable(true);
	action_chinese->setCheckable(true);
	action_traditional->setCheckable(true);
	action_english->setCheckable(true);
	connect(action_japanese, &QAction::triggered, this, &MainWindow::action_japanese_slot);
	connect(action_chinese, &QAction::triggered, this, &MainWindow::action_chinese_slot);
	connect(action_traditional, &QAction::triggered, this, &MainWindow::action_traditional_slot);
	connect(action_english, &QAction::triggered, this, &MainWindow::action_english_slot);

    // exit
    action_exit = new QAction(tr("&Exit"), this);
    action_exit->setStatusTip(tr("Exit program"));
    connect(action_exit, &QAction::triggered, this, &QMainWindow::close);

    // about
    action_about = new QAction(tr("About &Program"), this);
    action_about->setStatusTip(tr("About this program"));

    // bibliography
    action_bibliography = new QAction(tr("&Bibliography"), this);
	action_bibliography->setStatusTip(tr("Bibliography, reference and acknowledge"));
}

void MainWindow::action_japanese_slot()
{
	QSettings settings(QSettings::NativeFormat, QSettings::UserScope,
		INI_SETTING_FILE_PATH, INI_SETTING_FILE_PATH);
	settings.setValue("Language", "jp");
	QMessageBox::warning(this,
		"FGO Qt Toolkit",
		"言語設定を適用するには、アプリケーションを再起動してください。",
		QMessageBox::Ok
	);
}

void MainWindow::action_chinese_slot()
{
	QSettings settings(QSettings::NativeFormat, QSettings::UserScope,
		INI_SETTING_FILE_PATH, INI_SETTING_FILE_PATH);
	settings.setValue("Language", "zh_sc");
	QMessageBox::warning(this,
		"FGO Qt Toolkit",
		"请重新启动应用程序以应用语言设置。",
		QMessageBox::Ok
	);
}

void MainWindow::action_traditional_slot()
{
	QSettings settings(QSettings::NativeFormat, QSettings::UserScope,
		INI_SETTING_FILE_PATH, INI_SETTING_FILE_PATH);
	settings.setValue("Language", "zh_tc");
	QMessageBox::warning(this,
		"FGO Qt Toolkit",
		"請重新啟動應用程式以應用語言設置。",
		QMessageBox::Ok
	);
}

void MainWindow::action_english_slot()
{
	QSettings settings(QSettings::NativeFormat, QSettings::UserScope,
		INI_SETTING_FILE_PATH, INI_SETTING_FILE_PATH);
	settings.setValue("Language", "en");
	QMessageBox::warning(this,
		"FGO Qt Toolkit",
		"Please restart application in order to apply language setting.",
		QMessageBox::Ok
	);
}

void MainWindow::action_database_slot()
{
	// https://stackoverflow.com/questions/20491864/how-close-and-delete-a-modeless-qt-dialog
    // database_confirm_dialog->setAttribute(Qt::WA_DeleteOnClose);
	if (database_confirm_dialog) delete database_confirm_dialog;
	database_confirm_dialog = new database_dialog(this);
	connect(this, &MainWindow::action_database_transout, database_confirm_dialog, &database_dialog::database_transin);
	connect(database_confirm_dialog, &database_dialog::database_transout, this, &MainWindow::action_database_transin);
	connect(database_confirm_dialog, &database_dialog::close, this, &MainWindow::action_database_close);
	emit action_database_transout(ini_setting_data);
	database_confirm_dialog->show();
}

void MainWindow::ini_setting_read()
{
	// read setting
	ini_setting_data = QVector<QString>{};
	QSettings settings(QSettings::NativeFormat, QSettings::UserScope,
		INI_SETTING_FILE_PATH, INI_SETTING_FILE_PATH);
	for (int i = 0; i < INI_SETTING_FILE_INDEX.size(); i++)
	{
		ini_setting_data.push_back(settings.value(INI_SETTING_FILE_INDEX[i], "").toString());
	}
	// apply setting
	load_file(ini_setting_data[2]);
	initialize_database();
}

void MainWindow::ini_setting_write()
{
	QSettings settings(QSettings::NativeFormat, QSettings::UserScope,
		INI_SETTING_FILE_PATH, INI_SETTING_FILE_PATH);
	for (int i = 0; i < INI_SETTING_FILE_INDEX.size(); i++)
	{
		qDebug() << "Working" << ini_setting_data[i];
		settings.setValue(INI_SETTING_FILE_INDEX[i], ini_setting_data[i]);
	}
}

void MainWindow::action_database_transin(QVector<QString> path_pack)
{
	ini_setting_data = path_pack;
	ini_setting_write();
	initialize_database();
}

void MainWindow::action_database_close()
{
	if (database_confirm_dialog) delete database_confirm_dialog;
	database_confirm_dialog = nullptr;
}

//--- N. layout

void MainWindow::set_main_layout()
{
	status_bar = new QLabel;
	statusBar()->addWidget(status_bar);

	main_tabwidget = new QTabWidget;
	tab_servant = new tab_widget_servant(this);
	main_tabwidget->addTab(tab_servant, tr("Servant"));

	main_layout = new QGridLayout;
	main_layout->addWidget(main_tabwidget);

	auto central = new QWidget;
	central->setLayout(main_layout);
	setCentralWidget(central);
}

//--- O. actions on data

void MainWindow::set_connection_tab_widgets()
{
	// connection of database update
	connect(this, &MainWindow::action_database_to_tableview, tab_servant, &tab_widget_servant::receive_wiki_xml_database);

	// connection to tableview when file changes
	connect(this, &MainWindow::action_load_file_to_tableview, tab_servant, &tab_widget_servant::receive_user_data_changes);
}

void MainWindow::initialize_database()
{
	// clear
	wiki_database.clear();
	wiki_database = QVector<TreeModel*>(SERVANT_ICON_NUMBER, nullptr);
	QDir wiki_xml_folder_dir(ini_setting_data[0]);
	QStringList headers{};
	headers << tr("Name") << tr("Value");
	QStringList file_list{};
	foreach(QFileInfo file_info, wiki_xml_folder_dir.entryInfoList(QDir::Files))
	{
		if (file_info.suffix() == "xml") file_list << file_info.filePath();
	}
	foreach(QString xml_file, file_list)
	{
		QFile file(xml_file);
		if (!file.open(QFile::ReadOnly | QFile::Text)) continue;
		QXmlStreamReader xml;
		xml.setDevice(&file);
		TreeModel *model = new TreeModel(headers, xml);
		file.close();
		QModelIndex index_basic = model->item_find("basic", model->index(0, 0));
		QModelIndex index_id = model->item_find("id", index_basic);
		if (index_id.isValid())
			wiki_database[model->data(index_id.siblingAtColumn(1), Qt::DisplayRole).toInt()] = model;
	}
	emit action_database_to_tableview(ini_setting_data, wiki_database, user_data);
}

//--- P. action on user file

void MainWindow::closeEvent(QCloseEvent *event)
{
	if (ok_to_continue())
		event->accept();
	else 
		event->ignore();
}

bool MainWindow::ok_to_continue()
{
    if (isWindowModified())
	{
		int r = QMessageBox::warning(this, tr("FGO Qt Toolkit"),
			tr("The user data has been modified.\n"
				"Do you want to save your changes?"),
			QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		if (r == QMessageBox::Yes)
			return save();
		else if (r == QMessageBox::Cancel)
			return false;
	}
	return true;
}

bool MainWindow::save()
{
	if (cur_user_file_path.isEmpty())
		return save_as();
	else
		return save_file(cur_user_file_path);
}

bool MainWindow::save_as()
{
	QString file_name = QFileDialog::getSaveFileName(this,
		tr("Save as"), ".", tr("User Data (*.xml)"));
	if (file_name.isEmpty())
		return false;
	return save_file(file_name);
}

bool MainWindow::save_file(const QString &file_name)
{
	QFile file(file_name);
	file.open(QIODevice::WriteOnly | QFile::Text);
	QXmlStreamWriter xml;
	xml.setDevice(&file);
	xml.setAutoFormatting(true);
	xml.writeStartDocument();
	user_data->xml_write(xml);
	xml.writeEndDocument();
	if (xml.hasError())
	{
		statusBar()->showMessage("Save Error!", 3000);
		return false;
	}
	else
	{
		statusBar()->showMessage("File Saved", 3000);
		set_cur_user_file_path(file_name);
		return true;
	}
}

void MainWindow::open()
{
	if (ok_to_continue())
	{
		QString file_name = QFileDialog::getOpenFileName(this,
			tr("Open file"), ".", tr("User Data (*.xml)"));
		if (!file_name.isEmpty())
			load_file(file_name);
	}
}

bool MainWindow::load_file(const QString &file_name)
{
	QStringList headers;
	headers << tr("Name") << tr("Value");

	QString file_open(file_name);
	if (file_name.isEmpty())
		file_open = ":/misc_file/misc_file/empty_user_data.xml";
	QFile file(file_open);
	file.open(QFile::ReadOnly | QFile::Text);
	QXmlStreamReader xml;
	xml.setDevice(&file);
	if (user_data) delete user_data;
	user_data = new TreeModel(headers, xml);
    connect(user_data, &TreeModel::modified, this, &MainWindow::setWindowModified);
	file.close();
	if (xml.hasError())
	{
		statusBar()->showMessage("Load Error!", 3000);
		load_file("");
		return false;
	}
	else if (file_name.isEmpty())
	{
		statusBar()->showMessage("Empty File Loaded", 3000);
		set_cur_user_file_path(file_name);
		return true;
	}
	else
	{
		statusBar()->showMessage("File Loaded", 3000);
		set_cur_user_file_path(file_name);
		return true;
	}
}

void MainWindow::new_file()
{
	if (ok_to_continue())
		load_file("");
}

void MainWindow::set_cur_user_file_path(const QString &file_name)
{
	cur_user_file_path = file_name;
	ini_setting_data[2] = cur_user_file_path;
	user_data->setModified(false);
	setWindowModified(false);
	QString show_name = tr("Untitled");
	if (!cur_user_file_path.isEmpty())
	{
		show_name = QFileInfo(cur_user_file_path).fileName();
	}
	setWindowTitle(tr("%1[*] - %2").arg(show_name).arg(tr("FGO Qt Toolkit")));
	emit action_load_file_to_tableview(user_data);
}
