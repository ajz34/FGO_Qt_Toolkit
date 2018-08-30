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
    event_reset();
    month_reset();
}

void tab_widget_item::from_parent_user_data_loaded(TreeModel *user_dat)
{
    user_data = user_dat;
    filter_reset_data();
    event_refresh();
    month_refresh();
}

void tab_widget_item::from_parent_user_servant_data_loaded(TreeModel *user_dat)
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
    // filter_map_mask = QMap<int, bool>{};
    filter_map_priority = QMap<int, int>{};
    filter_map_exist = QMap<int, bool>{};
    filter_map_actual = QMap<int, QVector<int>>{};
    filter_map_ideal = QMap<int, QVector<int>>{};
    filter_map_costume = QMap<int, QVector<int>>{};
    filter_upper_model->clear();
    filter_lower_model->clear();
    // filter_widget_button = QMap<int, QRightClickPushButton*>{};
    // filter_table_button = QMap<int, QRightClickPushButton*>{};
    // I don't know where I have deleted those buttons...
    // maybe? since I assigned these buttons to flowlayout, I need to remove them out the flowlayout
    // to delete those buttons from memory
    // so reset filter_map_mask should be the last step?
    for (int i : filter_map_mask.keys())
        //     if (i) delete i;
    {
        if (filter_map_mask.value(i))
            filter_upper_layout->removeWidget(filter_widget_button.value(i));
        else
            filter_lower_layout->removeWidget(filter_widget_button.value(i));
        delete filter_widget_button.value(i);
    }
    filter_widget_button.empty();
    filter_table_button.empty();
    filter_map_mask = QMap<int, bool>{};

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
        if (user_data->data(index_follow.siblingAtColumn(1), Qt::DisplayRole).toInt() <= 0) continue;
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
    emit signal_user_servant_data_changed(user_data);
}

// 2. event

void tab_widget_item::event_reset()
{
    // this function is to reset this widget
    // if just refresh on user_data reloaded, use event_refresh.
    // re-initialize variables and widgets
    event_data_item = QHash<QString, QVector<QVector<int>>>{};
    event_data_date = QHash<QString, QVector<QDate>>{};
    event_data_type = QHash<QString, QVector<int>>{};
    event_user_type = QHash<QString, QVector<int>>{};
    event_seq = QHash<QString, int>{};
    event_sorted_events = QVector<QString>{};
    // we should know that, since all items are reparented to event_upper_vec,
    // we only need to delete items in flowlayout, the other widgets should also be freed
    {
        for (auto i : event_upper_vec)
        {
            event_upper_layout->removeWidget(i);
            delete i;
        }
        event_upper_vec = QVector<QWidget*>{};
        event_upper_figure = QVector<QPushButton*>{};
        event_upper_follow = QVector<QCheckBox*>{};
        event_upper_inf1 = QVector<QLabel*>{};
        event_upper_inf1_spin = QVector<QSpinBox*>{};
        event_upper_inf2 = QVector<QLabel*>{};
        event_upper_inf2_spin = QVector<QSpinBox*>{};
        for (auto i : event_lower_group)
        {
            if (i) delete i;
            i = nullptr;
        }
        // take from de-construct function of FlowLayout class
        QLayoutItem *item;
        while ((item = event_upper_layout->takeAt(0)))
            delete item;
        while ((item = event_lower_layout->takeAt(0)))
            delete item;
    }
    // we need to first initialize event_lower_group, since it is not initialized when data loaded
    event_lower_group = QVector<QGroupBox*>(5, nullptr);

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
                    if (sub_val > event_data_type[event_name].at(2))
                        event_data_type[event_name][2] = sub_val;
                }
            }
            // process infinity_
            // maybe redundant to define the same vector when lottery only has one pattern,
            // however, it can be convenient to implement calculation in event_on_object_responsed
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
    for (int i = 0; i < event_sorted_events.size(); ++i)
    {
        // initialize
        event_upper_vec[i] = new QWidget;
        event_upper_figure[i] = new QPushButton;
        event_upper_follow[i] = new QCheckBox;
        event_upper_inf1[i] = new QLabel;
        event_upper_inf2[i] = new QLabel;
        event_upper_inf1_spin[i] = new QSpinBox;
        event_upper_inf2_spin[i] = new QSpinBox;
        // figure
        event_upper_figure.at(i)->setIcon(event_figure->value(event_sorted_events.at(i), QPixmap()));
        event_upper_figure.at(i)->setIconSize(QSize(400, 150));
        event_upper_figure.at(i)->setFixedSize(QSize(400, 150));
        // follow
        event_upper_follow.at(i)->setText(tr("Follow"));
        // inf
        event_upper_inf1.at(i)->setText(tr("Lottery 1"));
        event_upper_inf2.at(i)->setText(tr("Lottery 2"));
        event_upper_inf1_spin.at(i)->setMinimum(0);
        event_upper_inf2_spin.at(i)->setMinimum(0);
        // hide inf if lottery does not exist
        // assert: all the events have "event" entry
        // inf1
        if (event_data_type.value(event_sorted_events.at(i)).at(1) <= 0)
        {
            event_upper_inf1.at(i)->setHidden(true);
            event_upper_inf1_spin.at(i)->setHidden(true);
        }
        if (event_data_type.value(event_sorted_events.at(i)).at(2) <= 0)
        {
            event_upper_inf2.at(i)->setHidden(true);
            event_upper_inf2_spin.at(i)->setHidden(true);
        }

        // layout
        auto layout_1 = new QGridLayout;
        auto layout_2 = new QHBoxLayout;

        layout_1->addWidget(event_upper_figure.at(i), 0, 0);
        layout_2->addWidget(event_upper_follow.at(i));
        layout_2->addStretch();
        layout_2->addWidget(event_upper_inf1.at(i));
        layout_2->addWidget(event_upper_inf1_spin.at(i));
        layout_2->addStretch();
        layout_2->addWidget(event_upper_inf2.at(i));
        layout_2->addWidget(event_upper_inf2_spin.at(i));
        layout_2->addStretch();
        layout_1->addLayout(layout_2, 1, 0);
        event_upper_vec.at(i)->setLayout(layout_1);

        event_upper_layout->addWidget(event_upper_vec.at(i));

        // connection
        connect(event_upper_figure.at(i), &QPushButton::clicked, this, &tab_widget_item::event_on_figure_clicked);
        connect(event_upper_follow.at(i), &QCheckBox::toggled, this, &tab_widget_item::event_on_follow_clicked_grayout_figure);
    }

    // this is the end of event_reset
    //-all widgets and connections should be carefully prepared before this line
    // after then, we read the user_data and check every entry in the database list
    //-at this time, we don't connect buttons that could change the user_data value,
    // that's because if connected, then if we toggle some icons or checkboxes,
    // that will make the whole event view try to recalculate the items expected
    event_refresh();
}

