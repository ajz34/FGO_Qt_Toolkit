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

    init_database_display();
    init_database_consume();
	init_user_data();
    set_widget_database_connection();
}

void resource_consume::init_database_display()
{
    // initialize labels and icons
    left_info_servant_name->setText("");
    left_info_servant_attribute->setText("");
    left_info_servant_class->setPixmap(QPixmap());
    left_info_servant_nobel->setText("");
    left_levelup_rarity->setText("");
    left_skill_vector_name[0]->setText("");
    left_skill_vector_name[1]->setText("");
    left_skill_vector_name[2]->setText("");

	// find servant_information
	if (!(*servant_icon_button_image)[id_number].isNull())
		right_info_icon->setPixmap((*servant_icon_button_image)[id_number].scaled(138, 150));
	// find servant basic information
	TreeModel *model = (*wiki_database)[id_number];
    QModelIndex index_basic = model->item_find("basic", model->index(0, 0));
	if (index_basic.isValid())
	{
        // name
		QModelIndex index_servant_name = model->item_find("name_en", index_basic);
		if (index_servant_name.isValid())
			left_info_servant_name->setText(model->data(index_servant_name.siblingAtColumn(1), Qt::DisplayRole).toString());

        // alignments
		bool flag_alignment = true;
		QString str_alignment = "";
		QModelIndexList index_alignment = model->item_find("alignments", 2, index_basic);
		if (index_alignment.count() == 2)
		{
			str_alignment += model->data(index_alignment[0].siblingAtColumn(1), Qt::DisplayRole).toString();
			str_alignment += ("¡¤" + model->data(index_alignment[1].siblingAtColumn(1), Qt::DisplayRole).toString());
		}
		else
			flag_alignment = false;
		QModelIndex index_attribute = model->item_find("attribute", index_basic);
		if (index_attribute.isValid())
			str_alignment += ("¡¤" + model->data(index_attribute.siblingAtColumn(1), Qt::DisplayRole).toString());
		else
			flag_alignment = false;
		if (flag_alignment)
			left_info_servant_attribute->setText(str_alignment);

        // class
        QModelIndex index_class = model->item_find("class", index_basic);
		if (index_class.isValid())
			left_info_servant_class->setPixmap(GLOB::MAP_CLASS[model->data(index_class.siblingAtColumn(1), Qt::DisplayRole).toString()].scaled(40, 40));

        // rarity
        QModelIndex index_rarity = model->item_find("rarity", index_basic);
        if (index_rarity.isValid())
            left_levelup_rarity->setText(tr("Rarity:") + model->data(index_rarity.siblingAtColumn(1), Qt::DisplayRole).toString());
	}

    // nobel
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

    // skill name
    QModelIndex index_skill_1 = model->item_find("skill_1", model->index(0, 0));
    QModelIndex index_skill_2 = model->item_find("skill_2", model->index(0, 0));
    QModelIndex index_skill_3 = model->item_find("skill_3", model->index(0, 0));
    QModelIndex index_skill_name_1 = model->item_find("name_sc", index_skill_1);
    QModelIndex index_skill_name_2 = model->item_find("name_sc", index_skill_2);
    QModelIndex index_skill_name_3 = model->item_find("name_sc", index_skill_3);
    QModelIndex index_skill_icon_1 = model->item_find("icon", index_skill_1);
    QModelIndex index_skill_icon_2 = model->item_find("icon", index_skill_2);
    QModelIndex index_skill_icon_3 = model->item_find("icon", index_skill_3);
    if (index_skill_name_1.isValid()) left_skill_vector_name[0]->setText(model->data(index_skill_name_1.siblingAtColumn(1), Qt::DisplayRole).toString());
    if (index_skill_name_2.isValid()) left_skill_vector_name[1]->setText(model->data(index_skill_name_2.siblingAtColumn(1), Qt::DisplayRole).toString());
    if (index_skill_name_3.isValid()) left_skill_vector_name[2]->setText(model->data(index_skill_name_3.siblingAtColumn(1), Qt::DisplayRole).toString());
    if (index_skill_icon_1.isValid())
    {
        left_skill_vector_icon[0]->setPixmap(GLOB::MAP_SKILL_ICON[model->data(index_skill_icon_1.siblingAtColumn(1), Qt::DisplayRole).toString()].scaled(70, 70));
        right_skill_vector_icon[0]->setPixmap(GLOB::MAP_SKILL_ICON[model->data(index_skill_icon_1.siblingAtColumn(1), Qt::DisplayRole).toString()].scaled(70, 70));
    }
    if (index_skill_icon_2.isValid())
    {
        left_skill_vector_icon[1]->setPixmap(GLOB::MAP_SKILL_ICON[model->data(index_skill_icon_2.siblingAtColumn(1), Qt::DisplayRole).toString()].scaled(70, 70));
        right_skill_vector_icon[1]->setPixmap(GLOB::MAP_SKILL_ICON[model->data(index_skill_icon_2.siblingAtColumn(1), Qt::DisplayRole).toString()].scaled(70, 70));
    }
    if (index_skill_icon_3.isValid())
    {
        left_skill_vector_icon[2]->setPixmap(GLOB::MAP_SKILL_ICON[model->data(index_skill_icon_3.siblingAtColumn(1), Qt::DisplayRole).toString()].scaled(70, 70));
        right_skill_vector_icon[2]->setPixmap(GLOB::MAP_SKILL_ICON[model->data(index_skill_icon_3.siblingAtColumn(1), Qt::DisplayRole).toString()].scaled(70, 70));
    }
}

