﻿#include "tab_widget_servant.h"

//--- A. servant class labels

void tab_widget_servant::set_servant_class_connection()
{
	connect(class_all_on, &QClickableFigureLabel::clicked, this, &tab_widget_servant::class_all_on_clicked_labelbehave);
	connect(class_all_off, &QClickableFigureLabel::clicked, this, &tab_widget_servant::class_all_off_clicked_labelbehave);
	QVector<QClickableFigureLabel*> classes{
		class_saber, class_archer, class_lancer, class_rider, class_caster, class_assassin,
		class_berserker, class_shielder, class_ruler, class_avenger, class_alterego,
		class_mooncancer, class_foreigner,
	};
	for (QClickableFigureLabel *i : classes)
	{
		connect(i, &QClickableFigureLabel::clicked, this, &tab_widget_servant::class_trival_clicked_labelbehave);
	}
}

void tab_widget_servant::class_all_on_clicked_labelbehave()
{
	QVector<QClickableFigureLabel*> classes{
		class_saber, class_archer, class_lancer, class_rider, class_caster, class_assassin,
		class_berserker, class_shielder, class_ruler, class_avenger, class_alterego,
		class_mooncancer, class_foreigner
	};
	for (QClickableFigureLabel* i : classes)
	{
		i->click_status = false;
		i->toggle();
	}
	table_widget_refresh();
}

void tab_widget_servant::class_all_off_clicked_labelbehave()
{
	QVector<QClickableFigureLabel*> classes{
		class_saber, class_archer, class_lancer, class_rider, class_caster, class_assassin,
		class_berserker, class_shielder, class_ruler, class_avenger, class_alterego,
		class_mooncancer, class_foreigner
	};
	for (QClickableFigureLabel* i : classes)
	{
		i->click_status = true;
		i->toggle();
	}
	table_widget_refresh();
}

void tab_widget_servant::class_trival_clicked_labelbehave()
{
	table_widget_refresh();
}

//--- C. filter

void tab_widget_servant::set_filter_connection()
{
    // rarity
	QVector<QAction*> filter_rarities{
		filter_rarity_5, filter_rarity_4, filter_rarity_3,
		filter_rarity_2, filter_rarity_1, filter_rarity_0,
	};
	for (auto i : filter_rarities)
	{
		connect(i, &QAction::triggered, this, &tab_widget_servant::filter_rarity_subitem_clicked_actionbehave);
	}
	connect(filter_rarity_all, &QAction::triggered, this, &tab_widget_servant::filter_rarity_all_clicked_actionbehave);

    // follow
    connect(filter_follow_all, &QAction::triggered, this, &tab_widget_servant::filter_follow_all_clicked_actionbehave);
    connect(filter_follow_yes, &QAction::triggered, this, &tab_widget_servant::filter_follow_subitem_clicked_actionbehave);
    connect(filter_follow_no, &QAction::triggered, this, &tab_widget_servant::filter_follow_subitem_clicked_actionbehave);
}

void tab_widget_servant::filter_rarity_subitem_clicked_actionbehave(bool checked)
{
	if (checked)
	{
		filter_rarity_all->setChecked(false);
		filter_rarity->setFlat(false);
	}
    table_widget_refresh();
}

void tab_widget_servant::filter_rarity_all_clicked_actionbehave(bool checked)
{
	QVector<QAction*> filter_rarities{
		filter_rarity_5, filter_rarity_4, filter_rarity_3,
		filter_rarity_2, filter_rarity_1, filter_rarity_0,
	};

	if (checked)
	{
		filter_rarity->setFlat(true);
		for (auto i : filter_rarities)
		{
			i->setChecked(false);
		}
	}
	else
	{
		filter_rarity->setFlat(false);
	}
    table_widget_refresh();
}

void tab_widget_servant::filter_follow_subitem_clicked_actionbehave(bool checked)
{
    if (checked)
    {
        filter_follow_all->setChecked(false);
        filter_follow->setFlat(false);
    }
    table_widget_refresh();
}