void tab_widget_item::event_refresh()
{
    // 1. reset memory
    event_user_type = QHash<QString, QVector<int>>{};
    event_user_expect = QVector<long long>{};
    for (QString s : event_sorted_events)
    {
        event_user_type[s] = QVector<int>{0, 0, 0};
    }
    // reset connection
    // this step is essetial, because when we assigning user_data to objects, these connection may well conflict
    // with each other; when assigning over, connection is restablished, and we need to do a re-calculation of items
    for (int event_id = 0; event_id < event_sorted_events.size(); ++event_id)
    {
        disconnect(event_upper_follow.at(event_id), &QCheckBox::toggled, this, &tab_widget_item::event_on_follow_clicked);
        disconnect(event_upper_inf1_spin.at(event_id), QOverload<int>::of(&QSpinBox::valueChanged), this, &tab_widget_item::event_on_spin_changed);
        disconnect(event_upper_inf2_spin.at(event_id), QOverload<int>::of(&QSpinBox::valueChanged), this, &tab_widget_item::event_on_spin_changed);
        disconnect(event_date_widget, &QDateEdit::dateChanged, this, QOverload<>::of(&tab_widget_item::event_on_date_changed));
    }

    // 2. read user_data
    // if no entry "event", create one
    QModelIndex index_root = user_data->index(0, 0);
    Q_ASSERT(index_root.isValid());
    {
        QModelIndex index_event = user_data->item_find("event", index_root);
        if (!index_event.isValid())
        {
            int i = user_data->rowCount(index_root);
            user_data->insertRow(i, index_root);
            QModelIndex ind = user_data->index(i, 0, index_root);
            user_data->setData(ind, "event");
            user_data->setModified(true);
        }
    }
    QModelIndex index_event = user_data->item_find("event", index_root);
    Q_ASSERT(index_event.isValid());

    // then read the information, by key of event_sorted_events
    for (int row = 0; row < user_data->rowCount(index_event); ++row)
    {
        QModelIndex index_cur_event = user_data->index(row, 0, index_event);
        QString str_cur_event = user_data->data(index_cur_event, Qt::DisplayRole).toString();
        int event_id = event_seq.value(str_cur_event, -1);
        if (event_id == -1)
        {
            if (str_cur_event == "date")
            {
                // assign date
                // date is assigned as yy-mm-dd
                QStringList date_list = user_data->data(index_cur_event.siblingAtColumn(1), Qt::DisplayRole).toString().split("-");
                if (date_list.size() != 3)
                {
                    // if date is not correct, give an initialized one
                    user_data->setData(index_cur_event.siblingAtColumn(1), event_date_widget->date().toString("yyyy-MM-dd"));
                    user_data->setModified(true);
                    continue;
                }
                event_date_widget->setDate(QDate(date_list.at(0).toInt(), date_list.at(1).toInt(), date_list.at(2).toInt()));
                // since this is not an event, we need to ignore the following code in this loop
                continue;
            }
            else
                continue; // no such event, simply ignore
        }
        QModelIndex index_cur_eve = user_data->item_find("event", index_cur_event);
        QModelIndex index_cur_inf1 = user_data->item_find("inf1", index_cur_event);
        QModelIndex index_cur_inf2 = user_data->item_find("inf2", index_cur_event);
        Q_ASSERT(index_cur_eve.isValid() && index_cur_inf1.isValid() && index_cur_inf2.isValid());
        // write to event_user_type
        event_user_type[str_cur_event][0] = user_data->data(index_cur_eve.siblingAtColumn(1), Qt::DisplayRole).toInt();
        event_user_type[str_cur_event][1] = user_data->data(index_cur_inf1.siblingAtColumn(1), Qt::DisplayRole).toInt();
        event_user_type[str_cur_event][2] = user_data->data(index_cur_inf2.siblingAtColumn(1), Qt::DisplayRole).toInt();
    }

    // 3. assigning values
    for (int event_id = 0; event_id < event_sorted_events.size(); ++event_id)
    {
        // write to object controls
        event_upper_follow.at(event_id)->setChecked(event_user_type[event_sorted_events.at(event_id)][0] > 0);
        event_upper_follow.at(event_id)->toggled(event_user_type[event_sorted_events.at(event_id)][0] > 0); // set grayscale of figures
        event_upper_inf1_spin.at(event_id)->setValue(event_user_type[event_sorted_events.at(event_id)][1]);
        event_upper_inf2_spin.at(event_id)->setValue(event_user_type[event_sorted_events.at(event_id)][2]);
    }

    // 4. connect those objects to slots
    for (int event_id = 0; event_id < event_sorted_events.size(); ++event_id)
    {
        connect(event_upper_follow.at(event_id), &QCheckBox::toggled, this, &tab_widget_item::event_on_follow_clicked);
        connect(event_upper_inf1_spin.at(event_id), QOverload<int>::of(&QSpinBox::valueChanged), this, &tab_widget_item::event_on_spin_changed);
        connect(event_upper_inf2_spin.at(event_id), QOverload<int>::of(&QSpinBox::valueChanged), this, &tab_widget_item::event_on_spin_changed);
        connect(event_date_widget, &QDateEdit::dateChanged, this, QOverload<>::of(&tab_widget_item::event_on_date_changed));
    }

    // 5. date process
    // in this program, we sort events by initial date, and ignore events by final date
    // if date is not created, here we create a date
    {
        QModelIndex index_event = user_data->item_find("event", index_root);
        Q_ASSERT(index_event.isValid());
        QModelIndex index_date = user_data->item_find("date", index_event);
        if (!index_date.isValid())
        {
            // create one here
            Q_ASSERT(user_data->insertRow(user_data->rowCount(index_event), index_event));
            user_data->setData(user_data->index(user_data->rowCount(index_event) - 1, 0, index_event), "date");
            QModelIndex index_date = user_data->item_find("date", index_event);
            Q_ASSERT(index_date.isValid());
            user_data->setData(index_date.siblingAtColumn(1), event_date_widget->date().toString("yyyy-MM-dd"));
            user_data->setModified(true);
        }
        // after then, we need to connect to update date widget, to filter the events before this very date
        event_on_date_changed(true);
    }

    // 6. re-calculate
    event_on_object_responsed();
}

