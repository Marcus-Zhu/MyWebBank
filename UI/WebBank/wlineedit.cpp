#include "wlineedit.h"

#include <QWidget>

WLineEdit::WLineEdit(QWidget *parent):
    QLineEdit(parent)
{
}

void WLineEdit::mousePressEvent(QMouseEvent *e)
{
	//if QLineEdit is clicked, emit a clicked signal
    if (e->button()==Qt::LeftButton)
    {
        emit Wclicked();
    }
    QLineEdit::mousePressEvent(e);
}
