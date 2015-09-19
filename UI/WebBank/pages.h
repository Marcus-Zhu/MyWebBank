#ifndef PAGES_H
#define PAGES_H

#include "wlineedit.h"
#include "qcustomplot.h"

#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QTableWidget>
#include <QTextEdit>
#include <QCalendarWidget>
#include <QWidget>

class WPage : public QWidget
{
    Q_OBJECT
public:
    explicit WPage(QWidget *parent = 0);
    virtual void updateLanguage() = 0;
protected:
    QLabel *mainTitle;
};

class MyAccountPage : public WPage
{
    Q_OBJECT
public:
    explicit MyAccountPage(QWidget *parent = 0);
    void updateLanguage();
    void setTable();
public slots:
    void showAccountRecord(int row, int column);
private:
    QLabel *bgLabel;
    QLabel *title2;
    QTableWidget *table1;
    QTableWidget *table2;
    QPushButton *plotBtn;
};

class AccountQueryPage : public WPage
{
    Q_OBJECT
public:
    explicit AccountQueryPage(QWidget *parent = 0);
    void updateLanguage();
    void setTable();
    void setComboBox();
public slots:
    void showCalendar1();
    void showCalendar2();
    void setCalendar1();
    void setCalendar2();
    void popExpense();
    void popIncome();
    void search();
    void recent();
    void exportExcel();
private:
    QLabel *bgLabel;
    QLabel *label1;
    QLabel *label2;
    QComboBox *accountBox;
    QTableWidget *table;
    QCheckBox *incomeCkBox;
    QCheckBox *expenseCkBox;
    QPushButton *searchBtn;
    QPushButton *recentBtn;
    QPushButton *exportBtn;
    WLineEdit *fromDate;
    WLineEdit *toDate;
    QCalendarWidget *calendar1;
    QCalendarWidget *calendar2;
    QLabel *calendarLabel;
    int queryType;
};

class TransferPage : public WPage
{
    Q_OBJECT
public:
    explicit TransferPage(QWidget *parent = 0);
    void updateLanguage();
    void setComboBox();
public slots:
    void confirm();
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
    void setComboBox();
public slots:
    void confirm();
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
    void setComboBox();
public slots:
    void confirm();
    void changeValue(int i);
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
    int value[3];
};

class AutoPayPage : public WPage
{
    Q_OBJECT
public:
    explicit AutoPayPage(QWidget *parent = 0);
    void updateLanguage();
    void setTable();
    void setComboBox();
public slots:
    void setAutoPay();
    void cancelAutoPay();
    void updateTable();
private:
    QLabel *bgLabel;
    QLabel *label1;
    QLabel *label2;
    QLabel *title2;
    QComboBox *edit1;
    QComboBox *edit2;
    QPushButton *settingBtn;
    QPushButton *cancelBtn;
    QTableWidget *table;
};

class CardApplyPage : public WPage
{
    Q_OBJECT
public:
    explicit CardApplyPage(QWidget *parent = 0);
    void updateLanguage();
public slots:
    void confirm();
private:
    QLabel *label1;
    QComboBox *edit1;
    QPushButton *confirmBtn;
};

class CardActivatePage : public WPage
{
    Q_OBJECT
public:
    explicit CardActivatePage(QWidget *parent = 0);
    void updateLanguage();
    void setComboBox();
public slots:
    void activate();
private:
    QLabel *label1;
    QComboBox *edit1;
    QPushButton *activateBtn;
};

class CardRepayPage : public WPage
{
    Q_OBJECT
public:
    explicit CardRepayPage(QWidget *parent = 0);
    void updateLanguage();
    void setComboBox();
public slots:
    void confirm();
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
    QPushButton *confirmBtn;
};

class CardLostPage : public WPage
{
    Q_OBJECT
public:
    explicit CardLostPage(QWidget *parent = 0);
    void updateLanguage();
    void setComboBox();
public slots:
    void report();
private:
    QLabel *label1;
    QComboBox *edit1;
    QPushButton *reportBtn;
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
    void confirm();
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
    void setSysMsg();
public slots:
private:
    QLabel *bgLabel;
    QTableWidget *table;
};

class AboutPage : public WPage
{
    Q_OBJECT
public:
    explicit AboutPage(QWidget *parent = 0);
    void updateLanguage();
public slots:
private:
    QTextEdit *label1;
};

class WelcomePage : public WPage
{
    Q_OBJECT
public:
    explicit WelcomePage(QWidget *parent = 0);
    void updateLanguage();
public slots:
private:
    QTextEdit *label1;
    QTextEdit *label2;
};

class PlotPage : public WPage
{
    Q_OBJECT
public:
    explicit PlotPage(QWidget *parent = 0);
    void updateLanguage();
    void setPlot();
public slots:
private:
    QPushButton *returnBtn;
    bool isHistogram;
    QCustomPlot *histogramPlot;
    QCustomPlot *piePlot;
    QCPBars *bars;
    QVector<QCPBars *> piePlotBars;
    QList <QCustomPlot *> plots;
    QVector<double> coor;
    void initPlot();
};

class CurrencyPage : public WPage
{
    Q_OBJECT
public:
    explicit CurrencyPage(QWidget *parent = 0);
    void updateLanguage();
    void setCurrency();
private:
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    QLineEdit *edit1;
    QLineEdit *edit2;
    QLineEdit *edit3;
    QLineEdit *edit4;
};

#endif // PAGES_H