void tab_widget_servant::filter_follow_all_clicked_actionbehave(bool checked)
{
    if (checked)
    {
        filter_follow_all->setChecked(true);
        filter_follow_yes->setChecked(false);
        filter_follow_no->setChecked(false);
        filter_follow->setFlat(true);
    }
    else
    {
        filter_follow->setFlat(false);
    }
    table_widget_refresh();
}

//--- D. servant table

void tab_widget_servant::from_parent_database_changed(
	QVector<QString> path_pack,
	QVector<TreeModel*> tree_model,
	TreeModel* user_dat,
    QVector<QPixmap> *serv_img)
{
	ini_setting_data = path_pack;
	wiki_database = tree_model;
    user_data = user_dat;
    servant_icon_button_image = serv_img;
    table_original_table_refresh();
}

void tab_widget_servant::table_original_table_refresh()
{
	table_widget_model_origin->clear();
	QStringList table_widget_model_header;
	table_widget_model_header
        << tr("Servant")        // 0
        << tr("ID")             // 1
        << tr("Name")           // 2
        << tr("Class")          // 3
        << tr("Rarity")         // 4
        << tr("Follow")         // 5
        << tr("Priority")       // 6
        << tr("Exist")          // 7
    ;
	table_widget_model_origin->setHorizontalHeaderLabels(table_widget_model_header);
	for (int i = 0; i < wiki_database.size(); i++)
	{
		TreeModel *model = wiki_database[i];
		if (model == nullptr) continue;
		// https://stackoverflow.com/questions/3290704/howto-find-subitem-in-qabstractitemmodel-and-qtreeview-class
		// 1. basic property
		// initial basic property
		QModelIndex item_basic = model->item_find("basic", model->index(0, 0));
		if (item_basic.isValid())
		{
            // need to have outer variable to know current id
            int id = 0;
            // id, 1
			{
                // id is the most important, so we use assert here
				QModelIndex item_id = model->item_find("id", item_basic);
                Q_ASSERT(item_id.isValid());
				if (item_id.isValid())
				{
					int val = model->data(item_id.siblingAtColumn(1), Qt::DisplayRole).toInt();
                    id = val;
					QStandardItem *item = new QStandardItem;
					item->setData(val, Qt::DisplayRole);
					item->setEditable(false);
					table_widget_model_origin->setItem(i, 1, item);
				}
			}

            // name, 2
			{
				QModelIndex item_name = model->item_find("name_sc", item_basic);
				if (item_name.isValid())
				{
					QString val = model->data(item_name.siblingAtColumn(1), Qt::DisplayRole).toString();
					QStandardItem *item = new QStandardItem;
					item->setData(val, Qt::DisplayRole);
					item->setEditable(false);
					table_widget_model_origin->setItem(i, 2, item);
				}
			}

            // class, 3
			{
				QModelIndex item_class = model->item_find("class", item_basic);
				if (item_class.isValid())
				{
					QString val = model->data(item_class.siblingAtColumn(1), Qt::DisplayRole).toString();
					QStandardItem *item = new QStandardItem;
					item->setData(val, Qt::DisplayRole);
					item->setEditable(false);
					table_widget_model_origin->setItem(i, 3, item);
				}
			}
				
            // rarity, 4
			{
				QModelIndex item_rarity = model->item_find("rarity", item_basic);
				if (item_rarity.isValid())
				{
					int val = model->data(item_rarity.siblingAtColumn(1), Qt::DisplayRole).toInt();
					QStandardItem *item = new QStandardItem;
					item->setData(val, Qt::DisplayRole);
					item->setEditable(false);
					table_widget_model_origin->setItem(i, 4, item);
				}
			}

            // user_data, 5-7
            {
                char id_full[4];
                sprintf(id_full, "%03d", id);
                QModelIndex item_user_data = user_data->item_find(QString("servant_") + QString(id_full), user_data->index(0, 0));
                if (item_user_data.isValid())
                {
                    QModelIndex item_status = user_data->item_find("status", item_user_data);
                    Q_ASSERT(item_status.isValid());

                    // follow, 5
                    QModelIndex item_follow = user_data->item_find("follow", item_status);
                    Q_ASSERT(item_follow.isValid());
                    if (user_data->data(item_follow.siblingAtColumn(1), Qt::DisplayRole).toInt() > 0)
                    {
                        QStandardItem *item = new QStandardItem;
                        item->setData(tr("Yes"), Qt::DisplayRole);
                        item->setEditable(false);
                        table_widget_model_origin->setItem(i, 5, item);
                    }

                    // priority, 6
                    QModelIndex item_priority = user_data->item_find("priority", item_status);
                    Q_ASSERT(item_priority.isValid());
                    {
                        int val = user_data->data(item_priority.siblingAtColumn(1), Qt::DisplayRole).toInt();
                        QStandardItem *item = new QStandardItem;
                        item->setData(val, Qt::DisplayRole);
                        item->setEditable(false);
                        table_widget_model_origin->setItem(i, 6, item);
                    }

                    // existance, 7
                    QModelIndex item_existance = user_data->item_find("existance", item_status);
                    Q_ASSERT(item_existance.isValid());
                    if (user_data->data(item_existance.siblingAtColumn(1), Qt::DisplayRole).toInt() > 0)
                    {
                        QStandardItem *item = new QStandardItem;
                        item->setData(tr("Yes"), Qt::DisplayRole);
                        item->setEditable(false);
                        table_widget_model_origin->setItem(i, 7, item);
                    }
                }
            }
		}
    }
	table_widget_refresh();
}

