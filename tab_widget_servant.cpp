#include "tab_widget_servant.h"

tab_widget_servant::tab_widget_servant(QWidget *parent)
	: QWidget(parent)
{
	//--- A. servant class labels
	set_servant_class_label();
	set_servant_class_connection();
	set_servant_class_layout();
	//--- B. sort
	set_sort_button();
	set_sort_layout();
	//--- C. filter
	set_filter_button();
	set_filter_connection();
	set_filter_layout();
	//--- D. servant table
	set_table_widget();
	//--- N. layout
	set_main_widget_layout();
}

tab_widget_servant::~tab_widget_servant()
{
}

//--- A. servant class labels

void tab_widget_servant::set_servant_class_label()
{
	const int SCALE_SIZE = 40;
	class_saber = new QClickableFigureLabel(
		QPixmap(":/servant_class/images/servant_class/saber_on.png").scaled(SCALE_SIZE, SCALE_SIZE),
		QPixmap(":/servant_class/images/servant_class/saber_off.png").scaled(SCALE_SIZE, SCALE_SIZE));
	class_saber->setFixedSize(SCALE_SIZE, SCALE_SIZE);
	class_archer = new QClickableFigureLabel(
		QPixmap(":/servant_class/images/servant_class/archer_on.png").scaled(SCALE_SIZE, SCALE_SIZE),
		QPixmap(":/servant_class/images/servant_class/archer_off.png").scaled(SCALE_SIZE, SCALE_SIZE));
	class_archer->setFixedSize(SCALE_SIZE, SCALE_SIZE);
	class_lancer = new QClickableFigureLabel(
		QPixmap(":/servant_class/images/servant_class/lancer_on.png").scaled(SCALE_SIZE, SCALE_SIZE),
		QPixmap(":/servant_class/images/servant_class/lancer_off.png").scaled(SCALE_SIZE, SCALE_SIZE));
	class_lancer->setFixedSize(SCALE_SIZE, SCALE_SIZE);
	class_rider = new QClickableFigureLabel(
		QPixmap(":/servant_class/images/servant_class/rider_on.png").scaled(SCALE_SIZE, SCALE_SIZE),
		QPixmap(":/servant_class/images/servant_class/rider_off.png").scaled(SCALE_SIZE, SCALE_SIZE));
	class_rider->setFixedSize(SCALE_SIZE, SCALE_SIZE);
	class_caster = new QClickableFigureLabel(
		QPixmap(":/servant_class/images/servant_class/caster_on.png").scaled(SCALE_SIZE, SCALE_SIZE),
		QPixmap(":/servant_class/images/servant_class/caster_off.png").scaled(SCALE_SIZE, SCALE_SIZE));
	class_caster->setFixedSize(SCALE_SIZE, SCALE_SIZE);
	class_assassin = new QClickableFigureLabel(
		QPixmap(":/servant_class/images/servant_class/assassin_on.png").scaled(SCALE_SIZE, SCALE_SIZE),
		QPixmap(":/servant_class/images/servant_class/assassin_off.png").scaled(SCALE_SIZE, SCALE_SIZE));
	class_assassin->setFixedSize(SCALE_SIZE, SCALE_SIZE);
	class_berserker = new QClickableFigureLabel(
		QPixmap(":/servant_class/images/servant_class/berserker_on.png").scaled(SCALE_SIZE, SCALE_SIZE),
		QPixmap(":/servant_class/images/servant_class/berserker_off.png").scaled(SCALE_SIZE, SCALE_SIZE));
	class_berserker->setFixedSize(SCALE_SIZE, SCALE_SIZE);
	class_shielder = new QClickableFigureLabel(
		QPixmap(":/servant_class/images/servant_class/shielder_on.png").scaled(SCALE_SIZE, SCALE_SIZE),
		QPixmap(":/servant_class/images/servant_class/shielder_off.png").scaled(SCALE_SIZE, SCALE_SIZE));
	class_shielder->setFixedSize(SCALE_SIZE, SCALE_SIZE);
	class_ruler = new QClickableFigureLabel(
		QPixmap(":/servant_class/images/servant_class/ruler_on.png").scaled(SCALE_SIZE, SCALE_SIZE),
		QPixmap(":/servant_class/images/servant_class/ruler_off.png").scaled(SCALE_SIZE, SCALE_SIZE));
	class_ruler->setFixedSize(SCALE_SIZE, SCALE_SIZE);
	class_avenger = new QClickableFigureLabel(
		QPixmap(":/servant_class/images/servant_class/avenger_on.png").scaled(SCALE_SIZE, SCALE_SIZE),
		QPixmap(":/servant_class/images/servant_class/avenger_off.png").scaled(SCALE_SIZE, SCALE_SIZE));
	class_avenger->setFixedSize(SCALE_SIZE, SCALE_SIZE);
	class_alterego = new QClickableFigureLabel(
		QPixmap(":/servant_class/images/servant_class/alterego_on.png").scaled(SCALE_SIZE, SCALE_SIZE),
		QPixmap(":/servant_class/images/servant_class/alterego_off.png").scaled(SCALE_SIZE, SCALE_SIZE));
	class_alterego->setFixedSize(SCALE_SIZE, SCALE_SIZE);
	class_mooncancer = new QClickableFigureLabel(
		QPixmap(":/servant_class/images/servant_class/mooncancer_on.png").scaled(SCALE_SIZE, SCALE_SIZE),
		QPixmap(":/servant_class/images/servant_class/mooncancer_off.png").scaled(SCALE_SIZE, SCALE_SIZE));
	class_mooncancer->setFixedSize(SCALE_SIZE, SCALE_SIZE);
	class_foreigner = new QClickableFigureLabel(
		QPixmap(":/servant_class/images/servant_class/foreigner_on.png").scaled(SCALE_SIZE, SCALE_SIZE),
		QPixmap(":/servant_class/images/servant_class/foreigner_off.png").scaled(SCALE_SIZE, SCALE_SIZE));
	class_foreigner->setFixedSize(SCALE_SIZE, SCALE_SIZE);
	class_all_on = new QClickableFigureLabel(
		QPixmap(":/servant_class/images/servant_class/all_on.png").scaled(SCALE_SIZE, SCALE_SIZE),
		QPixmap(":/servant_class/images/servant_class/all_on.png").scaled(SCALE_SIZE, SCALE_SIZE));
	class_all_on->setFixedSize(SCALE_SIZE, SCALE_SIZE);
	class_all_off = new QClickableFigureLabel(
		QPixmap(":/servant_class/images/servant_class/all_off.png").scaled(SCALE_SIZE, SCALE_SIZE),
		QPixmap(":/servant_class/images/servant_class/all_off.png").scaled(SCALE_SIZE, SCALE_SIZE));
	class_all_off->setFixedSize(SCALE_SIZE, SCALE_SIZE);
}