void tab_widget_item::event_on_follow_clicked_grayout_figure()
{
    // on follow clicked, we gray out figure
    // for follow clicked, change the user_data and event_user_expect, go to event_on_follow_clicked()
    // 1. get the index of the click
    QCheckBox *checkbox = qobject_cast<QCheckBox*>(sender());
    int event_id = event_upper_follow.indexOf(checkbox);
    Q_ASSERT(event_id != -1);
    if (checkbox->isChecked())
    {
        // image
        event_upper_figure.at(event_id)->setIcon(event_figure->value(event_sorted_events.at(event_id), QPixmap()));
        // lottery
        event_upper_inf1_spin.at(event_id)->setEnabled(true);
        event_upper_inf2_spin.at(event_id)->setEnabled(true);
    }
    else
    {
        // image gray scale
        // we don't want to disable this push button; however, we want to gray scale that
        // since Qt treats alpha-only figures as black, we need to paint white first,
        // then draw the event figure on that paint
        // this may time consuming step; however, figures are not so many
        // https://stackoverflow.com/questions/1549634/qt-qimage-always-saves-transparent-color-as-black
        QImage image1(event_figure->value(event_sorted_events.at(event_id)).toImage());
        QImage image2(image1.size(), QImage::Format_Grayscale8);
        image2.fill(QColor(Qt::white));
        QPainter painter(&image2);
        painter.drawImage(0, 0, image1);
        event_upper_figure.at(event_id)->setIcon(QPixmap::fromImage(image2));
        // lottery
        event_upper_inf1_spin.at(event_id)->setDisabled(true);
        event_upper_inf1_spin.at(event_id)->setValue(0);
        event_upper_inf2_spin.at(event_id)->setDisabled(true);
        event_upper_inf2_spin.at(event_id)->setValue(0);
    }
}

