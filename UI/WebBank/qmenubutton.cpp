#include "qmenubutton.h"
#include <QMenu>

QMenuButton::QMenuButton(QWidget *parent, btnType t) :
    QPushButton(parent)
{
    menu = new QMenu(this);
    switch(t)
    {
    case 1:
        menu->addAction(tr("Personal Info"));
        menu->addSeparator();
        menu->addAction(tr("ChangePassword"));
        menu->addSeparator();
        menu->addAction(tr("System Message"));
        menu->addSeparator();
        menu->addAction(tr("Log Out"));
        break;
    case 2:
        menu->addAction(tr("Language"));
        menu->addSeparator();
        menu->addAction(tr("About"));
    }
    connect(this, SIGNAL(clicked()), this, SLOT(popMenu()));
}

void QMenuButton::popMenu()
{
    QPoint pos;
    pos.setX(pos.x() - this->geometry().width());
    pos.setY(pos.y() + this->geometry().height());
    menu->exec(this->mapToGlobal(pos));
}