void tab_widget_servant::set_servant_class_layout()
{
	QHBoxLayout *layout_0 = new QHBoxLayout;
	layout_0->addStretch();
	layout_0->addStretch();
	layout_0->addStretch();
	layout_0->addWidget(class_all_on);
	layout_0->addStretch();
	layout_0->addWidget(class_all_off);
	layout_0->addStretch();
	layout_0->addStretch();
	layout_0->addStretch();
	QGroupBox *group_0 = new QGroupBox;
	group_0->setLayout(layout_0);
	group_0->setTitle(tr("Selection"));

	QGridLayout *layout_1 = new QGridLayout;
	layout_1->addWidget(class_saber, 0, 0, 1, 2, Qt::AlignHCenter);
	layout_1->addWidget(class_archer, 1, 0);
	layout_1->addWidget(class_lancer, 1, 1);
	layout_1->setHorizontalSpacing(SCALE_SIZE / 2);
	QGroupBox *group_1 = new QGroupBox;
	group_1->setLayout(layout_1);
	group_1->setTitle(tr("Tri-Knight"));

	QGridLayout *layout_2 = new QGridLayout;
	layout_2->addWidget(class_rider, 0, 0, 1, 2, Qt::AlignHCenter);
	layout_2->addWidget(class_caster, 1, 0);
	layout_2->addWidget(class_assassin, 1, 1);
	layout_2->setHorizontalSpacing(SCALE_SIZE / 2);
	QGroupBox *group_2 = new QGroupBox;
	group_2->setLayout(layout_2);
	group_2->setTitle(tr("Quad-Knight"));

	QGridLayout *layout_3 = new QGridLayout;
	layout_3->addWidget(class_ruler, 0, 0, 1, 2, Qt::AlignHCenter);
	layout_3->addWidget(class_mooncancer, 1, 0);
	layout_3->addWidget(class_avenger, 1, 1);
	layout_3->setHorizontalSpacing(SCALE_SIZE / 2);
	QGroupBox *group_3 = new QGroupBox;
	group_3->setLayout(layout_3);
	group_3->setTitle(tr("Extra-Class"));

	QHBoxLayout *layout_4 = new QHBoxLayout;
	layout_4->addStretch();
	layout_4->addStretch();
	layout_4->addWidget(class_alterego);
	layout_4->addStretch();
	layout_4->addWidget(class_foreigner);
	layout_4->addStretch();
	layout_4->addWidget(class_berserker);
	layout_4->addStretch();
	layout_4->addWidget(class_shielder);
	layout_4->addStretch();
	layout_4->addStretch();
	QGroupBox *group_4 = new QGroupBox;
	group_4->setLayout(layout_4);
	group_4->setTitle(tr("Classes out of Triangle"));

	// it is very possibly that we should have a fixed-sized widget, but not layout, to fix size
	QGridLayout *servant_class_layout_temp = new QGridLayout;
	servant_class_layout_temp->addWidget(group_0, 0, 0, 1, -1);
	servant_class_layout_temp->addWidget(group_1, 1, 0);
	servant_class_layout_temp->addWidget(group_2, 1, 1);
	servant_class_layout_temp->addWidget(group_3, 1, 2);
	servant_class_layout_temp->addWidget(group_4, 2, 0, 1, -1);
	// auto *servant_class_layout_widget = new QWidget;
	// servant_class_layout_widget->setLayout(servant_class_layout_temp);
	// servant_class_layout_widget->setFixedSize(servant_class_layout_temp->sizeHint());

	servant_class_layout = new QHBoxLayout;
	servant_class_layout->addStretch();
	servant_class_layout->addLayout(servant_class_layout_temp);
	servant_class_layout->addStretch();
}

