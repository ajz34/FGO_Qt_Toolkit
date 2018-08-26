#include "tab_widget_servant.h"

tab_widget_servant::tab_widget_servant(QWidget *parent)
	: QWidget(parent)
{
	//--- A. servant class labels
	set_servant_class_label();
	set_servant_class_connection();
    set_servant_class_layout();
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

//--- C. filter

void tab_widget_servant::set_filter_button()
{
	set_filter_rarity();
    set_filter_follow();
}

void tab_widget_servant::set_filter_rarity()
{
	filter_rarity = new QPushButton(tr("Rarity"));
	filter_rarity_all = new QAction(tr("All"));
    filter_rarity_5 = new QAction("5");
    filter_rarity_4 = new QAction("4");
    filter_rarity_3 = new QAction("3");
    filter_rarity_2 = new QAction("2");
    filter_rarity_1 = new QAction("1");
    filter_rarity_0 = new QAction("0");
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

void tab_widget_servant::set_filter_follow()
{
    filter_follow = new QPushButton(tr("Follow"));
    filter_follow_all = new QAction(tr("All"));
    filter_follow_yes = new QAction(tr("Yes"));
    filter_follow_no = new QAction(tr("No"));
    QMenu *menu = new QMenu;

    QVector<QAction*> filter_follows{
        filter_follow_all, filter_follow_yes, filter_follow_no,
    };

    for (auto i : filter_follows)
    {
        i->setCheckable(true);
        i->setChecked(false);
        menu->addAction(i);
    };
    filter_follow_all->setChecked(true);

    filter_follow->setMenu(menu);
    filter_follow->setFlat(true);
}

void tab_widget_servant::set_filter_layout()
{
	QVBoxLayout *filter_layout_temp = new QVBoxLayout;
	filter_layout_temp->addWidget(filter_rarity);
    filter_layout_temp->addWidget(filter_follow);
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
    // scroll for pixels but not for items
    // https://stackoverflow.com/questions/2016323/qt4-is-it-possible-to-make-a-qlistview-scroll-smoothly
    table_widget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	table_widget_model = new QStandardItemModel;
	table_widget_model_origin = new QStandardItemModel;
}

//--- N. layout

void tab_widget_servant::set_main_widget_layout()
{
	main_widget_layout = new QGridLayout;
	QGridLayout *upper_left_layout = new QGridLayout;
	QWidget *upper_left_widget = new QWidget;
    upper_left_layout->addLayout(servant_class_layout, 0, 0);
	upper_left_layout->addLayout(filter_layout, 0, 1);
	upper_left_widget->setLayout(upper_left_layout);
	upper_left_widget->setFixedHeight(upper_left_layout->sizeHint().height());
	
	QVBoxLayout *left_layout = new QVBoxLayout;
	left_layout->addWidget(upper_left_widget);
	left_layout->addWidget(table_widget);

	main_widget_layout->addLayout(left_layout, 0, 0);
	setLayout(main_widget_layout);
}
