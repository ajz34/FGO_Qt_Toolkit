#ifndef QCLICKABLEFIGURELABEL_H
#define QCLICKABLEFIGURELABEL_H

#include <QLabel>
#include <QtWidgets>
#include <Qt>

class QClickableFigureLabel : public QLabel
{
	Q_OBJECT

	QPixmap pixmap_1;
	QPixmap pixmap_2;

public:
	explicit QClickableFigureLabel(QPixmap pixmap_a, QPixmap pixmap_b, QWidget* parent = nullptr);
	~QClickableFigureLabel();

	bool click_status;

signals:
	void clicked();

public slots:
	void toggle();

protected:
	void mousePressEvent(QMouseEvent* event);

};

#endif