//--- B. sort

void tab_widget_servant::set_sort_button()
{
	sort_button_id_ascending = new QRadioButton;
	sort_button_id_descending = new QRadioButton;
	sort_button_atk_ascending = new QRadioButton;
	sort_button_atk_descending = new QRadioButton;
	sort_button_hp_ascending = new QRadioButton;
	sort_button_hp_descending = new QRadioButton;

	sort_button_id_descending->setChecked(true);

	sort_button_group = new QButtonGroup;
	sort_button_group->addButton(sort_button_id_ascending);
	sort_button_group->addButton(sort_button_id_descending);
	sort_button_group->addButton(sort_button_atk_ascending);
	sort_button_group->addButton(sort_button_atk_descending);
	sort_button_group->addButton(sort_button_hp_ascending);
	sort_button_group->addButton(sort_button_hp_descending);
}

void tab_widget_servant::set_sort_layout()
{
	QLabel *sort_label_ascending = new QLabel;
	QLabel *sort_label_descending = new QLabel;
	QLabel *sort_label_id = new QLabel;
	QLabel *sort_label_atk = new QLabel;
	QLabel *sort_label_hp = new QLabel;
	sort_label_ascending->setText(tr("Ascending"));
	sort_label_descending->setText(tr("Descending"));
	sort_label_id->setText(tr("ID"));
	sort_label_atk->setText(tr("ATK"));
	sort_label_hp->setText(tr("HP"));

	QGridLayout *sort_button_layout_temp = new QGridLayout;

	sort_button_layout_temp->addWidget(sort_label_ascending, 1, 0, Qt::AlignCenter);
	sort_button_layout_temp->addWidget(sort_label_descending, 2, 0, Qt::AlignCenter);
	sort_button_layout_temp->addWidget(sort_label_id, 0, 1, Qt::AlignCenter);
	sort_button_layout_temp->addWidget(sort_label_atk, 0, 2, Qt::AlignCenter);
	sort_button_layout_temp->addWidget(sort_label_hp, 0, 3, Qt::AlignCenter);

	sort_button_layout_temp->addWidget(sort_button_id_ascending, 1, 1, Qt::AlignCenter);
	sort_button_layout_temp->addWidget(sort_button_id_descending, 2, 1, Qt::AlignCenter);
	sort_button_layout_temp->addWidget(sort_button_atk_ascending, 1, 2, Qt::AlignCenter);
	sort_button_layout_temp->addWidget(sort_button_atk_descending, 2, 2, Qt::AlignCenter);
	sort_button_layout_temp->addWidget(sort_button_hp_ascending, 1, 3, Qt::AlignCenter);
	sort_button_layout_temp->addWidget(sort_button_hp_descending, 2, 3, Qt::AlignCenter);

	sort_button_layout_temp->setColumnMinimumWidth(1, 1.5 * SCALE_SIZE);
	sort_button_layout_temp->setColumnMinimumWidth(2, 1.5 * SCALE_SIZE);
	sort_button_layout_temp->setColumnMinimumWidth(3, 1.5 * SCALE_SIZE);

	sort_button_layout = new QHBoxLayout;
	sort_button_layout->addStretch();
	sort_button_layout->addLayout(sort_button_layout_temp);
	sort_button_layout->addStretch();
}

