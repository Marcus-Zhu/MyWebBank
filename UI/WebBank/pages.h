#ifndef PAGES_H
#define PAGES_H

#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QTableWidget>
#include <QWidget>

class WPage : public QWidget
{
    Q_OBJECT
public:
    explicit WPage(QWidget *parent = 0);
    virtual void updateLanguage()=0;
public slots:
protected:
    QLabel *mainTitle;
};

class MyAccountPage : public WPage
{
    Q_OBJECT
public:
    explicit MyAccountPage(QWidget *parent = 0);
    void updateLanguage();
public slots:
private:
    QLabel *title2;
    QTableWidget *table1;
    QTableWidget *table2;
};

class AccountQueryPage : public WPage
{
    Q_OBJECT
public:
    explicit AccountQueryPage(QWidget *parent = 0);
    void updateLanguage();
public slots:
private:
    QLabel *label1;
    QLabel *label2;
    QComboBox *comboBox;
    QCheckBox *box1;
    QCheckBox *box2;
    QPushButton *quernBtn;
    QPushButton *recentBtn;
    QTableWidget *table;
};

class TransferPage : public WPage
{
    Q_OBJECT
public:
    explicit TransferPage(QWidget *parent = 0);
    void updateLanguage();
public slots:
private:
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
    QPushButton *queryBtn;
    QPushButton *confirmBtn;
};

class CurrentFixPage : public WPage
{
    Q_OBJECT
public:
    explicit CurrentFixPage(QWidget *parent = 0);
    void updateLanguage();
public slots:
private:
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    QLabel *label5;
    QComboBox *edit1;
    QLineEdit *edit2;
    QLineEdit *edit3;
    QComboBox *edit4;
    QLineEdit *edit5;
    QPushButton *queryBtn;
    QPushButton *confirmBtn;
};

class PaymentPage : public WPage
{
    Q_OBJECT
public:
    explicit PaymentPage(QWidget *parent = 0);
    void updateLanguage();
public slots:
private:
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QComboBox *edit1;
    QComboBox *edit2;
    QLineEdit *edit3;
    QPushButton *queryBtn;
    QPushButton *confirmBtn;
    QPushButton *autoBtn;
};

class CardApplyPage : public WPage
{
    Q_OBJECT
public:
    explicit CardApplyPage(QWidget *parent = 0);
    void updateLanguage();
public slots:
private:
    QLabel *label1;
    QLabel *label2;
    QComboBox *edit1;
    QComboBox *edit2;
    QPushButton *confirmBtn;
};

class CardActivatePage : public WPage
{
    Q_OBJECT
public:
    explicit CardActivatePage(QWidget *parent = 0);
    void updateLanguage();
public slots:
private:
    QLabel *label1;
    QComboBox *edit1;
    QPushButton *confirmBtn;
};

class CardRepayPage : public WPage
{
    Q_OBJECT
public:
    explicit CardRepayPage(QWidget *parent = 0);
    void updateLanguage();
public slots:
private:
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    QLabel *label5;
    QComboBox *edit1;
    QLineEdit *edit2;
    QLineEdit *edit3;
    QComboBox *edit4;
    QLineEdit *edit5;
    QPushButton *queryBtn;
    QPushButton *confirmBtn;
};

class CardLostPage : public WPage
{
    Q_OBJECT
public:
    explicit CardLostPage(QWidget *parent = 0);
    void updateLanguage();
public slots:
private:
    QLabel *label1;
    QComboBox *edit1;
    QPushButton *confirmBtn;
};

class UserInfoPage : public WPage
{
    Q_OBJECT
public:
    explicit UserInfoPage(QWidget *parent = 0);
    void updateLanguage();
public slots:
private:
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    QLabel *label5;
    QLabel *label6;
    QLabel *label7;
    QLineEdit *edit1;
    QLineEdit *edit2;
    QLineEdit *edit3;
    QLineEdit *edit4;
    QLineEdit *edit5;
    QLineEdit *edit6;
    QLineEdit *edit7;
};

class ChangePwPage : public WPage
{
    Q_OBJECT
public:
    explicit ChangePwPage(QWidget *parent = 0);
    void updateLanguage();
public slots:
private:
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    QLineEdit *edit1;
    QLineEdit *edit2;
    QLineEdit *edit3;
    QPushButton *confirmBtn;
};

class SysMsgPage : public WPage
{
    Q_OBJECT
public:
    explicit SysMsgPage(QWidget *parent = 0);
    void updateLanguage();
public slots:
private:
    QLabel *mainTitle;
    QTableWidget *table;
};

#endif // PAGES_H
