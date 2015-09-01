#ifndef BANKUI_H
#define BANKUI_H

#include <QWidget>
#include <QLabel>
#include <QMenu>
#include <QPushButton>
#include <QMouseEvent>
#include <QTranslator>

#include "wstackedwidget.h"

class BankUI : public QWidget
{
    Q_OBJECT

public:
    BankUI(QWidget *parent = 0);
    ~BankUI();
    void openUX();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
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
    void changeLanguage();
    void popUserMenu();
    void popSettingMenu();
    void showMyAccountPage();
    void showAccountQueryPage();
    void showTransferPage();
    void shouCurrentFixPage();
    void showPaymentPage();
    void showAutoPayPage();
    void showCardApplyPage();
    void showCardActivatePage();
    void showCardRepayPage();
    void showCardLostPage();
    void showUserInfoPage();
    void showChangePwPage();
    void showSysMsgPage();
    void showAboutPage();
    bool closeWindow();
    void showWidgets();
    void openUX2();

private:
    QLabel *backgroundLabel;
    QLabel *topbarLabel;
    QLabel *menubarLabel;
    QLabel *navbarLabel;
    QPushButton *userBtn;
    QPushButton *settingBtn;
    QPushButton *minBtn;
    QPushButton *closeBtn;
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
    QLabel *logInfoLabel;
    QLabel *creditLabel;
    QMenu *userMenu;
    QMenu *settingMenu;
    QAction *personalInfoAction;
    QAction *changepwAction;
    QAction *sysmsgAction;
    QAction *logoutAction;
    QAction *languageAction;
    QAction *aboutAction;
    WStackedWidget *centerStack;
    bool isPressed;
    QPoint movePoint;
    void setTranslator();
    void setStyle();
    void initUI();
    void setConnections();
    void updateLanguage();
    void openWindow();

    QTranslator wTranslator;
    bool isChinese;
};

#endif // BANKUI_H
