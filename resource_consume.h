#ifdef WIN32
// character in chinese can't display in visual studio
// if Qt environment, possibly you can delete this
// this line may be included in all header files
// https://blog.csdn.net/nabariou/article/details/60468627
#pragma execution_character_set("utf-8")  
#endif

#ifndef RESOURCE_H
#define RESOURCE_H

#include <QtWidgets>
#include "treemodel.h"

class resource_consume : public QDialog
{
	Q_OBJECT;
	
	//--- Layout

	// left_skill_combination
	QVector<QLabel*> left_skill_vector_icon{};
	QVector<QDial*> left_skill_vector_dial{};
	QVector<QLCDNumber*> left_skill_vector_dial_LCD{};
	QVector<QVector<QLabel*>> left_skill_vector_consume{};
	QVector<QVector<QLabel*>> left_skill_vector_consume_number{};
	QVector<QLabel*> left_skill_vector_name{};
	QVector<QLCDNumber*> left_skill_vector_cd{};
	QVector<QWidget*> left_skill_vector_widget{};

	// right_skill_combination
	QVector<QLabel*> right_skill_vector_icon{};
	QVector<QDial*> right_skill_vector_dial{};
	QVector<QLCDNumber*> right_skill_vector_dial_LCD{};
	QVector<QVector<QLabel*>> right_skill_vector_consume{};
	QVector<QVector<QLabel*>> right_skill_vector_consume_number{};
	QVector<QWidget*> right_skill_vector_widget{};

	// left_ascension
	QDial *left_levelup_dial = nullptr;
	QLCDNumber *left_levelup_dial_LCD = nullptr;
	QDial *left_ascension_dial = nullptr;
	QLCDNumber *left_ascension_dial_LCD = nullptr;
	QLabel *left_levelup_consume = nullptr;
	QLabel *left_levelup_consume_number = nullptr;
	QVector<QLabel*> left_ascension_consume{};
	QVector<QLabel*> left_ascension_consume_number{};
	QLabel *left_levelup_rarity = nullptr;
	QWidget *left_ascension_widget = nullptr;

	// right_ascension
	QDial *right_levelup_dial = nullptr;
	QLCDNumber *right_levelup_dial_LCD = nullptr;
	QDial *right_ascension_dial = nullptr;
	QLCDNumber *right_ascension_dial_LCD = nullptr;
	QVector<QLabel*> right_ascension_consume{};
	QVector<QLabel*> right_ascension_consume_number{};
	QWidget *right_ascension_widget = nullptr;

	// left_information
	QLabel *left_info_servant_name = nullptr;
	QLabel *left_info_servant_nobel = nullptr;
	QLabel *left_info_servant_nobel_color = nullptr;
	QLabel *left_info_servant_class = nullptr;
	QLabel *left_info_servant_attribute = nullptr;
	QVector<QRadioButton*> left_info_priority{};
	QCheckBox *left_info_existance = nullptr;
	QGroupBox *left_info_follow = nullptr;
	QWidget *left_info_widget = nullptr;

	// right costume
	QLabel *right_info_icon = nullptr;
	QComboBox *right_costume_combobox = nullptr;
	QGroupBox *right_costume_group = nullptr;
	QVector<QLabel*> right_costume_consume{};
	QVector<QLabel*> right_costume_consume_number{};
	QWidget *right_costume_widget = nullptr;

	// function
	void set_layout();
	void set_lower_skill_widget();
	void set_lower_right_widget();
	void set_lower_combined_objects();
	void set_middle_left_widget();
	void set_middle_right_widget();
	void set_left_information_widget();
	void set_right_costume_widget();

	//--- Data process

	// database
	QVector<QString> ini_setting_data{};
	QVector<TreeModel*> *wiki_database = nullptr;
	QVector<QPixmap> *servant_icon_button_image = nullptr;
	int id_number = 0;
    void init_database_display();
    void init_database_consume();

    // data in database
    QVector<QVector<int>> database_skill_consume{ 10, {} };
    QVector<QVector<int>> database_ascension_consume{ 4, {}};
    QVector<QVector<int>> database_costume_consume{};
    int database_skill_rarity = -1;
    int database_ascension_rarity = -1;
    QVector<QVector<int>> database_costume_consume_total;

    // user data in class
    TreeModel *user_data = nullptr;
    void init_user_data();
    // <servant_xxx>
    int user_servant_id = 0;
    //   <status>
    int user_follow = 0;
    int user_priority = 0;
    int user_existance = 0;
    //   </status>
    //   <actual>
    int user_actual_ascension = 0;
    int user_actual_level = 1;
    int user_actual_skill_1 = 1;
    int user_actual_skill_2 = 1;
    int user_actual_skill_3 = 1;
    //   </actual>
    //   <ideal>
    int user_ideal_ascension = 0;
    int user_ideal_level = 1;
    int user_ideal_skill_1 = 1;
    int user_ideal_skill_2 = 1;
    int user_ideal_skill_3 = 1;
    //   </ideal>
    //   <costume>
    QVector<int> user_costume;
    //   </costume>
    // </servant_xxx>
    // total information
    QVector<QVector<int>> list_user_skill_consume{ 3, {} };
    QVector<int> list_user_ascension_and_lvup_consume{};
    QVector<QVector<int>> list_user_costume_consume{};

    // utility
    QString consume_int(int val);
    void list_minus(QVector<int> &vec_1, const QVector<int> &vec_2);
    void list_plus(QVector<int> &vec_1, const QVector<int> &vec_2);

	//--- Widget connection
    void set_widget_internal_connection();
    void set_widget_database_connection();

public slots:
	void data_transin(
		QVector<QString> ini_setting,
		QVector<TreeModel*> *wiki,
		QVector<QPixmap> *servant_icon,
		int id,
		TreeModel *user_dat);

private slots:
    //--- Layout
	void check_dial_left_to_right(int in_value);
    void check_dial_right_to_left(int in_value);

    //--- connection
    void connection_left_skill_dial();
    void connection_right_skill_dial();
    void connection_left_ascension_dial();
    void connection_levelup_dial();
    void connection_ascension_and_lvup_consume();
    void connection_ascension_levelup_mess();

public:
	resource_consume(QWidget *parent = nullptr);
	~resource_consume();
};

#endif // MAINWINDOW_H