void tab_widget_item::event_on_figure_clicked()
{
    // 1. delete what group have
    for (auto i : event_lower_group)
        if (i) delete i;
    event_lower_group = QVector<QGroupBox*>(5, nullptr);

    // 2. assign and layout
    // first, we need to get the event_id
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    int event_id = event_upper_figure.indexOf(button);
    Q_ASSERT(event_id != -1);
    // event
    if (event_data_type.value(event_sorted_events.at(event_id)).at(0) == 1)
    {
        event_lower_group[0] = new QGroupBox;
        event_lower_group.at(0)->setTitle(tr("Event"));
        event_show_items(event_lower_group.at(0), event_data_item.value(event_sorted_events.at(event_id)).at(0));
        event_lower_layout->addWidget(event_lower_group.at(0));
    }
    // inf1
    if (event_data_type.value(event_sorted_events.at(event_id)).at(1) >= 1)
    {
        event_lower_group[1] = new QGroupBox;
        event_lower_group.at(1)->setTitle(tr("Lottery 1"));
        event_show_items(event_lower_group.at(1), event_data_item.value(event_sorted_events.at(event_id)).at(1));
        event_lower_layout->addWidget(event_lower_group.at(1));
        if (event_data_type.value(event_sorted_events.at(event_id)).at(1) > 1)
        {
            event_lower_group[2] = new QGroupBox;
            event_lower_group.at(2)->setTitle(tr("Lottery 1 after ")
                                              + QVariant(event_data_type.value(event_sorted_events.at(event_id)).at(1) - 1).toString()
                                              + tr(" times"));
            event_show_items(event_lower_group.at(2), event_data_item.value(event_sorted_events.at(event_id)).at(2));
            event_lower_layout->addWidget(event_lower_group.at(2));
        }
    }
    // inf2
    if (event_data_type.value(event_sorted_events.at(event_id)).at(2) >= 1)
    {
        event_lower_group[3] = new QGroupBox;
        event_lower_group.at(3)->setTitle(tr("Lottery 2"));
        event_show_items(event_lower_group.at(3), event_data_item.value(event_sorted_events.at(event_id)).at(3));
        event_lower_layout->addWidget(event_lower_group.at(3));
        if (event_data_type.value(event_sorted_events.at(event_id)).at(2) > 1)
        {
            event_lower_group[4] = new QGroupBox;
            event_lower_group.at(4)->setTitle(tr("Lottery 2 after ")
                                              + QVariant(event_data_type.value(event_sorted_events.at(event_id)).at(2) - 1).toString()
                                              + tr(" times"));
            event_show_items(event_lower_group.at(4), event_data_item.value(event_sorted_events.at(event_id)).at(4));
            event_lower_layout->addWidget(event_lower_group.at(4));
        }
    }
}

void tab_widget_item::event_show_items(QGroupBox *group, const QVector<int> &vec)
{
    Q_ASSERT(vec.size() == GLOB::LIST_ITEM.size());
    // prepare items
    auto group_layout = new FlowLayout;
    for (int i = 0; i < vec.size(); ++i)
    {
        if (vec.at(i) > 0)
        {
            auto item = new QLabel;
            auto aquire = new QLabel;
            item->setPixmap(GLOB::MAP_ITEM.value(GLOB::LIST_ITEM.at(i)).scaled(46, 50));
            QFont font;
            font.setPixelSize(15);
            font.setFamily("Arial");
            font.setStyleHint(QFont::SansSerif);
            font.setBold(true);
            aquire->setFont(font);
            aquire->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
            aquire->setText(resource_consume::consume_int(vec.at(i)));
            auto layout = new QGridLayout;
            auto widget = new QWidget;
            layout->addWidget(item, 0, 0);
            layout->addWidget(aquire, 1, 0);
            widget->setLayout(layout);
            group_layout->addWidget(widget);
        }
    }
    group->setLayout(group_layout);
}

void tab_widget_item::event_on_follow_clicked()
{
    // 1. get the index of the click
    QCheckBox *checkbox = qobject_cast<QCheckBox*>(sender());
    int event_id = event_upper_follow.indexOf(checkbox);
    Q_ASSERT(event_id != -1);

    // 2. write to the event_user_type
    // since value should be changed in spinbox, event_on_spin_changed should have effect when calling setvalue
    // we may not have to change 1, 2 entry of event_user_type[event_sorted_events.at(event_id)]
    if (checkbox->isChecked())
        event_user_type[event_sorted_events.at(event_id)][0] = 1;
    else
        event_user_type[event_sorted_events.at(event_id)][0] = 0;

    // 2.9 disable objects before make change to user_data
    if (!checkbox->isChecked())
    {
        event_upper_inf1_spin.at(event_id)->setValue(0);
        event_upper_inf2_spin.at(event_id)->setValue(0);
        event_upper_inf1_spin.at(event_id)->setDisabled(true);
        event_upper_inf2_spin.at(event_id)->setDisabled(true);
    }

    // 3. make change to user_data
    if (checkbox->isChecked())
    {
        QModelIndex index_event = user_data->item_find("event", user_data->index(0, 0));
        Q_ASSERT(index_event.isValid());
        QModelIndex index_cur = user_data->item_find(event_sorted_events.at(event_id), index_event);
        if (!index_cur.isValid())
        {
            int row_to_append = user_data->rowCount(index_event);
            user_data->insertRow(row_to_append, index_event);
            user_data->setData(user_data->index(row_to_append, 0, index_event), event_sorted_events.at(event_id));
            QModelIndex index_cur = user_data->item_find(event_sorted_events.at(event_id), index_event);
            Q_ASSERT(index_cur.isValid());
            user_data->insertRows(0, 3, index_cur);
            user_data->setData(user_data->index(0, 0, index_cur), "event");
            user_data->setData(user_data->index(1, 0, index_cur), "inf1");
            user_data->setData(user_data->index(2, 0, index_cur), "inf2");
            user_data->setData(user_data->index(0, 1, index_cur), 1);
            user_data->setData(user_data->index(1, 1, index_cur), 0);
            user_data->setData(user_data->index(2, 1, index_cur), 0);
            user_data->setModified(true);
        }
        else
        {
            Q_ASSERT(user_data->rowCount(index_cur));
            user_data->setData(user_data->index(0, 1, index_cur), 1);
            user_data->setData(user_data->index(1, 1, index_cur), 0);
            user_data->setData(user_data->index(2, 1, index_cur), 0);
            user_data->setModified(true);
        }
    }
    else
    {
        QModelIndex index_event = user_data->item_find("event", user_data->index(0, 0));
        Q_ASSERT(index_event.isValid());
        QModelIndex index_cur = user_data->item_find(event_sorted_events.at(event_id), index_event);
        Q_ASSERT(index_cur.isValid());
        // well, remove a row in user_data may possibly not easy... we need to find the very row number to delete
        // since the last assert used, I think we can safely remove column by the following code
        for (int i = 0; i < user_data->rowCount(index_event); ++i)
        {
            if (user_data->index(i, 0, index_event) == index_cur)
            {
                user_data->removeRow(i, index_event);
                break;
            }
        }
        user_data->setModified(true);
    }

    // 3.1. enable objects after user_data entry created
    if (checkbox->isChecked())
    {
        // for safety, set to zero for spinboxes
        event_upper_inf1_spin.at(event_id)->setValue(0);
        event_upper_inf2_spin.at(event_id)->setValue(0);
        event_upper_inf1_spin.at(event_id)->setEnabled(true);
        event_upper_inf2_spin.at(event_id)->setEnabled(true);
    }

    // 4. re-calculate event_user_expect
    event_on_object_responsed();
}

