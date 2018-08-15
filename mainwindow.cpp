#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	// Qt + Visual Studio: https://stackoverflow.com/questions/28813526/qt-5-4-with-visual-studio-2013-qtcored-dll-missing
	
	//--- B. menu
	menu_create_action();
	set_menu();

	//--- N. layout
	set_main_layout();

	//--- O. actions on data
	ini_setting_read();
	update_wiki_database();

}

MainWindow::~MainWindow()
{
	ini_setting_write();
}

//--- B. menu

void MainWindow::set_menu()
{
    menu_file = menuBar()->addMenu(tr("&File"));
    menu_file->addAction(action_open);
	menu_file->addAction(action_database);
	menu_file->addSeparator();
    menu_file->addAction(action_exit);

    menu_about = menuBar()->addMenu(tr("&About"));
	menu_about->addAction(action_about);
	menu_about->addAction(action_bibliography);


}

void MainWindow::menu_create_action()
{
    // open file
    action_open = new QAction(tr("&Open"), this);
    action_open->setStatusTip(tr("Open servant skill level document"));

	// specify database
	action_database = new QAction(tr("&Database"), this);
	action_database->setStatusTip(tr("Specify master insensitive servant databases"));

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

//
void MainWindow::initialize_wiki_database()
{

}

//
void MainWindow::update_wiki_database()
{

}

//
void MainWindow::ini_setting_read()
{
	QSettings settings(INI_SETTING_FILE_PATH, QSettings::NativeFormat);
	wiki_xml_path = settings.value("wiki_xml_path", "").toString();
}

//
void MainWindow::ini_setting_write()
{
	QSettings settings(INI_SETTING_FILE_PATH, QSettings::NativeFormat);
	settings.setValue("wiki_xml_path", wiki_xml_path);
}

