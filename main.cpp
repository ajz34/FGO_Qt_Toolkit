#ifdef WIN32
// character in chinese can't display in visual studio
// if Qt environment, possibly you can delete this
// this line may be included in all header files
// https://blog.csdn.net/nabariou/article/details/60468627
#pragma execution_character_set("utf-8")  
#endif

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	// set translation
	const QString INI_SETTING_FILE_PATH = QString("fgo_helper_ajz_0_1");  // settings of database
	QSettings settings(QSettings::NativeFormat, QSettings::UserScope,
		INI_SETTING_FILE_PATH, INI_SETTING_FILE_PATH);
	QString lang = settings.value("Language", "").toString();

	qDebug() << lang;
	qDebug() << (lang == QString("jp"));

	QTranslator translator;
	if (lang == QString("jp"))
		translator.load("fgo_helper_ajz_0_1_ja");
	else if (lang == QString("zh_sc"))
		translator.load("fgo_helper_ajz_0_1_zh");
	else if (lang == QString("zh_tc"))
		translator.load("fgo_helper_ajz_0_1_tc");
	a.installTranslator(&translator);

    // set scroll line
    a.setWheelScrollLines(1);

	// MainWindow
    MainWindow w;
    w.show();

    return a.exec();
}