void tab_widget_item::event_on_spin_changed()
{
    // 1. get the index of the click
    QSpinBox *spinbox = qobject_cast<QSpinBox*>(sender());
    int inf = 1;
    int event_id = event_upper_inf1_spin.indexOf(spinbox);
    if (event_id == -1)
    {
        inf = 2;
        event_id = event_upper_inf2_spin.indexOf(spinbox);
    }
    Q_ASSERT(event_id != -1);

    // 2. write into the event_user_type
    event_user_type[event_sorted_events.at(event_id)][inf] = spinbox->value();

    // 3. make change to user_data
    // since we can get access to spinbox, we simply assume user_data have provided entry for this current event
    QModelIndex index_cur_inf = user_data->item_find("inf" + QVariant(inf).toString(),
                                user_data->item_find(event_sorted_events.at(event_id),
                                user_data->item_find("event",
                                user_data->index(0, 0))));
    Q_ASSERT(index_cur_inf.isValid());
    user_data->setData(index_cur_inf.siblingAtColumn(1), spinbox->value());

    // 4. re-calculate event_user_expect
    event_on_object_responsed();
}

void tab_widget_item::event_on_object_responsed()
{
    // re-calculate
    event_user_expect = QVector<long long>(GLOB::LIST_ITEM.size(), 0);
    for (int id = 0; id < event_sorted_events.size(); ++id)
    {
        if (event_user_type.value(event_sorted_events.at(id)).at(0) > 0)
        {
            util_list_plus(event_user_expect, event_data_item.value(event_sorted_events.at(id)).at(0));
            // it is expected that if event_user_type.value(event_sorted_events.at(id)).at(1, 2) > 0,
            // so judgement lies here, not outside this code block
            if (event_user_type.value(event_sorted_events.at(id)).at(1) > 0)
            {
                int user_inf = event_user_type.value(event_sorted_events.at(id)).at(1);
                int split_inf = event_data_type.value(event_sorted_events.at(id)).at(1);
                if (user_inf < split_inf) // only user condition considered
                    util_list_plus(event_user_expect, event_data_item.value(event_sorted_events.at(id)).at(1), user_inf);
                else // need to make split consideration
                {
                    util_list_plus(event_user_expect, event_data_item.value(event_sorted_events.at(id)).at(1), split_inf - 1);
                    util_list_plus(event_user_expect, event_data_item.value(event_sorted_events.at(id)).at(2), user_inf - split_inf + 1);
                }
            }
            if (event_user_type.value(event_sorted_events.at(id)).at(2) > 0)
            {
                int user_inf = event_user_type.value(event_sorted_events.at(id)).at(2);
                int split_inf = event_data_type.value(event_sorted_events.at(id)).at(2);
                if (user_inf < split_inf) // only user condition considered
                    util_list_plus(event_user_expect, event_data_item.value(event_sorted_events.at(id)).at(3), user_inf);
                else // need to make split consideration
                {
                    util_list_plus(event_user_expect, event_data_item.value(event_sorted_events.at(id)).at(3), split_inf - 1);
                    util_list_plus(event_user_expect, event_data_item.value(event_sorted_events.at(id)).at(4), user_inf - split_inf + 1);
                }
            }
        }
    }
}

void tab_widget_item::event_on_date_changed()
{
    // simply defined to act as slot
    event_on_date_changed(false);
}