void resource_consume::init_database_consume()
{
    TreeModel *model = (*wiki_database)[id_number];

    // assistant functions
    // this assist function try to append all items from parent index to map
    auto append_map = [model](QMap<QString, long long> &map, const QString &search, const QModelIndex &parent)
    {
        Q_ASSERT(parent.isValid());
        QModelIndex index = model->item_find(search, parent);
        Q_ASSERT(index.isValid());
        if (index.isValid())
        {
            int child_num = model->rowCount(index);
            for (int i = 0; i < child_num; ++i)
                map[model->data(model->index(i, 0, index), Qt::DisplayRole).toString()] =
                    model->data(model->index(i, 1, index), Qt::DisplayRole).toInt();
        }
    };
    // this assist function try to set the integer value
    auto set_int = [model](int &val, const QString &search, const QModelIndex &parent)
    {
        QModelIndex index = model->item_find(search, parent);
        Q_ASSERT(index.isValid());
        val = model->data(index.siblingAtColumn(1), Qt::DisplayRole).toInt();
    };

    // initialize database_skill_consume
    // first entry of database_skill_consume is set to empty
    // every servant should have skill consume, so use assert here
    QModelIndex index_skill_consume = model->item_find("skill_consume", model->index(0, 0));
    set_int(database_skill_rarity, "consume_rarity", index_skill_consume);
    for (int i = 1; i < 10; ++i)
    {
        qDebug() << i << "skill_level_" + QVariant(i).toString();
        append_map(database_skill_consume[i], "skill_level_" + QVariant(i).toString(), index_skill_consume);
    }
    QModelIndex index_skill_consume_total = model->item_find("total_consume", index_skill_consume);
    Q_ASSERT(index_skill_consume_total.isValid());
    list_database_skill_consume = QVector<long long>(GLOB::LIST_ITEM.count(), 0);
    for (int i = 0; i < model->rowCount(index_skill_consume_total); ++i)
    {
        QString item_name = model->data(model->index(i, 0, index_skill_consume_total), Qt::DisplayRole).toString();
        int item_number = model->data(model->index(i, 1, index_skill_consume_total), Qt::DisplayRole).toInt();
        qDebug() << "in init_database_consume" << GLOB::LIST_ITEM.indexOf(item_name);
        qDebug() << list_database_skill_consume;
        list_database_skill_consume[GLOB::LIST_ITEM.indexOf(item_name)] = item_number;
    }
}

