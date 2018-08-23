#include "resource_consume.h"

resource_consume::resource_consume(QWidget *parent)
    : QDialog(parent)
{
    // layout
    set_lower_combined_objects();
    set_middle_left_widget();
    set_middle_right_widget();
    set_left_information_widget();
    set_right_costume_widget();
    set_layout();

    // widget connection
    set_widget_internal_connection();
}

resource_consume::~resource_consume()
{

}

void resource_consume::set_lower_skill_widget()
{
    auto left_skill_icon = new QLabel;
    auto left_skill_dial = new QDial;
    auto left_skill_dial_LCD = new QLCDNumber;

    left_skill_icon->setFixedSize(QSize(70, 70));
    left_skill_dial->setFixedSize(QSize(55, 55));
    left_skill_dial_LCD->setFixedSize(QSize(45, 45));

    left_skill_icon->setPixmap(QPixmap(":/empty/images/empty_figure/skill_empty.png").scaled(70, 70));
    left_skill_dial_LCD->display(88);
    left_skill_dial_LCD->setDigitCount(2);
    left_skill_dial->setNotchesVisible(true);
    left_skill_dial->setMinimum(1);
    left_skill_dial->setMaximum(10);
    left_skill_dial->setEnabled(true);
    left_skill_dial_LCD->setFrameShape(QFrame::NoFrame);

    auto left_skill_layout_comb_1 = new QGridLayout;
    left_skill_layout_comb_1->addWidget(left_skill_icon, 0, 0, 1, 2, Qt::AlignCenter);
    left_skill_layout_comb_1->addWidget(left_skill_dial, 1, 0, Qt::AlignCenter);
    left_skill_layout_comb_1->addWidget(left_skill_dial_LCD, 1, 1, Qt::AlignCenter);
    left_skill_layout_comb_1->setVerticalSpacing(21);
    left_skill_layout_comb_1->setHorizontalSpacing(8);

    QVector<QLabel*> left_skill_consume{};
    QVector<QLabel*> left_skill_consume_number{};
    for (int i = 0; i < 5; ++i)
    {
        QLabel *label = new QLabel;
        label->setFixedSize(QSize(50, 50));
        label->setPixmap(QPixmap(":/empty/images/empty_figure/skill_consume_empty.png").scaled(46, 50));
        label->setAlignment(Qt::AlignCenter);
        left_skill_consume.push_back(label);
    }
    for (int i = 0; i < 5; ++i)
    {
        QLabel *label = new QLabel;
        label->setFixedSize(QSize(50, 18));
        label->setText("");
        QFont font;
        font.setPixelSize(18);
        font.setBold(true);
        font.setFamily("Arial");
        font.setStyleHint(QFont::SansSerif);
        label->setFont(font);
        label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        left_skill_consume_number.push_back(label);
    }

    auto left_skill_layout_comb_2 = new QGridLayout;
    for (int i = 0; i < 5; ++i)
    {
        left_skill_layout_comb_2->addWidget(left_skill_consume[i], 0, i);
        left_skill_layout_comb_2->addWidget(left_skill_consume_number[i], 1, i);
    }
    left_skill_layout_comb_2->setHorizontalSpacing(10);
    left_skill_layout_comb_2->setVerticalSpacing(2);

    auto left_skill_name = new QLabel;
    auto left_skill_cd = new QLCDNumber;
    left_skill_name->setText(tr("大神的睿智 A++"));
    QFont font;
    font.setPixelSize(16);
    font.setFamily("Dengxian");
    font.setWeight(QFont::Medium);
    font.setStyleHint(QFont::SansSerif);
    left_skill_name->setFont(font);
    left_skill_name->setMaximumWidth(180);
    left_skill_cd->setDigitCount(2);
    left_skill_cd->display(88);
    left_skill_cd->setFixedSize(QSize(40, 30));
    left_skill_cd->setFrameShape(QFrame::NoFrame);

    auto box_name = new QGroupBox;
    auto box_name_layout = new QGridLayout;
    box_name->setTitle(tr("Skill"));
    box_name->setAlignment(Qt::AlignLeft);
    box_name_layout->addWidget(left_skill_name, 0, 0, Qt::AlignCenter);
    box_name->setLayout(box_name_layout);
    box_name->setContentsMargins(0, 8, 0, 0);
    auto box_cd = new QGroupBox;
    auto box_cd_layout = new QGridLayout;
    box_cd->setTitle(tr("CD"));
    box_cd->setAlignment(Qt::AlignLeft);
    box_cd_layout->addWidget(left_skill_cd, 0, 0, Qt::AlignCenter);
    box_cd->setLayout(box_cd_layout);
    box_cd->setContentsMargins(0, 8, 0, 0);

    auto left_skill_layout_comb_3 = new QGridLayout;
    left_skill_layout_comb_3->addWidget(box_name, 0, 0);
    left_skill_layout_comb_3->addWidget(box_cd, 0, 1);
    left_skill_layout_comb_3->setColumnStretch(0, 5);
    left_skill_layout_comb_3->setColumnStretch(1, 1);
    left_skill_layout_comb_3->setHorizontalSpacing(15);

    auto left_skill_layout_comb = new QGridLayout;
    left_skill_layout_comb->addLayout(left_skill_layout_comb_1, 0, 0, 2, 1);
    left_skill_layout_comb->addLayout(left_skill_layout_comb_2, 1, 1);
    left_skill_layout_comb->addLayout(left_skill_layout_comb_3, 0, 1);
    left_skill_layout_comb->setVerticalSpacing(15);
    left_skill_layout_comb->setHorizontalSpacing(20);

    auto left_skill_widget = new QWidget;
    left_skill_widget->setLayout(left_skill_layout_comb);
    left_skill_widget->setFixedSize(left_skill_widget->sizeHint());
    qDebug() << "left" << left_skill_widget->sizeHint();

    left_skill_vector_icon.push_back(left_skill_icon);
    left_skill_vector_dial.push_back(left_skill_dial);
    left_skill_vector_dial_LCD.push_back(left_skill_dial_LCD);
    left_skill_vector_consume.push_back(left_skill_consume);
    left_skill_vector_consume_number.push_back(left_skill_consume_number);
    left_skill_vector_name.push_back(left_skill_name);
    left_skill_vector_cd.push_back(left_skill_cd);
    left_skill_vector_widget.push_back(left_skill_widget);
}

