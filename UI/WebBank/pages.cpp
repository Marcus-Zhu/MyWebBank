#include "nofocusdelegate.h"
#include "pages.h"
#include <QListWidget>

WPage::WPage(QWidget *parent):QWidget(parent){
    mainTitle = new QLabel(this);
}

MyAccountPage::MyAccountPage(QWidget *parent) : WPage(parent)
{
    mainTitle->setText(tr("My Account"));
    title2 = new QLabel(tr("Recent Transaction Records"), this);
    table1 = new QTableWidget(this);
    table2 = new QTableWidget(this);

    mainTitle->setObjectName("CMALabel1");
    title2->setObjectName("CMALabel2");
    table1->setObjectName("CMATable1");
    table2->setObjectName("CMATable2");

    mainTitle->setGeometry(QRect(24,12,400,48));
    title2->setGeometry(QRect(24,292,400,28));
    table1->setGeometry(QRect(24,72,708,192));
    table2->setGeometry(QRect(24,344,708,192));
}

void MyAccountPage::updateLanguage(){
    mainTitle->setText(tr("My Account"));
    title2->setText(tr("Recent Transaction Records"));
}

TransferPage::TransferPage(QWidget *parent) : WPage(parent)
{
    mainTitle->setText(tr("Current Deposit Transfer"));
    label1 = new QLabel(tr("paying account"), this);
    label2 = new QLabel(tr("receiver's name"), this);
    label3 = new QLabel(tr("receiver's account"), this);
    label4 = new QLabel(tr("transfer amount"), this);
    label5 = new QLabel(tr("comment"), this);
    edit1 = new QComboBox(this);
    edit2 = new QLineEdit(this);
    edit3 = new QLineEdit(this);
    edit4 = new QLineEdit(this);
    edit5 = new QLineEdit(this);
    confirmBtn = new QPushButton(tr("CONFIRM"), this);

    mainTitle->setObjectName("TTitle");
    label1->setObjectName("TLabel1");
    label2->setObjectName("TLabel2");
    label3->setObjectName("TLabel3");
    label4->setObjectName("TLabel4");
    label5->setObjectName("TLabel5");
    edit1->setObjectName("TEdit1");
    edit2->setObjectName("TEdit2");
    edit3->setObjectName("TEdit3");
    edit4->setObjectName("TEdit4");
    edit5->setObjectName("TEdit5");
    confirmBtn->setObjectName("TConfirmBtn");


    edit1->addItem("1231 2312 3123 1236");
    edit1->addItem("2175 7962 4595 4698");
    NoFocusDelegate* itemDelegate = new NoFocusDelegate();
    edit1->setItemDelegate(itemDelegate);

    mainTitle->setGeometry(QRect(24,12,400,48));
    label1->setGeometry(QRect(24,92,200,24));
    label2->setGeometry(QRect(24,140,200,24));
    label3->setGeometry(QRect(24,188,200,24));
    label4->setGeometry(QRect(24,236,200,24));
    label5->setGeometry(QRect(24,284,200,24));
    edit1->setGeometry(QRect(288,88,400,32));
    edit2->setGeometry(QRect(288,136,400,32));
    edit3->setGeometry(QRect(288,184,400,32));
    edit4->setGeometry(QRect(288,232,400,32));
    edit5->setGeometry(QRect(288,280,400,32));
    confirmBtn->setGeometry(QRect(584,336,108,36));


}

void TransferPage::updateLanguage(){
    mainTitle->setText(tr("Current Deposit Transfer"));
    label1->setText(tr("paying account"));
    label2->setText(tr("receiver's name"));
    label3->setText(tr("receiver's account"));
    label4->setText(tr("transfer amount"));
    label5->setText(tr("comment"));
    confirmBtn->setText(tr("CONFIRM"));
}
