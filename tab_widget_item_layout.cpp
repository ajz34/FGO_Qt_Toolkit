#include "tab_widget_item.h"

tab_widget_item::tab_widget_item(QWidget *parent)
    : QWidget(parent)
{
    main_set_layout();
}

tab_widget_item::~tab_widget_item()
{
}

void tab_widget_item::main_set_layout()
{
    // main layout
    main_tab = new QTabWidget;
    main_tab->setTabPosition(QTabWidget::West);

    filter_widget = new QWidget;
    event_widget = new QWidget;
    month_widget = new QWidget;
    for (int i = 0; i < 9; ++i)
        category_widget[i] = new QWidget;

    main_tab->tabBar()->setStyle(new CustomTabStyle);
    main_tab->addTab(filter_widget, tr("Filter"));
    main_tab->addTab(event_widget, tr("Event"));
    main_tab->addTab(month_widget, tr("Month"));
    QVector<QString> category_tab_name
    {
        tr("Bronze Item"), tr("Silver Item"), tr("Gold Item"), tr("Shining Gem"), tr("Magic Gem"),
        tr("Secret Gem"), tr("Piece"), tr("Monument"), tr("Misc"),
    };
    for (int i = 0; i < 9; ++i)
    {
        main_tab->addTab(category_widget.at(i), category_tab_name.at(i));
    }

    auto main_layout = new QGridLayout;
    main_layout->addWidget(main_tab);
    setLayout(main_layout);

    // sub layout
    filter_set_layout();
}

void tab_widget_item::filter_set_layout()
{
    // object initialization
    for (int i = 0; i < 6; ++i)
    {
        filter_priority_check[i] = new QCheckBox;
        filter_priority_check.at(i)->setText(QVariant(i).toString());
        filter_priority_check.at(i)->setChecked(true);
    }
    filter_exist_check = new QCheckBox;
    filter_exist_check->setText(tr("Exist"));
    filter_exist_check->setChecked(true);
    filter_other_check = new QCheckBox;
    filter_other_check->setText(tr("Other"));
    filter_other_check->setChecked(false);
    filter_other_check->setEnabled(false);
    filter_upper_switch = new QClickableFigureLabel(
        QPixmap(":/self_icon/images/self_icon/filter_square.png").scaled(20, 20),
        QPixmap(":/self_icon/images/self_icon/filter_list.png").scaled(20, 20));
    filter_lower_switch = new QClickableFigureLabel(
        QPixmap(":/self_icon/images/self_icon/filter_square.png").scaled(20, 20),
        QPixmap(":/self_icon/images/self_icon/filter_list.png").scaled(20, 20));
    filter_upper_widget = new QScrollArea;
    filter_lower_widget = new QScrollArea;
    filter_upper_table = new QTableView;
    filter_lower_table = new QTableView;
    filter_split_widget = new QSplitter;
    filter_split_widget->setOrientation(Qt::Vertical);

    // layout

    auto filter_option_group = new QGroupBox;
    auto filter_option_layout = new QHBoxLayout;
    filter_option_group->setTitle(tr("Filter Option"));
    auto temp_layout_1 = new QGridLayout;
    temp_layout_1->addWidget(filter_priority_check.at(0), 0, 0);
    temp_layout_1->addWidget(filter_priority_check.at(1), 0, 1);
    temp_layout_1->addWidget(filter_priority_check.at(2), 0, 2);
    temp_layout_1->addWidget(filter_priority_check.at(3), 1, 0);
    temp_layout_1->addWidget(filter_priority_check.at(4), 1, 1);
    temp_layout_1->addWidget(filter_priority_check.at(5), 1, 2);
    auto temp_layout_2 = new QGridLayout;
    temp_layout_2->addWidget(filter_exist_check, 0, 0);
    temp_layout_2->addWidget(filter_other_check, 1, 0);
    filter_option_layout->addStretch();
    filter_option_layout->addStretch();
    filter_option_layout->addStretch();
    filter_option_layout->addLayout(temp_layout_1);
    filter_option_layout->addStretch();
    filter_option_layout->addLayout(temp_layout_2);
    filter_option_layout->addStretch();
    filter_option_layout->addStretch();
    filter_option_layout->addStretch();
    filter_option_group->setLayout(filter_option_layout);

    auto filter_switch_group = new QGroupBox;
    auto filter_switch_layout = new QVBoxLayout;
    filter_switch_layout->addWidget(filter_upper_switch);
    filter_switch_layout->addWidget(filter_lower_switch);
    filter_switch_group->setLayout(filter_switch_layout);
    filter_switch_group->setTitle(tr("layout"));

    auto filter_top_widgets = new QWidget;
    auto temp_layout_3 = new QHBoxLayout;
    temp_layout_3->addWidget(filter_option_group);
    temp_layout_3->addWidget(filter_switch_group);
    filter_top_widgets->setLayout(temp_layout_3);
    filter_top_widgets->setFixedHeight(filter_top_widgets->sizeHint().height());

    filter_split_widget->addWidget(filter_upper_widget);
    filter_split_widget->addWidget(filter_lower_widget);

    auto filter_mainlayout = new QVBoxLayout;
    filter_mainlayout->addWidget(filter_top_widgets);
    filter_mainlayout->addWidget(filter_split_widget);
    filter_widget->setLayout(filter_mainlayout);
}



















