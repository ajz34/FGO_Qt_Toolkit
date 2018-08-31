#include "database_dialog.h"

database_dialog::database_dialog(QWidget *parent)
	: QDialog(parent)
{
	ini_setting_data = QVector<QString>{};

	wiki_xml_database_label = new QLabel;
    wiki_xml_database_label->setText(tr("fgo.wiki XML Database:"));
	wiki_xml_database_textedit = new QLineEdit;
    wiki_xml_database_button = new QPushButton;
    wiki_xml_database_button->setText(tr("Dir"));
    connect(wiki_xml_database_button, &QPushButton::clicked, this, &database_dialog::dir_button_clicked);

	servant_icon_present_label = new QLabel;
	servant_icon_present_label->setText(tr("Servant icon for presentation:"));
	servant_icon_present_textedit = new QLineEdit;
    servant_icon_present_button = new QPushButton;
    servant_icon_present_button->setText(tr("Dir"));
    connect(servant_icon_present_button, &QPushButton::clicked, this, &database_dialog::dir_button_clicked);

    event_item_label = new QLabel;
    event_item_label->setText(tr("Event item database:"));
    event_item_textedit = new QLineEdit;
    event_item_button = new QPushButton;
    event_item_button->setText(tr("File"));
    connect(event_item_button, &QPushButton::clicked, this, &database_dialog::file_button_clicked);

    exchange_item_label = new QLabel;
    exchange_item_label->setText(tr("Month exchange item database:"));
    exchange_item_textedit = new QLineEdit;
    exchange_item_button = new QPushButton;
    exchange_item_button->setText(tr("File"));
    connect(exchange_item_button, &QPushButton::clicked, this, &database_dialog::file_button_clicked);
    
    event_figure_label = new QLabel;
    event_figure_label->setText(tr("Event figures:"));
    event_figure_textedit = new QLineEdit;
    event_figure_button = new QPushButton;
    event_figure_button->setText(tr("Dir"));
    connect(event_figure_button, &QPushButton::clicked, this, &database_dialog::dir_button_clicked);

	QDialogButtonBox *dialog_box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(wiki_xml_database_label, 0, 0);
	layout->addWidget(wiki_xml_database_textedit, 0, 1);
    layout->addWidget(wiki_xml_database_button, 0, 2);
	layout->addWidget(servant_icon_present_label, 1, 0);
	layout->addWidget(servant_icon_present_textedit, 1, 1);
    layout->addWidget(servant_icon_present_button, 1, 2);
    layout->addWidget(event_item_label, 2, 0);
    layout->addWidget(event_item_textedit, 2, 1);
    layout->addWidget(event_item_button, 2, 2);
    layout->addWidget(exchange_item_label, 3, 0);
    layout->addWidget(exchange_item_textedit, 3, 1);
    layout->addWidget(exchange_item_button, 3, 2);
    layout->addWidget(event_figure_label, 4, 0);
    layout->addWidget(event_figure_textedit, 4, 1);
    layout->addWidget(event_figure_button, 4, 2);
	layout->addWidget(dialog_box, 5, 1, 1, 2);

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
    // ini_setting_data[2] : current user_data path, it is controled in mainwindow, when loading file
    ini_setting_data[3] = event_item_textedit->text();
    ini_setting_data[4] = exchange_item_textedit->text();
    ini_setting_data[5] = event_figure_textedit->text();
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
    event_item_textedit->setText(ini_setting_data[3]);
    exchange_item_textedit->setText(ini_setting_data[4]);
    event_figure_textedit->setText(ini_setting_data[5]);
}

void database_dialog::dir_button_clicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString show_string, return_string, guess_string;
    if (button == wiki_xml_database_button)
    {
        guess_string = wiki_xml_database_textedit->text();
        show_string = tr("Wiki Database Path...");
    }
    else if (button == servant_icon_present_button)
    {
        guess_string = servant_icon_present_textedit->text();
        show_string = tr("Servant Icon Path...");
    }
    else if (button == event_figure_button)
    {
        guess_string = event_figure_textedit->text();
        show_string = tr("Event Figure Path...");
    }

    return_string = QFileDialog::getExistingDirectory(this, show_string, guess_string, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!return_string.isEmpty())
    {
        if (button == wiki_xml_database_button) wiki_xml_database_textedit->setText(return_string);
        else if (button == servant_icon_present_button) servant_icon_present_textedit->setText(return_string);
        else if (button == event_figure_button) event_figure_textedit->setText(return_string);
    }
}

void database_dialog::file_button_clicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString show_string, return_string, guess_string;
    if (button == event_item_button)
    {
        guess_string = event_item_textedit->text();
        show_string = tr("Event Item File...");
    }
    else if (button == exchange_item_button)
    {
        guess_string = exchange_item_textedit->text();
        show_string = tr("Month Exchange Item File...");
    }

    return_string = QFileDialog::getOpenFileName(this, show_string, guess_string, tr("XML file (*.xml)"));
    if (!return_string.isEmpty())
    {
        if (button == event_item_button) event_item_textedit->setText(return_string);
        if (button == exchange_item_button) exchange_item_textedit->setText(return_string);
    }
}
