#pragma once

#include <QtWidgets>

#include "qclickablefigurelabel.h"
#include "xml_editable_mainwindow.h"

class tab_widget_servant : public QWidget
{
	Q_OBJECT;

	//--- HAND MADE PARAMETERS
	const int SCALE_SIZE = 40;  // servant class label width and height (px)

	//--- A. servant class labels
	QClickableFigureLabel *class_saber;
	QClickableFigureLabel *class_archer;
	QClickableFigureLabel *class_lancer;
	QClickableFigureLabel *class_rider;
	QClickableFigureLabel *class_caster;
	QClickableFigureLabel *class_assassin;
	QClickableFigureLabel *class_berserker;
	QClickableFigureLabel *class_shielder;
	QClickableFigureLabel *class_ruler;
	QClickableFigureLabel *class_avenger;
	QClickableFigureLabel *class_alterego;
	QClickableFigureLabel *class_mooncancer;
	QClickableFigureLabel *class_foreigner;
	QClickableFigureLabel *class_all_on;
	QClickableFigureLabel *class_all_off;
	QHBoxLayout *servant_class_layout;
	void set_servant_class_label();
	void set_servant_class_layout();
	void set_servant_class_connection();

	//--- B. sort
	QRadioButton *sort_button_id_ascending;
	QRadioButton *sort_button_id_descending;
	QRadioButton *sort_button_atk_ascending;
	QRadioButton *sort_button_atk_descending;
	QRadioButton *sort_button_hp_ascending;
	QRadioButton *sort_button_hp_descending;
	QButtonGroup *sort_button_group;
	QHBoxLayout *sort_button_layout;
	void set_sort_button();
	void set_sort_layout();

	//--- C. filter
	// QComboBox *filter_existence;
	// QComboBox *filter_urgency;
	// QComboBox *filter_card;
	// QComboBox *filter_nobel;
	// QComboBox *filter_gender;
	// QComboBox *filter_attribute;
	// rarity
	QPushButton *filter_rarity;
	QAction *filter_rarity_all;
	QAction *filter_rarity_5;
	QAction *filter_rarity_4;
	QAction *filter_rarity_3;
	QAction *filter_rarity_2;
	QAction *filter_rarity_1;
	QAction *filter_rarity_0;
	void set_filter_rarity();
	// other
	QVBoxLayout *filter_layout;
	void set_filter_button();
	void set_filter_layout();
	void set_filter_connection();

	//--- D. servant table
	QTableView *table_widget;
	QStandardItemModel *table_widget_model;
	QStandardItemModel *table_widget_model_origin;
	void set_table_widget();

	//--- N. layouot
	void set_main_widget_layout();
	QGridLayout *main_widget_layout;

public:
	tab_widget_servant(QWidget *parent);
	~tab_widget_servant();

private slots:
	//--- A. servant class labels
	void class_all_on_clicked_labelbehave();
	void class_all_off_clicked_labelbehave();
	//--- C. filter
	void filter_rarity_subitem_clicked_actionbehave(bool checked);
	void filter_rarity_all_clicked_actionbehave(bool checked);
};
