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
            str_alignment += ("·" + model->data(index_alignment[1].siblingAtColumn(1), Qt::DisplayRole).toString());
        }
        else
            flag_alignment = false;
        QModelIndex index_attribute = model->item_find("attribute", index_basic);
        if (index_attribute.isValid())
            str_alignment += ("·" + model->data(index_attribute.siblingAtColumn(1), Qt::DisplayRole).toString());
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
    auto append_vec = [model](QVector<int> &vec, const QString &search, const QModelIndex &parent)
    {
        QModelIndex index = model->item_find(search, parent);
        Q_ASSERT(index.isValid());
        vec = QVector<int>(GLOB::LIST_ITEM.size());
        if (index.isValid())
        {
            int child_num = model->rowCount(index);
            for (int i = 0; i < child_num; ++i)
                vec[GLOB::LIST_ITEM.indexOf(model->data(model->index(i, 0, index), Qt::DisplayRole).toString())] =
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
    // first entry of database_skill_consume is set to empty (no skill level 0)
    // every servant should have skill consume, so use assert here
    QModelIndex index_skill_consume = model->item_find("skill_consume", model->index(0, 0));
    set_int(database_skill_rarity, "consume_rarity", index_skill_consume);
    database_skill_consume[0] = QVector<int>(GLOB::LIST_ITEM.size());
    for (int i = 1; i < 10; ++i)
    {
        append_vec(database_skill_consume[i], "skill_level_" + QVariant(i).toString(), index_skill_consume);
        database_skill_consume[i][GLOB::LIST_ITEM.indexOf("QP")] = GLOB::VEC_SKILL_QP[database_skill_rarity][i];
    }

    // initialize database_ascension_consume
    QModelIndex index_ascension_consume = model->item_find("ascension_consume", model->index(0, 0));
    // for Mash Kyrielight, skip ascension code
    if (id_number != 1)
    {
        set_int(database_ascension_rarity, "consume_rarity", index_ascension_consume);
        for (int i = 0; i < 4; ++i)
        {
            append_vec(database_ascension_consume[i], "ascension_level_" + QVariant(i).toString(), index_ascension_consume);
            database_ascension_consume[i][GLOB::LIST_ITEM.indexOf("QP")] = GLOB::VEC_ASCENSION_QP[database_ascension_rarity][i];
        }
    }
    else
    {
        database_ascension_rarity = 4;
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
    connect(left_skill_vector_dial[0], &QDial::valueChanged, this, &resource_consume::connection_right_skill_dial);
    connect(left_skill_vector_dial[1], &QDial::valueChanged, this, &resource_consume::connection_right_skill_dial);
    connect(left_skill_vector_dial[2], &QDial::valueChanged, this, &resource_consume::connection_right_skill_dial);
    connect(right_skill_vector_dial[0], &QDial::valueChanged, this, &resource_consume::connection_right_skill_dial);
    connect(right_skill_vector_dial[1], &QDial::valueChanged, this, &resource_consume::connection_right_skill_dial);
    connect(right_skill_vector_dial[2], &QDial::valueChanged, this, &resource_consume::connection_right_skill_dial);
    connect(left_levelup_dial, &QDial::valueChanged, this, &resource_consume::connection_ascension_levelup_mess, Qt::QueuedConnection);
    connect(right_levelup_dial, &QDial::valueChanged, this, &resource_consume::connection_ascension_levelup_mess, Qt::QueuedConnection);
    connect(left_ascension_dial, &QDial::valueChanged, this, &resource_consume::connection_ascension_levelup_mess, Qt::QueuedConnection);
    connect(right_ascension_dial, &QDial::valueChanged, this, &resource_consume::connection_ascension_levelup_mess, Qt::QueuedConnection);
}

void resource_consume::connection_ascension_levelup_mess()
{
    // MASH CHECK
    if (id_number == 1)
    {
        if (left_ascension_dial->value() > 4)
        {
            left_ascension_dial->setValue(4);
            return;
        }
        if (right_ascension_dial->value() > 4)
        {
            right_ascension_dial->setValue(4);
            return;
        }
    }
    // LEVEL 1 CHECK
    // 0 0
    //
    // 0-0
    if (left_ascension_dial->value() > right_ascension_dial->value())
    {
        right_ascension_dial->setValue(left_ascension_dial->value());
        return;
    }
    // 0 0
    // |
    // 0 0
    if (left_levelup_dial->value() < GLOB::VEC_ASCENSION_LEVELMIN[database_ascension_rarity][left_ascension_dial->value()])
    {
        left_levelup_dial->setValue(GLOB::VEC_ASCENSION_LEVELMIN[database_ascension_rarity][left_ascension_dial->value()]);
        return;
    }
    else if (left_levelup_dial->value() > GLOB::VEC_ASCENSION_LEVELMAX[database_ascension_rarity][left_ascension_dial->value()])
    {
        left_levelup_dial->setValue(GLOB::VEC_ASCENSION_LEVELMAX[database_ascension_rarity][left_ascension_dial->value()]);
        return;
    }

    // LEVEL 2 CHECK
    // 0 0
    //   |
    // 0 0
    if (right_levelup_dial->value() < GLOB::VEC_ASCENSION_LEVELMIN[database_ascension_rarity][right_ascension_dial->value()])
    {
        right_levelup_dial->setValue(GLOB::VEC_ASCENSION_LEVELMIN[database_ascension_rarity][right_ascension_dial->value()]);
        return;
    }
    else if (right_levelup_dial->value() > GLOB::VEC_ASCENSION_LEVELMAX[database_ascension_rarity][right_ascension_dial->value()])
    {
        right_levelup_dial->setValue(GLOB::VEC_ASCENSION_LEVELMAX[database_ascension_rarity][right_ascension_dial->value()]);
        return;
    }

    // LEVEL 3 CHECK
    // 0-0
    //
    // 0 0
    if (left_levelup_dial->value() > right_levelup_dial->value())
    {
        right_levelup_dial->setValue(left_levelup_dial->value());
        return;
    }

    // FINALIZE
    // LCD
    left_levelup_dial_LCD->display(left_levelup_dial->value());
    right_levelup_dial_LCD->display(right_levelup_dial->value());
    left_ascension_dial_LCD->display(left_ascension_dial->value());
    right_ascension_dial_LCD->display(right_ascension_dial->value());
    if (left_levelup_dial->value() == 100) left_levelup_dial_LCD->display("UP");
    if (right_levelup_dial->value() == 100) right_levelup_dial_LCD->display("UP");
    if (left_ascension_dial->value() == 5) left_ascension_dial_LCD->display("UP");
    if (right_ascension_dial->value() == 5) right_ascension_dial_LCD->display("UP");
    // icon
    connection_levelup_dial();
    if (id_number != 1)
    {
        connection_left_ascension_dial();
        connection_ascension_and_lvup_consume();
    }
}

void resource_consume::connection_left_skill_dial()
{
    QDial *dial = qobject_cast<QDial*>(sender());
    int dial_num = 3;
    if (dial == left_skill_vector_dial[0]) dial_num = 0;
    else if (dial == left_skill_vector_dial[1]) dial_num = 1;
    else if (dial == left_skill_vector_dial[2]) dial_num = 2;
    for (QLabel* label : left_skill_vector_consume[dial_num]) label->setPixmap(GLOB::MAP_EMPTY["skill_large"]);
    for (QLabel* label : left_skill_vector_consume_number[dial_num]) label->setText("");
    if (dial->value() < 10)
    {
        int label_count = 0;
        const QVector<int> &vec = database_skill_consume[dial->value()];
        for (int i = 0; i < vec.size(); ++i)
        {
            if (vec[i] == 0) continue;
            left_skill_vector_consume[dial_num][label_count]->setPixmap(GLOB::MAP_ITEM[GLOB::LIST_ITEM[i]].scaled(46, 50));
            left_skill_vector_consume_number[dial_num][label_count]->setText(consume_int(vec[i]));
            if (++label_count >= 5) break;
        }
    }
}

void resource_consume::connection_right_skill_dial()
{
    // NOTE!!!
    // actually this dial should be both left and right responsive!!!
    // this name is just convenience for the duality
    QDial *dial = qobject_cast<QDial*>(sender());
    int dial_num = 3;
    if      ((dial == right_skill_vector_dial[0]) || (dial == left_skill_vector_dial[0])) dial_num = 0;
    else if ((dial == right_skill_vector_dial[1]) || (dial == left_skill_vector_dial[1])) dial_num = 1;
    else if ((dial == right_skill_vector_dial[2]) || (dial == left_skill_vector_dial[2])) dial_num = 2;
    for (QLabel* label : right_skill_vector_consume[dial_num]) label->setPixmap(GLOB::MAP_EMPTY["skill_small"]);
    for (QLabel* label : right_skill_vector_consume_number[dial_num]) label->setText("");
    QVector<int> &consume_total = list_user_skill_consume[dial_num];
    consume_total = QVector<int>(GLOB::LIST_ITEM.size(), 0);
    for (int level = left_skill_vector_dial[dial_num]->value(); level < right_skill_vector_dial[dial_num]->value(); ++level)
        list_plus(consume_total, database_skill_consume[level]);
    int label_count = 0;
    for (int i = 0; i < consume_total.size(); ++i)
    {
        if (consume_total[i] == 0) continue;
        right_skill_vector_consume[dial_num][label_count]->setPixmap(GLOB::MAP_ITEM[GLOB::LIST_ITEM[i]].scaled(29, 32));
        right_skill_vector_consume_number[dial_num][label_count]->setText(consume_int(consume_total[i]));
        if (++label_count >= 27) break;
    }
}

void resource_consume::connection_left_ascension_dial()
{
    if (id_number == 1) return;
    for (QLabel* label : left_ascension_consume) label->setPixmap(GLOB::MAP_EMPTY["skill_large"]);
    for (QLabel* label : left_ascension_consume_number) label->setText("");
    if (left_ascension_dial->value() < 4)
    {
        int label_count = 0;
        const QVector<int> &vec = database_ascension_consume[left_ascension_dial->value()];
        for (int i = 0; i < vec.size(); ++i)
        {
            if (vec[i] == 0) continue;
            left_ascension_consume[label_count]->setPixmap(GLOB::MAP_ITEM[GLOB::LIST_ITEM[i]].scaled(46, 50));
            left_ascension_consume_number[label_count]->setText(consume_int(vec[i]));
            if (++label_count >= 5) break;
        }
    }
}

void resource_consume::connection_levelup_dial()
{
    left_levelup_consume->setPixmap(GLOB::MAP_EMPTY["skill_large"]);
    left_levelup_consume_number->setText("");
    int exp = GLOB::MAP_LEVEL_EXP[right_levelup_dial->value()] - GLOB::MAP_LEVEL_EXP[left_levelup_dial->value()];
    int val = exp / 32400;
    if ((exp % 27000) != 0) val += 1;
    if (val >= 1)
    {
        left_levelup_consume->setPixmap(GLOB::MAP_ITEM["Exp"].scaled(36, 50));
        left_levelup_consume_number->setText(consume_int(val));
    }
}

void resource_consume::connection_ascension_and_lvup_consume()
{
    // return values needed in window widget by reference, and update list_user_ascension_and_lvup_consume
    // palingenesis

    // 1. find if current level is for palingenesis
    int p_1 = 0, p_2 = 0, p_cup = 0, p_QP = 0;
    QMap<int, int> map_level = GLOB::VEC_PALINGENESIS_LEVEL[database_ascension_rarity];
    QMap<int, int> map_QP = GLOB::VEC_PALINGENESIS_QP[database_ascension_rarity];
    QMap<int, int>::const_iterator it_1 = map_level.constBegin();
    while (it_1 != map_level.constEnd())
    {
        if (left_levelup_dial->value() < it_1.value())
        {
            p_1 = it_1.key() - 1;
            break;
        }
        ++it_1;
    }
    if (it_1 == map_level.constEnd()) p_1 = (it_1 - 1).key();
    QMap<int, int>::const_iterator it_2 = map_level.constBegin();
    while (it_2 != map_level.constEnd())
    {
        if (right_levelup_dial->value() < it_2.value())
        {
            p_2 = it_2.key() - 1;
            break;
        }
        ++it_2;
    }
    if (it_2 == map_level.constEnd()) p_2 = (it_2 - 1).key();
    // 2. check critical point at the first palingenesis
    // example (SSR)
    // if actual = 90, no cup, then p_1 -= 1, that is p_1 = 0
    // if actual = 90, cup, then p_1 = 0
    if ((left_ascension_dial->value() == 4) && (left_levelup_dial->value() == GLOB::VEC_ASCENSION_LEVELMIN[database_ascension_rarity][5])) p_1 -= 1;
    if ((right_ascension_dial->value() == 4) && (right_levelup_dial->value() == GLOB::VEC_ASCENSION_LEVELMIN[database_ascension_rarity][5])) p_2 -= 1;
    p_cup = p_2 - p_1;

    // 3. calculate and implement consume
    p_QP = 0;
    for (int i = p_1 + 1; i < p_2 + 1; ++i)
    {
        p_QP += GLOB::VEC_PALINGENESIS_QP[database_ascension_rarity][i];
    }

    // 4. set icon for left view, but notice that we should not overwrite
    if (left_ascension_dial->value() >= 4)
    {
        for (QLabel* label : left_ascension_consume) label->setPixmap(GLOB::MAP_EMPTY["skill_large"]);
        for (QLabel* label : left_ascension_consume_number) label->setText("");
        if (p_cup > 0)
        {
            left_ascension_consume[0]->setPixmap(GLOB::MAP_ITEM[QString("圣杯")].scaled(46, 50));
            left_ascension_consume_number[0]->setText(consume_int(p_cup));
            left_ascension_consume[1]->setPixmap(GLOB::MAP_ITEM[QString("QP")].scaled(46, 50));
            left_ascension_consume_number[1]->setText(consume_int(p_QP));
        }
    }

    // 5. calculate item cost
    int a_1 = left_ascension_dial->value(), a_2 = right_ascension_dial->value();
    if (a_1 > 3) a_1 = 4;
    if (a_2 > 3) a_2 = 4;
    list_user_ascension_and_lvup_consume = QVector<int>(GLOB::LIST_ITEM.size(), 0);
    for (int level = a_1; level < a_2; ++level)
        list_plus(list_user_ascension_and_lvup_consume, database_ascension_consume[level]);
    list_user_ascension_and_lvup_consume[GLOB::LIST_ITEM.indexOf(QString("圣杯"))] = p_cup;
    list_user_ascension_and_lvup_consume[GLOB::LIST_ITEM.indexOf(QString("QP"))] += p_QP;

    // 6. set icon for right view
    for (QLabel* label : right_ascension_consume) label->setPixmap(GLOB::MAP_EMPTY["skill_small"]);
    for (QLabel* label : right_ascension_consume_number) label->setText("");
    int label_count = 0;
    for (int i = 0; i < list_user_ascension_and_lvup_consume.size(); ++i)
    {
        if (list_user_ascension_and_lvup_consume[i] == 0) continue;
        right_ascension_consume[label_count]->setPixmap(GLOB::MAP_ITEM[GLOB::LIST_ITEM[i]].scaled(29, 32));
        qDebug() << i << list_user_ascension_and_lvup_consume[i];
        right_ascension_consume_number[label_count]->setText(consume_int(list_user_ascension_and_lvup_consume[i]));
        if (++label_count >= 27) break;
    }
};

QString resource_consume::consume_int(int val)
{
    Q_ASSERT(val >= 0);
    // possible no need to set value for the largest value, since int should < 999, 999, 999 < 2,147,483,647
    // if only one servant, QP consume maximum is 54, 400, 400;
    // Exp maximum is 20, 311, 400
    // HOWEVER, if more than 40 SSR servants, long long is required
    // since this widget only handle one servant, int is enough
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

void resource_consume::list_minus(QVector<int> &vec_1, const QVector<int> &vec_2)
{
    // vec_1 = vec_1 - vec_2
    Q_ASSERT(vec_1.size() == vec_2.size());
    for (int i = 0; i < vec_1.size(); ++i)
        vec_1[i] -= vec_2[i];
}

void resource_consume::list_plus(QVector<int> &vec_1, const QVector<int> &vec_2)
{
    // vec_1 = vec_1 + vec_2
    Q_ASSERT(vec_1.size() == vec_2.size());
    for (int i = 0; i < vec_1.size(); ++i)
        vec_1[i] += vec_2[i];
}














