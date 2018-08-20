#pragma once

#include <QPushButton>
#include <QMouseEvent>

class QRightClickPushButton : public QPushButton
{
	Q_OBJECT;

protected:
	void mousePressEvent(QMouseEvent *e);

signals:
	void rightClicked();

public:
	QString text_save;
	QRightClickPushButton(QWidget *parent);
	~QRightClickPushButton();
};
