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
}

void filter_set_layout()
{

}



















