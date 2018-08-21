#include "resource_consume.h"

void resource_consume::data_transin(
	QVector<QString> ini_setting,
	QVector<TreeModel*> *wiki,
	QVector<QPixmap> *servant_icon,
	int id)
{
	wiki_database = wiki;
	servant_icon_button_image = servant_icon;
	id_number = id;

	init_database();
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
		QModelIndex index_alignment = model->item_find("alignments", index_basic);
		if (index_alignment.isValid())
		{
			QModelIndex index_1 = model->index(0, 2, index_alignment);
			if (index_1.isValid())
				str_alignment += model->data(index_1, Qt::DisplayRole).toString();
			else
				flag_alignment = false;
			QModelIndex index_2 = model->index(1, 2, index_alignment);
			if (index_2.isValid())
				str_alignment += ("¡¤" + model->data(index_2, Qt::DisplayRole).toString());
			else
				flag_alignment = false;
		}
		QModelIndex index_attribute = model->item_find("attribute", index_basic);
		if (index_attribute.isValid())
			str_alignment += ("¡¤" + model->data(index_attribute.siblingAtColumn(1), Qt::DisplayRole).toString());
		else
			flag_alignment = false;
		if (flag_alignment)
			left_info_servant_attribute->setText(str_alignment);
	}

	// nobel
	left_info_servant_nobel->setText("");
	QModelIndex index_nobel = model->item_find("nobel", model->index(0, 0));
	if (index_nobel.isValid())
	{
		QModelIndex index_nobel_name = model->item_find("name_sc", index_nobel);
		if (index_nobel.isValid())
			left_info_servant_nobel->setText(model->data(index_nobel_name.siblingAtColumn(1), Qt::DisplayRole).toString());
	}
}