void tab_widget_servant::table_widget_refresh()
{
	// delete table_widget_model;
	// table_widget_model = nullptr;
	// table_widget_model = new QStandardItemModel;
	table_widget_model->clear();
	// set header
	QStringList table_widget_model_header;
	table_widget_model_header
        << tr("Servant")        // 0
        << tr("ID")             // 1
        << tr("Name")           // 2
        << tr("Class")          // 3
        << tr("Rarity")         // 4
        << tr("Follow")         // 5
        << tr("Priority")       // 6
        << tr("Exist")          // 7
    ;
	table_widget_model->setHorizontalHeaderLabels(table_widget_model_header);
	// set item
	int row_count = 0;
	for (int row = 0; row < table_widget_model_origin->rowCount(); ++row)
	{
		// check if this item is filtered
		// check class
		QString class_name = table_widget_model_origin->data(table_widget_model_origin->index(row, 3)).toString();
		if (!(
			((class_saber->click_status) &&			QString::compare(class_name, "Saber"		, Qt::CaseInsensitive) == 0) ||
			((class_archer->click_status) &&		QString::compare(class_name, "Archer"		, Qt::CaseInsensitive) == 0) ||
			((class_lancer->click_status) &&		QString::compare(class_name, "Lancer"		, Qt::CaseInsensitive) == 0) ||
			((class_rider->click_status) &&			QString::compare(class_name, "Rider"		, Qt::CaseInsensitive) == 0) ||
			((class_caster->click_status) &&		QString::compare(class_name, "Caster"		, Qt::CaseInsensitive) == 0) ||
			((class_assassin->click_status) &&		QString::compare(class_name, "Assassin"		, Qt::CaseInsensitive) == 0) ||
			((class_berserker->click_status) &&		QString::compare(class_name, "Berserker"	, Qt::CaseInsensitive) == 0) ||
			((class_shielder->click_status) &&		QString::compare(class_name, "Shielder"		, Qt::CaseInsensitive) == 0) ||
			((class_ruler->click_status) &&			QString::compare(class_name, "Ruler"		, Qt::CaseInsensitive) == 0) ||
			((class_avenger->click_status) &&		QString::compare(class_name, "Avenger"		, Qt::CaseInsensitive) == 0) ||
			((class_alterego->click_status) &&		QString::compare(class_name, "Alterego"		, Qt::CaseInsensitive) == 0) ||
			((class_mooncancer->click_status) &&	QString::compare(class_name, "MoonCancer"	, Qt::CaseInsensitive) == 0) ||
			((class_foreigner->click_status) &&		QString::compare(class_name, "Foreigner"	, Qt::CaseInsensitive) == 0)
			)) continue;
        // check rarity
        int rarity = table_widget_model_origin->data(table_widget_model_origin->index(row, 4)).toInt();
        if (!(filter_rarity_all->isChecked()) && !(
            ((filter_rarity_0->isChecked()) && rarity == 0) ||
            ((filter_rarity_1->isChecked()) && rarity == 1) ||
            ((filter_rarity_2->isChecked()) && rarity == 2) ||
            ((filter_rarity_3->isChecked()) && rarity == 3) ||
            ((filter_rarity_4->isChecked()) && rarity == 4) ||
            ((filter_rarity_5->isChecked()) && rarity == 5)
            )) continue;
        // check follow
        bool follow = (table_widget_model_origin->data(table_widget_model_origin->index(row, 5)).isValid());
        if (!(filter_follow_all->isChecked()) && !(
            (filter_follow_yes->isChecked() && follow) ||
            (filter_follow_no->isChecked() && !follow)
            )) continue;
		// set vertical header
		for (int col = 0; col < table_widget_model_origin->columnCount(); ++col)
		{
			QStandardItem *item = new QStandardItem;
			item->setData(table_widget_model_origin->data(table_widget_model_origin->index(row, col)), Qt::DisplayRole);
			item->setEditable(false);
			table_widget_model->setItem(row_count, col, item);
		}
		QStandardItem *item = new QStandardItem;
		item->setData(QString(""), Qt::DisplayRole);
		table_widget_model->setVerticalHeaderItem(row_count, item);
		++row_count;
	}
	table_widget->setModel(table_widget_model);
	// set buttons
	for (int row = 0; row < table_widget_model->rowCount(); ++row)
	{
		QRightClickPushButton *button = new QRightClickPushButton(this);
		button->text_save = table_widget_model->data(table_widget_model->index(row, 1)).toString();
		button->setIcon((*servant_icon_button_image)[table_widget_model->data(table_widget_model->index(row, 1)).toInt()]);
        button->setIconSize(QSize(SERVANT_ICON_WIDTH, SERVANT_ICON_HEIGHT));
		button->setFixedSize(QSize(SERVANT_ICON_WIDTH, SERVANT_ICON_HEIGHT));
		table_widget->setIndexWidget(table_widget_model->index(row, 0), button);
		connect(button, &QRightClickPushButton::rightClicked, this, &tab_widget_servant::table_pushbutton_right_click);
		connect(button, &QRightClickPushButton::clicked, this, &tab_widget_servant::table_pushbutton_click);
	}
	// finalize layout
	table_widget->resizeColumnsToContents();
	table_widget->resizeRowsToContents();
	table_widget->setSortingEnabled(true);
}

