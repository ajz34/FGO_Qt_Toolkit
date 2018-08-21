#include "global_var.h"

QMap<QString, QPixmap> GLOB::MAP_SKILL_ICON;
QMap<QString, QPixmap> GLOB::MAP_ITEM_PIECE_SILVER;
QMap<QString, QPixmap> GLOB::MAP_ITEM_PIECE_GOLD;
QMap<QString, QPixmap> GLOB::MAP_ITEM_GEM_SHINING;
QMap<QString, QPixmap> GLOB::MAP_ITEM_GEM_MAGIC;
QMap<QString, QPixmap> GLOB::MAP_ITEM_GEM_SECRET;
QMap<QString, QPixmap> GLOB::MAP_ITEM_BRONZE;
QMap<QString, QPixmap> GLOB::MAP_ITEM_SILVER;
QMap<QString, QPixmap> GLOB::MAP_ITEM_GOLD;
QMap<QString, QPixmap> GLOB::MAP_ITEM_EVENT;
QMap<QString, QPixmap> GLOB::MAP_ITEM_MISC;
QMap<QString, QPixmap> GLOB::MAP_CARD;
QMap<QString, QPixmap> GLOB::MAP_CLASS;
QVector<QString> GLOB::LIST_ITEM;

void GLOB::MAP_INIT()
{
	// https://stackoverflow.com/questions/13509799/how-to-get-list-of-files-stored-in-a-qrc-qt-resorce-file
	// MAP_SKILL_ICON
	QDirIterator *it;
	it = new QDirIterator(":/skill_icon/images/skill_icon", QDirIterator::Subdirectories);
	while (it->hasNext()) {
		it->next();
		if (it->fileInfo().suffix() == "png")
		{
			MAP_SKILL_ICON[it->fileInfo().baseName()] = QPixmap(it->filePath());
		}
	}
	delete it;
	// MAP_ITEM_PIECE_SILVER
	it = new QDirIterator(":/item_icon/images/item_icon/piece_silver", QDirIterator::Subdirectories);
	while (it->hasNext()) {
		it->next();
		if (it->fileInfo().suffix() == "jpg")
		{
			MAP_ITEM_PIECE_SILVER[it->fileInfo().baseName()] = QPixmap(it->filePath());
			LIST_ITEM.push_back(it->fileInfo().baseName());
		}
	}
	delete it;
	// MAP_ITEM_PIECE_GOLD
	it = new QDirIterator(":/item_icon/images/item_icon/piece_gold", QDirIterator::Subdirectories);
	while (it->hasNext()) {
		it->next();
		if (it->fileInfo().suffix() == "jpg")
		{
			MAP_ITEM_PIECE_GOLD[it->fileInfo().baseName()] = QPixmap(it->filePath());
			LIST_ITEM.push_back(it->fileInfo().baseName());
		}
	}
	delete it;
	// MAP_ITEM_GEM_SHINING
	it = new QDirIterator(":/item_icon/images/item_icon/gem_shining", QDirIterator::Subdirectories);
	while (it->hasNext()) {
		it->next();
		if (it->fileInfo().suffix() == "jpg")
		{
			MAP_ITEM_GEM_SHINING[it->fileInfo().baseName()] = QPixmap(it->filePath());
			LIST_ITEM.push_back(it->fileInfo().baseName());
		}
	}
	delete it;
	// MAP_ITEM_GEM_MAGIC
	it = new QDirIterator(":/item_icon/images/item_icon/gem_magic", QDirIterator::Subdirectories);
	while (it->hasNext()) {
		it->next();
		if (it->fileInfo().suffix() == "jpg")
		{
			MAP_ITEM_GEM_MAGIC[it->fileInfo().baseName()] = QPixmap(it->filePath());
			LIST_ITEM.push_back(it->fileInfo().baseName());
		}
	}
	delete it;
	// MAP_ITEM_GEM_SECRET
	it = new QDirIterator(":/item_icon/images/item_icon/gem_secret", QDirIterator::Subdirectories);
	while (it->hasNext()) {
		it->next();
		if (it->fileInfo().suffix() == "jpg")
		{
			MAP_ITEM_GEM_SECRET[it->fileInfo().baseName()] = QPixmap(it->filePath());
			LIST_ITEM.push_back(it->fileInfo().baseName());
		}
	}
	delete it;
	// MAP_ITEM_BRONZE
	it = new QDirIterator(":/item_icon/images/item_icon/bronze", QDirIterator::Subdirectories);
	while (it->hasNext()) {
		it->next();
		if (it->fileInfo().suffix() == "jpg")
		{
			MAP_ITEM_BRONZE[it->fileInfo().baseName()] = QPixmap(it->filePath());
			LIST_ITEM.push_back(it->fileInfo().baseName());
		}
	}
	delete it;
	// MAP_ITEM_SILVER
	it = new QDirIterator(":/item_icon/images/item_icon/silver", QDirIterator::Subdirectories);
	while (it->hasNext()) {
		it->next();
		if (it->fileInfo().suffix() == "jpg")
		{
			MAP_ITEM_SILVER[it->fileInfo().baseName()] = QPixmap(it->filePath());
			LIST_ITEM.push_back(it->fileInfo().baseName());
		}
	}
	delete it;
	// MAP_ITEM_GOLD
	it = new QDirIterator(":/item_icon/images/item_icon/gold", QDirIterator::Subdirectories);
	while (it->hasNext()) {
		it->next();
		if (it->fileInfo().suffix() == "jpg")
		{
			MAP_ITEM_GOLD[it->fileInfo().baseName()] = QPixmap(it->filePath());
			LIST_ITEM.push_back(it->fileInfo().baseName());
		}
	}
	delete it;
	// MAP_ITEM_EVENT
	it = new QDirIterator(":/item_icon/images/item_icon/event", QDirIterator::Subdirectories);
	while (it->hasNext()) {
		it->next();
		if (it->fileInfo().suffix() == "jpg")
		{
			MAP_ITEM_EVENT[it->fileInfo().baseName()] = QPixmap(it->filePath());
			LIST_ITEM.push_back(it->fileInfo().baseName());
		}
	}
	delete it;
	// MAP_ITEM_MISC
	it = new QDirIterator(":/item_icon/images/item_icon/misc", QDirIterator::Subdirectories);
	while (it->hasNext()) {
		it->next();
		if (it->fileInfo().suffix() == "jpg")
		{
			MAP_ITEM_MISC[it->fileInfo().baseName()] = QPixmap(it->filePath());
			LIST_ITEM.push_back(it->fileInfo().baseName());
		}
	}
	delete it;
	// MAP_CLASS
	MAP_CLASS =
	{
		{ "Saber", QPixmap(":/servant_class/images/servant_class/saber_on.png") },
		{ "Archer", QPixmap(":/servant_class/images/servant_class/archer_on.png") },
		{ "Lancer", QPixmap(":/servant_class/images/servant_class/lancer_on.png") },
		{ "Rider", QPixmap(":/servant_class/images/servant_class/rider_on.png") },
		{ "Caster", QPixmap(":/servant_class/images/servant_class/caster_on.png") },
		{ "Assassin", QPixmap(":/servant_class/images/servant_class/assassin_on.png") },
		{ "Berserker", QPixmap(":/servant_class/images/servant_class/berserker_on.png") },
		{ "Ruler", QPixmap(":/servant_class/images/servant_class/ruler_on.png") },
		{ "Avenger", QPixmap(":/servant_class/images/servant_class/avenger_on.png") },
		{ "Mooncancer", QPixmap(":/servant_class/images/servant_class/mooncancer_on.png") },
		{ "Alterego", QPixmap(":/servant_class/images/servant_class/alterego_on.png") },
		{ "Foreigner", QPixmap(":/servant_class/images/servant_class/foreigner_on.png") },
		{ "Shielder", QPixmap(":/servant_class/images/servant_class/shielder_on.png") },
	};
	// MAP_CARD
	MAP_CARD =
	{
		{ "Q", QPixmap(":/card_color/images/card_color/Quick.png") },
		{ "A", QPixmap(":/card_color/images/card_color/Arts.png") },
		{ "B", QPixmap(":/card_color/images/card_color/Buster.png") },
	};
}

