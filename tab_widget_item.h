#pragma once

#include <QtWidgets>
#include "qclickablefigurelabel.h"
#include "qrightclickpushbutton.h"

class tab_widget_item : public QWidget
{
    Q_OBJECT;

    //--- Layout and Controls

    // 0. main tab control
    QTabWidget *main_tab = nullptr;
    void main_set_layout();

    // 1. filter
    QWidget *filter_widget = nullptr;
    void filter_set_layout();
    QVector<QCheckBox*> filter_priority_check = QVector<QCheckBox*>(6, nullptr);
    QCheckBox *filter_exist_check = nullptr;
    QCheckBox *filter_other_check = nullptr;
    QClickableFigureLabel *filter_upper_switch = nullptr;
    QClickableFigureLabel *filter_lower_switch = nullptr;
    QMap<int, QRightClickPushButton*> filter_map_button;
    QVector<bool> filter_map_mask;
    QScrollArea *filter_upper_widget = nullptr;
    QScrollArea *filter_lower_widget = nullptr;
    QTableView *filter_upper_table = nullptr;
    QTableView *filter_lower_table = nullptr;
    QStandardItemModel *filter_upper_model = nullptr;
    QStandardItemModel *filter_lower_model = nullptr;
    QSplitter *filter_split_widget = nullptr;

    // 2. event
    QWidget *event_widget = nullptr;

    // 3. month
    QWidget *month_widget = nullptr;

    // 4. category
    // [0:3] bronze, silver, gold
    // [3:6] gem: shining, magic, secret
    // [6:9] piece, monument, misc
    QVector<QWidget*> category_widget = QVector<QWidget*>(9, nullptr);

    //--- Connection

    // 0. main tab control
private:
    // void main_set_connection();

public slots:
    // void main_set_ini();

public:
    tab_widget_item(QWidget *parent);
    ~tab_widget_item();
};

// set tab widget text horizontally
// https://www.qtcentre.org/threads/13293-QTabWidget-customization
// another possible solution, however, may have layout issue between label and tab itself
// https://stackoverflow.com/questions/48457149/qtabwidget-horizontal-tabs-when-tabposition-west
class CustomTabStyle : public QProxyStyle
{
public:
    QSize sizeFromContents(ContentsType type, const QStyleOption *option,
                           const QSize &size, const QWidget *widget) const
    {
        QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
        if (type == QStyle::CT_TabBarTab)
            s.transpose();
        return s;
    }

    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
    {
        if (element == CE_TabBarTabLabel)
        {
            if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option))
            {
                QStyleOptionTab opt(*tab);
                opt.shape = QTabBar::RoundedNorth;
                QProxyStyle::drawControl(element, &opt, painter, widget);
                return;
            }
        }
        QProxyStyle::drawControl(element, option, painter, widget);
    }
};
