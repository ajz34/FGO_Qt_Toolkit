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

class resource_consume : public QDialog
{
	Q_OBJECT


		// left_skill
		/*
		* QLabel *left_skill_icon = nullptr;
		* QDial *left_skill_dial = nullptr;
		* QLCDNumber *left_skill_dial_LCD = nullptr;
		* QVector<QLabel*> left_skill_consume{};
		* QVector<QLabel*> left_skill_consume_number{};
		* QLabel *left_skill_name;
		* QLCDNumber *left_skill_cd;
		* QWidget *left_skill_widget = nullptr;
		*/

		// left_skill_combination
		QVector<QLabel*> left_skill_vector_icon{};
	QVector<QDial*> left_skill_vector_dial{};
	QVector<QLCDNumber*> left_skill_vector_dial_LCD{};
	QVector<QVector<QLabel*>> left_skill_vector_consume{};
	QVector<QVector<QLabel*>> left_skill_vector_consume_number{};
	QVector<QLabel*> left_skill_vector_name{};
	QVector<QLCDNumber*> left_skill_vector_cd{};
	QVector<QWidget*> left_skill_vector_widget{};

	// right_skill
	/*
	* QLabel* right_skill_icon;
	* QDial* right_skill_dial{};
	* QLCDNumber* right_skill_dial_LCD{};
	* QVector<QLabel*> right_skill_consume{};
	* QVector<QLabel*> right_skill_consume_number{};
	* QWidget* right_skill_widget{};
	*/

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
	QLabel *left_info_icon = nullptr;
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
	QComboBox *right_costume_combobox = nullptr;
	QGroupBox *right_costume_group = nullptr;
	QVector<QLabel*> right_costume_consume{};
	QVector<QLabel*> right_costume_consume_number{};
	QWidget *right_costume_widget = nullptr;

	void set_layout();
	void set_lower_skill_widget();
	void set_lower_right_widget();
	void set_lower_combined_objects();
	void set_middle_left_widget();
	void set_middle_right_widget();
	void set_left_information_widget();
	void set_right_costume_widget();
public:
	resource_consume(QWidget *parent = nullptr);
	~resource_consume();
};

#endif // MAINWINDOW_H
