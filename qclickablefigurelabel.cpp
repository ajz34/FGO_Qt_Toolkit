#include "qclickablefigurelabel.h"

QClickableFigureLabel::QClickableFigureLabel(QPixmap pixmap_a, QPixmap pixmap_b, QWidget* parent)
	: QLabel(parent) {
	
	click_status = true;
	pixmap_1 = pixmap_a;
	pixmap_2 = pixmap_b;
	toggle();
	connect(this, &QClickableFigureLabel::clicked, this, &QClickableFigureLabel::toggle);

}

QClickableFigureLabel::~QClickableFigureLabel() {}

void QClickableFigureLabel::mousePressEvent(QMouseEvent* event) {
	emit clicked();
}

void QClickableFigureLabel::toggle()
{
	click_status = !click_status;
	(click_status) ? setPixmap(pixmap_1) : setPixmap(pixmap_2);
}