void resource_consume::set_lower_right_widget()
{
    auto right_skill_icon = new QLabel;
    auto right_skill_dial = new QDial;
    auto right_skill_dial_LCD = new QLCDNumber;

    right_skill_icon->setFixedSize(QSize(70, 70));
    right_skill_dial->setFixedSize(QSize(55, 55));
    right_skill_dial_LCD->setFixedSize(QSize(45, 45));

    right_skill_icon->setPixmap(QPixmap(":/empty/images/empty_figure/skill_empty.png").scaled(70, 70));
    right_skill_dial->setNotchesVisible(true);
    right_skill_dial->setMinimum(1);
    right_skill_dial->setMaximum(10);
    right_skill_dial_LCD->display(88);
    right_skill_dial_LCD->setDigitCount(2);
    right_skill_dial_LCD->setFrameShape(QFrame::NoFrame);

    auto right_skill_layout_comb_1 = new QGridLayout;
    right_skill_layout_comb_1->addWidget(right_skill_icon, 0, 0, 1, 2, Qt::AlignCenter);
    right_skill_layout_comb_1->addWidget(right_skill_dial, 1, 0, Qt::AlignCenter);
    right_skill_layout_comb_1->addWidget(right_skill_dial_LCD, 1, 1, Qt::AlignCenter);
    right_skill_layout_comb_1->setVerticalSpacing(21);
    right_skill_layout_comb_1->setHorizontalSpacing(8);

    QVector<QLabel*> right_skill_consume{};
    QVector<QLabel*> right_skill_consume_number{};
    for (int i = 0; i < 27; ++i)
    {
        QLabel *label = new QLabel;
        label->setFixedSize(QSize(32, 32));
        label->setPixmap(QPixmap(":/empty/images/empty_figure/skill_consume_empty.png").scaled(29, 32));
        label->setAlignment(Qt::AlignCenter);
        right_skill_consume.push_back(label);
    }
    for (int i = 0; i < 27; ++i)
    {
        QLabel *label = new QLabel;
        label->setFixedSize(QSize(32, 11));
        label->setText("");
        QFont font;
        font.setPixelSize(11);
        font.setFamily("Arial");
        font.setStyleHint(QFont::SansSerif);
        font.setBold(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        right_skill_consume_number.push_back(label);
    }

    auto right_skill_layout_comb_2 = new QGridLayout;
    auto right_skill_layout_comb_3 = new QGridLayout;
    auto right_skill_layout_comb_4 = new QGridLayout;
    auto right_skill_layout_comb_234 = new QGridLayout;
    for (int i = 0; i < 9; ++i)
    {
        right_skill_layout_comb_2->addWidget(right_skill_consume[i], 0, i);
        right_skill_layout_comb_2->addWidget(right_skill_consume_number[i], 1, i);
        right_skill_layout_comb_3->addWidget(right_skill_consume[i + 9], 0, i);
        right_skill_layout_comb_3->addWidget(right_skill_consume_number[i + 9], 1, i);
        right_skill_layout_comb_4->addWidget(right_skill_consume[i + 18], 0, i);
        right_skill_layout_comb_4->addWidget(right_skill_consume_number[i + 18], 1, i);
    }
    right_skill_layout_comb_2->setVerticalSpacing(0);
    right_skill_layout_comb_2->setHorizontalSpacing(10);
    right_skill_layout_comb_3->setVerticalSpacing(0);
    right_skill_layout_comb_3->setHorizontalSpacing(10);
    right_skill_layout_comb_4->setVerticalSpacing(0);
    right_skill_layout_comb_4->setHorizontalSpacing(10);
    right_skill_layout_comb_234->addLayout(right_skill_layout_comb_2, 0, 0);
    right_skill_layout_comb_234->addLayout(right_skill_layout_comb_3, 1, 0);
    right_skill_layout_comb_234->addLayout(right_skill_layout_comb_4, 2, 0);

    auto right_skill_layout_comb = new QGridLayout;
    right_skill_layout_comb->addLayout(right_skill_layout_comb_1, 0, 0);
    right_skill_layout_comb->addLayout(right_skill_layout_comb_234, 0, 1);
    right_skill_layout_comb->setHorizontalSpacing(20);

    auto right_skill_widget = new QWidget;
    right_skill_widget->setLayout(right_skill_layout_comb);
    right_skill_widget->setFixedSize(right_skill_widget->sizeHint());
    qDebug() << right_skill_widget->sizeHint();

    right_skill_vector_icon.push_back(right_skill_icon);
    right_skill_vector_dial.push_back(right_skill_dial);
    right_skill_vector_dial_LCD.push_back(right_skill_dial_LCD);
    right_skill_vector_consume.push_back(right_skill_consume);
    right_skill_vector_consume_number.push_back(right_skill_consume_number);
    right_skill_vector_widget.push_back(right_skill_widget);
}

void resource_consume::set_lower_combined_objects()
{
    for (int i = 0; i < 3; ++i) set_lower_skill_widget();
    for (int i = 0; i < 3; ++i) set_lower_right_widget();
}

void resource_consume::set_middle_left_widget()
{
    left_levelup_dial = new QDial;
    left_ascension_dial = new QDial;
    left_levelup_dial_LCD = new QLCDNumber;
    left_ascension_dial_LCD = new QLCDNumber;

    left_levelup_dial->setFixedSize(QSize(55, 55));
    left_ascension_dial->setFixedSize(QSize(55, 55));
    left_levelup_dial_LCD->setFixedSize(QSize(45, 45));
    left_ascension_dial_LCD->setFixedSize(QSize(45, 45));

    left_levelup_dial_LCD->display(88);
    left_levelup_dial_LCD->setDigitCount(2);
    left_ascension_dial_LCD->display(88);
    left_ascension_dial_LCD->setDigitCount(2);
    left_levelup_dial_LCD->setFrameShape(QFrame::NoFrame);
    left_ascension_dial_LCD->setFrameShape(QFrame::NoFrame);
    left_levelup_dial->setNotchesVisible(true);
    left_levelup_dial->setMinimum(1);
    left_levelup_dial->setMaximum(100);
    left_levelup_dial->setEnabled(true);
    left_ascension_dial->setNotchesVisible(true);
    left_ascension_dial->setMinimum(0);
    left_ascension_dial->setMaximum(5);
    left_ascension_dial->setEnabled(true);

    auto left_ascension_layout_comb_1 = new QGridLayout;
    left_ascension_layout_comb_1->addWidget(left_levelup_dial, 0, 0, Qt::AlignCenter);
    left_ascension_layout_comb_1->addWidget(left_levelup_dial_LCD, 0, 1, Qt::AlignCenter);
    left_ascension_layout_comb_1->addWidget(left_ascension_dial, 1, 0, Qt::AlignCenter);
    left_ascension_layout_comb_1->addWidget(left_ascension_dial_LCD, 1, 1, Qt::AlignCenter);
    left_ascension_layout_comb_1->setHorizontalSpacing(8);
    left_ascension_layout_comb_1->setVerticalSpacing(36);

    for (int i = 0; i < 6; ++i)
    {
        QLabel *label = new QLabel;
        label->setFixedSize(QSize(50, 50));
        label->setPixmap(QPixmap(":/empty/images/empty_figure/skill_consume_empty.png").scaled(46, 50));
        label->setAlignment(Qt::AlignCenter);
        if (i < 5)
            left_ascension_consume.push_back(label);
        else
            left_levelup_consume = label;
    }
    for (int i = 0; i < 6; ++i)
    {
        QLabel *label = new QLabel;
        label->setFixedSize(QSize(50, 18));
        label->setText("");
        QFont font;
        font.setPixelSize(18);
        font.setBold(true);
        font.setFamily("Arial");
        font.setStyleHint(QFont::SansSerif);
        label->setFont(font);
        label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        if (i < 5)
            left_ascension_consume_number.push_back(label);
        else
            left_levelup_consume_number = label;
    }

    auto left_ascension_layout_comb_2 = new QGridLayout;
    for (int i = 0; i < 5; ++i)
    {
        left_ascension_layout_comb_2->addWidget(left_ascension_consume[i], 0, i);
        left_ascension_layout_comb_2->addWidget(left_ascension_consume_number[i], 1, i);
    }
    left_ascension_layout_comb_2->setHorizontalSpacing(10);
    left_ascension_layout_comb_2->setVerticalSpacing(2);

    auto left_ascension_layout_comb_3 = new QGridLayout;
    left_ascension_layout_comb_3->addWidget(left_levelup_consume, 0, 0, Qt::AlignLeft | Qt::AlignVCenter);
    left_ascension_layout_comb_3->addWidget(left_levelup_consume_number, 1, 0, Qt::AlignLeft | Qt::AlignVCenter);
    left_ascension_layout_comb_3->setHorizontalSpacing(10);
    left_ascension_layout_comb_3->setVerticalSpacing(5);

    left_levelup_rarity = new QLabel;
    left_levelup_rarity->setText(tr("Rarity: ") + QString("5"));
    QFont font;
    font.setPixelSize(16);
    font.setFamily("Dengxian");
    font.setWeight(QFont::Medium);
    font.setStyleHint(QFont::SansSerif);
    left_levelup_rarity->setFont(font);
    left_levelup_rarity->setMaximumWidth(180);
    auto left_levelup_rarity_box = new QGroupBox;
    auto left_levelup_rarity_layout = new QGridLayout;
    left_levelup_rarity_layout->addWidget(left_levelup_rarity, 0, 0, Qt::AlignCenter);
    left_levelup_rarity_box->setTitle(tr("Ascention"));
    left_levelup_rarity_box->setLayout(left_levelup_rarity_layout);

    auto left_ascension_layout_comb = new QGridLayout;
    left_ascension_layout_comb->addLayout(left_ascension_layout_comb_1, 0, 0, 2, 1);
    left_ascension_layout_comb->addLayout(left_ascension_layout_comb_2, 1, 1, 1, 5);
    left_ascension_layout_comb->addWidget(left_levelup_rarity_box, 0, 1, 1, 4);
    left_ascension_layout_comb->addLayout(left_ascension_layout_comb_3, 0, 5);
    left_ascension_layout_comb->setVerticalSpacing(15);
    left_ascension_layout_comb->setHorizontalSpacing(20);

    left_ascension_widget = new QWidget;
    left_ascension_widget->setLayout(left_ascension_layout_comb);
    left_ascension_widget->setFixedSize(QSize(444, 172));
    qDebug() << "left ascension" << left_ascension_widget->size();
}

void resource_consume::set_middle_right_widget()
{
    right_levelup_dial = new QDial;
    right_ascension_dial = new QDial;
    right_levelup_dial_LCD = new QLCDNumber;
    right_ascension_dial_LCD = new QLCDNumber;

    right_levelup_dial->setFixedSize(QSize(55, 55));
    right_ascension_dial->setFixedSize(QSize(55, 55));
    right_levelup_dial_LCD->setFixedSize(QSize(45, 45));
    right_ascension_dial_LCD->setFixedSize(QSize(45, 45));

    right_levelup_dial_LCD->display(88);
    right_levelup_dial_LCD->setDigitCount(2);
    right_ascension_dial_LCD->display(88);
    right_ascension_dial_LCD->setDigitCount(2);
    right_levelup_dial_LCD->setFrameShape(QFrame::NoFrame);
    right_ascension_dial_LCD->setFrameShape(QFrame::NoFrame);
    right_levelup_dial->setNotchesVisible(true);
    right_levelup_dial->setMinimum(1);
    right_levelup_dial->setMaximum(100);
    right_ascension_dial->setNotchesVisible(true);
    right_ascension_dial->setMinimum(0);
    right_ascension_dial->setMaximum(5);

    auto right_ascension_layout_comb_1 = new QGridLayout;
    right_ascension_layout_comb_1->addWidget(right_levelup_dial, 0, 0, Qt::AlignCenter);
    right_ascension_layout_comb_1->addWidget(right_levelup_dial_LCD, 0, 1, Qt::AlignCenter);
    right_ascension_layout_comb_1->addWidget(right_ascension_dial, 1, 0, Qt::AlignCenter);
    right_ascension_layout_comb_1->addWidget(right_ascension_dial_LCD, 1, 1, Qt::AlignCenter);
    right_ascension_layout_comb_1->setHorizontalSpacing(8);
    right_ascension_layout_comb_1->setVerticalSpacing(36);

    for (int i = 0; i < 27; ++i)
    {
        QLabel *label = new QLabel;
        label->setFixedSize(QSize(32, 32));
        label->setPixmap(QPixmap(":/empty/images/empty_figure/skill_consume_empty.png").scaled(29, 32));
        label->setAlignment(Qt::AlignCenter);
        right_ascension_consume.push_back(label);
    }
    for (int i = 0; i < 27; ++i)
    {
        QLabel *label = new QLabel;
        label->setFixedSize(QSize(32, 11));
        label->setText("");
        QFont font;
        font.setPixelSize(11);
        font.setFamily("Arial");
        font.setStyleHint(QFont::SansSerif);
        font.setBold(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        right_ascension_consume_number.push_back(label);
    }

    auto right_ascension_layout_comb_2 = new QGridLayout;
    auto right_ascension_layout_comb_3 = new QGridLayout;
    auto right_ascension_layout_comb_4 = new QGridLayout;
    auto right_ascension_layout_comb_234 = new QGridLayout;
    for (int i = 0; i < 9; ++i)
    {
        right_ascension_layout_comb_2->addWidget(right_ascension_consume[i], 0, i);
        right_ascension_layout_comb_2->addWidget(right_ascension_consume_number[i], 1, i);
        right_ascension_layout_comb_3->addWidget(right_ascension_consume[i + 9], 0, i);
        right_ascension_layout_comb_3->addWidget(right_ascension_consume_number[i + 9], 1, i);
        right_ascension_layout_comb_4->addWidget(right_ascension_consume[i + 18], 0, i);
        right_ascension_layout_comb_4->addWidget(right_ascension_consume_number[i + 18], 1, i);
    }
    right_ascension_layout_comb_2->setVerticalSpacing(0);
    right_ascension_layout_comb_2->setHorizontalSpacing(10);
    right_ascension_layout_comb_3->setVerticalSpacing(0);
    right_ascension_layout_comb_3->setHorizontalSpacing(10);
    right_ascension_layout_comb_4->setVerticalSpacing(0);
    right_ascension_layout_comb_4->setHorizontalSpacing(10);
    right_ascension_layout_comb_234->addLayout(right_ascension_layout_comb_2, 0, 0);
    right_ascension_layout_comb_234->addLayout(right_ascension_layout_comb_3, 1, 0);
    right_ascension_layout_comb_234->addLayout(right_ascension_layout_comb_4, 2, 0);

    auto right_ascension_layout_comb = new QGridLayout;
    right_ascension_layout_comb->addLayout(right_ascension_layout_comb_1, 0, 0);
    right_ascension_layout_comb->addLayout(right_ascension_layout_comb_234, 0, 1);
    right_ascension_layout_comb->setHorizontalSpacing(20);

    right_ascension_widget = new QWidget;
    right_ascension_widget->setLayout(right_ascension_layout_comb);
    right_ascension_widget->setFixedSize(QSize(522, 172));
    qDebug() << "right ascension" << right_ascension_widget->size();
}

void resource_consume::set_left_information_widget()
{
    QFont font;
    font.setPixelSize(14);
    font.setFamily("Dengxian");
    font.setWeight(QFont::Medium);
    font.setStyleHint(QFont::SansSerif);

    left_info_servant_name = new QLabel;
    left_info_servant_nobel = new QLabel;
    left_info_servant_attribute = new QLabel;
    left_info_servant_name->setText("阿尔托莉雅·潘德拉贡");
    left_info_servant_nobel->setText("誓约胜利之剑");
    left_info_servant_attribute->setText("秩序·善·地");
    left_info_servant_name->setFont(font);
    left_info_servant_nobel->setFont(font);
    left_info_servant_attribute->setFont(font);

    left_info_servant_class = new QLabel;
    left_info_servant_class->setFixedSize(QSize(40, 40));
    left_info_servant_class->setPixmap(QPixmap(":/servant_class/images/servant_class/all_on.png").scaled(40, 40));

    left_info_servant_nobel_color = new QLabel;
    left_info_servant_nobel_color->setFixedSize(QSize(40, 40));
    left_info_servant_nobel_color->setPixmap(QPixmap(":/card_color/images/card_color/Buster.png").scaled(40, 40));

    auto left_info_layout_1 = new QGridLayout;
    for (int i = 0; i < 6; i++)
    {
        auto radio = new QRadioButton;
        radio->setText(QVariant(i).toString());
        left_info_priority.push_back(radio);
        left_info_layout_1->addWidget(radio, i / 3, i % 3, Qt::AlignCenter);
    }
    left_info_priority[0]->setChecked(true);
    left_info_existance = new QCheckBox;
    left_info_existance->setText(tr("Exist"));
    left_info_layout_1->addWidget(left_info_existance, 0, 3, 2, 1, Qt::AlignCenter);
    auto left_info_layout_2 = new QHBoxLayout;
    left_info_layout_2->addStretch();
    left_info_layout_2->addLayout(left_info_layout_1);
    left_info_layout_2->addStretch();

    auto left_info_layout_5 = new QGridLayout;
    left_info_layout_5->addWidget(left_info_servant_name, 0, 0, 1, 3, Qt::AlignCenter);
    left_info_layout_5->addWidget(left_info_servant_nobel_color, 1, 0, 2, 1, Qt::AlignLeft | Qt::AlignVCenter);
    left_info_layout_5->addWidget(left_info_servant_class, 1, 2, 2, 1, Qt::AlignRight | Qt::AlignVCenter);
    left_info_layout_5->addWidget(left_info_servant_nobel, 1, 1, Qt::AlignCenter);
    left_info_layout_5->addWidget(left_info_servant_attribute, 2, 1, Qt::AlignCenter);
    left_info_layout_5->addLayout(left_info_layout_2, 3, 0, 1, 3, Qt::AlignCenter);

    left_info_follow = new QGroupBox;
    left_info_follow->setTitle(tr("Follow"));
    left_info_follow->setCheckable(true);
    left_info_follow->setChecked(false);
    left_info_follow->setLayout(left_info_layout_5);

    auto left_info_main_layout = new QGridLayout;
    left_info_main_layout->addWidget(left_info_follow);

    left_info_widget = new QWidget;
    left_info_widget->setLayout(left_info_main_layout);
    left_info_widget->setFixedWidth(444);
    qDebug() << "left information" << left_info_widget->size();
}

void resource_consume::set_right_costume_widget()
{
    right_info_icon = new QLabel;
    right_info_icon->setFixedSize(QSize(138, 150));
    right_info_icon->setPixmap(QPixmap(":/empty/images/empty_figure/servant_empty.png").scaled(138, 150));

    right_costume_combobox = new QComboBox;
    right_costume_combobox->setEnabled(true);

    right_costume_group = new QGroupBox;
    auto right_costume_layout_comb_1 = new QGridLayout;
    right_costume_layout_comb_1->addWidget(right_costume_combobox);
    right_costume_group->setLayout(right_costume_layout_comb_1);
    right_costume_group->setTitle(tr("Costume"));
    right_costume_group->setEnabled(true);

    for (int i = 0; i < 5; ++i)
    {
        QLabel *label = new QLabel;
        label->setFixedSize(QSize(50, 50));
        label->setPixmap(QPixmap(":/empty/images/empty_figure/skill_consume_empty.png").scaled(46, 50));
        label->setAlignment(Qt::AlignCenter);
        right_costume_consume.push_back(label);
    }
    for (int i = 0; i < 5; ++i)
    {
        QLabel *label = new QLabel;
        label->setFixedSize(QSize(50, 18));
        label->setText("");
        QFont font;
        font.setPixelSize(18);
        font.setBold(true);
        font.setFamily("Arial");
        font.setStyleHint(QFont::SansSerif);
        label->setFont(font);
        label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        right_costume_consume_number.push_back(label);
    }

    auto right_costume_layout_comb_2 = new QGridLayout;
    for (int i = 0; i < 5; ++i)
    {
        right_costume_layout_comb_2->addWidget(right_costume_consume[i], 0, i);
        right_costume_layout_comb_2->addWidget(right_costume_consume_number[i], 1, i);
    }
    right_costume_layout_comb_2->setHorizontalSpacing(10);
    right_costume_layout_comb_2->setVerticalSpacing(2);

    auto right_costume_layout_comb = new QGridLayout;
    right_costume_layout_comb->addWidget(right_info_icon, 0, 0, 2, 1, Qt::AlignCenter);
    right_costume_layout_comb->addWidget(right_costume_group, 0, 1);
    right_costume_layout_comb->addLayout(right_costume_layout_comb_2, 1, 1);
    right_costume_layout_comb->setVerticalSpacing(15);
    right_costume_layout_comb->setHorizontalSpacing(20);

    right_costume_widget = new QWidget;
    right_costume_widget->setLayout(right_costume_layout_comb);
    right_costume_widget->setFixedWidth(right_costume_widget->sizeHint().width());
    qDebug() << "right costume" << right_costume_widget->size();
}

void resource_consume::set_layout()
{
    QGridLayout *layout_main = new QGridLayout;
    layout_main->addWidget(left_info_widget, 0, 0);
    layout_main->addWidget(right_costume_widget, 0, 1);
    layout_main->addWidget(left_ascension_widget, 1, 0);
    layout_main->addWidget(right_ascension_widget, 1, 1);
    layout_main->addWidget(left_skill_vector_widget[0], 2, 0);
    layout_main->addWidget(left_skill_vector_widget[1], 3, 0);
    layout_main->addWidget(left_skill_vector_widget[2], 4, 0);
    layout_main->addWidget(right_skill_vector_widget[0], 2, 1);
    layout_main->addWidget(right_skill_vector_widget[1], 3, 1);
    layout_main->addWidget(right_skill_vector_widget[2], 4, 1);

    QWidget *left_skill_layout_main_widget = new QWidget;
    left_skill_layout_main_widget->setLayout(layout_main);
    left_skill_layout_main_widget->setFixedWidth(left_skill_layout_main_widget->sizeHint().width());
    // setCentralWidget(left_skill_layout_main_widget);

    QScrollArea *scroll = new QScrollArea;
    // QGridLayout *scroll_layout = new QGridLayout;
    // scroll_layout->addWidget(left_skill_layout_main_widget, 0, 0);
    // scroll->setLayout(scroll_layout);
    scroll->setWidget(left_skill_layout_main_widget);
    scroll->setFrameShape(QFrame::NoFrame);
    // scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setFixedWidth(left_skill_layout_main_widget->sizeHint().width()
        + 2 * scroll->verticalScrollBar()->sizeHint().width());

    auto layout_final = new QVBoxLayout;
    layout_final->addWidget(scroll);
    setLayout(layout_final);
    setWindowFlags(Qt::Window);
}

void resource_consume::set_widget_internal_connection()
{
    // NOTE!!!
    // this function should be static connection only, so no database information should be included here
    // for database-related connection implementation, go to init_database_widget_connection

    // combination
    QVector<QDial*> left_dials = { left_ascension_dial, left_levelup_dial,
        left_skill_vector_dial[0], left_skill_vector_dial[1], left_skill_vector_dial[2] };
    QVector<QDial*> right_dials = { right_ascension_dial, right_levelup_dial,
        right_skill_vector_dial[0], right_skill_vector_dial[1], right_skill_vector_dial[2] };
    QVector<QLCDNumber*> left_LCDs = { left_ascension_dial_LCD, left_levelup_dial_LCD,
        left_skill_vector_dial_LCD[0], left_skill_vector_dial_LCD[1], left_skill_vector_dial_LCD[2] };
    QVector<QLCDNumber*> right_LCDs = { right_ascension_dial_LCD, right_levelup_dial_LCD,
        right_skill_vector_dial_LCD[0], right_skill_vector_dial_LCD[1], right_skill_vector_dial_LCD[2] };

    // dial-dial and dial-LCD control
    // if Qt::QueuedConnection not set, the right LCD won't change value when right dial value setted lower than left dial
    // reason: signal(valueChanged) -> [ check_dial_right_to_left -> signal(valueChanged) ]
    //         |-> emitter thread        |-> receiver thread
    // emitter thread will ignore the receiver's behavior, so using Qt::QueuedConnection to use receiver thread
    // this should be useful in looped emit-receive event
    // https://stackoverflow.com/questions/1144240/qt-how-to-call-slot-from-custom-c-code-running-in-a-different-thread
    for (int i = 0; i < 5; ++i)
    {
        // special case for levelup_dial: this check should be in resource_consume_connection
        // left_dial value may well have changed after check_dial_levelup_to_ascension
        // it might not have conflict situation in right and left dial, however, the calling process may not well-behaved
        // define the following code in check_dial_levelup_to_ascension
        if ((i != 0) && (i != 1))
        {
            connect(left_dials[i], &QDial::valueChanged, this, &resource_consume::check_dial_left_to_right);
            connect(right_dials[i], &QDial::valueChanged, this, &resource_consume::check_dial_right_to_left, Qt::QueuedConnection);
            connect(left_dials[i], &QDial::valueChanged, left_LCDs[i], QOverload<int>::of(&QLCDNumber::display));
            connect(right_dials[i], &QDial::valueChanged, right_LCDs[i], QOverload<int>::of(&QLCDNumber::display));
        }
    }
    // overflow only occurs when level is 100
    connect(left_levelup_dial_LCD, &QLCDNumber::overflow, this, &resource_consume::check_levelup_LCD_overflow);
    connect(right_levelup_dial_LCD, &QLCDNumber::overflow, this, &resource_consume::check_levelup_LCD_overflow);

}

void resource_consume::check_dial_right_to_left(int in_value)
{
    // if right dial value smaller than left dial, set right dial the left dial value
    // WARNING!!! USING sender()!!!
    QDial *right_dial = qobject_cast<QDial*>(sender());
    QDial *left_dial = nullptr;
    if (right_dial == right_levelup_dial) left_dial = left_levelup_dial;
    else if (right_dial == right_ascension_dial) left_dial = left_ascension_dial;
    else if (right_dial == right_skill_vector_dial[0]) left_dial = left_skill_vector_dial[0];
    else if (right_dial == right_skill_vector_dial[1]) left_dial = left_skill_vector_dial[1];
    else if (right_dial == right_skill_vector_dial[2]) left_dial = left_skill_vector_dial[2];
    if (in_value < left_dial->value()) right_dial->setValue(left_dial->value());
}

void resource_consume::check_dial_left_to_right(int in_value)
{
    // if left dial value larger than right dial, set right dial the left dial value
    // WARNING!!! USING sender()!!!
    QDial *left_dial = qobject_cast<QDial*>(sender());
    QDial *right_dial = nullptr;
    if (left_dial == left_levelup_dial) right_dial = right_levelup_dial;
    else if (left_dial == left_ascension_dial) right_dial = right_ascension_dial;
    else if (left_dial == left_skill_vector_dial[0]) right_dial = right_skill_vector_dial[0];
    else if (left_dial == left_skill_vector_dial[1]) right_dial = right_skill_vector_dial[1];
    else if (left_dial == left_skill_vector_dial[2]) right_dial = right_skill_vector_dial[2];
    if (in_value > right_dial->value()) right_dial->setValue(left_dial->value());
}

void resource_consume::check_ascension_5(int in_value)
{
    // if left dial value larger than right dial, set right dial the left dial value
    // WARNING!!! USING sender()!!!
    QDial *dial = qobject_cast<QDial*>(sender());
    QLCDNumber *LCD = nullptr;
    qDebug() << LCD;
    if (dial == left_ascension_dial) LCD = left_ascension_dial_LCD;
    else if (dial == right_ascension_dial) LCD = right_ascension_dial_LCD;
    if (in_value == 5)
        LCD->display("UP");
    else
        LCD->display(in_value);
}