void resource_consume::init_user_data()
{
    // this function should have the following functionalities
    //  1.  store essential information to private-class-level global value

    // read servant index
    TreeModel *model = (*wiki_database)[id_number];
    QModelIndex index_database_id =
        model->item_find("id",
            model->item_find("basic",
                model->index(0, 0)));
    Q_ASSERT(index_database_id.isValid());
    user_servant_id = model->data(index_database_id.siblingAtColumn(1), Qt::DisplayRole).toInt();
    char id_full_cstring[4];
    sprintf(id_full_cstring, "%03d", user_servant_id);
    QString id_full(id_full_cstring);

    // read user data for the current servant
    // assist_func
    // https://stackoverflow.com/questions/38595834/compilation-error-this-cannot-be-implicitly-captured-in-this-context
    auto assist_func = [this](int &val, const QModelIndex &index)
    {
        if (index.isValid())
            val = user_data->data(index.siblingAtColumn(1), Qt::DisplayRole).toInt();
    };
    // <servant_xxx>
    QModelIndex index_user_id = user_data->item_find("servant_" + id_full, user_data->index(0, 0));
    //   <status>
    QModelIndex index_status = user_data->item_find("status", index_user_id);
    assist_func(user_follow, user_data->item_find("follow", index_status));
    assist_func(user_priority, user_data->item_find("priority", index_status));
    assist_func(user_existance, user_data->item_find("existance", index_status));
    //   </status>
    //   <actual>
    QModelIndex index_actual = user_data->item_find("actual", index_user_id);
    assist_func(user_actual_ascension, user_data->item_find("ascension", index_actual));
    assist_func(user_actual_level, user_data->item_find("level", index_actual));
    assist_func(user_actual_skill_1, user_data->item_find("skill_1", index_actual));
    assist_func(user_actual_skill_2, user_data->item_find("skill_2", index_actual));
    assist_func(user_actual_skill_3, user_data->item_find("skill_3", index_actual));
    //   </actual>
    //   <ideal>
    QModelIndex index_ideal = user_data->item_find("ideal", index_user_id);
    assist_func(user_ideal_ascension, user_data->item_find("ascension", index_ideal));
    assist_func(user_ideal_level, user_data->item_find("level", index_ideal));
    assist_func(user_ideal_skill_1, user_data->item_find("skill_1", index_ideal));
    assist_func(user_ideal_skill_2, user_data->item_find("skill_2", index_ideal));
    assist_func(user_ideal_skill_3, user_data->item_find("skill_3", index_ideal));
    //   </ideal>
    //   <costume>
    QModelIndex index_costume = user_data->item_find("costume", index_user_id);
    //     in costume, we just count the number of childs, but not check the costume name here
    for (int i = 0; i < user_data->rowCount(index_costume); ++i)
        user_costume.push_back(user_data->data(user_data->index(i, 1, index_costume), Qt::DisplayRole).toInt());
    //   </costume>
    // </servant_xxx>
}


void resource_consume::set_widget_database_connection()
{
    connect(left_skill_vector_dial[0], &QDial::valueChanged, this, &resource_consume::connection_left_skill_dial);
    connect(left_skill_vector_dial[1], &QDial::valueChanged, this, &resource_consume::connection_left_skill_dial);
    connect(left_skill_vector_dial[2], &QDial::valueChanged, this, &resource_consume::connection_left_skill_dial);
}

void resource_consume::connection_left_skill_dial()
{
    QDial *dial = qobject_cast<QDial*>(sender());
    int dial_num = 3;
    if (dial == left_skill_vector_dial[0]) dial_num = 0;
    else if (dial == left_skill_vector_dial[1]) dial_num = 1;
    else if (dial == left_skill_vector_dial[2]) dial_num = 2;
    qDebug() << "in connection_left_skill_dial" << dial_num;
    for (QLabel* label : left_skill_vector_consume[dial_num]) label->setPixmap(GLOB::MAP_EMPTY["skill_large"]);
    for (QLabel* label : left_skill_vector_consume_number[dial_num]) label->setText("");
    qDebug() << "in connection_left_skill_dial" << "step 1";
    if (dial->value() < 10)
    {
        int label_count = 0;
        const QMap<QString, long long> &map = database_skill_consume[dial->value()];
        qDebug() << "in connection_left_skill_dial" << "step 2";
        QMap<QString, long long>::const_iterator i = map.constBegin();
        while (i != map.constEnd() && label_count < 5)
        {
            qDebug() << "in connection_left_skill_dial" << "step 3";
            left_skill_vector_consume[dial_num][label_count]->setPixmap(GLOB::MAP_ITEM[i.key()].scaled(46, 50));
            left_skill_vector_consume_number[dial_num][label_count]->setText(consume_int(i.value()));
            ++i;
            ++label_count;
        }
    }
}

QString resource_consume::consume_int(long long val)
{
    Q_ASSERT(val >= 0);
    Q_ASSERT(val < 1000LL * 1000LL * 1000LL * 1000LL);
    if (val == 0)
        return QString();
    else if (val < 1000)
        return QVariant(val).toString();
    else if (val < 1000 * 1000)
    {
        if (val % 1000 == 0)
            return QVariant(val / 1000).toString() + QString("k");
        else
            return QVariant(val / 1000).toString() + QString(".")
                    + QVariant((val % 1000) / 100).toString() + QString("k");
    }
    else if (val < 1000 * 1000 * 1000)
    {
        if (val % (1000 * 1000) == 0)
            return QVariant(val / 1000 / 1000).toString() + QString("M");
        else
            return QVariant(val / 1000 / 1000).toString() + QString(".")
                    + QVariant((val % (1000 * 1000)) / 100 / 1000).toString() + QString("M");
    }
    else
    {
        if (val % (1000 * 1000 * 1000) == 0)
            return QVariant(val / 1000 / 1000 / 1000).toString() + QString("G");
        else
            return QVariant(val / 1000 / 1000 / 1000).toString() + QString(".")
                    + QVariant((val % (1000 * 1000 * 1000)) / 100 / 1000 / 1000).toString() + QString("G");
    }
}

















