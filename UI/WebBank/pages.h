#ifndef PAGES_H
#define PAGES_H

#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QWidget>

class MyAccountPage : public QWidget
{
    Q_OBJECT
public:
    explicit MyAccountPage(QWidget *parent = 0);
public slots:
private:
    QLabel *title1;
    QLabel *title2;
    QTableWidget *table1;
    QTableWidget *table2;
};

class TransferPage : public QWidget
{
    Q_OBJECT
public:
    explicit TransferPage(QWidget *parent = 0);
public slots:
private:
    QLabel *title;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    QLabel *label5;
    QComboBox *edit1;
    QLineEdit *edit2;
    QLineEdit *edit3;
    QLineEdit *edit4;
    QLineEdit *edit5;
    QPushButton *confirmBtn;
};
#endif // PAGES_H
