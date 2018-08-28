#pragma once

#include <QtWidgets>
#include "qclickablefigurelabel.h"
#include "qrightclickpushbutton.h"
#include "treemodel.h"
#include "flowlayout.h"
#include "resource_consume.h"

class tab_widget_item : public QWidget
{
    Q_OBJECT;

private:
    //--- frequently used data
    const int SERVANT_ICON_NUMBER = 500;
    const QString INI_SETTING_FILE_PATH = QString("fgo_helper_ajz_0_1");
    QVector<QString> ini_setting_data{};
    QVector<TreeModel*> wiki_database = QVector<TreeModel*>(SERVANT_ICON_NUMBER, nullptr);
    TreeModel *user_data = nullptr;
    QVector<QPixmap> *servant_icon_button_image = nullptr;
    TreeModel *event_item = nullptr;
    TreeModel *exchange_item = nullptr;
    QHash<QString, QPixmap> *event_figure = nullptr;

private:
    //--- Layout and Controls

    // 0. main tab control
private:
    QTabWidget *main_tab = nullptr;
    void main_set_layout();
    void main_set_connection();

    // 1. filter
private:
    QWidget *filter_widget = nullptr;
    void filter_set_layout();
    QVector<QCheckBox*> filter_priority_check = QVector<QCheckBox*>(6, nullptr);
    QVector<QCheckBox*> filter_exist_check = QVector<QCheckBox*>(2, nullptr);
    QCheckBox *filter_other_check = nullptr;
    QClickableFigureLabel *filter_upper_switch = nullptr;
    QClickableFigureLabel *filter_lower_switch = nullptr;
    QMap<int, bool> filter_map_mask{};
    QMap<int, int> filter_map_priority{};
    QMap<int, bool> filter_map_exist{};
    QMap<int, QVector<int>> filter_map_actual{};
    QMap<int, QVector<int>> filter_map_ideal{};
    QMap<int, QVector<int>> filter_map_costume{};
    QScrollArea *filter_upper_widget = nullptr;
    QScrollArea *filter_lower_widget = nullptr;
    FlowLayout *filter_upper_layout = nullptr;
    FlowLayout *filter_lower_layout = nullptr;
    QMap<int, QRightClickPushButton*> filter_widget_button{};
    QTableView *filter_upper_table = nullptr;
    QTableView *filter_lower_table = nullptr;
    QMap<int, QRightClickPushButton*> filter_table_button{};
    QStandardItemModel *filter_upper_model = nullptr;
    QStandardItemModel *filter_lower_model = nullptr;
    QSplitter *filter_split_widget = nullptr;
private:
    void filter_set_connection();
private:
    void filter_reset_data();
    void filter_refresh_table();
private slots:
    void filter_interchange_table();
    void filter_refresh_layout();
    void filter_on_trival_check_clicked();
    void filter_on_other_check_clicked();
    void filter_on_button_right_clicked();
signals:
    void from_filter_mask_changed();
    void from_filter_change_user_data(
        QVector<QString> ini_setting,
        QVector<TreeModel*> *wiki,
        QVector<QPixmap> *servant_icon,
        int id,
        TreeModel* user_dat);

    // 2. event
private:
    QWidget *event_widget = nullptr;

    // 3. month
    QWidget *month_widget = nullptr;

    // 4. category
    // [0:3] bronze, silver, gold
    // [3:6] gem: shining, magic, secret
    // [6:9] piece, monument, misc
    QVector<QWidget*> category_widget = QVector<QWidget*>(9, nullptr);

    //--- Central Connection
signals:
    void signal_user_data_changed(TreeModel *user_dat);
public slots:
    void from_parent_database_changed(
        QVector<QString> path_pack,
        QVector<TreeModel*> tree_model,
        TreeModel* user_dat,
        QVector<QPixmap> *serv_img,
        TreeModel *event_item_dat,
        TreeModel *exchange_item_dat,
        QHash<QString, QPixmap> *event_figure_dat);
    void from_parent_user_data_loaded(TreeModel *user_dat);

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
