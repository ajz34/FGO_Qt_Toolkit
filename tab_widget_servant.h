#pragma once

#include <QtWidgets>

#include "qclickablefigurelabel.h"
#include "xml_editable_mainwindow.h"
#include "treemodel.h"

class tab_widget_servant : public QWidget
{
	Q_OBJECT;

	//--- HAND MADE PARAMETERS
	const int SCALE_SIZE = 40;  // servant class label width and height (px)

	//--- A. servant class labels
	QClickableFigureLabel *class_saber = nullptr;
	QClickableFigureLabel *class_archer = nullptr;
	QClickableFigureLabel *class_lancer = nullptr;
	QClickableFigureLabel *class_rider = nullptr;
	QClickableFigureLabel *class_caster = nullptr;
	QClickableFigureLabel *class_assassin = nullptr;
	QClickableFigureLabel *class_berserker = nullptr;
	QClickableFigureLabel *class_shielder = nullptr;
	QClickableFigureLabel *class_ruler = nullptr;
	QClickableFigureLabel *class_avenger = nullptr;
	QClickableFigureLabel *class_alterego = nullptr;
	QClickableFigureLabel *class_mooncancer = nullptr;
	QClickableFigureLabel *class_foreigner = nullptr;
	QClickableFigureLabel *class_all_on = nullptr;
	QClickableFigureLabel *class_all_off = nullptr;
	QHBoxLayout *servant_class_layout = nullptr;
	void set_servant_class_label();
	void set_servant_class_layout();
	void set_servant_class_connection();

	//--- B. sort
	QRadioButton *sort_button_id_ascending = nullptr;
	QRadioButton *sort_button_id_descending = nullptr;
	QRadioButton *sort_button_atk_ascending = nullptr;
	QRadioButton *sort_button_atk_descending = nullptr;
	QRadioButton *sort_button_hp_ascending = nullptr;
	QRadioButton *sort_button_hp_descending = nullptr;
	QButtonGroup *sort_button_group = nullptr;
	QHBoxLayout *sort_button_layout = nullptr;
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
	QPushButton *filter_rarity = nullptr;
	QAction *filter_rarity_all = nullptr;
	QAction *filter_rarity_5 = nullptr;
	QAction *filter_rarity_4 = nullptr;
	QAction *filter_rarity_3 = nullptr;
	QAction *filter_rarity_2 = nullptr;
	QAction *filter_rarity_1 = nullptr;
	QAction *filter_rarity_0 = nullptr;
	void set_filter_rarity();
	// other
	QVBoxLayout *filter_layout = nullptr;
	void set_filter_button();
	void set_filter_layout();
	void set_filter_connection();

	//--- D. servant table
	QTableView *table_widget = nullptr;
	QStandardItemModel *table_widget_model = nullptr;
	QStandardItemModel *table_widget_model_origin = nullptr;
	QVector<QString> ini_setting_data;
	QVector<TreeModel*> wiki_database{};
	void set_table_widget();

	//--- N. layouot
	void set_main_widget_layout();
	QGridLayout *main_widget_layout = nullptr;

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
	void table_widget_refresh();

public slots:
	void receive_wiki_xml_database(QVector<QString> path_pack, QVector<TreeModel*> tree_model);
};
