#pragma once

#include <QtWidgets>

namespace GLOB {
	// mapping icon and item to figure
	// since images are stored in project and not specified by user, this process is user safe
	extern QMap<QString, QPixmap> MAP_SKILL_ICON;
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
    extern QMap<QString, QPixmap> MAP_ITEM;
	extern QMap<QString, QPixmap> MAP_CARD;
    extern QMap<QString, QPixmap> MAP_CLASS;
    extern QMap<QString, QPixmap> MAP_EMPTY;
	extern void MAP_INIT();

	// mapping of ascension or skill Exp or QP
	extern QVector<QMap<int, int>> VEC_ASCENSION_LEVELMIN;
	extern QVector<QMap<int, int>> VEC_ASCENSION_LEVELMAX;
	extern QVector<QMap<int, int>> VEC_ASCENSION_QP;
	extern QVector<QMap<int, int>> VEC_SKILL_QP;
	extern QVector<QMap<int, int>> VEC_PALINGENESIS_LEVEL;
	extern QVector<QMap<int, int>> VEC_PALINGENESIS_QP;
	extern QMap<int, int> MAP_LEVEL_EXP;
}


