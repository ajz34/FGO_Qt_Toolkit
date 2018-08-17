#include "qdoubleclickpushbutton.h"

QDoubleClickPushButton::QDoubleClickPushButton(QWidget *parent)
	: QPushButton(parent)
{
}

QDoubleClickPushButton::~QDoubleClickPushButton()
{
}

void QDoubleClickPushButton::mouseDoubleClickEvent(QMouseEvent *e)
{
	emit doubleClicked();
}
