#pragma once
#ifdef WIN32
// character in chinese can't display in visual studio
// if Qt environment, possibly you can delete this
// this line may be included in all header files
// https://blog.csdn.net/nabariou/article/details/60468627
#pragma execution_character_set("utf-8")  
#endif

#include <QtWidgets>

namespace GLOB {
	// mapping icon and item to figure
	// since images are stored in project and not specified by user, this process is user safe
	extern QHash<QString, QPixmap> MAP_SKILL_ICON;
	extern QVector<QString> LIST_ITEM_PIECE_SILVER;
	extern QVector<QString> LIST_ITEM_PIECE_GOLD;
	extern QVector<QString> LIST_ITEM_GEM_SHINING;
	extern QVector<QString> LIST_ITEM_GEM_MAGIC;
	extern QVector<QString> LIST_ITEM_GEM_SECRET;
	extern QVector<QString> LIST_ITEM_BRONZE;
	extern QVector<QString> LIST_ITEM_SILVER;
	extern QVector<QString> LIST_ITEM_GOLD;
	extern QVector<QString> LIST_ITEM_EVENT;
	extern QVector<QString> LIST_ITEM_MISC;
    extern QVector<QString> LIST_ITEM;
    extern QVector<QVector<QString>> LIST_CATEGORY;
    extern QHash<QString, int> MAP_ITEM_INDEX;
    extern QHash<QString, QPixmap> MAP_ITEM;
	extern QHash<QString, QPixmap> MAP_CARD;
    extern QHash<QString, QPixmap> MAP_CLASS;
    extern QHash<QString, QPixmap> MAP_EMPTY;
	extern void MAP_INIT();

	// mapping of ascension or skill Exp or QP
	extern QVector<QMap<int, int>> VEC_ASCENSION_LEVELMIN;
	extern QVector<QMap<int, int>> VEC_ASCENSION_LEVELMAX;
	extern QVector<QMap<int, int>> VEC_ASCENSION_QP;
	extern QVector<QMap<int, int>> VEC_SKILL_QP;
	extern QVector<QMap<int, int>> VEC_PALINGENESIS_LEVEL;
	extern QVector<QMap<int, int>> VEC_PALINGENESIS_QP;
	extern QHash<int, int> MAP_LEVEL_EXP;
}


