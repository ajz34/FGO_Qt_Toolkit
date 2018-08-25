#include "database_dialog.h"

database_dialog::database_dialog(QWidget *parent)
	: QDialog(parent)
{
	ini_setting_data = QVector<QString>{};

	wiki_xml_database_label = new QLabel;
	wiki_xml_database_label->setText(tr("fate.wiki XML Database:"));
	wiki_xml_database_textedit = new QLineEdit;
    wiki_xml_database_button = new QPushButton;
    wiki_xml_database_button->setText(tr("Dir"));
    connect(wiki_xml_database_button, &QPushButton::clicked, this, &database_dialog::button_clicked);

	servant_icon_present_label = new QLabel;
	servant_icon_present_label->setText(tr("Servant icon for presentation:"));
	servant_icon_present_textedit = new QLineEdit;
    servant_icon_present_button = new QPushButton;
    servant_icon_present_button->setText(tr("Dir"));
    connect(servant_icon_present_button, &QPushButton::clicked, this, &database_dialog::button_clicked);

	QDialogButtonBox *dialog_box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(wiki_xml_database_label, 0, 0);
	layout->addWidget(wiki_xml_database_textedit, 0, 1);
    layout->addWidget(wiki_xml_database_button, 0, 2);
	layout->addWidget(servant_icon_present_label, 1, 0);
	layout->addWidget(servant_icon_present_textedit, 1, 1);
    layout->addWidget(servant_icon_present_button, 1, 2);
	layout->addWidget(dialog_box, 2, 1, 1, 2);

	setLayout(layout);
	setFixedHeight(layout->sizeHint().height());

	connect(dialog_box, &QDialogButtonBox::accepted, this, &database_dialog::database_accepted_slot);
	connect(dialog_box, &QDialogButtonBox::rejected, this, &database_dialog::close);
}

database_dialog::~database_dialog()
{
}

void database_dialog::database_accepted_slot() {
	ini_setting_data[0] = wiki_xml_database_textedit->text();
	ini_setting_data[1] = servant_icon_present_textedit->text();
	emit database_transout(ini_setting_data);
	this->close();
}

void database_dialog::database_transin(QVector<QString> path_file)
{
	ini_setting_data = path_file;
	database_textedit_update();
}

void database_dialog::database_textedit_update()
{
	wiki_xml_database_textedit->setText(ini_setting_data[0]);
	servant_icon_present_textedit->setText(ini_setting_data[1]);
}

void database_dialog::button_clicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString show_string, return_string, guess_string;
    if (button == wiki_xml_database_button)
    {
        guess_string = wiki_xml_database_label->text();
        show_string = tr("Wiki Database Path...");
    }
    else if (button == servant_icon_present_button)
    {
        guess_string = wiki_xml_database_label->text();
        show_string = tr("Servant Icon Path... (show on tab table)");
    }

    return_string = QFileDialog::getExistingDirectory(this, show_string, ".", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!return_string.isEmpty())
    {
        if (button == wiki_xml_database_button) wiki_xml_database_textedit->setText(return_string);
        else if (button == servant_icon_present_button) servant_icon_present_textedit->setText(return_string);
    }
}