void tab_widget_item::event_on_date_changed(bool init)
{
    // 0. first test whether "root->event->date" entry exists
    QModelIndex index_date = user_data->item_find("date",
                             user_data->item_find("event",
                             user_data->index(0, 0)));
    Q_ASSERT(index_date.isValid());

    // 1. read and write date from widget
    QDate date = event_date_widget->date();
    if (!user_data->data(index_date, Qt::DisplayRole).isValid() || !init)
    {
        Q_ASSERT(user_data->setData(index_date.siblingAtColumn(1), date.toString("yyyy-MM-dd")));
        user_data->setModified(true);
    }

    // 2. toggle some events before this very date
    // judgement: final date of the event
    // it is aquired to remove widgets
    // if not, the hidden widgets will still use some space, causing the first visible widget shift to right
    /*
    for (int id = 0; id < event_sorted_events.size(); ++id)
    {
        if (event_data_date.value(event_sorted_events.at(id)).at(1) < date)
        {
            if (event_upper_follow.at(id)->isChecked()) event_upper_follow.at(id)->setChecked(false);
            event_upper_vec.at(id)->setVisible(false);
        }
        else
        {
            event_upper_vec.at(id)->setVisible(true);
        }
    }
    */
    for (auto i : event_upper_vec)
        event_upper_layout->removeWidget(i);
    for (int id = 0; id < event_sorted_events.size(); ++id)
    {
        if (event_data_date.value(event_sorted_events.at(id)).at(1) < date)
        {
            if (event_upper_follow.at(id)->isChecked()) event_upper_follow.at(id)->setChecked(false);
            event_upper_vec.at(id)->setEnabled(false);
            event_upper_vec.at(id)->setVisible(false);
        }
        else
        {
            event_upper_vec.at(id)->setEnabled(true);
            event_upper_vec.at(id)->setVisible(true);
            event_upper_layout->addWidget(event_upper_vec.at(id));
        }
    }

    // I think we can stop here, since all calculation works will be done when checkboxes toggled
}

// 3. month

void tab_widget_item::month_reset()
{
    // this function occurs when database changed

    // 1. reset data
    month_header_str = QVector<QString>{};
    month_header_date = QVector<QDate>{};
    month_data_data = QVector<QVector<QString>>{};

    // 2. reset widgets
    for (auto i : month_widget_group)
    {
        month_widget_layout->removeWidget(i);
        if (i) delete i;
    }
    month_widget_group = QVector<QGroupBox*>{};
    month_widget_figure = QVector<QVector<QLabel*>>{};
    month_widget_spin = QVector<QVector<QSpinBox*>>{};

    // 3. read data from exchange_item
    // if exchange_item = 0, nothing should happen here
    if (exchange_item == nullptr) return;
    {
        QModelIndex index_root = exchange_item->index(0, 0);
        Q_ASSERT(index_root.isValid());
        if (exchange_item->rowCount(index_root) == 0) return;
        for (int row = 0; row < exchange_item->rowCount(index_root); ++row)
        {
            // storage format is
            // <date-yyyy-MM-dd>
            //   <item_1>XX
            //   <item_2>XX
            //   <item_3>XX
            // as well, all items should be sorted carefully
            // so many asserts may occur
            // month test
            QModelIndex index_date = exchange_item->index(row, 0, index_root);
            QString date_str = exchange_item->data(index_date, Qt::DisplayRole).toString();
            QStringList date_lst = date_str.split("-");
            Q_ASSERT(date_lst.size() == 4);
            QDate date(date_lst.at(1).toInt(), date_lst.at(2).toInt(), date_lst.at(3).toInt());
            Q_ASSERT(date.isValid());
            if (month_header_date.size() > 0)
                Q_ASSERT(date > month_header_date.at(month_header_date.size() - 1));
            // item test
            QVector<QString> items(3, "");
            QModelIndex index_item1 = exchange_item->index(0, 0, index_date);
            QModelIndex index_item2 = exchange_item->index(1, 0, index_date);
            QModelIndex index_item3 = exchange_item->index(2, 0, index_date);
            Q_ASSERT(exchange_item->data(index_item1, Qt::DisplayRole).toString() == "item_1" &&
                     exchange_item->data(index_item2, Qt::DisplayRole).toString() == "item_2" &&
                     exchange_item->data(index_item3, Qt::DisplayRole).toString() == "item_3");
            items[0] = exchange_item->data(index_item1.siblingAtColumn(1), Qt::DisplayRole).toString();
            items[1] = exchange_item->data(index_item2.siblingAtColumn(1), Qt::DisplayRole).toString();
            items[2] = exchange_item->data(index_item3.siblingAtColumn(1), Qt::DisplayRole).toString();
            // write to memory
            month_header_str.push_back(date_str);
            month_header_date.push_back(date);
            month_data_data.push_back(items);
        }
        qDebug() << month_data_data;
    }

    // 4. assign widgets
    for (int id = 0; id < month_header_date.size(); ++id)
    {
        // define
        QVector<QLabel*> figure = QVector<QLabel*>{};
        QVector<QSpinBox*> spin = QVector<QSpinBox*>{};
        auto layout = new QGridLayout;
        for (int i = 0; i < 3; ++i)
        {
            figure.push_back(new QLabel);
            figure.at(i)->setPixmap(GLOB::MAP_ITEM.value(month_data_data.at(id).at(i)).scaled(66, 72));
            figure.at(i)->setFixedSize(QSize(66, 72));
            layout->addWidget(figure.at(i), 0, i, Qt::AlignCenter);
            spin.push_back(new QSpinBox);
            spin.at(i)->setMinimum(0);
            spin.at(i)->setMaximum(30);
            layout->addWidget(spin.at(i), 1, i, Qt::AlignCenter);
        }
        QGroupBox *group = new QGroupBox;
        group->setTitle(month_header_date.at(id).toString("yyyy-MM"));
        group->setLayout(layout);
        // append
        month_widget_group.push_back(group);
        month_widget_figure.push_back(figure);
        month_widget_spin.push_back(spin);
        // display
        month_widget_layout->addWidget(group);
    }

    // up to here, all layout should be finished
    // then, read user data to fill in values
    month_refresh();
}

