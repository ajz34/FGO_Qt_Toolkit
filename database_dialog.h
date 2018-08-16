#pragma once

#include <QDialog>
#include <QtWidgets>

class database_dialog : public QDialog
{
	Q_OBJECT;

	QVector<QString> ini_setting_data;

	QLabel *wiki_xml_database_label;
	QLineEdit *wiki_xml_database_textedit;
	QLabel *servant_icon_present_label;
	QLineEdit *servant_icon_present_textedit;

	void database_textedit_update();

public:
	database_dialog(QWidget *parent);
	~database_dialog();

signals:
	void database_transout(QVector<QString> path_file);

private slots:
	inline void database_accepted_slot();

public slots:
	void database_transin(QVector<QString> path_file);
};
