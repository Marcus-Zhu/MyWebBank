#ifndef BARS_H
#define BARS_H

#include <QWidget>
#include <QLabel>
#include <QAction>
#include <QMenu>
#include <QPushButton>

class WTopbar : public QWidget
{
    Q_OBJECT
public:
    explicit WTopbar(QWidget *parent = 0);

signals:

public slots:
    void popUserMenu();
    void popSettingMenu();
    void updateLanguage();

private:
    QLabel *topbarLabel;
    QPushButton *minBtn;
    QPushButton *closeBtn;	
    QPushButton *userBtn;
    QPushButton *settingBtn;
    QMenu *userMenu;
    QMenu *settingMenu;
    QAction *personalInfoAction;
    QAction *changepwAction;
    QAction *sysmsgAction;
    QAction *logoutAction;
    QAction *languageAction;
    QAction *aboutAction;
};

class WNavbar : public QWidget
{
    Q_OBJECT
public:
    explicit WNavbar(QWidget *parent = 0);

signals:

public slots:
    void checkQuery();
    void checkMyAccount();
    void checkAccountQuery();
    void checkTransfer();
    void checkCurrentTransfer();
    void checkCurrentFix();
    void checkPayment();
    void checkCCard();
    void checkCCApply();
    void checkCCActivate();
    void checkCCRepay();
    void checkCCLost();
    void updateLanguage();

private:
    QLabel *navbarLabel;
    QPushButton *queryBtn;
    QPushButton *myAccountBtn;
    QPushButton *accountQueryBtn;
    QPushButton *transferBtn;
    QPushButton *currTransferBtn;
    QPushButton *currentFixBtn;
    QPushButton *paymentBtn;
    QPushButton *ccardBtn;
    QPushButton *ccApplyBtn;
    QPushButton *ccActivateBtn;
    QPushButton *ccRepayBtn;
    QPushButton *ccLostBtn;
    QLabel *queryLabel;
    QLabel *myAccountLabel;
    QLabel *accountQueryLabel;
    QLabel *transferLabel;
    QLabel *currTransferLabel;
    QLabel *currentFixLabel;
    QLabel *paymentLabel;
    QLabel *ccardLabel;
    QLabel *ccApplyLabel;
    QLabel *ccActivateLabel;
    QLabel *ccRepayLabel;
    QLabel *ccLostLabel;
};

#endif // BARS_H
