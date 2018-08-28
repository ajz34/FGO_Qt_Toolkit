#include "tab_widget_item.h"

//--- Central Connection

void tab_widget_item::from_parent_database_changed(
    QVector<QString> path_pack,
    QVector<TreeModel*> tree_model,
    TreeModel* user_dat,
    QVector<QPixmap> *serv_img,
    TreeModel *event_item_dat,
    TreeModel *exchange_item_dat,
    QHash<QString, QPixmap> *event_figure_dat)
{
    ini_setting_data = path_pack;
    wiki_database = tree_model;
    user_data = user_dat;
    servant_icon_button_image = serv_img;
    event_item = event_item_dat;
    exchange_item = exchange_item_dat;
    event_figure = event_figure_dat;

    filter_reset_data();
    event_refresh();
}

void tab_widget_item::from_parent_user_data_loaded(TreeModel *user_dat)
{
    user_data = user_dat;
    filter_reset_data();
    event_refresh();
}

void tab_widget_item::main_set_connection()
{
    filter_set_connection();
    event_set_connection();
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
    filter_map_actual.empty();
    filter_map_ideal.empty();
    filter_map_costume.empty();
    filter_upper_model->clear();
    filter_lower_model->clear();
    for (QRightClickPushButton *i : filter_widget_button.values())
        if (i) delete i;
    filter_widget_button.empty();
    for (QRightClickPushButton *i : filter_table_button.values())
        if (i) delete i;
    filter_table_button.empty();
    // table model setting
    QStringList table_widget_model_header;
    table_widget_model_header
        << tr("Servant")      // 0
        << tr("ID")           // 1
        << tr("Priority")     // 2
        << tr("Exist")        // 3
        << tr("Ascension")    // 4
        << tr("Level")        // 5
        << tr("Skill_1")      // 6
        << tr("Skill_2")      // 7
        << tr("Skill_3")      // 8
        << tr("Costume")      // 9
    ;
    filter_upper_model->setHorizontalHeaderLabels(table_widget_model_header);
    filter_lower_model->setHorizontalHeaderLabels(table_widget_model_header);

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

        // more information needed for table view
        // actual
        QModelIndex index_actual = user_data->item_find("actual", index_servant);
        Q_ASSERT(index_actual.isValid());
        // data in index_actual
        {
            QVector<QModelIndex> index_vec(5);
            QVector<int> actual_vec;
            index_vec[0] = user_data->item_find("ascension", index_actual);
            index_vec[1] = user_data->item_find("level", index_actual);
            index_vec[2] = user_data->item_find("skill_1", index_actual);
            index_vec[3] = user_data->item_find("skill_2", index_actual);
            index_vec[4] = user_data->item_find("skill_3", index_actual);
            for (auto i : index_vec)
            {
                Q_ASSERT(i.isValid());
                actual_vec.push_back(user_data->data(i.siblingAtColumn(1), Qt::DisplayRole).toInt());
            }
            filter_map_actual[id] = actual_vec;
        }
        // ideal
        QModelIndex index_ideal = user_data->item_find("ideal", index_servant);
        Q_ASSERT(index_ideal.isValid());
        // data in index_ideal
        {
            QVector<QModelIndex> index_vec(5);
            QVector<int> ideal_vec;
            index_vec[0] = user_data->item_find("ascension", index_ideal);
            index_vec[1] = user_data->item_find("level", index_ideal);
            index_vec[2] = user_data->item_find("skill_1", index_ideal);
            index_vec[3] = user_data->item_find("skill_2", index_ideal);
            index_vec[4] = user_data->item_find("skill_3", index_ideal);
            for (auto i : index_vec)
            {
                Q_ASSERT(i.isValid());
                ideal_vec.push_back(user_data->data(i.siblingAtColumn(1), Qt::DisplayRole).toInt());
            }
            filter_map_ideal[id] = ideal_vec;
        }
        // costume
        QModelIndex index_costume = user_data->item_find("costume", index_servant);
        if (index_costume.isValid())
        {
            QVector<int> ideal_vec;
            for (int i = 0; i < user_data->rowCount(index_costume); ++i)
                ideal_vec.push_back(user_data->data(user_data->index(i, 1, index_costume), Qt::DisplayRole).toInt());
            filter_map_costume[id] = ideal_vec;
        }

        // insert table contents
        /*
        table_widget_model_header
            << tr("Servant")      // 0
            << tr("ID")           // 1
            << tr("Priority")     // 2
            << tr("Exist")        // 3
            << tr("Ascension")    // 4
            << tr("Level")        // 5
            << tr("Skill_1")      // 6
            << tr("Skill_2")      // 7
            << tr("Skill_3")      // 8
            << tr("Costume")      // 9
        */
        int model_row = filter_upper_model->rowCount();
        // id
        {
            auto *item = new QStandardItem;
            item->setData(id, Qt::DisplayRole);
            item->setEditable(false);
            filter_upper_model->setItem(model_row, 1, item);
        }
        // priority
        {
            auto *item = new QStandardItem;
            item->setData(filter_map_priority.value(id),
                          Qt::DisplayRole);
            item->setEditable(false);
            filter_upper_model->setItem(model_row, 2, item);
        }
        // exist
        {
            auto *item = new QStandardItem;
            item->setData((filter_map_exist.value(id) ? "Yes" : ""),
                          Qt::DisplayRole);
            item->setEditable(false);
            filter_upper_model->setItem(model_row, 3, item);
        }
        // ascension
        {
            auto *item = new QStandardItem;
            item->setData(QVariant(filter_map_actual.value(id).at(0)).toString() + "→" +
                          QVariant(filter_map_ideal.value(id).at(0)).toString(),
                          Qt::DisplayRole);
            item->setEditable(false);
            filter_upper_model->setItem(model_row, 4, item);
        }
        // level
        {
            auto *item = new QStandardItem;
            item->setData(QVariant(filter_map_actual.value(id).at(1)).toString() + "→" +
                          QVariant(filter_map_ideal.value(id).at(1)).toString(),
                          Qt::DisplayRole);
            item->setEditable(false);
            filter_upper_model->setItem(model_row, 5, item);
        }
        // skill_1
        {
            auto *item = new QStandardItem;
            item->setData(QVariant(filter_map_actual.value(id).at(2)).toString() + "→" +
                          QVariant(filter_map_ideal.value(id).at(2)).toString(),
                          Qt::DisplayRole);
            item->setEditable(false);
            filter_upper_model->setItem(model_row, 6, item);
        }
        // skill_2
        {
            auto *item = new QStandardItem;
            item->setData(QVariant(filter_map_actual.value(id).at(3)).toString() + "→" +
                          QVariant(filter_map_ideal.value(id).at(3)).toString(),
                          Qt::DisplayRole);
            item->setEditable(false);
            filter_upper_model->setItem(model_row, 7, item);
        }
        // skill_3
        {
            auto *item = new QStandardItem;
            item->setData(QVariant(filter_map_actual.value(id).at(4)).toString() + "→" +
                          QVariant(filter_map_ideal.value(id).at(4)).toString(),
                          Qt::DisplayRole);
            item->setEditable(false);
            filter_upper_model->setItem(model_row, 8, item);
        }
        // costume
        QString str_costume = "";
        for (int i = 0; i < filter_map_costume.value(id).size(); ++i)
        {
            if (filter_map_costume.value(id).at(i) <= 0) break;
            if (str_costume.isEmpty())
                str_costume += QVariant(i + 1).toString();
            else
                str_costume += (", " + QVariant(i + 1).toString());
        }
        {
            auto *item = new QStandardItem;
            item->setData(str_costume, Qt::DisplayRole);
            item->setEditable(false);
            filter_upper_model->setItem(model_row, 9, item);
        }
    }

    // finalize
    filter_refresh_table();
}

