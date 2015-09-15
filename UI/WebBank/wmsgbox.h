#ifndef WMSGBOX_H
#define WMSGBOX_H

#include <QLabel>
#include <QPushButton>
#include <QObject>
#include <QDialog>
#include <QString>
#include <QMouseEvent>

class WMsgBox : public QDialog
{
    Q_OBJECT
public:
    explicit WMsgBox(QWidget *parent = 0);
    static void information(QString content);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QLabel *bgLabel;
    QLabel *contentLabel;
    QPushButton *closeBtn;
    QPushButton *okBtn;
    bool isPressed;
    QPoint movePoint;
};

#endif // WMSGBOX_H
