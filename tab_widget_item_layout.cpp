#include "tab_widget_item.h"

tab_widget_item::tab_widget_item(QWidget *parent)
    : QWidget(parent)
{
    main_set_layout();
    main_set_connection();
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
    event_set_layout();
    month_set_layout();
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
    filter_exist_check[0] = new QCheckBox;
    filter_exist_check.at(0)->setText(tr("Exist"));
    filter_exist_check.at(0)->setChecked(true);
    filter_exist_check[1] = new QCheckBox;
    filter_exist_check.at(1)->setText(tr("Not Exist"));
    filter_exist_check.at(1)->setChecked(true);
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
    filter_upper_widget->setWidgetResizable(true);
    filter_lower_widget->setWidgetResizable(true);
    filter_upper_layout = new FlowLayout;
    filter_lower_layout = new FlowLayout;
    filter_upper_table = new QTableView;
    filter_lower_table = new QTableView;
    filter_upper_table->setSortingEnabled(true);
    filter_upper_table->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    filter_upper_table->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    filter_lower_table->setSortingEnabled(true);
    filter_lower_table->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    filter_lower_table->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    filter_upper_model = new QStandardItemModel;
    filter_lower_model = new QStandardItemModel;
    filter_upper_table->setModel(filter_upper_model);
    filter_lower_table->setModel(filter_lower_model);
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
    temp_layout_2->addWidget(filter_exist_check.at(0), 0, 0);
    temp_layout_2->addWidget(filter_exist_check.at(1), 1, 0);
    auto temp_layout_3 = new QVBoxLayout;
    temp_layout_3->addStretch();
    temp_layout_3->addWidget(filter_other_check);
    temp_layout_3->addStretch();
    filter_option_layout->addStretch();
    filter_option_layout->addStretch();
    filter_option_layout->addStretch();
    filter_option_layout->addLayout(temp_layout_1);
    filter_option_layout->addStretch();
    filter_option_layout->addLayout(temp_layout_2);
    filter_option_layout->addStretch();
    filter_option_layout->addLayout(temp_layout_3);
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
    auto temp_layout_4 = new QHBoxLayout;
    temp_layout_4->addWidget(filter_option_group);
    temp_layout_4->addWidget(filter_switch_group);
    filter_top_widgets->setLayout(temp_layout_4);
    filter_top_widgets->setFixedHeight(filter_top_widgets->sizeHint().height());

    // flow layout is not directly applicable to the scrollarea;
    // however, we can use a widget to wrap that around
    // some more codes need to be added, and it is not wise to set layout other than here
    // solution: https://forum.qt.io/topic/11938/solved-flowlayout-in-a-qscrollarea/
    auto filter_upper_widget_inter = new QWidget;
    auto filter_lower_widget_inter = new QWidget;
    filter_upper_widget_inter->setLayout(filter_upper_layout);
    filter_lower_widget_inter->setLayout(filter_lower_layout);
    filter_upper_widget->setWidget(filter_upper_widget_inter);
    filter_lower_widget->setWidget(filter_lower_widget_inter);
    filter_split_widget->addWidget(filter_upper_widget);
    filter_split_widget->addWidget(filter_lower_widget);

    // set background color white
    // https://wiki.qt.io/How_to_Change_the_Background_Color_of_QWidget
    // use method 1, QPalette method
    // method 2 is style sheet method
    // however, since this method may also change the color style of scroll bar,
    // I decided not to take method 2
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    filter_split_widget->setAutoFillBackground(true);
    filter_split_widget->setPalette(pal);
    filter_upper_widget->setAutoFillBackground(true);
    filter_upper_widget->setPalette(pal);
    filter_lower_widget->setAutoFillBackground(true);
    filter_lower_widget->setPalette(pal);

    auto filter_mainlayout = new QVBoxLayout;
    filter_mainlayout->addWidget(filter_top_widgets);
    filter_mainlayout->addWidget(filter_split_widget);
    filter_widget->setLayout(filter_mainlayout);
}

void tab_widget_item::event_set_layout()
{
    // object initialization
    event_date_widget = new QDateEdit;
    event_date_widget->setCalendarPopup(true);
    event_date_widget->setDate(QDate::currentDate().addDays(-440));
    event_date_notify = new QLabel;
    event_date_notify->setText(tr("Only select date after"));
    event_upper_layout = new FlowLayout;
    event_lower_layout = new QVBoxLayout;
    event_upper_widget = new QScrollArea;
    event_lower_widget = new QScrollArea;
    event_upper_widget->setWidgetResizable(true);
    event_lower_widget->setWidgetResizable(true);
    event_split = new QSplitter;
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    event_split->setAutoFillBackground(true);
    event_split->setPalette(pal);
    event_upper_widget->setAutoFillBackground(true);
    event_upper_widget->setPalette(pal);
    event_lower_widget->setAutoFillBackground(true);
    event_lower_widget->setPalette(pal);

    // layout
    auto temp_layout_1 = new QHBoxLayout;
    temp_layout_1->addStretch();
    temp_layout_1->addWidget(event_date_notify);
    temp_layout_1->addWidget(event_date_widget);

    auto event_upper_widget_inter = new QWidget;
    auto event_lower_widget_inter = new QWidget;
    event_upper_widget_inter->setLayout(event_upper_layout);
    event_lower_widget_inter->setLayout(event_lower_layout);
    event_upper_widget->setWidget(event_upper_widget_inter);
    event_lower_widget->setWidget(event_lower_widget_inter);

    event_split->setOrientation(Qt::Vertical);
    event_split->addWidget(event_upper_widget);
    event_split->addWidget(event_lower_widget);
    event_split->setStretchFactor(0, 4);
    event_split->setStretchFactor(1, 1);

    auto event_main_layout = new QGridLayout;
    event_main_layout->addLayout(temp_layout_1, 0, 0, Qt::AlignRight);
    event_main_layout->addWidget(event_split, 1, 0);
    event_widget->setLayout(event_main_layout);
}

