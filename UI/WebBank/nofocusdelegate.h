#ifndef NOFOCUSDELEGATE_H
#define NOFOCUSDELEGATE_H

#include <QStyledItemDelegate>


class NoFocusDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    NoFocusDelegate(QObject *parent = NULL);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // NOFOCUSDELEGATE_H
