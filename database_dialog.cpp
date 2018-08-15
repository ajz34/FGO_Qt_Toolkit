#include "database_dialog.h"

database_dialog::database_dialog(QWidget *parent)
	: QDialog(parent)
{
	ini_setting_data = QVector<QString>{};

	wiki_xml_database_label = new QLabel;
	wiki_xml_database_label->setText(tr("fate.wiki XML Database:"));
	wiki_xml_database_textedit = new QLineEdit;

	QDialogButtonBox *dialog_box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(wiki_xml_database_label, 0, 0);
	layout->addWidget(wiki_xml_database_textedit, 0, 1);
	layout->addWidget(dialog_box, 1, 1);

	setLayout(layout);
	setFixedHeight(layout->sizeHint().height());

	connect(dialog_box, &QDialogButtonBox::accepted, this, &database_dialog::database_accepted_slot);
	connect(dialog_box, &QDialogButtonBox::rejected, this, &database_dialog::close);
}

database_dialog::~database_dialog()
{
}

void database_dialog::database_textedit_update()
{
	wiki_xml_database_textedit->setText(ini_setting_data[0]);
}

void database_dialog::database_accepted_slot() {
	ini_setting_data[0] = wiki_xml_database_textedit->text();
	emit database_transout(ini_setting_data);
	this->close();
}

void database_dialog::database_transin(QVector<QString> path_file)
{
	ini_setting_data = path_file;
	database_textedit_update();
}
