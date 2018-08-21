#include "resource_consume.h"
#include "global_var.h"

void resource_consume::data_transin(
	QVector<QString> ini_setting,
	QVector<TreeModel*> *wiki,
	QVector<QPixmap> *servant_icon,
	int id,
	TreeModel *user_dat)
{
	wiki_database = wiki;
	servant_icon_button_image = servant_icon;
	id_number = id;
	user_data = user_dat;

	init_database();
	init_user_data();
}

void resource_consume::init_database()
{
	// find servant_information
	if (!(*servant_icon_button_image)[id_number].isNull())
		right_info_icon->setPixmap((*servant_icon_button_image)[id_number].scaled(138, 150));
	// find servant basic information
	TreeModel *model = (*wiki_database)[id_number];
	QModelIndex index_basic = model->item_find("basic", model->index(0, 0));
	if (index_basic.isValid())
	{
		// name
		left_info_servant_name->setText("");
		QModelIndex index_servant_name = model->item_find("name_en", index_basic);
		if (index_servant_name.isValid())
			left_info_servant_name->setText(model->data(index_servant_name.siblingAtColumn(1), Qt::DisplayRole).toString());

		// alignments
		left_info_servant_attribute->setText("");
		bool flag_alignment = true;
		QString str_alignment = "";
		QModelIndexList index_alignment = model->item_find("alignments", 2, index_basic);
		if (index_alignment.count() == 2)
		{
			str_alignment += model->data(index_alignment[0].siblingAtColumn(1), Qt::DisplayRole).toString();
			str_alignment += ("��" + model->data(index_alignment[1].siblingAtColumn(1), Qt::DisplayRole).toString());
		}
		else
			flag_alignment = false;
		QModelIndex index_attribute = model->item_find("attribute", index_basic);
		if (index_attribute.isValid())
			str_alignment += ("��" + model->data(index_attribute.siblingAtColumn(1), Qt::DisplayRole).toString());
		else
			flag_alignment = false;
		if (flag_alignment)
			left_info_servant_attribute->setText(str_alignment);

		// class
		left_info_servant_class->setPixmap(QPixmap());
		QModelIndex index_class = model->item_find("class", index_basic);
		if (index_class.isValid())
			left_info_servant_class->setPixmap(GLOB::MAP_CLASS[model->data(index_class.siblingAtColumn(1), Qt::DisplayRole).toString()].scaled(40, 40));
	}

	// nobel
	left_info_servant_nobel->setText("");
	left_info_servant_nobel_color->setPixmap(QPixmap());
	QModelIndex index_nobel = model->item_find("nobel", model->index(0, 0));
	if (index_nobel.isValid())
	{
		QModelIndex index_nobel_name = model->item_find("name_sc", index_nobel);
		if (index_nobel_name.isValid())
			left_info_servant_nobel->setText(model->data(index_nobel_name.siblingAtColumn(1), Qt::DisplayRole).toString());
		QModelIndex index_nobel_color = model->item_find("card", index_nobel);
		if (index_nobel_color.isValid())
			left_info_servant_nobel_color->setPixmap(GLOB::MAP_CARD[model->data(index_nobel_color.siblingAtColumn(1), Qt::DisplayRole).toString()].scaled(40, 40));
	}
}

void resource_consume::init_user_data()
{
	// read servant index
	TreeModel *database = (*wiki_database)[id_number];
	QModelIndex index_database_id = 
		database->item_find("id",
			database->item_find("basic",
				database->index(0, 0)));
	Q_ASSERT(index_database_id.isValid());
	int id = database->data(index_database_id.siblingAtColumn(1), Qt::DisplayRole).toInt();
	char id_full_cstring[4];
	sprintf(id_full_cstring, "%03d", id);
	QString id_full(id_full_cstring);
	qDebug() << "in init_user_data" << id_full_cstring;

	// read user data for the current servant
	QModelIndex index_user_id =
		user_data->item_find("follow",
			user_data->item_find("status",
				user_data->item_find("servant_" + id_full,
					user_data->index(0, 0))));
	if (user_data->data(index_user_id.siblingAtColumn(1), Qt::DisplayRole) == 1)
		left_info_follow->setChecked(true);
}