//--- C. filter

void tab_widget_servant::set_filter_button()
{
	set_filter_rarity();
}

void tab_widget_servant::set_filter_rarity()
{
	filter_rarity = new QPushButton(tr("Rarity"));
	filter_rarity_all = new QAction(tr("All"));
	filter_rarity_5 = new QAction(tr("5"));
	filter_rarity_4 = new QAction(tr("4"));
	filter_rarity_3 = new QAction(tr("3"));
	filter_rarity_2 = new QAction(tr("2"));
	filter_rarity_1 = new QAction(tr("1"));
	filter_rarity_0 = new QAction(tr("0"));
	QMenu *menu = new QMenu;

	QVector<QAction*> filter_rarities{
		filter_rarity_all, filter_rarity_5, filter_rarity_4, filter_rarity_3,
		filter_rarity_2, filter_rarity_1, filter_rarity_0,
	};

	for (auto i : filter_rarities)
	{
		i->setCheckable(true);
		i->setChecked(false);
		menu->addAction(i);
	}
	filter_rarity_all->setChecked(true);

	filter_rarity->setMenu(menu);
	filter_rarity->setFlat(true);
}

void tab_widget_servant::set_filter_layout()
{
	QVBoxLayout *filter_layout_temp = new QVBoxLayout;
	filter_layout_temp->addWidget(filter_rarity);
	filter_layout_temp->addStretch();

	QGroupBox *filter_layout_frame = new QGroupBox;
	filter_layout_frame->setTitle(tr("Filter"));
	filter_layout_frame->setLayout(filter_layout_temp);

	filter_layout = new QVBoxLayout;
	filter_layout->addWidget(filter_layout_frame);
}

//--- D. servant table

void tab_widget_servant::set_table_widget()
{
	table_widget = new QTableView;
	table_widget_model = new QStandardItemModel();
	QStringList table_widget_model_header;
	table_widget_model_header << tr("Servant") << tr("Name") << tr("Rarity");
	table_widget_model->setHorizontalHeaderLabels(table_widget_model_header);
	QStandardItem *i = new QStandardItem(QString(tr("Hello, ")));
	QStandardItem *j = new QStandardItem(QString(tr("Hello, ")));
	table_widget_model->setItem(1, 0, i);
	table_widget_model->setItem(1, 1, j);
	table_widget->setModel(table_widget_model);
}

//--- N. layout

void tab_widget_servant::set_main_widget_layout()
{
	main_widget_layout = new QGridLayout;
	QGridLayout *upper_left_layout = new QGridLayout;
	QWidget *upper_left_widget = new QWidget;
	upper_left_layout->addLayout(servant_class_layout, 0, 0);
	upper_left_layout->addLayout(sort_button_layout, 1, 0);
	upper_left_layout->addLayout(filter_layout, 0, 1, 2, 1);
	upper_left_widget->setLayout(upper_left_layout);
	upper_left_widget->setFixedHeight(upper_left_layout->sizeHint().height());
	
	QVBoxLayout *left_layout = new QVBoxLayout;
	left_layout->addWidget(upper_left_widget);
	left_layout->addWidget(table_widget);

	main_widget_layout->addLayout(left_layout, 0, 0);
	setLayout(main_widget_layout);
}