void tab_widget_item::filter_refresh_table()
{
    // 1. reconstruct mask
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
    // 3. apply model
    QVector<int> upper_rows_to_delete;
    for (int row = 0; row < filter_upper_model->rowCount(); ++row)
    {
        int id = filter_upper_model->item(row, 1)->data(Qt::DisplayRole).toInt();
        filter_upper_table->setIndexWidget(filter_upper_model->index(row, 0), nullptr);
        if (!filter_map_mask.value(id)) upper_rows_to_delete.push_front(row); // large row at first
    }
    QVector<int> lower_rows_to_delete;
    for (int row = 0; row < filter_lower_model->rowCount(); ++row)
    {
        int id = filter_lower_model->item(row, 1)->data(Qt::DisplayRole).toInt();
        filter_lower_table->setIndexWidget(filter_lower_model->index(row, 0), nullptr);
        if (filter_map_mask.value(id)) lower_rows_to_delete.push_front(row); // large row at first
    }
    for (int row : upper_rows_to_delete)
        filter_lower_model->appendRow(filter_upper_model->takeRow(row));
    for (int row : lower_rows_to_delete)
        filter_upper_model->appendRow(filter_lower_model->takeRow(row));
    // 4. set button
    for (int row = 0; row < filter_upper_model->rowCount(); ++row)
    {
        int id = filter_upper_model->item(row, 1)->data(Qt::DisplayRole).toInt();
        QRightClickPushButton *button = new QRightClickPushButton(this);
        button->text_save = QVariant(id).toString();
        button->setIcon((*servant_icon_button_image)[id]);
        button->setIconSize(QSize(69, 75));
        button->setFixedSize(QSize(69, 75));
        filter_upper_table->setIndexWidget(filter_upper_model->index(row, 0), button);
        connect(button, &QRightClickPushButton::rightClicked,
                this, &tab_widget_item::filter_on_button_right_clicked);
        connect(button, &QRightClickPushButton::clicked,
                this, &tab_widget_item::filter_interchange_table);
    }
    for (int row = 0; row < filter_lower_model->rowCount(); ++row)
    {
        int id = filter_lower_model->item(row, 1)->data(Qt::DisplayRole).toInt();
        QRightClickPushButton *button = new QRightClickPushButton(this);
        button->text_save = QVariant(id).toString();
        button->setIcon((*servant_icon_button_image)[id]);
        button->setIconSize(QSize(69, 75));
        button->setFixedSize(QSize(69, 75));
        filter_lower_table->setIndexWidget(filter_lower_model->index(row, 0), button);
        connect(button, &QRightClickPushButton::rightClicked,
                this, &tab_widget_item::filter_on_button_right_clicked);
        connect(button, &QRightClickPushButton::clicked,
                this, &tab_widget_item::filter_interchange_table);
    }
    filter_upper_table->resizeColumnsToContents();
    filter_upper_table->resizeRowsToContents();
    filter_lower_table->resizeColumnsToContents();
    filter_lower_table->resizeRowsToContents();

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
    // 3. change table row
    if (origin_mask)
    {
        int row_to_swap = -1;
        // first we need to find which row it is
        for (int row = 0; row < filter_upper_model->rowCount(); ++row)
        {
            if (filter_upper_model->item(row, 1)->data(Qt::DisplayRole).toInt() == id)
            {
                row_to_swap = row;
                break;
            }
        }
        filter_lower_model->appendRow(filter_upper_model->takeRow(row_to_swap));
        QRightClickPushButton *button = new QRightClickPushButton(this);
        button->text_save = QVariant(id).toString();
        button->setIcon((*servant_icon_button_image)[id]);
        button->setIconSize(QSize(69, 75));
        button->setFixedSize(QSize(69, 75));
        filter_lower_table->setIndexWidget(filter_lower_model->index(filter_lower_model->rowCount() - 1, 0), button);
        connect(button, &QRightClickPushButton::rightClicked,
                this, &tab_widget_item::filter_on_button_right_clicked);
        connect(button, &QRightClickPushButton::clicked,
                this, &tab_widget_item::filter_interchange_table);
    }
    else
    {
        int row_to_swap = -1;
        // first we need to find which row it is
        for (int row = 0; row < filter_lower_model->rowCount(); ++row)
        {
            if (filter_lower_model->item(row, 1)->data(Qt::DisplayRole).toInt() == id)
            {
                row_to_swap = row;
                break;
            }
        }
        filter_upper_model->appendRow(filter_lower_model->takeRow(row_to_swap));
        QRightClickPushButton *button = new QRightClickPushButton(this);
        button->text_save = QVariant(id).toString();
        button->setIcon((*servant_icon_button_image)[id]);
        button->setIconSize(QSize(69, 75));
        button->setFixedSize(QSize(69, 75));
        filter_upper_table->setIndexWidget(filter_upper_model->index(filter_upper_model->rowCount() - 1, 0), button);
        connect(button, &QRightClickPushButton::rightClicked,
                this, &tab_widget_item::filter_on_button_right_clicked);
        connect(button, &QRightClickPushButton::clicked,
                this, &tab_widget_item::filter_interchange_table);
    }
    filter_upper_table->resizeColumnsToContents();
    filter_upper_table->resizeRowsToContents();
    filter_lower_table->resizeColumnsToContents();
    filter_lower_table->resizeRowsToContents();
    // 4. change check box status
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

// 2. event

void tab_widget_item::event_set_connection()
{

}

void tab_widget_item::event_refresh()
{
    // re-initialize variables and widgets
    event_data_item = QHash<QString, QVector<QVector<int>>>{};
    event_data_date = QHash<QString, QVector<QDate>>{};
    event_data_type = QHash<QString, QVector<int>>{};
    event_user_type = QHash<QString, QVector<int>>{};
    event_seq = QHash<QString, int>{};
    event_sorted_events = QVector<QString>{};
    // we should know that, since all items are reparented to event_upper_vec,
    // we only need to delete event_upper_vec, the other widgets should also be freed
    for (auto i : event_upper_vec) if (i) delete i;

    // 1. read the whole data imported from mainwindow
    // however, if event_item = 0, nothing should happen here
    if (event_item == nullptr) return;
    {
        QModelIndex index_root = event_item->index(0, 0);
        Q_ASSERT(index_root.isValid());
        if (event_item->rowCount(index_root) == 0) return;
        for (int row = 0; row < event_item->rowCount(index_root); ++row)
        {
            QModelIndex index_name = event_item->index(row, 0, index_root);
            QModelIndex index_date_init = event_item->item_find("date_init", index_name);
            QModelIndex index_date_end = event_item->item_find("date_end", index_name);
            QModelIndex index_event = event_item->item_find("event", index_name);
            // since every event should have "event" list of items, as well as "date_init" and "date_end"
            // so these index must be exist
            Q_ASSERT(index_event.isValid() && index_date_init.isValid() && index_date_end.isValid());
            QString event_name = event_item->data(index_name, Qt::DisplayRole).toString();
            // init space for hash mappings
            event_data_type[event_name] = QVector<int>(3, -1);
            event_data_item[event_name] = QVector<QVector<int>>(5, QVector<int>{});
            // date process
            QStringList str_date_init = event_item->data(index_date_init.siblingAtColumn(1), Qt::DisplayRole).toString().split("-");
            QStringList str_date_end = event_item->data(index_date_end.siblingAtColumn(1), Qt::DisplayRole).toString().split("-");
            Q_ASSERT((str_date_init.size() == 3) && (str_date_end.size() == 3));
            event_data_date[event_name] = QVector<QDate>
            {
                QDate(QVariant(str_date_init[0]).toInt(), QVariant(str_date_init[1]).toInt(), QVariant(str_date_init[2]).toInt()),
                QDate(QVariant(str_date_end[0]).toInt(), QVariant(str_date_end[1]).toInt(), QVariant(str_date_end[2]).toInt())
            };
            // process event
            event_data_item[event_name][0] = util_read_items(user_data, index_event);
            event_data_type[event_name][0] = 1;
            // process infinity_ / infinity-
            // first we judge what's type of infinity is, then we return to to the processing step
            for (int sub_row = 0; sub_row < event_item->rowCount(index_name); ++sub_row)
            {
                QModelIndex index_sub = event_item->index(sub_row, 0, index_name);
                QString sub_name = event_item->data(index_sub, Qt::DisplayRole).toString();
                QStringList sub_name_char_under = sub_name.split("_");
                if ((sub_name_char_under.size() == 2) && (sub_name_char_under.at(0) == "infinity"))
                {
                    int sub_val = sub_name_char_under.at(1).toInt();
                    if (sub_val > event_data_type[event_name].at(1))
                        event_data_type[event_name][1] = sub_val;
                }
                QStringList sub_name_char_minus = sub_name.split("-");
                if ((sub_name_char_minus.size() == 2) && (sub_name_char_minus.at(0) == "infinity"))
                {
                    int sub_val = sub_name_char_minus.at(1).toInt();
                    if (sub_val > event_data_type[event_name].at(1))
                        event_data_type[event_name][2] = sub_val;
                }
            }
            // process infinity_
            if (event_data_type.value(event_name).at(1) > 0)
            {
                QModelIndex index_inf1_1 = event_item->item_find("infinity_1", index_name);
                QModelIndex index_inf1_2 = event_item->item_find("infinity_" + QVariant(event_data_type.value(event_name).at(1)).toString(), index_name);
                event_data_item[event_name][1] = util_read_items(user_data, index_inf1_1);
                event_data_item[event_name][2] = util_read_items(user_data, index_inf1_2);
            }
            // process infinity-
            if (event_data_type.value(event_name).at(2) > 0)
            {
                QModelIndex index_inf2_1 = event_item->item_find("infinity-1", index_name);
                QModelIndex index_inf2_2 = event_item->item_find("infinity-" + QVariant(event_data_type.value(event_name).at(2)).toString(), index_name);
                event_data_item[event_name][3] = util_read_items(user_data, index_inf2_1);
                event_data_item[event_name][4] = util_read_items(user_data, index_inf2_2);
            }
        }
    }
    qDebug() << event_data_type;

    // 2. sort events by their starting date
    {
        QHash<QString, QVector<QDate>>::const_iterator it = event_data_date.constBegin();
        Q_ASSERT(it != event_data_date.constEnd()); // it is estimated that we have at least one event
        event_sorted_events.push_back(it.key());
        ++it;
        while (it != event_data_date.constEnd())
        {
            QDate cur_date = it.value().at(1);
            int insert_key = -1;
            for (int i = 0; i < event_sorted_events.size(); ++i)
            {
                if (cur_date < event_data_date.value(event_sorted_events.at(i)).at(0))
                {
                    insert_key = i;
                    break;
                }
            }
            if (insert_key == -1) insert_key = event_sorted_events.size();
            event_sorted_events.insert(insert_key, it.key());
            ++it;
        }
        qDebug() << event_sorted_events;
        for (int i = 0; i < event_sorted_events.size(); ++i)
        {
            event_seq[event_sorted_events.at(i)] = i;
        }
        qDebug() << event_seq;
    }

    // 3. prepare connection
    // this is probably a big role, and I decided to let this part an individual function
    event_set_after_layout();
}

void tab_widget_item::event_set_after_layout()
{
    // initialize widget numbers
    {
        int number = event_seq.size();
        event_upper_vec = QVector<QWidget*>(number, nullptr);
        event_upper_figure = QVector<QPushButton*>(number, nullptr);
        event_upper_follow = QVector<QCheckBox*>(number, nullptr);
        event_upper_inf1 = QVector<QLabel*>(number, nullptr);
        event_upper_inf1_spin = QVector<QSpinBox*>(number, nullptr);
        event_upper_inf2 = QVector<QLabel*>(number, nullptr);
        event_upper_inf2_spin = QVector<QSpinBox*>(number, nullptr);
    }

    // setup widgets
    {
        for (int i = 0; i < event_sorted_events.size(); ++i)
        {
            // initialize
            event_upper_figure[i] = new QPushButton;
            event_upper_vec[i] = new QWidget;
            // figure
            event_upper_figure.at(i)->setIcon(event_figure->value(event_sorted_events.at(i), QPixmap()));
            event_upper_figure.at(i)->setIconSize(QSize(400, 150));
            event_upper_figure.at(i)->setFixedSize(QSize(400, 150));

            auto layout = new QGridLayout;
            layout->addWidget(event_upper_figure.at(i));
            event_upper_vec.at(i)->setLayout(layout);

            event_upper_layout->addWidget(event_upper_vec.at(i));
        }
    }
}

void tab_widget_item::event_on_follow_clicked()
{

}

void tab_widget_item::event_on_figure_clicked()
{

}

void tab_widget_item::event_on_spin_changed()
{

}

void tab_widget_item::event_on_date_changed()
{

}








