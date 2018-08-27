#include "tab_widget_item.h"

//--- Central Connection

void tab_widget_item::from_parent_database_changed(
    QVector<QString> path_pack,
    QVector<TreeModel*> tree_model,
    TreeModel* user_dat,
    QVector<QPixmap> *serv_img)
{
    ini_setting_data = path_pack;
    wiki_database = tree_model;
    user_data = user_dat;
    servant_icon_button_image = serv_img;

    filter_reset_data();
}

void tab_widget_item::from_parent_user_data_loaded(TreeModel *user_dat)
{
    user_data = user_dat;
    filter_reset_data();
}

void tab_widget_item::main_set_connection()
{
    filter_set_connection();
}

// 1. filter

void tab_widget_item::filter_set_connection()
{
    // here we can only define some connection which is static
    // for connection which is defined by data, we need to define them in filter_reset_data
    for (auto i : filter_priority_check)
        connect(i, &QCheckBox::clicked, this, &tab_widget_item::filter_on_trival_check_clicked);
    for (auto i : filter_exist_check)
        connect(i, &QCheckBox::clicked, this, &tab_widget_item::filter_on_trival_check_clicked);
    connect(filter_other_check, &QCheckBox::clicked, this, &tab_widget_item::filter_on_other_check_clicked);
    connect(filter_upper_switch, &QClickableFigureLabel::clicked, this, &tab_widget_item::filter_refresh_layout);
    connect(filter_lower_switch, &QClickableFigureLabel::clicked, this, &tab_widget_item::filter_refresh_layout);
}

void tab_widget_item::filter_reset_data()
{
    // 1. check if other checkbox is pushed
    if (filter_other_check->isChecked())
    {
        filter_other_check->setChecked(false);
        filter_other_check->setEnabled(false);
        for (auto i : filter_priority_check)
            i->setChecked(true);
        for (auto i : filter_exist_check)
            i->setChecked(true);
    }

    // 2. empty what we have
    filter_map_mask.empty();
    filter_map_priority.empty();
    filter_map_exist.empty();
    for (QRightClickPushButton *i : filter_widget_button.values())
        if (i) delete i;
    filter_widget_button.empty();
    for (QRightClickPushButton *i : filter_table_button.values())
        if (i) delete i;
    filter_table_button.empty();

    // 3. set table and button
    QModelIndex index_user_data = user_data->index(0, 0);
    for (int row = 0; row < user_data->rowCount(index_user_data); ++row)
    {
        QModelIndex index_servant = user_data->index(row, 0, index_user_data);
        QString servant = user_data->data(index_servant, Qt::DisplayRole).toString();
        QStringList servant_list = servant.split("_");
        if (servant_list.at(0) != "servant") continue;
        int id = servant_list.at(1).toInt();
        Q_ASSERT((id > 0) && (id < SERVANT_ICON_NUMBER));
        QModelIndex index_status = user_data->item_find("status", index_servant);
        Q_ASSERT(index_status.isValid());
        // follow
        QModelIndex index_follow = user_data->item_find("follow", index_status);
        Q_ASSERT(index_follow.isValid());
        if (user_data->data(index_follow.siblingAtColumn(1), Qt::DisplayRole).toInt() < 0) continue;
        // priority
        QModelIndex index_priority = user_data->item_find("priority", index_status);
        Q_ASSERT(index_priority.isValid());
        filter_map_priority[id] = user_data->data(index_priority.siblingAtColumn(1), Qt::DisplayRole).toInt();
        // exist
        QModelIndex index_exist = user_data->item_find("exist", index_status);
        Q_ASSERT(index_exist.isValid());
        filter_map_exist[id] = user_data->data(index_exist.siblingAtColumn(1), Qt::DisplayRole).toInt() > 0;
        // mask
        filter_map_mask[id] = true;
        // button setting
        filter_widget_button[id] = new QRightClickPushButton(this);
        filter_widget_button.value(id)->text_save = servant_list.at(1);
        filter_widget_button.value(id)->setIcon(servant_icon_button_image->at(id));
        filter_widget_button.value(id)->setIconSize(QSize(69, 75));
        filter_widget_button.value(id)->setFixedSize(QSize(69, 75));
        connect(filter_widget_button.value(id), &QRightClickPushButton::rightClicked,
                this, &tab_widget_item::filter_on_button_right_clicked);
        connect(filter_widget_button.value(id), &QRightClickPushButton::clicked,
                this, &tab_widget_item::filter_interchange_table);
    }

    // finalize
    filter_refresh_table();
}

