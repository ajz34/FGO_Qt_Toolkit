#pragma once

#include <QtWidgets>

namespace GLOB {
	// mapping icon and item to figure
	// since images are stored in project and not specified by user, this process is user safe
	extern QMap<QString, QPixmap> MAP_SKILL_ICON;
	extern QMap<QString, QPixmap> MAP_ITEM_PIECE_SILVER;
	extern QMap<QString, QPixmap> MAP_ITEM_PIECE_GOLD;
	extern QMap<QString, QPixmap> MAP_ITEM_GEM_SHINING;
	extern QMap<QString, QPixmap> MAP_ITEM_GEM_MAGIC;
	extern QMap<QString, QPixmap> MAP_ITEM_GEM_SECRET;
	extern QMap<QString, QPixmap> MAP_ITEM_BRONZE;
	extern QMap<QString, QPixmap> MAP_ITEM_SILVER;
	extern QMap<QString, QPixmap> MAP_ITEM_GOLD;
	extern QMap<QString, QPixmap> MAP_ITEM_EVENT;
	extern QMap<QString, QPixmap> MAP_ITEM_MISC;
	extern void MAP_INIT();
}