// VEC_ASCENSION_LEVELMIN
QVector<QMap<int, int>> GLOB::VEC_ASCENSION_LEVELMIN =
{
	{ { 0, 1 },{ 1, 25 },{ 2, 35 },{ 3, 45 },{ 4, 55 },{ 5, 65 } },  // 0 star
	{ { 0, 1 },{ 1, 20 },{ 2, 30 },{ 3, 40 },{ 4, 50 },{ 5, 60 } },  // 1 star
	{ { 0, 1 },{ 1, 25 },{ 2, 35 },{ 3, 45 },{ 4, 55 },{ 5, 65 } },  // 2 star
	{ { 0, 1 },{ 1, 30 },{ 2, 40 },{ 3, 50 },{ 4, 60 },{ 5, 70 } },  // 3 star
	{ { 0, 1 },{ 1, 40 },{ 2, 50 },{ 3, 60 },{ 4, 70 },{ 5, 80 } },  // 4 star
	{ { 0, 1 },{ 1, 50 },{ 2, 60 },{ 3, 70 },{ 4, 80 },{ 5, 90 } },  // 5 star
};

// VEC_ASCENSION_LEVELMAX
QVector<QMap<int, int>> GLOB::VEC_ASCENSION_LEVELMAX =
{
	{ { 0, 25 },{ 1, 35 },{ 2, 45 },{ 3, 55 },{ 4, 65 },{ 5, 100 } },  // 0 star
	{ { 0, 20 },{ 1, 30 },{ 2, 40 },{ 3, 50 },{ 4, 60 },{ 5, 100 } },  // 1 star
	{ { 0, 25 },{ 1, 35 },{ 2, 45 },{ 3, 55 },{ 4, 65 },{ 5, 100 } },  // 2 star
	{ { 0, 30 },{ 1, 40 },{ 2, 50 },{ 3, 60 },{ 4, 70 },{ 5, 100 } },  // 3 star
	{ { 0, 40 },{ 1, 50 },{ 2, 60 },{ 3, 70 },{ 4, 80 },{ 5, 100 } },  // 4 star
	{ { 0, 50 },{ 1, 60 },{ 2, 70 },{ 3, 80 },{ 4, 90 },{ 5, 100 } },  // 5 star
};

