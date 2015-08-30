#ifndef WSTACKEDWIDGET_H
#define WSTACKEDWIDGET_H

#include <QObject>
#include <QWidget>
#include <QStackedWidget>

class WStackedWidget : public QStackedWidget
{
public:
    WStackedWidget(QWidget *parent = 0);
};

#endif // WSTACKEDWIDGET_H
