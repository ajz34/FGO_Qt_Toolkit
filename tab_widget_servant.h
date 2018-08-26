#pragma once

#include <QtWidgets>

#include "qclickablefigurelabel.h"
#include "xml_editable_mainwindow.h"
#include "treemodel.h"
#include "qrightclickpushbutton.h"
#include "resource_consume.h"

class tab_widget_servant : public QWidget
{
	Q_OBJECT;

	//--- HAND MADE PARAMETERS
	const int SCALE_SIZE = 40;  // servant class label width and height (px)
	const int SERVANT_ICON_NUMBER = 500;
	const int SERVANT_ICON_WIDTH = 69;
	const int SERVANT_ICON_HEIGHT = 75;

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
    // follow
    QPushButton *filter_follow = nullptr;
    QAction *filter_follow_all = nullptr;
    QAction *filter_follow_yes = nullptr;
    QAction *filter_follow_no = nullptr;
    void set_filter_follow();
	// other
	QVBoxLayout *filter_layout = nullptr;
	void set_filter_button();
    void set_filter_layout();
    void set_filter_connection();

	//--- D. servant table
	// though it is possible to use proxy model, 
	// here I just didn't apply that model,
	// and control filter action manually, using copy but not hide filtered items
	QTableView *table_widget = nullptr;
	QStandardItemModel *table_widget_model = nullptr;
	QStandardItemModel *table_widget_model_origin = nullptr;
	QVector<QString> ini_setting_data;
	QVector<TreeModel*> wiki_database{};
	QVector<QPixmap> servant_icon_button_image = QVector<QPixmap>(SERVANT_ICON_NUMBER);
	void set_table_widget();

	//--- E. servant consume
	TreeModel* user_data = nullptr;

	//--- N. layouot
	void set_main_widget_layout();
	QGridLayout *main_widget_layout = nullptr;

public:
	tab_widget_servant(QWidget *parent);
	~tab_widget_servant();

signals:
	void table_pushbutton_transout(
		QVector<QString> ini_setting,
		QVector<TreeModel*> *wiki,
		QVector<QPixmap> *servant_icon,
		int id,
		TreeModel* user_dat);

private slots:
	//--- A. servant class labels
	void class_all_on_clicked_labelbehave();
	void class_all_off_clicked_labelbehave();
	void class_trival_clicked_labelbehave();
	//--- C. filter
    // rarity
	void filter_rarity_subitem_clicked_actionbehave(bool checked);
    void filter_rarity_all_clicked_actionbehave(bool checked);
    // follow
    void filter_follow_subitem_clicked_actionbehave(bool checked);
    void filter_follow_all_clicked_actionbehave(bool checked);
	//--- D. servant table
	void table_pushbutton_right_click();
    void table_widget_refresh();
    void table_original_table_refresh();
	//--- E. servant consume
	void table_pushbutton_click();

public slots:
	void receive_wiki_xml_database(
		QVector<QString> path_pack,
		QVector<TreeModel*> tree_model,
		TreeModel* user_dat);
	void receive_user_data_changes(TreeModel *user_dat);
};