// VEC_ASCENSION_QP
// key: -1 means all QP needed in ascension
QVector<QMap<int, int>> GLOB::VEC_ASCENSION_QP =
{
	{ { 0,  15000 },{ 1,  45000 },{ 2,  150000 },{ 3,  450000 },{ -1,  660000 } },  // 0 star
	{ { 0,  10000 },{ 1,  30000 },{ 2,   90000 },{ 3,  300000 },{ -1,  430000 } },  // 1 star
	{ { 0,  15000 },{ 1,  45000 },{ 2,  150000 },{ 3,  450000 },{ -1,  660000 } },  // 2 star
	{ { 0,  30000 },{ 1, 100000 },{ 2,  300000 },{ 3,  900000 },{ -1, 1330000 } },  // 3 star
	{ { 0,  50000 },{ 1, 150000 },{ 2,  500000 },{ 3, 1500000 },{ -1, 2200000 } },  // 4 star
	{ { 0, 100000 },{ 1, 300000 },{ 2, 1000000 },{ 3, 3000000 },{ -1, 4400000 } },  // 5 star
};

// VEC_SKILL_QP
QVector<QMap<int, int>> GLOB::VEC_SKILL_QP =
{
	 { { 1,  20000 },{ 2,  40000 },{ 3,  120000 },{ 4,  160000 },{ 5,  400000 },{ 6,  500000 },{ 7,  1000000 },{ 8,  1200000 },{ 9,  2000000 },{ -1,  5440000 } },  // 0 star
	 { { 1,  10000 },{ 2,  20000 },{ 3,   60000 },{ 4,   80000 },{ 5,  200000 },{ 6,  250000 },{ 7,   500000 },{ 8,   600000 },{ 9,  1000000 },{ -1,  2720000 } },  // 1 star
	 { { 1,  20000 },{ 2,  40000 },{ 3,  120000 },{ 4,  160000 },{ 5,  400000 },{ 6,  500000 },{ 7,  1000000 },{ 8,  1200000 },{ 9,  2000000 },{ -1,  5440000 } },  // 2 star
	 { { 1,  50000 },{ 2, 100000 },{ 3,  300000 },{ 4,  400000 },{ 5, 1000000 },{ 6, 1250000 },{ 7,  2500000 },{ 8,  3000000 },{ 9,  5000000 },{ -1, 13600000 } },  // 3 star
	 { { 1, 100000 },{ 2, 200000 },{ 3,  600000 },{ 4,  800000 },{ 5, 2000000 },{ 6, 2500000 },{ 7,  5000000 },{ 8,  6000000 },{ 9, 10000000 },{ -1, 27200000 } },  // 4 star
	 { { 1, 200000 },{ 2, 400000 },{ 3, 1200000 },{ 4, 1600000 },{ 5, 4000000 },{ 6, 5000000 },{ 7, 10000000 },{ 8, 12000000 },{ 9, 20000000 },{ -1, 54400000 } },  // 5 star
};