void tab_widget_servant::table_pushbutton_right_click()
{
	// WARNING!!! USING sender()!!!
	QRightClickPushButton *button = qobject_cast<QRightClickPushButton*>(sender());
	int id_number = button->text_save.toInt();
	char id_full[4];
	sprintf(id_full, "%03d", id_number);
	xml_editable_mainwindow *edit_xml = new xml_editable_mainwindow(ini_setting_data[0] + "/" + id_full + ".xml", this);
	edit_xml->setAttribute(Qt::WA_DeleteOnClose);
	edit_xml->show();
}

//--- E. servant_consume

void tab_widget_servant::table_pushbutton_click()
{
	// WARNING!!! USING sender()!!!
	QRightClickPushButton *button = qobject_cast<QRightClickPushButton*>(sender());
	int id_number = button->text_save.toInt();

	resource_consume *consume_widget = new resource_consume(this);
	consume_widget->setMinimumHeight(600);
	consume_widget->setAttribute(Qt::WA_DeleteOnClose);
	consume_widget->setFixedWidth(consume_widget->sizeHint().width());
    connect(this, &tab_widget_servant::table_pushbutton_transout, consume_widget, &resource_consume::data_transin);
    connect(consume_widget, &resource_consume::signal_user_servant_data_changed, this, &tab_widget_servant::from_consume_user_data_changed);
	emit table_pushbutton_transout(
		ini_setting_data,
		&wiki_database,
		servant_icon_button_image,
		id_number,
		user_data);
    consume_widget->exec();
}

void tab_widget_servant::from_parent_user_data_loaded(TreeModel * user_dat)
{
	user_data = user_dat;
    table_original_table_refresh();
}