void tab_widget_item::month_refresh()
{
    // 1. reset memory
    month_user_data = QVector<QVector<int>>(month_header_date.size(), {0, 0, 0});
    month_user_date = QDate(month_widget_date->date());

    // 2. reset connection
    for (int id = 0; id < month_header_date.size(); ++id)
        for (int i = 0; i < 3; ++i)
            disconnect(month_widget_spin.at(id).at(i), QOverload<int>::of(&QSpinBox::valueChanged), this, &tab_widget_item::month_on_spin_changed);
    disconnect(month_widget_date, &QDateEdit::dateChanged, this, QOverload<>::of(&tab_widget_item::month_on_spin_changed));

    // 3. read user_data
    // if no entry "month", create one
    QModelIndex index_root = user_data->index(0, 0);
    Q_ASSERT(index_root.isValid());
    {
        QModelIndex index_month = user_data->item_find("month", index_root);
        if (!index_month.isValid())
        {
            int i = user_data->rowCount(index_root);
            user_data->insertRow(i, index_root);
            QModelIndex ind = user_data->index(i, 0, index_root);
            user_data->setData(ind, "month");
            user_data->setModified(true);
        }
    }
    QModelIndex index_month = user_data->item_find("month", index_root);
    Q_ASSERT(index_month.isValid());

    // then try to find if "root->month->date" exists; if no, create one with the current month_widget_date
    // if yes, assign date to memory month_user_date
    {
        QModelIndex index_cur_date = user_data->item_find("date", index_month);
        if (!index_cur_date.isValid())
        {
            user_data->insertRow(0, index_month);
            user_data->setData(user_data->index(0, 0, index_month), "date");
            user_data->setData(user_data->index(0, 1, index_month), month_widget_date->date().toString("yyyy-MM-dd"));
            user_data->setModified(true);
        }
        else
        {
            QStringList date_str = user_data->data(index_cur_date.siblingAtColumn(1), Qt::DisplayRole).toString().split("-");
            Q_ASSERT(date_str.size() == 3);
            month_user_date = QDate(date_str.at(0).toInt(), date_str.at(1).toInt(), date_str.at(2).toInt());
            Q_ASSERT(month_user_date.isValid());
        }
    }
    QModelIndex index_cur_date = user_data->item_find("date", index_month);
    Q_ASSERT(index_cur_date.isValid());

    // read the whole data without date information
    for (int id = 0; id < month_header_date.size(); ++id)
    {
        QModelIndex index_date = user_data->item_find(month_header_str.at(id), index_month);
        if (!index_date.isValid()) continue; // remains {0, 0, 0}
        // if valid, we assert three items in user_data, and the three items should be the same
        // to the database
        Q_ASSERT(user_data->rowCount(index_date) == 3);
        Q_ASSERT(user_data->data(user_data->index(0, 0, index_date), Qt::DisplayRole).toString() == month_data_data.at(id).at(0));
        Q_ASSERT(user_data->data(user_data->index(1, 0, index_date), Qt::DisplayRole).toString() == month_data_data.at(id).at(1));
        Q_ASSERT(user_data->data(user_data->index(2, 0, index_date), Qt::DisplayRole).toString() == month_data_data.at(id).at(2));
        month_user_data[id] = QVector<int>
        {
            user_data->data(user_data->index(0, 1, index_date), Qt::DisplayRole).toInt(),
            user_data->data(user_data->index(1, 1, index_date), Qt::DisplayRole).toInt(),
            user_data->data(user_data->index(2, 1, index_date), Qt::DisplayRole).toInt(),
        };
    }

    // 4. write to widgets
    for (int id = 0; id < month_header_date.size(); ++id)
        for (int i = 0; i < 3; ++i)
            month_widget_spin.at(id).at(i)->setValue(month_user_data.at(id).at(i));

    // 5. connect those objects to slots
    for (int id = 0; id < month_header_date.size(); ++id)
        for (int i = 0; i < 3; ++i) // since we need to double check the sum of three spin values lower than 30, we need to use queued connection
            connect(month_widget_spin.at(id).at(i), QOverload<int>::of(&QSpinBox::valueChanged), this, &tab_widget_item::month_on_spin_changed, Qt::QueuedConnection);
    connect(month_widget_date, &QDateEdit::dateChanged, this, QOverload<>::of(&tab_widget_item::month_on_date_changed));

    // 6. date process
    month_on_date_changed(true);

    // 7. re-calculate
    month_on_object_responsed();
}