void tab_widget_item::filter_refresh_table()
{
    // 1. reconstruct mask
    qDebug() << filter_map_priority;
    qDebug() << filter_map_exist;
    for (int id : filter_map_mask.keys())
    {
        if (
               ((filter_map_priority.value(id) == 0 && filter_priority_check.at(0)->isChecked()) ||
                (filter_map_priority.value(id) == 1 && filter_priority_check.at(1)->isChecked()) ||
                (filter_map_priority.value(id) == 2 && filter_priority_check.at(2)->isChecked()) ||
                (filter_map_priority.value(id) == 3 && filter_priority_check.at(3)->isChecked()) ||
                (filter_map_priority.value(id) == 4 && filter_priority_check.at(4)->isChecked()) ||
                (filter_map_priority.value(id) == 5 && filter_priority_check.at(5)->isChecked())) &&
               ((filter_map_exist.value(id) && filter_exist_check.at(0)->isChecked()) ||
                (!filter_map_exist.value(id) && filter_exist_check.at(1)->isChecked()))
            )
            filter_map_mask[id] = true;
        else
            filter_map_mask[id] = false;
    }
    emit from_filter_mask_changed();
    // 2. apply widgets
    for (int id : filter_map_mask.keys())
    {
        if (filter_map_mask.value(id)) filter_upper_layout->addWidget(filter_widget_button.value(id));
        else filter_lower_layout->addWidget(filter_widget_button.value(id));
    }
}

void tab_widget_item::filter_refresh_condition()
{

}

void tab_widget_item::filter_interchange_table()
{
    QRightClickPushButton *button = qobject_cast<QRightClickPushButton*>(sender());
    int id = button->text_save.toInt();
    // 1. change mask
    bool origin_mask = filter_map_mask.value(id);
    filter_map_mask[id] = !origin_mask;
    emit from_filter_mask_changed();
    // 2. change widget item
    if (origin_mask)
    {
        filter_upper_layout->removeWidget(filter_widget_button.value(id));
        filter_lower_layout->addWidget(filter_widget_button.value(id));
    }
    else
    {
        filter_lower_layout->removeWidget(filter_widget_button.value(id));
        filter_upper_layout->addWidget(filter_widget_button.value(id));
    }
    // 3. change check box status
    for (auto i : filter_priority_check)
        i->setChecked(false);
    for (auto i : filter_exist_check)
        i->setChecked(false);
    filter_other_check->setChecked(true);
    filter_other_check->setEnabled(true);
}

void tab_widget_item::filter_refresh_layout()
{
    QClickableFigureLabel *label = qobject_cast<QClickableFigureLabel*>(sender());
    if (label == filter_upper_switch)
    {
        if (filter_upper_switch->click_status) filter_split_widget->replaceWidget(0, filter_upper_widget);
        else filter_split_widget->replaceWidget(0, filter_upper_table);
    }
    if (label == filter_lower_switch)
    {
        if (filter_lower_switch->click_status) filter_split_widget->replaceWidget(1, filter_lower_widget);
        else filter_split_widget->replaceWidget(1, filter_lower_table);
    }
}

void tab_widget_item::filter_on_trival_check_clicked()
{
    filter_other_check->setChecked(false);
    filter_other_check->setEnabled(false);
    filter_refresh_table();
}

void tab_widget_item::filter_on_other_check_clicked()
{
    for (auto i : filter_priority_check)
        i->setChecked(true);
    for (auto i : filter_exist_check)
        i->setChecked(true);
    filter_other_check->setEnabled(false);
    filter_other_check->setChecked(false);
    filter_refresh_table();
}

void tab_widget_item::filter_on_button_right_clicked()
{
    // WARNING!!! USING sender()!!!
    QRightClickPushButton *button = qobject_cast<QRightClickPushButton*>(sender());
    int id_number = button->text_save.toInt();

    resource_consume *consume_widget = new resource_consume(this);
    consume_widget->setMinimumHeight(600);
    consume_widget->setAttribute(Qt::WA_DeleteOnClose);
    consume_widget->setFixedWidth(consume_widget->sizeHint().width());
    connect(this, &tab_widget_item::from_filter_change_user_data, consume_widget, &resource_consume::data_transin);
    emit from_filter_change_user_data(
        ini_setting_data,
        &wiki_database,
        servant_icon_button_image,
        id_number,
        user_data);
    consume_widget->exec();
    emit signal_user_data_changed(user_data);
}
