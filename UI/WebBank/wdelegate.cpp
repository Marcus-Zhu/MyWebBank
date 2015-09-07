#include "wdelegate.h"

WDelegate::WDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void WDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	//if an item has focus, get rid of it
    QStyleOptionViewItem item(option);
    if (item.state & QStyle::State_HasFocus)
    {
        item.state ^= QStyle::State_HasFocus;
    }
    QStyledItemDelegate::paint(painter, item, index);
}
