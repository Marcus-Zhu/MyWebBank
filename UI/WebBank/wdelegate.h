#ifndef NOFOCUSDELEGATE_H
#define NOFOCUSDELEGATE_H

#include <QStyledItemDelegate>


class WDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    WDelegate(QObject *parent = NULL);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // NOFOCUSDELEGATE_H