void tab_widget_item::month_set_layout()
{
    // object initialization
    month_widget_scroll = new QScrollArea;
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    month_widget_scroll->setAutoFillBackground(true);
    month_widget_scroll->setPalette(pal);
    month_widget_scroll->setWidgetResizable(true);
    month_widget_layout = new FlowLayout;
    month_widget_date = new QDateEdit;
    month_widget_date->setCalendarPopup(true);
    month_widget_date->setDate(QDate::currentDate().addDays(-440));
    month_widget_date_label = new QLabel;
    month_widget_date_label->setText(tr("Only select date after"));

    // layout
    auto layout_1 = new QHBoxLayout;
    layout_1->addStretch();
    layout_1->addWidget(month_widget_date_label);
    layout_1->addWidget(month_widget_date);

    auto widget_1 = new QWidget;
    widget_1->setLayout(month_widget_layout);
    month_widget_scroll->setWidget(widget_1);

    auto month_main_layout = new QVBoxLayout;
    month_main_layout->addLayout(layout_1);
    month_main_layout->addWidget(month_widget_scroll);
    month_widget->setLayout(month_main_layout);
}

//--- Utility

QVector<int> tab_widget_item::util_read_items(TreeModel *tree, const QModelIndex &index)
{
    QVector<int> item_list = QVector<int>(GLOB::LIST_ITEM.size(), 0);
    Q_ASSERT(index.isValid());
    for (int row = 0; row < tree->rowCount(index); ++row)
    {
        QModelIndex item_index = tree->index(row, 0, index);
        QString item_str = tree->data(item_index, Qt::DisplayRole).toString();
        int item_val = tree->data(item_index.siblingAtColumn(1), Qt::DisplayRole).toInt();
        int list_ind = GLOB::MAP_ITEM_INDEX.value(item_str, -1);
        Q_ASSERT(list_ind >= 0);  // items should in the list!
        item_list[list_ind] = item_val;
    }
    return item_list;
}

QString tab_widget_item::util_consume_int(long long val, bool turn_100)
{
    Q_ASSERT(val >= 0);
    // trun_100: if returned value > 100, then the space is not enough for many labels; we need to truncate them.
    // define headers
    long long h_k = 1000;
    long long h_M = 1000 * 1000;
    long long h_G = 1000 * 1000 * 1000;
    long long h_T = 1000LL * 1000LL * 1000LL * 1000LL;
    const QVector<long long> h_vec = { h_k, h_M, h_G, h_T };
    const QVector<QString> h_str = { "k", "M", "G" , "T"};
    // actual code
    if (val == 0)
        return QString();
    else if (val < h_k)
        return QVariant(val).toString();
    else
    {
        for (int i = 0; i < 4; ++i)
        {
            if (val < 1000 * h_vec.at(i))
            {
                const long long &h = h_vec.at(i);
                const QString &s = h_str.at(i);
                if (val % h == 0)
                    return QVariant(val / h).toString() + s;
                else if (turn_100)
                    if (val / h > 100)
                        return QVariant(val / h).toString() + "." + s;
                return QVariant(val / h).toString() + "."
                        + QVariant((val % h) / (h / 10)).toString() + s;
            }
        }
        return "overflow";
    }
}

void tab_widget_item::util_list_minus(QVector<long long> &vec_1, const QVector<int> &vec_2)
{
    // vec_1 = vec_1 - vec_2
    Q_ASSERT(vec_1.size() == vec_2.size());
    for (int i = 0; i < vec_1.size(); ++i)
        vec_1[i] -= vec_2[i];
}

void tab_widget_item::util_list_minus(QVector<long long> &vec_1, const QVector<long long> &vec_2)
{
    // vec_1 = vec_1 - vec_2
    Q_ASSERT(vec_1.size() == vec_2.size());
    for (int i = 0; i < vec_1.size(); ++i)
        vec_1[i] -= vec_2[i];
}

void tab_widget_item::util_list_plus(QVector<long long> &vec_1, const QVector<int> &vec_2)
{
    // vec_1 = vec_1 + vec_2
    Q_ASSERT(vec_1.size() == vec_2.size());
    for (int i = 0; i < vec_1.size(); ++i)
        vec_1[i] += vec_2[i];
}

void tab_widget_item::util_list_plus(QVector<long long> &vec_1, const QVector<int> &vec_2, const int &fact)
{
    // vec_1 = vec_1 + vec_2 * fact
    Q_ASSERT(vec_1.size() == vec_2.size());
    for (int i = 0; i < vec_1.size(); ++i)
        vec_1[i] += vec_2[i] * fact;
}

void tab_widget_item::util_list_plus(QVector<long long> &vec_1, const QVector<long long> &vec_2)
{
    // vec_1 = vec_1 + vec_2
    Q_ASSERT(vec_1.size() == vec_2.size());
    for (int i = 0; i < vec_1.size(); ++i)
        vec_1[i] += vec_2[i];
}