void tab_widget_item::month_on_object_responsed()
{
    // re-calculate
    month_user_expect = QVector<long long>(GLOB::LIST_ITEM.size(), 0);
    for (int id = 0; id < month_header_date.size(); ++id)
    {
        for (int i = 0; i < 3; ++i)
        {
            int fact = month_user_data.at(id).at(i);
            if (fact > 0)
            {
                int ind = GLOB::MAP_ITEM_INDEX.value(month_data_data.at(id).at(i), -1);
                Q_ASSERT(ind != -1);
                month_user_expect[ind] += fact;
            }
        }
    }
    qDebug() << month_user_expect;
    emit signal_user_month_data_changed();
}

void tab_widget_item::month_on_spin_changed()
{
    // 1. search which spin it is
    QSpinBox *spin = qobject_cast<QSpinBox*>(sender());
    int spin_id = -1; // date-id
    int spin_item = -1; // which item of the current date-id
    for (int id = 0; id < month_header_date.size(); ++id)
    {
        int item = month_widget_spin.at(id).indexOf(spin);
        if (item != -1)
        {
            spin_id = id;
            spin_item = item;
            break;
        }
    }
    Q_ASSERT((spin_id != -1) && (spin_item != -1));

    // 1.5 check if the spin value is valid
    {
        QVector<int> spin_items = {0, 1, 2};
        spin_items.remove(spin_item);
        Q_ASSERT(spin_items.size() == 2);
        // first, if these two spins value > 30, check those spins
        int val1 = month_widget_spin.at(spin_id).at(spin_items.at(0))->value();
        int val2 = month_widget_spin.at(spin_id).at(spin_items.at(1))->value();
        int val = spin->value();
        if (val1 + val2 + val > 30)
        {
            if (val1 + val2 > 30)
                month_widget_spin.at(spin_id).at((spin_item + 1) % 3)->setValue(0);
            else
                spin->setValue(30 - val1 - val2);
        }
    }

    // 2. set value to memory
    month_user_data[spin_id][spin_item] = spin->value();

    // 3. set value to user_data
    // if no entry of the current date, create one
    QModelIndex index_month = user_data->item_find("month", user_data->index(0, 0));
    Q_ASSERT(index_month.isValid());
    qDebug() << month_header_str;
    QModelIndex index_date = user_data->item_find(month_header_str.at(spin_id), index_month);
    if (!index_date.isValid())
    {
        int i = user_data->rowCount(index_month);
        Q_ASSERT(user_data->insertRow(i, index_month));
        QModelIndex index_date = user_data->index(i, 0, index_month);
        Q_ASSERT(user_data->setData(index_date, month_header_str.at(spin_id)));
        Q_ASSERT(user_data->insertRows(0, 3, index_date));
        for (int row = 0; row < 3; row++)
        {
            Q_ASSERT(user_data->setData(user_data->index(row, 0, index_date), month_data_data.at(spin_id).at(row)));
            Q_ASSERT(user_data->setData(user_data->index(row, 1, index_date), month_widget_spin.at(spin_id).at(row)->value()));
        }
    }
    else
    {
        QModelIndex index_item = user_data->item_find(month_data_data.at(spin_id).at(spin_item), index_date);
        Q_ASSERT(index_item.isValid());
        Q_ASSERT(user_data->setData(index_item.siblingAtColumn(1), spin->value()));
    }
    user_data->setModified(true);

    // 4. re-calculate
    month_on_object_responsed();
}

void tab_widget_item::month_on_date_changed()
{
    month_on_date_changed(false);
}

void tab_widget_item::month_on_date_changed(bool init)
{
    // 1. set value to user_data
    // if this process is called in user_data initialization, we skip this process
    // since user_data initialization process should have checked "root->month->date", we can assert here
    if (!init)
    {
        QModelIndex index_cur_date = user_data->item_find("date",
                                     user_data->item_find("month",
                                     user_data->index(0, 0)));
        Q_ASSERT(index_cur_date.isValid());
        Q_ASSERT(user_data->setData(index_cur_date.siblingAtColumn(1), month_widget_date->date().toString("yyyy-MM-dd")));
        user_data->setModified(true);
    }

    // 2. check if widgets before the current date
    // it is aquired to remove widgets
    // if not, the hidden widgets will still use some space, causing the first visible widget shift to right
    for (auto i : month_widget_group)
        month_widget_layout->removeWidget(i);
    for (int id = 0; id < month_header_date.size(); ++id)
    {
        if (month_header_date.at(id) < month_widget_date->date())
        {
            month_widget_group.at(id)->setVisible(false);
            month_widget_group.at(id)->setEnabled(false);
            for (int i = 0; i < 3; ++i)
                month_widget_spin.at(id).at(i)->setValue(0);
        }
        else
        {
            month_widget_group.at(id)->setVisible(true);
            month_widget_group.at(id)->setEnabled(true);
            month_widget_layout->addWidget(month_widget_group.at(id));
        }
    }
}



