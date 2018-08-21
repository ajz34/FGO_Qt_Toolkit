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

void GLOB::MAP_INIT()
{
	// https://stackoverflow.com/questions/13509799/how-to-get-list-of-files-stored-in-a-qrc-qt-resorce-file
	// MAP_SKILL_ICON
	QDirIterator *it;
	it = new QDirIterator(":/skill_icon/images/skill_icon", QDirIterator::Subdirectories);
	while (it->hasNext()) {
		it->next();
		if (it->fileInfo().suffix() == "png")
			GLOB::MAP_SKILL_ICON[it->fileInfo().baseName()] = QPixmap(it->filePath());
	}
	delete it;
	qDebug() << GLOB::MAP_SKILL_ICON;
	// MAP_ITEM_PIECE_SILVER
	it = new QDirIterator(":/item_icon/images/item_icon/piece_silver", QDirIterator::Subdirectories);
	while (it->hasNext()) {
		it->next();
		if (it->fileInfo().suffix() == "jpg")
			GLOB::MAP_ITEM_PIECE_SILVER[it->fileInfo().baseName()] = QPixmap(it->filePath());
	}
	delete it;
	qDebug() << GLOB::MAP_ITEM_PIECE_SILVER;
	// MAP_ITEM_PIECE_GOLD
	it = new QDirIterator(":/item_icon/images/item_icon/piece_gold", QDirIterator::Subdirectories);
	while (it->hasNext()) {
		it->next();
		if (it->fileInfo().suffix() == "jpg")
			GLOB::MAP_ITEM_PIECE_GOLD[it->fileInfo().baseName()] = QPixmap(it->filePath());
	}
	delete it;
	qDebug() << GLOB::MAP_ITEM_PIECE_GOLD;
	// MAP_ITEM_GEM_SHINING
	it = new QDirIterator(":/item_icon/images/item_icon/gem_shining", QDirIterator::Subdirectories);
	while (it->hasNext()) {
		it->next();
		if (it->fileInfo().suffix() == "jpg")
			GLOB::MAP_ITEM_GEM_SHINING[it->fileInfo().baseName()] = QPixmap(it->filePath());
	}
	delete it;
	qDebug() << GLOB::MAP_ITEM_GEM_SHINING;
	// MAP_ITEM_GEM_MAGIC
	it = new QDirIterator(":/item_icon/images/item_icon/gem_magic", QDirIterator::Subdirectories);
	while (it->hasNext()) {
		it->next();
		if (it->fileInfo().suffix() == "jpg")
			GLOB::MAP_ITEM_GEM_MAGIC[it->fileInfo().baseName()] = QPixmap(it->filePath());
	}
	delete it;
	qDebug() << GLOB::MAP_ITEM_GEM_MAGIC;
	// MAP_ITEM_GEM_SECRET
	it = new QDirIterator(":/item_icon/images/item_icon/gem_secret", QDirIterator::Subdirectories);
	while (it->hasNext()) {
		it->next();
		if (it->fileInfo().suffix() == "jpg")
			GLOB::MAP_ITEM_GEM_SECRET[it->fileInfo().baseName()] = QPixmap(it->filePath());
	}
	delete it;
	qDebug() << GLOB::MAP_ITEM_GEM_SECRET;
	// MAP_ITEM_BRONZE
	it = new QDirIterator(":/item_icon/images/item_icon/bronze", QDirIterator::Subdirectories);
	while (it->hasNext()) {
		it->next();
		if (it->fileInfo().suffix() == "jpg")
			GLOB::MAP_ITEM_BRONZE[it->fileInfo().baseName()] = QPixmap(it->filePath());
	}
	delete it;
	qDebug() << GLOB::MAP_ITEM_BRONZE;
	// MAP_ITEM_SILVER
	it = new QDirIterator(":/item_icon/images/item_icon/silver", QDirIterator::Subdirectories);
	while (it->hasNext()) {
		it->next();
		if (it->fileInfo().suffix() == "jpg")
			GLOB::MAP_ITEM_SILVER[it->fileInfo().baseName()] = QPixmap(it->filePath());
	}
	delete it;
	qDebug() << GLOB::MAP_ITEM_SILVER;
	// MAP_ITEM_GOLD
	it = new QDirIterator(":/item_icon/images/item_icon/gold", QDirIterator::Subdirectories);
	while (it->hasNext()) {
		it->next();
		if (it->fileInfo().suffix() == "jpg")
			GLOB::MAP_ITEM_GOLD[it->fileInfo().baseName()] = QPixmap(it->filePath());
	}
	delete it;
	qDebug() << GLOB::MAP_ITEM_GOLD;
	// MAP_ITEM_EVENT
	it = new QDirIterator(":/item_icon/images/item_icon/event", QDirIterator::Subdirectories);
	while (it->hasNext()) {
		it->next();
		if (it->fileInfo().suffix() == "jpg")
			GLOB::MAP_ITEM_EVENT[it->fileInfo().baseName()] = QPixmap(it->filePath());
	}
	delete it;
	qDebug() << GLOB::MAP_ITEM_EVENT;
	// MAP_ITEM_MISC
	it = new QDirIterator(":/item_icon/images/item_icon/misc", QDirIterator::Subdirectories);
	while (it->hasNext()) {
		it->next();
		if (it->fileInfo().suffix() == "jpg")
			GLOB::MAP_ITEM_MISC[it->fileInfo().baseName()] = QPixmap(it->filePath());
	}
	delete it;
	qDebug() << GLOB::MAP_ITEM_MISC;
}