// VEC_PALINGENESIS_LEVEL
QVector<QMap<int, int>> GLOB::VEC_PALINGENESIS_LEVEL =
{
	{ { 1, 70 },{ 2, 75 },{ 3, 80 },{ 4, 85 },{ 5, 90 },{ 6, 92 },{ 7, 94 },{ 8, 96 },{ 9, 98 },{ 10, 100 } },  // 0 star
	{ { 1, 70 },{ 2, 75 },{ 3, 80 },{ 4, 85 },{ 5, 90 },{ 6, 92 },{ 7, 94 },{ 8, 96 },{ 9, 98 },{ 10, 100 } },  // 1 star
	{ { 1, 70 },{ 2, 75 },{ 3, 80 },{ 4, 85 },{ 5, 90 },{ 6, 92 },{ 7, 94 },{ 8, 96 },{ 9, 98 },{ 10, 100 } },  // 2 star
	{ { 1, 75 },{ 2, 80 },{ 3, 85 },{ 4, 90 },{ 5, 92 },{ 6, 94 },{ 7, 96 },{ 8, 98 },{ 9, 100 } },				// 3 star
	{ { 1, 85 },{ 2, 90 },{ 3, 92 },{ 4, 94 },{ 5, 96 },{ 6, 98 },{ 7, 100 } },									// 4 star
	{ { 1, 92 },{ 2, 94 },{ 3, 96 },{ 4, 98 },{ 5, 100 } },														// 5 star
};

QMap<int, int> MAP_LEVEL_EXP =
{ 
	{ 1,0 },{ 2,100 },{ 3,400 },{ 4,1000 },{ 5,2000 },{ 6,3500 },{ 7,5600 },{ 8,8400 },{ 9,12000 },{ 10,16500 },
	{ 11,22000 },{ 12,28600 },{ 13,36400 },{ 14,45500 },{ 15,56000 },{ 16,68000 },{ 17,81600 },{ 18,96900 },{ 19,114000 },{ 20,133000 },
	{ 21,154000 },{ 22,177100 },{ 23,202400 },{ 24,230000 },{ 25,260000 },{ 26,292500 },{ 27,327600 },{ 28,365400 },{ 29,406000 },{ 30,449500 },
	{ 31,496000 },{ 32,545600 },{ 33,598400 },{ 34,654500 },{ 35,714000 },{ 36,777000 },{ 37,843600 },{ 38,913900 },{ 39,988000 },{ 40,1066000 },
	{ 41,1148000 },{ 42,1234100 },{ 43,1324400 },{ 44,1419000 },{ 45,1518000 },{ 46,1621500 },{ 47,1729600 },{ 48,1842400 },{ 49,1960000 },{ 50,2082500 },
	{ 51,2210000 },{ 52,2342600 },{ 53,2480400 },{ 54,2623500 },{ 55,2772000 },{ 56,2926000 },{ 57,3085600 },{ 58,3250900 },{ 59,3422000 },{ 60,3599000 },
	{ 61,3782000 },{ 62,3871100 },{ 63,4166400 },{ 64,4368000 },{ 65,4576000 },{ 66,4790500 },{ 67,5011600 },{ 68,5239400 },{ 69,5474000 },{ 70,5715500 },
	{ 71,5964000 },{ 72,6219600 },{ 73,6482400 },{ 74,6752500 },{ 75,7030000 },{ 76,7315000 },{ 77,7607600 },{ 78,7907900 },{ 79,8216000 },{ 80,8532000 },
	{ 81,8856000 },{ 82,9188100 },{ 83,9528400 },{ 84,9877000 },{ 85,10234000 },{ 86,10599500 },{ 87,10973600 },{ 88,11356400 },{ 89,11748000 },{ 90,12148500 },
	{ 91,12567000 },{ 92,13021900 },{ 93,13531900 },{ 94,14116400 },{ 95,14794900 },{ 96,15587400 },{ 97,16514300 },{ 98,17596400 },{ 99,18854900 },{ 100,20311400 },
};