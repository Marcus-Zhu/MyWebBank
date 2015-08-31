#include "nofocusdelegate.h"

NoFocusDelegate::NoFocusDelegate(QObject *parent)
 : QStyledItemDelegate(parent)
{
}

void NoFocusDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem item(option);
    if (item.state & QStyle::State_HasFocus)
    {
        item.state ^= QStyle::State_HasFocus;
    }
    QStyledItemDelegate::paint(painter, item, index);
}
