#ifndef WLOADING_H
#define WLOADING_H

#include <QDialog>
#include <QMovie>
#include <QLabel>

class WLoading : public QDialog
{
    Q_OBJECT
public:
    explicit WLoading(QDialog *parent = 0);
private slots:
    void showLabel();
private:
    QLabel *label1;
    QLabel *label2;
    QMovie *movie;
};

#endif // WLOADING_H
