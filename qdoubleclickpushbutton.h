#pragma once

#include <QPushButton>
#include <QMouseEvent>

class QDoubleClickPushButton : public QPushButton
{
	Q_OBJECT;

protected:
	void mouseDoubleClickEvent(QMouseEvent *e);

signals:
	void doubleClicked();

public:
	QString text_save;
	QDoubleClickPushButton(QWidget *parent);
	~QDoubleClickPushButton();
};
