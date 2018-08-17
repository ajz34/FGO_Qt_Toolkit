#include "tab_widget_servant.h"

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
	QVector<QAction*> filter_rarities{
		filter_rarity_5, filter_rarity_4, filter_rarity_3,
		filter_rarity_2, filter_rarity_1, filter_rarity_0,
	};

	for (auto i : filter_rarities)
	{
		connect(i, &QAction::triggered, this, &tab_widget_servant::filter_rarity_subitem_clicked_actionbehave);
	}

	connect(filter_rarity_all, &QAction::triggered, this, &tab_widget_servant::filter_rarity_all_clicked_actionbehave);
}

void tab_widget_servant::filter_rarity_subitem_clicked_actionbehave(bool checked)
{
	if (checked)
	{
		filter_rarity_all->setChecked(false);
		filter_rarity->setFlat(false);
	}
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
}

//--- D. servant table

void tab_widget_servant::receive_wiki_xml_database(QVector<QString> path_pack, QVector<TreeModel*> tree_model)
{
	ini_setting_data = path_pack;
	wiki_database = tree_model;
	delete table_widget_model_origin;
	table_widget_model_origin = new QStandardItemModel;
	QStringList table_widget_model_header;
	table_widget_model_header
		<< tr("Servant")		// 0
		<< tr("ID")				// 1
		<< tr("Name")			// 2
		<< tr("Class")			// 3
		<< tr("Rarity");		// 4
	table_widget_model_origin->setHorizontalHeaderLabels(table_widget_model_header);
	for (int i = 0; i < wiki_database.size(); i++)
	{
		TreeModel *model = wiki_database[i];
		// https://stackoverflow.com/questions/3290704/howto-find-subitem-in-qabstractitemmodel-and-qtreeview-class
		// 1. basic property
		// initial basic property
		QModelIndexList item_basic = model->match(
			model->index(0, 0),
			Qt::DisplayRole,
			QVariant::fromValue(QString("basic")),
			1, Qt::MatchRecursive);
		if (!item_basic.isEmpty())
		{
			// id
			{
				QModelIndexList item = model->match(
					model->index(0, 0, item_basic[0]),
					Qt::DisplayRole,
					QVariant::fromValue(QString("id")),
					1);
				if (!item.isEmpty())
				{
					int val = model->data(item[0].siblingAtColumn(2), Qt::DisplayRole).toInt();
					QStandardItem *item = new QStandardItem;
					item->setData(val, Qt::DisplayRole);
					item->setEditable(false);
					table_widget_model_origin->setItem(i, 1, item);
				}
			}

			// name
			{
				QModelIndexList item = model->match(
					model->index(0, 0, item_basic[0]),
					Qt::DisplayRole,
					QVariant::fromValue(QString("name_en")),
					1);
				if (!item.isEmpty())
				{
					QString val = model->data(item[0].siblingAtColumn(2), Qt::DisplayRole).toString();
					QStandardItem *item = new QStandardItem;
					item->setData(val, Qt::DisplayRole);
					item->setEditable(false);
					table_widget_model_origin->setItem(i, 2, item);
				}
			}

			// class
			{
				QModelIndexList item = model->match(
					model->index(0, 0, item_basic[0]),
					Qt::DisplayRole,
					QVariant::fromValue(QString("class")),
					1);
				if (!item.isEmpty())
				{
					QString val = model->data(item[0].siblingAtColumn(2), Qt::DisplayRole).toString();
					QStandardItem *item = new QStandardItem;
					item->setData(val, Qt::DisplayRole);
					item->setEditable(false);
					table_widget_model_origin->setItem(i, 3, item);
				}
			}
				
			// rarity
			{
				QModelIndexList item = model->match(
					model->index(0, 0, item_basic[0]),
					Qt::DisplayRole,
					QVariant::fromValue(QString("rarity")),
					1);
				if (!item.isEmpty())
				{
					int val = model->data(item[0].siblingAtColumn(2), Qt::DisplayRole).toInt();
					QStandardItem *item = new QStandardItem;
					item->setData(val, Qt::DisplayRole);
					item->setEditable(false);
					table_widget_model_origin->setItem(i, 4, item);
				}
			}
		}
	}
	// set buttons
	// this process is slow, set process bar here
	QProgressDialog progress(tr("Setup table icon image"), "", 0, table_widget_model_origin->rowCount());
	progress.setCancelButton(0);
	progress.setWindowModality(Qt::WindowModal);
	progress.show();
	for (int row = 0; row < table_widget_model_origin->rowCount(); ++row)
	{
		progress.setValue(row + 1);
		QApplication::processEvents();
		if (progress.wasCanceled())
			break;
		char num_full[4];
		sprintf(num_full, "%03d", table_widget_model_origin->data(table_widget_model_origin->index(row, 1)).toInt());
		QPixmap pixmap(ini_setting_data[1] + QString("/") + QString(num_full) + QString(".png"));
		servant_icon_button_image[table_widget_model_origin->data(table_widget_model_origin->index(row, 1)).toInt()] = pixmap;
	}
	progress.setValue(table_widget_model_origin->rowCount());
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
		<< tr("Servant")		// 0
		<< tr("ID")				// 1
		<< tr("Name")			// 2
		<< tr("Class")			// 3
		<< tr("Rarity");		// 4
	table_widget_model->setHorizontalHeaderLabels(table_widget_model_header);
	// set item
	int row_count = 0;
	qDebug() << "row count" << table_widget_model->rowCount();
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
		QPushButton *button = new QPushButton;
		button->setIcon(servant_icon_button_image[table_widget_model->data(table_widget_model->index(row, 1)).toInt()]);
		button->setIconSize(QSize(SERVANT_ICON_WIDTH, SERVANT_ICON_HEIGHT));
		button->setFixedSize(button->minimumSizeHint());
		button->setFixedSize(QSize(SERVANT_ICON_WIDTH, SERVANT_ICON_HEIGHT));
		table_widget->setIndexWidget(table_widget_model->index(row, 0), button);
	}
	// finalize layout
	table_widget->resizeColumnsToContents();
	table_widget->resizeRowsToContents();
	table_widget->setSortingEnabled(true);
}
