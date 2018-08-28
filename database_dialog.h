#pragma once

#include <QDialog>
#include <QtWidgets>

class database_dialog : public QDialog
{
	Q_OBJECT;

	QVector<QString> ini_setting_data;

	QLabel *wiki_xml_database_label = nullptr;
	QLineEdit *wiki_xml_database_textedit = nullptr;
    QPushButton *wiki_xml_database_button = nullptr;
	QLabel *servant_icon_present_label = nullptr;
	QLineEdit *servant_icon_present_textedit = nullptr;
    QPushButton *servant_icon_present_button = nullptr;
    QLabel *event_item_label = nullptr;
    QLineEdit *event_item_textedit = nullptr;
    QPushButton *event_item_button = nullptr;
    QLabel *exchange_item_label = nullptr;
    QLineEdit *exchange_item_textedit = nullptr;
    QPushButton *exchange_item_button = nullptr;
    QLabel *event_figure_label = nullptr;
    QLineEdit *event_figure_textedit = nullptr;
    QPushButton *event_figure_button = nullptr;

	void database_textedit_update();

public:
	database_dialog(QWidget *parent);
	~database_dialog();

signals:
	void database_transout(QVector<QString> path_file);

private slots:
	void database_accepted_slot();
    void dir_button_clicked();
    void file_button_clicked();

public slots:
	void database_transin(QVector<QString> path_file);
};
