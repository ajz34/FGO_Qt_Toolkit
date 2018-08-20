#include "qrightclickpushbutton.h"

QRightClickPushButton::QRightClickPushButton(QWidget *parent)
	: QPushButton(parent)
{
}

QRightClickPushButton::~QRightClickPushButton()
{
}

void QRightClickPushButton::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::RightButton)
		emit rightClicked();
	else
		emit clicked();
}
